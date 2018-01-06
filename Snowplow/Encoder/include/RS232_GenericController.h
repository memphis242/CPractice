#ifndef __JJC__RS232GENERIC__H__
#define __JJC__RS232GENERIC__H__

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

#define SC SerialController

enum Parity {
    Parity_Odd, Parity_Even, Parity_Off
};

enum WordSize {
    WordSize_7, WordSize_8
};

enum StopBits {
    StopBits_1, StopBits_2
};

class SerialController {
private:
    termios tty;
    int fd = -1;
    bool serialPortSet = false;
    void parityEnable(void);

public:
    // constructor that does nothing
    SerialController(void);

    // constructor with serial port as argument
    SerialController(const std::string& serialPort);

    // specify a serial device to use
    void set_SerialPort(const std::string& serialPort);

    // read a certain number of bytes from the serial port
    int readBuffer(char* buffer, int bufSize);

    // write a certain number of bytes from the serial port
    int writeBuffer(char* buffer, int bufSize);

    // set the read/write speeds for the serial port
    void set_BaudRate(int baudrate);

    // set odd/even/no parity for this serial port
    void set_Parity(Parity parity);

    // set either 7 or 8 bit word for this serial port
    void set_WordSize(WordSize wordsize);

    // set either 1 or 2 stop bits for this port
    void set_StopBits(StopBits stopbits);

    // start serial communications
    void start(void);

    int get_FileDescriptor(void);

    void readChunk(SerialController& sc, char* buf, int n);
};

#endif // __JJC__RS232GENERIC__H__
