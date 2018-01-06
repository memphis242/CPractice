// test file for rs232 library
// used with Arduino serial device

#include <RS232_GenericController.h>
#include <sys/ioctl.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

struct DataStruct {
    float   numF;
    int32_t numI;
};

int main(int argc, char* argv[]) {
    SerialController sc;

    sc.set_SerialPort("/dev/ttyUSB0");
    sc.set_BaudRate(B115200);
    sc.set_Parity  (SerialController::PARITY::OFF);
    sc.set_StopBits(SerialController::STOPBITS::_1);
    sc.set_WordSize(SerialController::WORDSIZE::_8);
    sc.start();

    cout << "Serial port opening successful" << endl;

    int iters = 0;

    while(1) {
        if(sc.hasData() >= 8) {
            DataStruct data;
            sc.readBuffer((char*)&data, 8);
            cout << "Iters: " << ++iters << endl;
            cout << "    Float: " << data.numF << endl;
            cout << "    Int:   " << data.numI << endl;

            // constant defined in math.h
            if(data.numF == INFINITY)
                return 1;
        }
    }

    return 0;
}
