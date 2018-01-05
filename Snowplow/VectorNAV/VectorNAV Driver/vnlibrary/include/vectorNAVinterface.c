/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "../include/vectorNAVinterface.h"

SERIALPORT oldconfig;



/*STUFF RELATED TO SETTING UP A NEW COMPORT*/
int openport(void) {
    int comport;
    
    //Open file.
    if( (comport = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY) ) == -1 ) {   //opening port as read/write, not controlling terminal, and ignoring DCD signal
        perror("Error opening port.");
        exit(EXIT_FAILURE);
    }
    
    fcntl(comport, F_SETFL, 0); //--> Set flags to 0?
    
    //Lock file so no other process can use it.
    if( flock(comport, LOCK_EX | LOCK_NB) != 0 ) {
        close(comport);
        perror("Another process has locked the comport.");
        exit(EXIT_FAILURE);
    }
    
    return(comport);
}

//Will set up 115200 8N1
//Returns what the termios structure that the file was configured to
SERIALPORT * setup_comport(int comport) {
    SERIALPORT newconfig;
    memset(&newconfig, 0, sizeof(newconfig));  /* clear the new struct */
    tcgetattr(comport, &oldconfig); //Save old attributes in case this fails.
    
    //Set baud rate
    cfsetispeed(&newconfig, B115200);
    cfsetospeed(&newconfig, B115200);
    
    //Enable readings and set local mode
    newconfig.c_cflag |= ( CLOCAL | CREAD );
    
    //8 data bits
//    newconfig.c_cflag &= ~CSIZE; --> Don't need cuz memset() has set all bytes to 0.
    newconfig.c_cflag |= CS8;
    
    //Set no parity.
    newconfig.c_cflag &= ~PARENB;
    
    //Set 1 stop bit
    newconfig.c_cflag &= ~CSTOPB; 
    
    //Set to raw input
    //Can also just newconfig.c_lflag = 0;
    newconfig.c_lflag &= ~( ICANON | ECHO | ECHOE | ISIG );
    
    //Make sure raw output
    //Can also just newconfig.c_oflag = 0;
    newconfig.c_oflag &= ~OPOST;
    
    //Set VMIN and VTIME to 0 cuz we don't need a minimum number of bytes read and setting VTIME to 0 keeps the read line open.
    newconfig.c_cc[VMIN] = 0;
    newconfig.c_cc[VTIME] = 0;
    
    //Set up serial device to be a serial port
    if( tcsetattr(comport, TCSANOW, &newconfig) == -1 ) {
        tcsetattr(comport, TCSANOW, &oldconfig);
        close(comport);
        perror("Unable to set attributes to file.");
        exit(EXIT_FAILURE);
    }
    
    return newconfig;
}

//This allows you to send a particular configuration through the SERIALPORT structure
void setup_comport_config(int file_descriptor, SERIALPORT *config) {
    tcsetattr(file_descriptor, TCSANOW, config);
}



/*FUNCTIONS RELATED TO USUAL ACTIONS ONCE A COMPORT IS OPEN*/
//Returns number of bytes read
int pollcomport(int comport, unsigned char *buf, int size) {
    
    int num_of_bytes_read;
    if( (num_of_bytes_read = read(comport, buf, size)) != size ) {
        perror("Unable to read all bytes.");
    }

    return(num_of_bytes_read);
}

//Returns 1 if successful and 0 otherwise
int sendbyte(int comport_number, unsigned char byte) {
    
    if( write(Cport[comport_number], &byte, 1) != 1 ) {
        perror("Unable to send all bytes.");
        return(0);
    }

    return(1);
}

//Returns number of bytes sent
int sendbuf(int comport, unsigned char *buf, int size) {
    
    int num_of_bytes_sent;
    if( (num_of_bytes_sent = write(comport, buf, size)) != size ) {
        perror("Unable to send all bytes.");
        return(0);
    }

    return(num_of_bytes_sent);
}

void flushRX(int comport_number) {
    tcflush(Cport[comport_number], TCIFLUSH);
}

void flushTX(int comport_number) {
    tcflush(Cport[comport_number], TCOFLUSH);
}

void flushRXTX(int comport_number) {
    tcflush(Cport[comport_number], TCIOFLUSH);
}



/*CLOSING A COMPORT*/
void closeport(int file_descriptor) {
    tcsetattr(file_descriptor, TCSANOW, &oldconfig);
    close(file_descriptor);
}
