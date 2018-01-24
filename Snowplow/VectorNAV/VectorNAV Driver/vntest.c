/* 
 * File:   vntest.c
 * Author: abdullah
 *
 * Created on January 3, 2018, 5:45 AM
 */

/* TASK-LIST
 * Switch everything to double. --> DONE
    * (slightly more overhead because of it but anyways, at most FILTNUM measurements are taken in any given loop, and those should be low.
 
 * Implement calibration --> DONE --> CAN IMPROVE.
    * NEED TO ACCOUNT FOR WHAT EXACTLY ENTAILS AN EQUILIBRIUM STATE FOR OUR PURPOSES
 
 * Set error range and associated statements --> DONE --> CAN IMPROVE
    * GOES HAND IN HAND WITH CALIBRATION. NEED TO ADJUST RANGEDEVIATIONS ACCORDINGLY
 
 * Implement filter on current measurements --> DONE --> CAN IMPROVE
    * HERE IS WHERE I SEE THE KEY. IF WE CAN FILTER OUT THE NOISE HERE AND JUST EXTRACT WHAT MAKES SENSE, WE SHOULD BE GOOD TO GO.
 
 * Implement if currentacc = 0, vel1 = vel0. --> DONE
 
 * Account for sensor data being skewed by orientation. --> DONE
    * Try out all the different acceleration registers --> DONE
        * Try delta v async output --> DONE
        * Try binary output linear body acceleration --> DONE
    * Put a recalibration process every time orientation is changed. --> VERY IMPRACTICAL
 
 * Implement if currentacc < 0, vel1 = 0. --> DONE --> CAN IMPROVE
    * HERE IS OUR SECOND KEY. IF WE CAN DEFINE OUR MOTION SUCH THAT WE SIMPLIFY THE TYPE OF DATA WE NEED TO LOOK AT, WE SHOULD BE BETTER OFF.
 
 * Implement integration using trapezoid --> DONE --> CAN IMPROVE
    * Main improvement factor here is the timeinterval - the smaller, the better.
    * Another factory may be using an integration technique less error-prone than trapezoid.
 *************************
 * Improve main() by simplifying/modulating it through functions.
 
 * Possible scaling factor for acceleration and positioning needed.
 
 * Given the simplified motion of the robot, all you really need to know is --> NO GOOD :(
    * When the robot starts up, how long does it take before it reaches a constant velocity (i.e., when does acceleration hit 0 again)
    * When the robot stops, how long does it take before it reaches 0 velocity (i.e., when acceleration hits 0 again).
    * JUST NEED TO KNOW THE ACCELERATION'S 0 POINTS TO DETERMINE TRANSITIONS BETWEEN START, CONSTANT VELOCITY, AND STOP!
    * USE ENCODERS TO DETERMINE ASSUMPTIONS TO BE MADE FOR WHAT POSITIONING IS LIKE FOR STARTING, CONSTANT VELOCITY, AND STOPING.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
//#include <time.h>
//#include <sys/time.h>
//#include <bits/time.h>
#include <math.h>

#include "vnlibrary/include/vn/sensors.h"
#include "vnlibrary/include/vn/util.h"
#include "vnlibrary/include/vn/math/vector.h"
#include "vnlibrary/include/vn/xplat/time.h"


#define ASYNCFREQ 100                                       /*Frequency of asynchronous output. THIS NEEDS TO BE VALID - 1, 2, 4, 5, 10, 20, 25, 40, 50, 100, 200*/
#define ASYNCTIMEMS ( 1 / (ASYNCFREQ / 1000.0) )            /*Time it takes for a single measuremnt to come in ms*/
#define ASYNCDIVISOR 800 / ASYNCFREQ                        /*Divisor used command to configure async output - 800, 400, 200, 160, 80, 40, 32, 20, 16, 8, 4*/
#define TIMEOFLOOP 30                                       /*Approximate amount of time for main loop to run*/
#define TIMEINTERVAL (ASYNCTIMEMS + TIMEOFLOOP)             /*Time between measurements in milliseconds. Should be atleast greater than time to execute while(1) + do-while loops once each.*/
#define CALNUM 100                                          /*Number of times to run the calibration loop. DON'T MAKE LESS THAN 1!*/
#define CALLOOPTIME 5                                       /*Amount of time it takes for a single calibration loop. NEEDS TO BE LESS THAN 1000.0/ASYNCFREQ!*/
#define FILTNUM 5                                           /*Number of times filter runs on acc measurement values. DON'T MAKE IT 0!*/
#define FILTLOOPTIME (CALLOOPTIME / 2)                      /*Amount of time it takes for single filter loop. NEEDS TO BE LESS THAN 1000.0/ASYNCFREQ!*/
#define RANGEDEVIATIONS 1                                   /*This will determine how far from calibration point will we still acept as = 0. Should be atleast 1*/



//typedef struct timeval TIME;


/* Function for processing errors. */
int processErrorReceived(char* errorMessage, VnError errorCode);
/* Converting vec3f structures into vec3d */
void vec3ftod(vec3f *fvector, vec3d *dvector);
/* Getting current acceleration, but in vec3d form*/
void getCurrentAccel(VnSensor *imu, vec3f *accf, vec3d *accd);
/* Get current delta velocity, but in vec3d form*/
void getDeltaV(vec3d *deltaVd);
/* Get current delta velocity and delta time, but in vec3d form*/
void getDeltaVT(vec3d *deltaVd, double *deltaTimed);
/* Function to be used as call method binary packets*/
void BinaryAsyncHandlerLinBodAcc(void *userData, VnUartPacket *packet, size_t runningIndex);
/* Function to be used as call method for ascii packets for VNDTV messages*/
void AsciiAsyncHandlerDeltaV(void *userData, VnUartPacket *packet, size_t runningIndex);
/* Function for multipling a vector by a scalar. */
vec3d scaleVector(vec3d vector, double scalar);
/* Function for comparing two vec3d structures, defined by the MAGNITUDE Of each component.
 * Returns 1 is v1>v2, -1 if v2>v1, and 0 if v1=v2 */
int compvec3d(vec3d v1, vec3d v2);
/* Function for checking if either the x OR y value in a vector is negative. ONLY USE FOR ACCELERATION*/
int isNegative(vec3d *vector);
/* Function for reset values of a vector to 0. */
void resetVector(vec3d *vector);



vec3d zeroVector = { 0.0, 0.0, 0.0 };       /*The zero vector*/
vec3d deltaPosStop = { 0.0, 0.0, 0.0 };     /*This is the ASSUMED change in x, y, z components of position when the robot stops*/
vec3f linearAcc;                            /*Having a vec3f to use with library, but converting that to above vec3d*/
vec3f deltaVf;                              /*Vectors for use in the deltaV Ascii Async method*/
float deltaTimef;



int main(int argc, char** argv) {
    
    VnSensor imu;
    BinaryOutputRegister bor;
    vec3d accInitial = zeroVector, accCurrent = zeroVector, velInitial = zeroVector, velCurrent = zeroVector, posInitial = zeroVector, posCurrent = zeroVector;
    vec3d calacc;   /*Calibrated acceleration reference*/
    vec3d *accInitialptr = &accInitial, *accCurrentptr = &accCurrent, *velInitialptr = &velInitial, *velCurrentptr = &velCurrent, *posInitialptr = &posInitial, *posCurrentptr = &posCurrent;
    char accCurrentstr[50], velCurrentstr[50], posCurrentstr[50];
    char calaccstr[50], errRangstr[50];
    VnError error;
    VnStopwatch timer;
    
    vec3d deltaVd;
    vec3d *deltaVptr = &deltaVd;
    vec3d caldeltaV;    /*Calibrated delta velocity reference*/
    double deltaTime;
    char caldeltaVstr[50];

    const char SENSOR_PORT[] = "/dev/ttyUSB0";
    const uint32_t SENSOR_BAUDRATE = 115200;


    /*BEGIN
     ********************************************************************/
    /*Initialize VnSensor imu*/
    VnSensor_initialize(&imu);
    /*Connect to IMU*/
    if ((error = VnSensor_connect(&imu, SENSOR_PORT, SENSOR_BAUDRATE)) != E_NONE) {
            return processErrorReceived("Error connecting to sensor.", error);
    }
    /*Initialize timer*/
    VnStopwatch_initializeAndStart(&timer);
    float timeInitial, currentTime;
    
    
    
/*************INITIAL SETUP OF SENSOR*****************************/
//    //Restore to factory default settings     //--> NOTE! NEED TO GIVE THE SENSOR SOME TIME AFTER THIS OR ELSE WILL TIMEOUT!
    if( (error = VnSensor_restoreFactorySettings(&imu, true)) != E_NONE ) {
        return processErrorReceived("Error restoring to factory default settings.", error);
    }
    
    /*Wait 100ms to avoid clashes*/
    VnStopwatch_elapsedMs(&timer, &timeInitial);        
    do {

        VnStopwatch_elapsedMs(&timer, &currentTime);

    } while( (currentTime - timeInitial) < 100 );
    
    
    
    /*Set async output frequency*/
    if ((error = VnSensor_writeAsyncDataOutputFrequency(&imu, ASYNCFREQ, false)) != E_NONE) {
		return processErrorReceived("Error writing async data output frequency.", error);
    }

    /******************Setup ascii output*************************/
    if( (error = VnSensor_writeAsyncDataOutputType(&imu, VNOFF, false)) != E_NONE ) {
        return processErrorReceived("Error setting Async Output Type to VNOFF.", error);
    }
//    if( (error = VnSensor_writeAsyncDataOutputType(&imu, VNDTV, false)) != E_NONE ) {
//        return processErrorReceived("Error setting Async Output Type to VNOFF.", error);
//    }
//    
//    VnSensor_registerAsyncPacketReceivedHandler(&imu, AsciiAsyncHandlerDeltaV, NULL);
    
    /*Wait 100ms*/
    VnStopwatch_elapsedMs(&timer, &timeInitial);        
    do {

        VnStopwatch_elapsedMs(&timer, &currentTime);

    } while( (currentTime - timeInitial) < 100 );
    
    
    
    /*Setup binary output*/
    BinaryOutputRegister_initialize(
		&bor,
		ASYNCMODE_PORT1,
		ASYNCDIVISOR, /*This will set rate to 50Hz*/
		COMMONGROUP_NONE,
		TIMEGROUP_NONE,
		IMUGROUP_NONE,
		GPSGROUP_NONE,
		ATTITUDEGROUP_LINEARACCELBODY,
		INSGROUP_NONE);
    
    if ((error = VnSensor_writeBinaryOutput1(&imu, &bor, false)) != E_NONE) {
		return processErrorReceived("Error writing binary output 1.", error);
    }
    
    /*Wait 100ms*/
    VnStopwatch_elapsedMs(&timer, &timeInitial);        
    do {

        VnStopwatch_elapsedMs(&timer, &currentTime);

    } while( (currentTime - timeInitial) < 100 );
    
    /*Setup function handler for binary packets*/
    VnSensor_registerAsyncPacketReceivedHandler(&imu, BinaryAsyncHandlerLinBodAcc, NULL);
    
    
    
    /*Wait 30 seconds because first set of measurements from async are 0.*/
    VnStopwatch_elapsedMs(&timer, &timeInitial);        
    do {

        VnStopwatch_elapsedMs(&timer, &currentTime);

    } while( (currentTime - timeInitial) < 30000 );
    
    
/*******************************************************************************/
    
/*******************************************************************************/
//    /* QUICK TEST TO SEE WHAT ACCELERATION VALUES LOOK LIKE */
//    
//    char accstr[50];
//    while(1) {
//        str_vec3f(accstr, linearAcc);
//        printf("Acceleration: %s\n", accstr);
//        
//        VnStopwatch_elapsedMs(&timer, &timeInitial);        
//        do {
//            
//            VnStopwatch_elapsedMs(&timer, &currentTime);
//            
//        } while( (currentTime - timeInitial) < TIMEINTERVAL );
//    }
/*******************************************************************************/
    
    
    
    /* SET INITIAL VALUES
     * Calibrate
     * Set error range
     * Get initial acceleration measurement for loop
     *********************************************************************/
    
    /*
     * Calibration of acceleration measurements
     * Obtaining error range
     */
    vec3d tempacc;                          /*Vector to hold temporary acceleration measurements.*/
    double tempx, tempy, tempz;
    vec3d errorRange;
    double errmaxx = 0.0, errmaxy = 0.0, errmaxz = 0.0;    /*Values to be used to get error range*/
    calacc = create_v3d(0.0, 0.0, 0.0);
    char accstr[50];
    
    for(int i = 0; i < CALNUM; i++) {
        getCurrentAccel(&imu, &linearAcc, &tempacc);
        
        tempx = fabs(tempacc.c[0]);
        tempy = fabs(tempacc.c[1]);
        tempz = fabs(tempacc.c[2]);
        
        if( tempx > errmaxx ) {
            errmaxx = tempx;
        }
        if( tempy > errmaxy ) {
            errmaxy = tempy;
        }
        if( tempz > errmaxz ) {
            errmaxz = tempz;
        }
        
        calacc = add_v3d_v3d(calacc, tempacc);
        
//        str_vec3f(accstr, linearAcc);
//        printf("Acceleration: %s\n", accstr);
        
        
        /*Wait some time for next output update*/
        VnStopwatch_elapsedMs(&timer, &timeInitial);        
        do {

            VnStopwatch_elapsedMs(&timer, &currentTime);

        } while( (currentTime - timeInitial) < ((ASYNCTIMEMS) - CALLOOPTIME) );
    }
    
    calacc = scaleVector(calacc, (1.0 / CALNUM));  /*Average it out*/
    str_vec3d(calaccstr, calacc);
    printf("Calibration Values for Acceleration: %s\n", calaccstr);
    
    /*Will represent maximum range around calibration point that is = 0*/
    errorRange = scaleVector( create_v3d(errmaxx, errmaxy, errmaxz), RANGEDEVIATIONS );
    str_vec3d(errRangstr, errorRange);
    printf("Range Deviation Values for Acceleration: %s\n\n", errRangstr);
    
//    /********************************************************************
//     * Calibration of deltaV measurements
//     * Obtaining error range
//     */
//    vec3d tempDeltaV;                          /*Vector to hold temporary delta V measurements.*/
//    double tempx, tempy, tempz;
//    vec3d errorRange;
//    double errmaxx = 0.0, errmaxy = 0.0, errmaxz = 0.0;    /*Values to be used to get error range*/
//    caldeltaV = create_v3d(0.0, 0.0, 0.0);
//    
//    for(int i = 0; i < CALNUM; i++) {
//        getDeltaV(&tempDeltaV);
//        
//        tempx = fabs(tempDeltaV.c[0]);
//        tempy = fabs(tempDeltaV.c[1]);
//        tempz = fabs(tempDeltaV.c[2]);
//        
//        if( tempx > errmaxx ) {
//            errmaxx = tempx;
//        }
//        if( tempy > errmaxy ) {
//            errmaxy = tempy;
//        }
//        if( tempz > errmaxz ) {
//            errmaxz = tempz;
//        }
//        
//        caldeltaV = add_v3d_v3d(calacc, tempDeltaV);
//        
//        VnStopwatch_elapsedMs(&timer, &timeInitial);        
//        do {
//
//          VnStopwatch_elapsedMs(&timer, &currentTime);
//
//        } while( (currentTime - timeInitial) < 1000.0 / ASYNCFREQ );
//    }
//    
//    caldeltaV = scaleVector(caldeltaV, (1.0 / CALNUM));  /*Average it out*/
//    str_vec3d(caldeltaVstr, caldeltaV);
//    printf("Calibration Values for Delta Velocity: %s\n", caldeltaVstr);
//    
//    /*Will represent maximum range around calibration point that is = 0*/
//    errorRange = scaleVector( create_v3d(errmaxx, errmaxy, errmaxz), RANGEDEVIATIONS );
//    str_vec3d(errRangstr, errorRange);
//    printf("Range Deviation Values for Delta Velocity: %s\n\n", errRangstr);
    
    
    /*Initial values for acc0, vel0, and pos0*/
    resetVector(accInitialptr);
    resetVector(velInitialptr);
    resetVector(posInitialptr);
    
    
    
    /* START LOOPING BINARY OUTPUT LINEAR BODY ACCELERATION
     ************************************************************************/
    while(1) {
        
        /* Wait time interval
         * NOTE that TIMEINTERVAL should be LONGER
         * than executing all the code proceeding
         * this loop AND AT LEAST 1 DO LOOP.
         */
        VnStopwatch_elapsedMs(&timer, &timeInitial);
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
        
        /* Applying filter*/
        if( FILTNUM > 1) {  /*In case FILTNUM is set to 0 or something, which would be a problem to divide by.*/
            for(int i=0; i < FILTNUM; i++) {
                getCurrentAccel(&imu, &linearAcc, &tempacc);
                *accCurrentptr = add_v3d_v3d(*accCurrentptr, tempacc);
                
                /*Wait some time for next output update*/
                VnStopwatch_elapsedMs(&timer, &timeInitial);        
                do {

                    VnStopwatch_elapsedMs(&timer, &currentTime);

                } while( (currentTime - timeInitial) < (ASYNCTIMEMS - FILTLOOPTIME) );
            }
            *accCurrentptr = scaleVector(*accCurrentptr, (1.0 / FILTNUM));  /*Average it out.*/
            *accCurrentptr = sub_v3d_v3d(*accCurrentptr, calacc);           /*Calibrate --> Calibration means calibratedValue = obtainedValue - calibrationReference*/
        } else {
            getCurrentAccel(&imu, &linearAcc, accCurrentptr);
            *accCurrentptr = sub_v3d_v3d(*accCurrentptr, calacc);           /*Just calibrate*/
        }
        
        if( compvec3d(*accCurrentptr, errorRange) != 1 ) {    /*Vector is within error range of calibration point*/
            resetVector(accCurrentptr);                       /*Set it to 0.*/
        }
        
        
        
        /* Get current velocity & position
         * 
         * USING TRAPEZOID AREA FORMULA:
            * delta = ((a + b)/2)*h, which implies
            * currentVal = prevVal + delta
            
            * a & b are the previous and current value of upper level
            * (i.e., for velocity --> acceleration; position --> velocity),
            * and h is TIMEINTERVAL in this context
         *
         * Example:
         * current position = (initial position) + (((initial velocity + current velocity) / 2) * TIMEINTERVAL)
         * Need to convert TIMEINTERVAL into seconds cuz measurement units
         * are in SI units (i.e., m/s^2, m/s, m).
         * 
         * If acceleration is in zero range, then
         * velocity shouldn't change, so set it to the
         * same value as before. This should be done without
         * having to explicitly code for it, but just in case.
         * Otherwise, get new value.
         * 
         * If acceleration is negative, just going to assume
         * robot is stopping, and so going to make an ASSUMED
         * change in position according to testing.
         * 
         * Else, apply integration.
         */
        if( compvec3d(*accCurrentptr, zeroVector) == 0 ) {
            *velCurrentptr = *velInitialptr;
            *posCurrentptr = add_v3d_v3d(*posInitialptr, scaleVector( add_v3d_v3d(*velInitialptr, *velCurrentptr), (0.5 * (TIMEINTERVAL / 1000.0)) ));
//        } else if ( isNegative(acc1ptr) ) {
//            resetVector(vel1ptr);
//            *pos1ptr = add_v3d_v3d(*pos0ptr, deltaPosStop);
        } else {
            *velCurrentptr = add_v3d_v3d(*velInitialptr, scaleVector( add_v3d_v3d(*accInitialptr, *accCurrentptr), (0.5 * (TIMEINTERVAL / 1000.0)) ));
            *posCurrentptr = add_v3d_v3d(*posInitialptr, scaleVector( add_v3d_v3d(*velInitialptr, *velCurrentptr), (0.5 * (TIMEINTERVAL / 1000.0)) ));
        }
        
        
                
        /* Set new initials
         * Current acceleration becomes initial acceleration for next interval (i.e., loop)
         * Current velocity becoems initial velocity for next interval
         * Current position becomes initial position for next interval
         */
        accInitialptr = accCurrentptr;
        velInitialptr = velCurrentptr;
        posInitialptr = posCurrentptr;
        /* I'm having the pointer to current values point to initial because they need to point to SOME vec3d structure
         * and the initial values for this loop don't matter anymore, so they can be overwritten and used in next loop
         * as future current values.
         */
        accCurrentptr = accInitialptr;
        velCurrentptr = velInitialptr;
        posCurrentptr = posInitialptr;
        
        
        
        /* PRINT OUT
         * This assumes that the time taken to print and get to the next
         * loop is less than TIMEINTERVAL.
         */
        str_vec3d(accCurrentstr, *accCurrentptr);
        str_vec3d(velCurrentstr, *velCurrentptr);
        str_vec3d(posCurrentstr, *posCurrentptr);
        printf("Current Acceleration: %s\nCurrent Velocity: %s\nCurrent Position: %s\n\n", accCurrentstr, velCurrentstr, posCurrentstr);
    }
    
//    /* START LOOPING FOR ASCII OUTPUT DELTA V
//     ************************************************************************/
//    while(1) {
//        
//        /* Wait time interval
//         * NOTE that TIMEINTERVAL should be LONGER
//         * than executing all the code proceeding
//         * this loop AND AT LEAST 1 DO LOOP.
//         */
//        VnStopwatch_elapsedMs(&timer, &timeInitial);
//        do {
//            
//            VnStopwatch_elapsedMs(&timer, &currentTime);
//        
//        } while( (currentTime - timeInitial) < TIMEINTERVAL );
//        
//        
//        
//        /* READ CURRENT VALUES
//         * 
//         * Reason for all the pointer mania is because current loop's final value
//         * becomes the next loops initial value. And the current loop's initial
//         * value needs to go somewhere. The approach I'm using uses pointers;
//         * perhaps a recursive function might work as well, or some other structure.
//         * 
//         * ALSO! Before using acceleration value, am applying filter.
//         * Filter seems to take heavy time, though. Need to adjust FILTNUM
//         * and TIMEINTERVAL accordingly.
//        ***********************************************************************/
//        
//        /* Applying filter*/
//        if( FILTNUM > 1) {  /*In case FILTNUM is set to 0 or something, which would be a problem to divide by.*/
//            for(int i=0; i < FILTNUM; i++) {
//                getDeltaVT(&tempDeltaV, &deltaTime);
//                *deltaVptr = add_v3d_v3d(*deltaVptr, tempDeltaV);
//            }
//            *deltaVptr = scaleVector(*deltaVptr, (1.0 / FILTNUM));      /*Average it out.*/
//            *deltaVptr = sub_v3d_v3d(*deltaVptr, caldeltaV);            /*Calibrate --> Calibration means calibratedValue = obtainedValue - calibrationReference*/
//        } else {
//            getDeltaV(deltaVptr);
//            *deltaVptr = sub_v3d_v3d(*deltaVptr, caldeltaV);            /*Just calibrate*/
//        }
//        
//        if( compvec3d(*deltaVptr, errorRange) != 1 ) {    /*Vector is within error range of calibration point*/
//            resetVector(deltaVptr);                       /*Set it to 0.*/
//        }
//        
//        
//        
//        /* Get current velocity & position
//         * 
//         * USING TRAPEZOID AREA FORMULA:
//            * delta = ((a + b)/2)*h, which implies
//            * currentVal = prevVal + delta
//            
//            * a & b are the previous and current value of upper level
//            * (i.e., for velocity --> acceleration; position --> velocity),
//            * and h is TIMEINTERVAL in this context
//         *
//         * Example:
//         * current position = (initial position) + (((initial velocity + current velocity) / 2) * TIMEINTERVAL)
//         * Need to convert TIMEINTERVAL into seconds cuz measurement units
//         * are in SI units (i.e., m/s^2, m/s, m).
//         */
//
//        *velCurrentptr = add_v3d_v3d(*velInitialptr, deltaVd);
//        *posCurrentptr = add_v3d_v3d(*posInitialptr, scaleVector( add_v3d_v3d(*velInitialptr, *velCurrentptr), (0.5 * deltaTime) ));
//        
//        
//        
//                
//        /* Set new initials
//         * Current velocity becoems initial velocity for next interval
//         * Current position becomes initial position for next interval
//         */
//        velInitialptr = velCurrentptr;
//        posInitialptr = posCurrentptr;
//        /* I'm having the pointer to current values point to initial because they need to point to SOME vec3d structure
//         * and the initial values for this loop don't matter anymore, so they can be overwritten and used in next loop
//         * as future current values.
//         */
//        velCurrentptr = velInitialptr;
//        posCurrentptr = posInitialptr;
//        
//        
//        
//        /* PRINT OUT
//         * This assumes that the time taken to print and get to the next
//         * loop is less than TIMEINTERVAL.
//         */
//        str_vec3d(velCurrentstr, *velCurrentptr);
//        str_vec3d(posCurrentstr, *posCurrentptr);
//        printf("Current Velocity: %s\nCurrent Position: %s\n\n", velCurrentstr, posCurrentstr);
//    }
    
    return (EXIT_SUCCESS);
}

/*
 * Part of the runtime example given with the VectorNAV library
 */
int processErrorReceived(char* errorMessage, VnError errorCode)
{
	char errorCodeStr[100];
	strFromVnError(errorCodeStr, errorCode);
	printf("%s\nERROR: %s\n", errorMessage, errorCodeStr);
	return -1;
}

void vec3ftod(vec3f *fvector, vec3d *dvector) {
    dvector->c[0] = (double) fvector->c[0];
    dvector->c[1] = (double) fvector->c[1];
    dvector->c[2] = (double) fvector->c[2];
}

/*
 * RECALL! Using doubles in the code instead of floats for better precision!
 * Am also passing float vector because it is perhaps quicker than declaring a new
 *float vector each time this function is called.
 */
void getCurrentAccel(VnSensor *imu, vec3f *accf, vec3d *accd) {
//    VnSensor_readAccelerationMeasurements(imu, accf);
    vec3ftod(accf, accd);
}

void getDeltaV(vec3d *deltaVd) {
    vec3ftod(&deltaVf, deltaVd);
}

void getDeltaVT(vec3d *deltaVd, double *deltaTimed) {
    vec3ftod(&deltaVf, deltaVd);
    *deltaTimed = (double) deltaTimef;
}

void BinaryAsyncHandlerLinBodAcc(void *userData, VnUartPacket *packet, size_t runningIndex) {

    if (VnUartPacket_type(packet) == PACKETTYPE_BINARY)
    {

            /* First make sure we have a binary packet type we expect since there
             * are many types of binary output types that can be configured. */
            if ( !VnUartPacket_isCompatible(packet,
                    COMMONGROUP_NONE,
                    TIMEGROUP_NONE,
                    IMUGROUP_NONE,
                    GPSGROUP_NONE,
                    ATTITUDEGROUP_LINEARACCELBODY,
                    INSGROUP_NONE) ) {
                
                /* Not the type of binary packet we are expecting. */
                return;
            }

            /* Ok, we have our expected binary output packet. Since there are many
             * ways to configure the binary data output, the burden is on the user
             * to correctly parse the binary packet. However, we can make use of
             * the parsing convenience methods provided by the Packet structure.
             * When using these convenience methods, you have to extract them in
             * the order they are organized in the binary packet per the User Manual. */
            linearAcc = VnUartPacket_extractVec3f(packet);
            
            return;
    }
}

void AsciiAsyncHandlerDeltaV(void *userData, VnUartPacket *packet, size_t runningIndex) {
    
    vec3f deltaTheta;

    /* Make sure we have an ASCII packet and not a binary packet. */
    if (VnUartPacket_type(packet) != PACKETTYPE_ASCII)
            return;

    /* Make sure we have a VNYPR data packet. */
    if (VnUartPacket_determineAsciiAsyncType(packet) != VNDTV)
            return;

    /* We now need to parse out the yaw, pitch, roll data. */
    VnUartPacket_parseVNDTV(packet, &deltaTimef, &deltaTheta, &deltaVf);
}

vec3d scaleVector(vec3d vector, double scalar) {
    vec3d scaledVector;
    
    scaledVector.c[0] = vector.c[0] * scalar;
    scaledVector.c[1] = vector.c[1] * scalar;
    scaledVector.c[2] = vector.c[2] * scalar;
    
    return scaledVector;
}

/*
 * Function to compare magnitudes of components of vectors.
 * Equality here is defined to be if the MAGNITUDES of components are equivalent, then vectors are equivalent.
 * If any of the component magnitudes are greater, then the vector is greater.
    * Note this could imply two vectors are greater than each other, which makes this
    * a poor way of comparing vectors, but for our specific use, it works ok.
 * Else v1 is less.
 */
int compvec3d(vec3d v1, vec3d v2) {
    float v1x = fabs(v1.c[0]), v1y = fabs(v1.c[1]), v1z = fabs(v1.c[2]);
    float v2x = fabs(v2.c[0]), v2y = fabs(v2.c[1]), v2z = fabs(v2.c[2]);
    
    if( (v1x > v2x) || (v1y > v2y) || (v1z > v2z) ) {
        return 1;
    } else if( (v1x == v2x) && (v1y == v2y) && (v1z == v2z) ) {
        return 0;
    } else {
        return -1;
    }
}

int isNegative(vec3d *vector) {
    if( (vector->c[0] < 0) || (vector->c[1] < 0) ) {
        return 1;
    } else {
        return 0;
    }
}

void resetVector(vec3d *vector) {
    *vector = zeroVector;
}



