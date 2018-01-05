/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: abdullah
 *
 * Created on January 3, 2018, 5:45 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include "vnlibrary/include/vn/sensors.h"
#include "vnlibrary/include/vn/util.h"
#include "vnlibrary/include/vn/math/vector.h"

int processErrorReceived(char* errorMessage, VnError errorCode);

/*
 * 
// */
int main(int argc, char** argv) {
   
    VnSensor imu;
    char strconversions[50];
    vec3f ypr, acc;
    VnError error;
    VnAsciiAsync outputtype;

    const char SENSOR_PORT[] = "/dev/ttyUSB0";
    const uint32_t SENSOR_BAUDRATE = 115200;



    //Initialize VnSensor structure
    VnSensor_initialize(&imu);

    //Connect to IMU
    if ((error = VnSensor_connect(&imu, SENSOR_PORT, SENSOR_BAUDRATE)) != E_NONE) {
            return processErrorReceived("Error connecting to sensor.", error);
    }
    
    /*THIS STUFF JUST NEEDS TO BE RUN ONCE.*/
//    //Restore to factory default settings     //--> NOTE! NEED TO GIVE THE SENSOR SOME TIME AFTER THIS OR ELSE WILL TIMEOUT!
//    if( (error = VnSensor_restoreFactorySettings(&imu, true)) != E_NONE ) {
//        return processErrorReceived("Error restoring to factory default settings.", error);
//    }
//
//    //Set Async Output Type to VNOFF
//    outputtype = VNOFF;
//    if( (error = VnSensor_writeAsyncDataOutputType(&imu, outputtype, false)) != E_NONE ) {
//        return processErrorReceived("Error setting Async Output Type to VNOFF.", error);
//    }
//    /*
//     * Now, there currently is neither ASCII Async data being sent
//     * nor Binary Output Data automatically. This is to simplify
//     * things and make it clear that the only data going through
//     * is what is requested from a function directly calling to
//     * read a register.
//    */
    
    
    while(1) {
        //Get values for ypr
        if ((error = VnSensor_readYawPitchRoll(&imu, &ypr)) != E_NONE) {
            return processErrorReceived("Error reading yaw pitch roll.", error);
        }
        str_vec3f(strconversions, ypr);
        printf("Current YPR: %s\n", strconversions);

        //Get values for acc
        if( (error = VnSensor_readAccelerationMeasurements(&imu, &acc)) != E_NONE ) {
            return processErrorReceived("Error reading acceleration data.", error);
        }
        str_vec3f(strconversions, acc);
        printf("Current Acceleration: %s\n", strconversions);
        
        puts("");
    }
    
    
    return (EXIT_SUCCESS);
}

int processErrorReceived(char* errorMessage, VnError errorCode)
{
	char errorCodeStr[100];
	strFromVnError(errorCodeStr, errorCode);
	printf("%s\nERROR: %s\n", errorMessage, errorCodeStr);
	return -1;
}