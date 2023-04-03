#include <stdio.h>
#include <stdint.h>

/************* USEFUL MACROS *************/
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define TWO_BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN
#define TWENTY_BITS_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"

#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#define TWO_BYTE_TO_BINARY(word)  \
  (word & 0x8000 ? '1' : '0'), \
  (word & 0x4000 ? '1' : '0'), \
  (word & 0x2000 ? '1' : '0'), \
  (word & 0x1000 ? '1' : '0'), \
  (word & 0x0800 ? '1' : '0'), \
  (word & 0x0400 ? '1' : '0'), \
  (word & 0x0200 ? '1' : '0'), \
  (word & 0x0100 ? '1' : '0'), \
  (word & 0x0080 ? '1' : '0'), \
  (word & 0x0040 ? '1' : '0'), \
  (word & 0x0020 ? '1' : '0'), \
  (word & 0x0010 ? '1' : '0'), \
  (word & 0x0008 ? '1' : '0'), \
  (word & 0x0004 ? '1' : '0'), \
  (word & 0x0002 ? '1' : '0'), \
  (word & 0x0001 ? '1' : '0')

  #define TWENTY_BITS_TO_BINARY(word1, word2)  \
  (word1 & 0x0008 ? '1' : '0'), \
  (word1 & 0x0004 ? '1' : '0'), \
  (word1 & 0x0002 ? '1' : '0'), \
  (word1 & 0x0001 ? '1' : '0'), \
  (word2 & 0x8000 ? '1' : '0'), \
  (word2 & 0x4000 ? '1' : '0'), \
  (word2 & 0x2000 ? '1' : '0'), \
  (word2 & 0x1000 ? '1' : '0'), \
  (word2 & 0x0800 ? '1' : '0'), \
  (word2 & 0x0400 ? '1' : '0'), \
  (word2 & 0x0200 ? '1' : '0'), \
  (word2 & 0x0100 ? '1' : '0'), \
  (word2 & 0x0080 ? '1' : '0'), \
  (word2 & 0x0040 ? '1' : '0'), \
  (word2 & 0x0020 ? '1' : '0'), \
  (word2 & 0x0010 ? '1' : '0'), \
  (word2 & 0x0008 ? '1' : '0'), \
  (word2 & 0x0004 ? '1' : '0'), \
  (word2 & 0x0002 ? '1' : '0'), \
  (word2 & 0x0001 ? '1' : '0')

#define LOG_SIZE	20u

/**************** GLOBAL VARIABLES ***************/
uint16_t log_arr[2];
uint8_t newest_bit;
uint8_t newest_idx;
uint8_t oldest_bit;
uint8_t oldest_idx;
uint8_t log_counter;
uint8_t active_counter, inactive_counter;

/********* LOCAL FUNCTION DECLARATIONS ************/
static void print_log( void );
static void add_measurement_to_log( uint8_t measurement );
static void wrap_queue_trackers( uint8_t * tracker_bit, uint8_t * tracker_idx );
static uint8_t peak_oldest_measurement( void );

/***************** MAIN FUNCTION ******************/
int main( int argc, char * argv[] )
{
	printf("\nWe will start off with a full queue of 20 bits.\n\n");
	
//	printf("argv[0]: %s\targv[1]: %s\n", argv[0], argv[1]);

	// Verify that user has put in at least 20 values to start off with.
	if ( argc < 21 )
	{
		printf("Please enter at least 20 \"1\"s or \"0\"s.");

		return 1; // indicate error occured
	}


	// Now fill in the log array and print contents in hex and binary form
	// Start off with filling log array...	
	for ( uint8_t i=0u; i< 20u; i++ )
	{
		if ( *argv[i + 1] == '1' )
		{
			add_measurement_to_log(1u);
		}
		else if ( *argv[i+1] == '0' )
		{
			add_measurement_to_log(0u);
		}
	}
	// Now print out log array in binary and hex
	print_log();
	
	// Now ask user to start feeding in data one at a time, and print out the log at each step, again in hex and binary
	printf("\nNow, enter in measurements, one at a time, and the log will be printed at each step. At any point, enter q to stop.\n\n");
	unsigned char measurement = 0u;
	while ( ( measurement = getchar() ) != 'q' )
	{

		if ( measurement == '1' )
		{
			add_measurement_to_log(1u);
			print_log();
		}
		else if ( measurement == '0' )
		{
			add_measurement_to_log(0u);
			print_log();
		}

		// get rid of any newline characters from previous input...
		while ( getchar() != '\n' )
		{
			continue;
		}

	}



	return 0;	// No error occured
}



static void print_log( void )
{
	// printf("\npeak_oldest_measurement(): %d", peak_oldest_measurement());
	printf("\nLog in Hex:\t%0.4x %0.4x", log_arr[1], log_arr[0]);
	printf( "\nLog in Binary:\t" TWENTY_BITS_PATTERN, 
		TWENTY_BITS_TO_BINARY(log_arr[1], log_arr[0]) );
	printf("\nNewest Idx: %d\tNewest Bit: %d", newest_idx, newest_bit);
	printf("\nOldest Idx: %d\tOldest Bit: %d", oldest_idx, oldest_bit);
	printf("\nActive Counter: %d\nInactive Counter: %d\nLog Counter: %d\n\n", active_counter, inactive_counter, log_counter);
}
	

static void add_measurement_to_log( uint8_t measurement )
{
	if ( measurement == 1u )
	{
		// if the oldest measurement was different than this newest measurement,
		// and we are at full-size, then increment and decrement the corresponding counters
		if ( peak_oldest_measurement() == 0u && log_counter >= LOG_SIZE )
		{
			active_counter++;
			inactive_counter--;
		}

		log_arr[newest_idx] |= ( 0x0001u << newest_bit );
		
		// Now increment newest and oldest variables in such a way that newest tracks the next position to be filled
			// and oldest tracks the measurement that was 19 measurements ago (i.e., the oldest measurement)
			// if we are at full size, then increment both newest and oldest bits
		if ( log_counter >= LOG_SIZE )
		{
			newest_bit++;
			oldest_bit++;
		}
		// otherwise, just increment the corresponding counter
		else
		{
			log_counter++;
			active_counter++;

			newest_bit++;
		}

	}

	else if ( measurement == 0u )
	{
		if ( peak_oldest_measurement() == 1u && log_counter >= LOG_SIZE )
		{
			inactive_counter++;
			active_counter--;
		}

		log_arr[newest_idx] &= ~( 0x0001u << newest_bit );
	
		// if the oldest measurement was different than this newest measurement,
		// and we are at full-size, then increment and decrement the corresponding counters
		if ( log_counter >= LOG_SIZE )
		{
			newest_bit++;
			oldest_bit++;
		}
		// otherwise, just increment the corresponding counter
		else
		{
			log_counter++;
			inactive_counter++;

			newest_bit++;
		}
	}

	wrap_queue_trackers(&newest_bit, &newest_idx);
	wrap_queue_trackers(&oldest_bit, &oldest_idx);
}

static void wrap_queue_trackers( uint8_t * tracker_bit, uint8_t * tracker_idx )
{
	if ( *tracker_bit > 15u )
	{
		*tracker_bit = 0u;	// newest_bit will be the next idx's LSb
		*tracker_idx = *tracker_idx + 1;		// increment to the next idx

		if ( *tracker_idx > 1u )
		{
			*tracker_idx = 0u;	// wrap idx around
		}
	}
	else if ( *tracker_bit > 3u && *tracker_idx == 1u )
	{
		*tracker_bit = 0u;
		*tracker_idx = 0u;
	}
	
}

static uint8_t peak_oldest_measurement( void )
{
	return ( log_arr[oldest_idx] & ( 0x0001u << oldest_bit ) ) >> oldest_bit;
}
