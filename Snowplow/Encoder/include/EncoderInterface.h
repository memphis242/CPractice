//hey soul sister
#ifndef __ENCODER_ARDUINO__H__
#define __ENCODER_ARDUINO__H__

#include <iostream>
#include <RS232_GenericController.h>

struct ENCODERS{
  int leftSpeed_Raw;   //left wheel speed in raw ticks form
  int rightSpeed_Raw;  //right wheel speed in raw ticks form
  double leftSpeed_MpS;     //Left wheel speed in Meters per second
  double rightSpeed_MpS;   //Right wheel speed in Meters per second
};
enum SIDE{
    ENC_LEFT, ENC_RIGHT
};
class ArduinoEncoder{
private:
    char* port;
    char sendByte;
    SerialController arduino;
    char buf[8];

    bool checkDatSum(char* buf);
public:

    int Lspeed;
    int Rspeed; 
    ENCODERS encoders;

    // constructor with explict port that the arduino is plug in to
    ArduinoEncoder();

    ArduinoEncoder(char* usbPort);

    // set the port that the arduino is connected to on the computer.
    void setPort(char* usbPort);

    // gets the data from ENCODERS retunrs the first byte of the string
    char readEncoders(void);

    char requestData(void);
};
#endif
