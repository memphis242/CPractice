/************ INCLUDE HEADERS *****************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


/************* STRUCTURE DEFINITIONS *********************/
typedef struct
{
	unsigned char state_req : 4; 		// 0
	unsigned char isolation_req : 4; 	// 4
	unsigned char sleep_req : 4; 		// 8
	unsigned char range_req : 4; 		// 12
} KREISEL_PTREQUEST_REQUEST_TYPE;

typedef struct
{
	unsigned char ctrl_aux1 : 1;
	unsigned char ctrl_aux2 : 1;
	unsigned char ctrl_aux3 : 1;
	unsigned char ctrl_aux4 : 1;
	unsigned char alivecounter : 4;
} KREISEL_PTREQUEST_COMM_TYPE;

// CAN Msg 0x11B => PT Request
typedef struct
{
	KREISEL_PTREQUEST_REQUEST_TYPE request; // 0
	unsigned char chargepoweravail[2]; 	// 16
	unsigned char rsvd; 			// 32 => set to 0
	KREISEL_PTREQUEST_COMM_TYPE comm; 	// 40
	unsigned char crc; 			// 48
} KREISEL_PTREQUEST_TYPE; 			// 7 Bytes Total



/****************** GLOBAL VARIABLE/DATA DECLARATIONS *******************/
// Main PTRequest struct
static KREISEL_PTREQUEST_TYPE Kreisel_PTRequest;

// Declaring the buffer that will be used to read in user input
static char data_bytes_as_ascii[13];	// XX XX XX XX XX XX (ignoring the spaces)
// Declaring the actual data bytes array that the CRC will be assigned to Kreisel_PTRequest
static unsigned char data_bytes[7];
static unsigned char alive_counter;
static unsigned char num_of_bytes;


// CRC Lookup-Table /w from Polynomial: 0x2F
static const unsigned char KREISELCRCTABLEDEF[] = {
0x00, 0x2F, 0x5E, 0x71, 0xBC, 0x93, 0xE2, 0xCD, 0x57, 0x78, 0x09, 0x26, 0xEB, 0xC4, 0xB5, 0x9A,
0xAE, 0x81, 0xF0, 0xDF, 0x12, 0x3D, 0x4C, 0x63, 0xF9, 0xD6, 0xA7, 0x88, 0x45, 0x6A, 0x1B, 0x34,
0x73, 0x5C, 0x2D, 0x02, 0xCF, 0xE0, 0x91, 0xBE, 0x24, 0x0B, 0x7A, 0x55, 0x98, 0xB7, 0xC6, 0xE9,
0xDD, 0xF2, 0x83, 0xAC, 0x61, 0x4E, 0x3F, 0x10, 0x8A, 0xA5, 0xD4, 0xFB, 0x36, 0x19, 0x68, 0x47,
0xE6, 0xC9, 0xB8, 0x97, 0x5A, 0x75, 0x04, 0x2B, 0xB1, 0x9E, 0xEF, 0xC0, 0x0D, 0x22, 0x53, 0x7C,
0x48, 0x67, 0x16, 0x39, 0xF4, 0xDB, 0xAA, 0x85, 0x1F, 0x30, 0x41, 0x6E, 0xA3, 0x8C, 0xFD, 0xD2,
0x95, 0xBA, 0xCB, 0xE4, 0x29, 0x06, 0x77, 0x58, 0xC2, 0xED, 0x9C, 0xB3, 0x7E, 0x51, 0x20, 0x0F,
0x3B, 0x14, 0x65, 0x4A, 0x87, 0xA8, 0xD9, 0xF6, 0x6C, 0x43, 0x32, 0x1D, 0xD0, 0xFF, 0x8E, 0xA1,
0xE3, 0xCC, 0xBD, 0x92, 0x5F, 0x70, 0x01, 0x2E, 0xB4, 0x9B, 0xEA, 0xC5, 0x08, 0x27, 0x56, 0x79,
0x4D, 0x62, 0x13, 0x3C, 0xF1, 0xDE, 0xAF, 0x80, 0x1A, 0x35, 0x44, 0x6B, 0xA6, 0x89, 0xF8, 0xD7,
0x90, 0xBF, 0xCE, 0xE1, 0x2C, 0x03, 0x72, 0x5D, 0xC7, 0xE8, 0x99, 0xB6, 0x7B, 0x54, 0x25, 0x0A,
0x3E, 0x11, 0x60, 0x4F, 0x82, 0xAD, 0xDC, 0xF3, 0x69, 0x46, 0x37, 0x18, 0xD5, 0xFA, 0x8B, 0xA4,
0x05, 0x2A, 0x5B, 0x74, 0xB9, 0x96, 0xE7, 0xC8, 0x52, 0x7D, 0x0C, 0x23, 0xEE, 0xC1, 0xB0, 0x9F,
0xAB, 0x84, 0xF5, 0xDA, 0x17, 0x38, 0x49, 0x66, 0xFC, 0xD3, 0xA2, 0x8D, 0x40, 0x6F, 0x1E, 0x31,
0x76, 0x59, 0x28, 0x07, 0xCA, 0xE5, 0x94, 0xBB, 0x21, 0x0E, 0x7F, 0x50, 0x9D, 0xB2, 0xC3, 0xEC,
0xD8, 0xF7, 0x86, 0xA9, 0x64, 0x4B, 0x3A, 0x15, 0x8F, 0xA0, 0xD1, 0xFE, 0x33, 0x1C, 0x6D, 0x42,
};

// Additional step that Kreisel takes that involves the alive counter member of the PTRequest message
static const unsigned char KREISELCTCTABLEMSG[] = {
0x3D, 0xBE, 0x44, 0xC5, 0x4B, 0xCC, 0x52, 0xD3, 0x59, 0xDA, 0x60, 0xE1, 0x67, 0xE8, 0x6E, 0xEF,
};



/************************** LOCAL FUNCTION DECLARATIONS *******************************/
static void KREISEL_CRC(void);
static void KREISEL_CRC_4BYTES(void);



/*************************** MAIN FUNCTION *******************************************/

int main( int argc, char *argv[] )
{
	/****** GET DATA BYTES FROM USER ********/
	// Verify that user has entered at least six bytes...
	if ( argc < 7 )
	{
		printf("\nError: You need to enter at least six bytes.\n");
		return 1;
	}
	// If user has entered more than seven bytes, give a warning but still proceed...
	if ( argc > 8 )
	{
		printf("\nWarning: You entered more than six bytes. Only the first six bytes will be considered and the rest will be ignored.\n");
	}
	
	// Obtain data bytes + alive counter from command-line input; for now, I'm going to expect bytes to be written in hex without the "0x" prefix and to be space separated...
	if ( argc >= 2 )	memcpy(&data_bytes_as_ascii[0], argv[1], 2);
	if ( argc >= 3 )	memcpy(&data_bytes_as_ascii[2], argv[2], 2);
	if ( argc >= 4 )	memcpy(&data_bytes_as_ascii[4], argv[3], 2);
	if ( argc >= 5 )	memcpy(&data_bytes_as_ascii[6], argv[4], 2);
	if ( argc >= 6 )	memcpy(&data_bytes_as_ascii[8], argv[5], 2);
	if ( argc >= 7 )	memcpy(&data_bytes_as_ascii[10], argv[6], 2);
	if ( argc >= 8 )	num_of_bytes = (unsigned char) strtol(argv[7], NULL, 10);	// The user may pass this number of bytes through as one of the arguments in the command line invocation of the program

	// Confirm by printing out what was obtained...
	// printf("Read input was: %s\n", data_bytes_as_ascii);
	
	/****** CONVERT ASCII VALUES INTO HEXADECIMAL INTEGERS ********/
	// For PT_Request, there are six bytes to compute the CRC over; for SC01_State, there are four. Hence the two control branches below...
	if ( num_of_bytes != 4u )	// Message 11B --> PT_Request
	{
		// Need to use a char array per hexadecimal entry in order to use strtol; hence the array of char arrays...
		char bytes[6][3];
		for ( uint8_t i=0; i<6; i++ )	bytes[i][3] = '\0';		// Terminate with null character to indicate this is a string...
		// Copy bytes over from data_bytes_as_ascii into data_bytes
		for ( uint8_t i=0; i<6; i++ )
		{
			memcpy(&bytes[0][i], &data_bytes_as_ascii[2*i], 2);
			data_bytes[i] = (unsigned char) ( strtol(&bytes[0][i], NULL, 16) & 0xFFu );
		}

		// Print converted values...
		printf("\nRead input converted into hexadecimal integer: %02X %02X %02X %02X %02X %02X\n", data_bytes[0], data_bytes[1], data_bytes[2], data_bytes[3], data_bytes[4], data_bytes[5]); 

		// Now fill up the Kreisel_PTRequest struct...
		// request part...
		Kreisel_PTRequest.request.state_req = data_bytes[0] & 0x0Fu;
		Kreisel_PTRequest.request.isolation_req = ( data_bytes[0] & 0xF0u ) >> 4;
		Kreisel_PTRequest.request.sleep_req = data_bytes[1] & 0x0Fu;
		Kreisel_PTRequest.request.range_req = ( data_bytes[1] & 0xF0u ) >> 4;
		// Charge Power Available
		Kreisel_PTRequest.chargepoweravail[0] = data_bytes[2];
		Kreisel_PTRequest.chargepoweravail[1] = data_bytes[3];
		// reserved byte (byte 5)...
		Kreisel_PTRequest.rsvd = data_bytes[4];
		// comm part
		Kreisel_PTRequest.comm.ctrl_aux1 = data_bytes[5] & 0x01u;
		Kreisel_PTRequest.comm.ctrl_aux2 = data_bytes[5] & 0x02u;
		Kreisel_PTRequest.comm.ctrl_aux3 = data_bytes[5] & 0x04u;
		Kreisel_PTRequest.comm.ctrl_aux4 = data_bytes[5] & 0x08u;
		Kreisel_PTRequest.comm.alivecounter = ( data_bytes[5] & 0xF0u ) >> 4;
		
		// Print out to confirm correct assignment...
		uint16_t charge_power = ( (uint16_t) Kreisel_PTRequest.chargepoweravail[0] << 8 ) | ( (uint16_t) Kreisel_PTRequest.chargepoweravail[1] );
		printf("\nState Request:\t\t%d\nIsolation Request:\t%d\nSleep Request:\t\t%d\nRange Request:\t\t%d\nCharge Power Available:\t%d\nReserved:\t\t%d\n",
			Kreisel_PTRequest.request.state_req, Kreisel_PTRequest.request.isolation_req, Kreisel_PTRequest.request.sleep_req, Kreisel_PTRequest.request.range_req, charge_power,
			Kreisel_PTRequest.rsvd);
		printf("Ctrl Aux1:\t\t%d\nCtrl Aux2:\t\t%d\nCtrl Aux3:\t\t%d\nCtrl Aux4:\t\t%d\nAlive Counter:\t\t%d\n",
			Kreisel_PTRequest.comm.ctrl_aux1, Kreisel_PTRequest.comm.ctrl_aux2, Kreisel_PTRequest.comm.ctrl_aux3, Kreisel_PTRequest.comm.ctrl_aux4, Kreisel_PTRequest.comm.alivecounter);
		
		
		/****** CALL CRC FUNCTION AND PRINT RESULT ********/
		// Now compute the CRC!
		KREISEL_CRC();
	}
	else		// TODO: Message 1F --> SC01_State	-->		STILL WORK IN PROGRESS!
	{
		// Need to use a char array per hexadecimal entry in order to use strtol; hence the array of char arrays...
		char bytes[4][3];
		for ( uint8_t i=0; i<4; i++ )	bytes[i][3] = '\0';			// Terminate with null character to indicate this is a string...
		// Copy bytes over from data_bytes_as_ascii into data_bytes
		for ( uint8_t i=0; i<4; i++ )
		{
			memcpy(&bytes[0][i], &data_bytes_as_ascii[2*i], 2);
			data_bytes[i] = (unsigned char) ( strtol(&bytes[0][i], NULL, 16) & 0xFFu );
		}
		alive_counter = data_bytes[3] & 0x0Fu;	// Alive counter in this message is the lower 4 bits of byte 4
		
		KREISEL_CRC_4BYTES();
	}

	// Print out CRC result... 
	printf("\nCRC Result:\t\t%02X\n", Kreisel_PTRequest.crc);


	return 0;
}




/*************************** LOCAL FUNCTION DEFINITIONS *******************************/
static void KREISEL_CRC(void)
{
	// Auto local variables...
	unsigned char *s, crc, datalen;

	// s will be used to point to the members of the Kreisel_PTRequest struct, which hopefully is laid out the same
	// way that the PTRequest message is laid out...
	s = (unsigned char*) &Kreisel_PTRequest;
	// Six data bytes are used to compute the CRC first, prior to accounting for alive counter...
	datalen = 6;
	crc = 0xFF; // CRC = 255 Startvalue
	// Incrememt alivecounter...	-->		Not doing that because I'll assume we are passing in the alive counter as it should appear in the message!
	// Kreisel_PTRequest.comm.alivecounter = (Kreisel_PTRequest.comm.alivecounter + 1) & 0x0F; // 4-Bit Counter

	// Compute CRC over data bytes and alive counter ...
	while (datalen--) crc = KREISELCRCTABLEDEF[*s++ ^ crc];
	// Now do additional step /w alivecounter...
	crc = KREISELCTCTABLEMSG[Kreisel_PTRequest.comm.alivecounter] ^ crc;
	// Finalze CRC
	crc = KREISELCRCTABLEDEF[crc];
	Kreisel_PTRequest.crc = crc ^ 0xFF;
}

static void KREISEL_CRC_4BYTES(void)
{
	// Auto local variables...
	unsigned char *s, crc, datalen;

	// s will be used to point to the data_bytes buffer that was updated /w user input bytes
	s = (unsigned char*) data_bytes;
	// Four data bytes are used to compute the CRC first
	datalen = 4;
	crc = 0xFF; // CRC = 255 Startvalue
	// Incrememt alivecounter...	-->		Not doing that because I'll assume we are passing in the alive counter as it should appear in the message!
	// Kreisel_PTRequest.comm.alivecounter = (Kreisel_PTRequest.comm.alivecounter + 1) & 0x0F; // 4-Bit Counter

	// Compute CRC over data bytes and alive counter ...
	while (datalen--) crc = KREISELCRCTABLEDEF[*s++ ^ crc];
	// Now do additional step /w alivecounter...
	crc = KREISELCTCTABLEMSG[alive_counter] ^ crc;
	// Finalze CRC
	crc = KREISELCRCTABLEDEF[crc];
	Kreisel_PTRequest.crc = crc ^ 0xFF;
}








