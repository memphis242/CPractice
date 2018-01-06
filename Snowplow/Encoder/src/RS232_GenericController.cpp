#include <RS232_GenericController.h>

#include <string>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

//#define SC SerialController

SC::SerialController(void) {
    ;
}

SC::SerialController(const std::string& serialPort) {
    SerialController::set_SerialPort(serialPort);
}

void SC::set_SerialPort(const std::string& serialPort) {
    memset(&tty, 0, sizeof tty);
    fd = open(serialPort.c_str(), O_RDWR | O_NOCTTY | O_NDELAY); // pretty standard flags
    if(fd < 0) {
        int e = errno;
        std::cerr << "Error opening file" << std::endl;
        std::cerr << "    Error code: " << e << std::endl;
        exit(-1);
    }

    if(tcgetattr(fd, &tty) < 0) {
        int e = errno;
        std::cerr << "Error retrieving attributes" << std::endl;
        std::cerr << "    Error code: " << e << std::endl;
        exit(-1);
    }
    serialPortSet = true;
}

void SC::parityEnable(void) {
    tty.c_cflag |= PARENB;
}

int SC::writeBuffer(char* buffer, int bufSize) {
    return write(fd, buffer, bufSize);
}

int SC::readBuffer(char* buffer, int bufSize) {
//    std::cout << "buff size lowlevel read: " << bufSize << std::endl;
    return read(fd, buffer, bufSize);
}

void SC::set_BaudRate(int baudrate) {
    cfsetispeed(&tty, baudrate);
    cfsetospeed(&tty, baudrate);
}

void SC::set_Parity(Parity parity) {
    switch(parity) {
        case Parity_Even:
            tty.c_cflag |= PARENB;
            tty.c_cflag &= ~PARODD;
            break;
        case Parity_Odd:
            tty.c_cflag |= PARENB;
            tty.c_cflag |= PARODD;
            break;
        case Parity_Off: // disable the parity bit
            tty.c_cflag &= ~PARENB;
            break;
        default:
            std::cerr << "Invalid parity argument" << std::endl;
            exit(-1); // all error comditions return -1
    }
}

void SC::set_StopBits(StopBits stopbits) {
    switch(stopbits) {
        case StopBits_1:
            tty.c_cflag &= ~CSTOPB;
            break;
        case StopBits_2:
            tty.c_cflag |= CSTOPB;
            break;
        default:
            std::cerr << "Invalid stop bit argument" << std::endl;
            exit(-1);
    }
}

void SC::set_WordSize(WordSize wordsize) {
    switch(wordsize) {
        case WordSize_7:
            tty.c_cflag &= ~CSIZE;
            tty.c_cflag |= CS7;
            break;
        case WordSize_8:
            tty.c_cflag &= ~CSIZE;
            tty.c_cflag |= CS8;
            break;
        default:
            std::cerr << "Invalid word size argument" << std::endl;
            exit(-1);
    }
}

void SerialController::start(void) {
    if(serialPortSet == false) {
        std::cerr << "Serial port has not been opened" << std::endl;
        exit(-1);
    }

    if(tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error starting serial communications" << std::endl;
        std::cerr << "    Error code: " << errno << std::endl;
        exit(-1);
    }
}

int SerialController::get_FileDescriptor(void) {
    return fd;
}

void SerialController::readChunk(SerialController& sc, char* buf, int n) {
    int bytes_read = 0;
    int read_byte;
    while(bytes_read < n) {
        read_byte = sc.readBuffer(buf+bytes_read, n-bytes_read);
        if(read_byte == -1){
            break;
        }else{
        bytes_read ++;
        }

        usleep(5000);
    }
}
