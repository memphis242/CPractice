
#include <unistd.h>
#include <stdlib.h>
#include "../include/EncoderInterface.h"
// #include "../include/RS232_GenericController.h"


ArduinoEncoder::ArduinoEncoder(void){
    arduino.set_SerialPort(port);
    arduino.set_BaudRate(B57600);
    arduino.set_Parity(Parity_Off);
    arduino.set_WordSize(WordSize_8);
    arduino.set_StopBits(StopBits_1);
    arduino.start();
}

ArduinoEncoder::ArduinoEncoder(char* usbPort){
    this->port = usbPort;
    arduino.set_SerialPort(port);
    arduino.set_BaudRate(B57600);
    arduino.set_Parity(Parity_Off);
    arduino.set_WordSize(WordSize_8);
    arduino.set_StopBits(StopBits_1);
    arduino.start();
}

void ArduinoEncoder::setPort(char* usbPort){
    this->port = usbPort;
    arduino.set_SerialPort(usbPort);
}

//compares checksum from arduino with CPU
bool ArduinoEncoder::checkDatSum(char* buf){

    //test if the char we sent match the one returned
    if(sendByte != buf[0]){
        std::cout << "Error: char recieved: "<< (buf[0]) << "  char expect: " << sendByte << std::endl;
        return false;
    }
    // makes sure the 2nd byte is a capital L
    if('L' != (*(int16_t*)(buf+1))){
        // cout << "L not in right spot  L: "<< *(int16_t*)(buf+1) << endl;
        return false;
    }
    // makes sure the 4th byte is a capital R
    if('R' != buf[4]){
        std::cout << "R not in right spot" << std::endl;
        return false;
    }

    //build our checksum
    char cpuCheckSum =0;
    for(int i =0; i<7; i++){
        cpuCheckSum = cpuCheckSum ^ buf[i];
    }

    if(buf[7] == cpuCheckSum) {
        //update previous checksum
        return true;
    }else {
        // cout << "checksum does not match cpu: " << cpuCheckSum << " recieved:  " << *(int16_t*)(buf+7) << endl;
        return false;
    }

}
char ArduinoEncoder::requestData(void){
    this->sendByte = (char)(32 + (rand() % (95)));// generate a random byte. ie Space to ~ in ascii
    arduino.writeBuffer(&sendByte, 1);
    return sendByte;
}

char ArduinoEncoder::readEncoders(void){
    //set all values in the buf to 0
    for(int i = 0; i < 8; i++){
        this->buf[i] = 0x00;
    }

    // std::cout << "reading the  data" << std::endl;
    //read recieved data
    arduino.readChunk(arduino, buf, 8);

    for(int i=0; i<8; i++){
        std::cout << buf[i];
    }
    std::cout << std::endl;

    //if the schecksum is valid populate values in the struct
    if(checkDatSum(buf)){
        this->Lspeed = *((int16_t*)(buf+2));
        this->Rspeed = *(int16_t*)(buf+5);
        // ArduinoEncoder::encoders.rightSpeed_MpS = encoders.rightSpeed_Raw * some converstion factor.;
        // ArduinoEncoder::encoders.leftSpeed_MpS =(* encoders.rig)htSpeed_Raw * convervstion factor;
    }
    // usleep(10000);
    return buf[0];
}
