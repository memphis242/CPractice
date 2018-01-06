
#include <iostream>
#include <XboxControllerInterface.h>
#include <RoboteQ.h>
#include <EncoderInterface.h>

using namespace std;

float mapFloat(float in_min, float in_max, float x, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(int argc, char* argv[]) {

    ArduinoEncoder AEs = ArduinoEncoder("/dev/ttyUSB0");
/*
    SDL_Init(SDL_INIT_EVERYTHING); // initialize joysticks

   RoboteQInterface rqi("/dev/ttyUSB4"); // change this depending on where serial converter mounts to
    XboxController xc;
    // cout << "1 " << endl;
    SDL_Joystick* j = 0;

    if(SDL_NumJoysticks()) {
        j = SDL_JoystickOpen(0);
    } else {
        SDL_Quit();
        return -1;
    }
    // cout << "2 " << endl;
    int rightSpeed = 0;
    int leftSpeed  = 0;
    XboxController::STICK sRight = XboxController::STICK::RIGHT;
    XboxController::STICK sLeft  = XboxController::STICK::LEFT;

    WHEEL lMotor = WHEEL::LEFT;
    WHEEL rMotor = WHEEL::RIGHT;
    */

    char firstByte;
    char datbyte;// = AEs.requestData();

    while(1) {
        datbyte = AEs.requestData();
        usleep(5000);
        firstByte = AEs.readEncoders();

//        cout  << "Left xbox speed: " << leftSpeed << " Right xbox speed: " << rightSpeed << endl;
        if(datbyte == firstByte){
            cout  << "Left encoderSpeed: " << AEs.Lspeed << " Right encoderSpeed " << AEs.Rspeed << endl;
        }else{
            cout << "sendByte: " << datbyte << " recieved: " << firstByte << endl;
            //firstByte = AEs.requestData();
        }
        // rqi.wheelVelocity(rightSpeed, rMotor);
        // rqi.wheelVelocity(leftSpeed,  lMotor);
        usleep(100000);
    }

}
