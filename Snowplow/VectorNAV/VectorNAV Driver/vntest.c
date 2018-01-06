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
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <bits/time.h>

#include "vnlibrary/include/vn/sensors.h"
#include "vnlibrary/include/vn/util.h"
#include "vnlibrary/include/vn/math/vector.h"
#include "vnlibrary/include/vn/xplat/time.h"



#define TIMEINTERVAL 50.0F      /*In milliseconds*/
#define CALNUM 1000             /*Number of times to run the calibration loop. DON'T MAKE LESS THAN 1!*/
#define FILTNUM 5               /*Number of times filter runs on acc measurement values. DON'T MAKE IT 0!*/



typedef struct timeval TIME;


/* Method for processing errors. */
int processErrorReceived(char* errorMessage, VnError errorCode);
/* Method for multipling a vector by a scalar. */
vec3f scaleVector(vec3f vector, float scalar);
/* Method for reset values of a vector to 0. */
void resetVector(vec3f *vector);



int main(int argc, char** argv) {
    
    VnSensor imu;
    vec3f acc0, acc1, vel0, vel1, pos0, pos1;
    vec3f calacc;
    vec3f *acc0ptr = &acc0, *acc1ptr = &acc1, *vel0ptr = &vel0, *vel1ptr = &vel1, *pos0ptr = &pos0, *pos1ptr = &pos1;
    char acc1str[50], vel1str[50], pos1str[50];
    char calaccstr[50];
    VnError error;
    VnStopwatch timer;

    const char SENSOR_PORT[] = "/dev/ttyUSB0";
    const uint32_t SENSOR_BAUDRATE = 115200;


    
    /*Initialize VnSensor imu*/
    VnSensor_initialize(&imu);
    /*Connect to IMU*/
    if ((error = VnSensor_connect(&imu, SENSOR_PORT, SENSOR_BAUDRATE)) != E_NONE) {
            return processErrorReceived("Error connecting to sensor.", error);
    }
    /*Initialize timer*/
    VnStopwatch_initializeAndStart(&timer);
    float timeInitial, currentTime;
    
    
    
    /* SET INITIAL VALUES
     * Assume initial velocity and position are 0 and initialize accordingly
     * ACTUALLY. Scratch that. Need to CALIBRATE first.
     *********************************************************************/
    /*
     * Calibration of acceleration measurements
     */
    vec3f tempacc;    
    calacc = create_v3f(0.0F, 0.0F, 0.0F);
    for(int i = 0; i < CALNUM; i++) {
        VnSensor_readAccelerationMeasurements(&imu, &tempacc);
        calacc = add_v3f_v3f(calacc, tempacc);
    }
    calacc = scaleVector(calacc, (1.0F / CALNUM));
    str_vec3f(calaccstr, calacc);
    printf("Calibration Value for Acceleration: %s\n\n", calaccstr);
    
    
    /* First acc0 value before going into loop. */
    VnSensor_readAccelerationMeasurements(&imu, acc0ptr);
    *acc0ptr = sub_v3f_v3f(*acc0ptr, calacc);
    
    while(1) {
        
        /*Wait time interval*/
        do {
            
            VnStopwatch_elapsedMs(&timer, &currentTime);
        
        } while( (currentTime - timeInitial) < TIMEINTERVAL );
        
        
        /* READ CURRENT VALUES
         * 
         * Reason for all the pointer mania is because current loop's final value
         * becomes the next loops initial value. And the current loop's initial
         * value needs to go somewhere. The approach I'm using uses pointers;
         * perhaps a recursive function might work as well, or some other structure.
         * 
         * ALSO! Before using acceleration value, am applying filter.
         * Filter seems to take heavy time, though. Need to adjust FILTNUM
         * and TIMEINTERVAL accordingly.
        ***********************************************************************/
        
        /* Applying filter
         * Reseting tempacc because this is used as incrementation value every loop
         */
        resetVector(&tempacc);
        
        if( FILTNUM > 1) {
            for(int i=0; i < FILTNUM; i++) {
                VnSensor_readAccelerationMeasurements(&imu, &tempacc);
                *acc1ptr = add_v3f_v3f(*acc1ptr, tempacc);
            }
            *acc1ptr = scaleVector(*acc1ptr, (1.0F / FILTNUM));
        }
        *acc1ptr = sub_v3f_v3f(*acc1ptr, calacc);
        
        VnSensor_readAccelerationMeasurements(&imu, acc1ptr);
        *acc1ptr = sub_v3f_v3f(*acc1ptr, calacc);
        
        /* Get velocity by integrating acceleration.
         * Need to convert TIMEINTERVAL into seconds cuz measurement units
         * are in SI units (i.e., m/s^2, m/s, m)
         */
        *vel1ptr = add_v3f_v3f(*vel0ptr, scaleVector(add_v3f_v3f(*acc1ptr, acc0), (0.5F * (TIMEINTERVAL / 1000.0F))));
        
        /* Get position by integrating velocity.
         * Same conversion for TIMEINTERVAL
         */
        *pos1ptr = add_v3f_v3f(*pos0ptr, scaleVector(add_v3f_v3f(*vel1ptr, vel0), (0.5F * (TIMEINTERVAL / 1000.0F))));
        
        /*Reset new initials*/
        VnStopwatch_elapsedMs(&timer, &timeInitial);
        acc0ptr = acc1ptr;
        vel0ptr = vel1ptr;
        pos0ptr = pos1ptr;
        /*I'm having the current ones point to old because they need to point to SOME vec3f structure*/
        acc1ptr = acc0ptr;
        vel1ptr = vel0ptr;
        pos1ptr = pos0ptr;
        
        
        
        /* PRINT OUT
         * This assumes that the time taken to print and get to the next
         * loop is less than TIMEINTERVAL.
         */
        str_vec3f(acc1str, *acc1ptr);
        str_vec3f(vel1str, *vel1ptr);
        str_vec3f(pos1str, *pos1ptr);
        printf("Current Acceleration: %s\nCurrent Velocity: %s\nCurrent Position: %s\n\n", acc1str, vel1str, pos1str);
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

vec3f scaleVector(vec3f vector, float scalar) {
    vec3f scaledVector;
    
    scaledVector.c[0] = vector.c[0] * scalar;
    scaledVector.c[1] = vector.c[1] * scalar;
    scaledVector.c[2] = vector.c[2] * scalar;
    
    return scaledVector;
}

void resetVector(vec3f *vector) {
    vector->c[0] = 0.0F;
    vector->c[1] = 0.0F;
    vector->c[2] = 0.0F;
}



    /*THIS STUFF JUST NEEDS TO BE RUN ONCE.*/
//    //Restore to factory default settings     //--> NOTE! NEED TO GIVE THE SENSOR SOME TIME AFTER THIS OR ELSE WILL TIMEOUT!
//    if( (error = VnSensor_restoreFactorySettings(&imu, true)) != E_NONE ) {
//        return processErrorReceived("Error restoring to factory default settings.", error);
//    }

//    VnAsciiAsync outputtype;
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