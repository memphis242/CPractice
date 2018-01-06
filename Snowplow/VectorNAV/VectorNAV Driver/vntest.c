/* 
 * File:   main.c
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
 * Implement if currentacc < 0, vel1 = 0. --> DONE --> CAN IMPROVE
    * HERE IS OUR SECOND KEY. IF WE CAN DEFINE OUR MOTION SUCH THAT WE SIMPLIFY THE TYPE OF DATA WE NEED TO LOOK AT, WE SHOULD BE BETTER OFF.
 * Implement integration using trapezoid --> DONE --> CAN IMPROVE
    * Main improvement factor here is the timeinterval - the smaller, the better.
    * Another factory may be using an integration technique less error-prone than trapezoid.
 * Improve main() by simplifying/modulating it through functions.
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



#define TIMEINTERVAL 50.0       /*In milliseconds. Should be atleast greater than time to execute while(1) + do-while loops once each.*/
#define CALNUM 1000             /*Number of times to run the calibration loop. DON'T MAKE LESS THAN 1!*/
#define FILTNUM 0               /*Number of times filter runs on acc measurement values. DON'T MAKE IT 0!*/
#define RANGEDEVIATIONS 1       /*This will determine how far from calibration point will we still acept as = 0. Should be atleast 1*/



//typedef struct timeval TIME;


/* Function for processing errors. */
int processErrorReceived(char* errorMessage, VnError errorCode);
/* Converting vec3f structures into vec3d */
void vec3ftod(vec3f *fvector, vec3d *dvector);
/* Getting current acceleration, but in vec3d form*/
void getCurrentAccel(VnSensor *imu, vec3f *accf, vec3d *accd);
/* Function for multipling a vector by a scalar. */
vec3d scaleVector(vec3d vector, double scalar);
/* Function for comparing two vec3d structures, defined by the MAGNITUDE Of each component.
 * Returns 1 is v1>v2, -1 if v2>v1, and 0 if v1=v2 */
int compvec3d(vec3d v1, vec3d v2);
/* Function for checking if either the x OR y value in a vector is negative. ONLY USE FOR ACCELERATION*/
int isNegative(vec3d *vector);
/* Function for reset values of a vector to 0. */
void resetVector(vec3d *vector);



vec3d zeroVector = { 0.0, 0.0, 0.0 };    /*The zero vector*/



int main(int argc, char** argv) {
    
    VnSensor imu;
    vec3d acc0 = zeroVector, acc1 = zeroVector, vel0 = zeroVector, vel1 = zeroVector, pos0 = zeroVector, pos1 = zeroVector;
    vec3f acc;  /*Having a vec3f to use with library, but converting that to above vec3d*/
    vec3d calacc;
    vec3d *acc0ptr = &acc0, *acc1ptr = &acc1, *vel0ptr = &vel0, *vel1ptr = &vel1, *pos0ptr = &pos0, *pos1ptr = &pos1;
    char acc1str[50], vel1str[50], pos1str[50];
    char calaccstr[50], errRangstr[50];
    VnError error;
    VnStopwatch timer;

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
    
    
    
//    /* QUICK TEST TO SEE WHAT ACCELERATION VALUES LOOK LIKE
//     * Notes:
//        * For some reason, certain orientations are associated with
//        * accelerations for x and y, EVEN at equilibrium state. PROBLEM!
//        * NEED TO ACCOUNT FOR!
//     * 
//     */
//    vec3f acc;
//    char accstr[50];
//    while(1) {
//        VnSensor_readAccelerationMeasurements(&imu, &acc);
//        str_vec3f(accstr, acc);
//        printf("Acceleration: %s\n", accstr);
//    }
    
    /* SET INITIAL VALUES
     * Calibrate
     * Set error range
     * Get initial acceleration measurement for loop
     *********************************************************************/
    /*
     * Calibration of acceleration measurements
     * Obtaining error range
     */
    vec3d tempacc;                          /*Vector to hold calibration point for acceleration measurements.*/
    double tempx, tempy, tempz;
    vec3d errorRange;
    double errmaxx = 0.0, errmaxy = 0.0, errmaxz = 0.0;    /*Values to be used to get error range*/
    calacc = create_v3d(0.0, 0.0, 0.0);
    
    for(int i = 0; i < CALNUM; i++) {
        getCurrentAccel(&imu, &acc, &tempacc);
        
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
    }
    
    calacc = scaleVector(calacc, (1.0 / CALNUM));  /*Average it out*/
    str_vec3d(calaccstr, calacc);
    printf("Calibration Values for Acceleration: %s\n", calaccstr);
    
    /*Will represent maximum range around calibration point that is = 0*/
    errorRange = scaleVector( create_v3d(errmaxx, errmaxy, errmaxz), RANGEDEVIATIONS );
    str_vec3d(errRangstr, errorRange);
    printf("Range Deviation Values for Acceleration: %s\n\n", errRangstr);
    
    
    /* Initial values for acc0, vel0, and pos0. */
    resetVector(acc0ptr);
    resetVector(vel0ptr);
    resetVector(pos0ptr);
    
    /* START LOOPING
     ************************************************************************/
    while(1) {
        
        /* Wait time interval
         * NOTE that TIMEINTERVAL should be LONGER
         * than executing all the code proceeding
         * this loop AND AT LEAST 1 LOOP HERE.
         */
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
                getCurrentAccel(&imu, &acc, &tempacc);
                *acc1ptr = add_v3d_v3d(*acc1ptr, tempacc);
            }
            *acc1ptr = scaleVector(*acc1ptr, (1.0 / FILTNUM));  /*Average it out.*/
            *acc1ptr = sub_v3d_v3d(*acc1ptr, calacc);           /*Calibrate*/
        } else {
            getCurrentAccel(&imu, &acc, acc1ptr);
            *acc1ptr = sub_v3d_v3d(*acc1ptr, calacc);           /*Just calibrate*/
        }
        
        if( compvec3d(*acc1ptr, errorRange) != 1 ) {    /*Vector is within error range of calibration point*/
            resetVector(acc1ptr);                       /*Set it to 0.*/
        }
        
        /* Get velocity by integrating acceleration.
         * USING TRAPEZOID AREA FORMULA: delta = ((a + b)/2)*h,
         * a & b are point0 and 1 of upper level (i.e., for
         * velocity --> acceleration; position --> velocity),
         * and h is TIMEINTERVAL in this context
         * Example:
         * current position = (initial position) + ((initial velocity + current velocity) / 2) * TIMEINTERVAL
         * Need to convert TIMEINTERVAL into seconds cuz measurement units
         * are in SI units (i.e., m/s^2, m/s, m).
         * 
         * NOTE! If acceleration is in zero range, then
         * velocity shouldn't change, so set it to the
         * same value as before. Otherwise, get new value.
         */
        if( compvec3d(*acc1ptr, zeroVector) == 0 ) {
            *vel1ptr = *vel0ptr;
        } else if ( isNegative(acc1ptr) ) {
            resetVector(vel1ptr);
        } else {
            *vel1ptr = add_v3d_v3d(*vel0ptr, scaleVector( add_v3d_v3d(*acc0ptr, *acc1ptr), (0.5 * (TIMEINTERVAL / 1000.0)) ));
        }        
        
        /* Get position by integrating velocity.
         * Same conversion for TIMEINTERVAL
         */
        *pos1ptr = add_v3d_v3d(*pos0ptr, scaleVector( add_v3d_v3d(*vel0ptr, *vel1ptr), (0.5 * (TIMEINTERVAL / 1000.0)) ));
        
        
        
        /* Set new initials
         * Current acceleration becomes initial acceleration for next interval (i.e., loop)
         * Current velocity becoems initial velocity for next interval
         * Current position becomes initial position for next interval
         */
        VnStopwatch_elapsedMs(&timer, &timeInitial);
        acc0ptr = acc1ptr;
        vel0ptr = vel1ptr;
        pos0ptr = pos1ptr;
        /* I'm having the pointer to current values point to initial because they need to point to SOME vec3d structure
         * and the initial values for this loop don't matter anymore, so they can be overwritten and used in next loop
         * as future current values.
         */
        acc1ptr = acc0ptr;
        vel1ptr = vel0ptr;
        pos1ptr = pos0ptr;
        
        
        
        /* PRINT OUT
         * This assumes that the time taken to print and get to the next
         * loop is less than TIMEINTERVAL.
         */
        str_vec3d(acc1str, *acc1ptr);
        str_vec3d(vel1str, *vel1ptr);
        str_vec3d(pos1str, *pos1ptr);
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

void vec3ftod(vec3f *fvector, vec3d *dvector) {
    dvector->c[0] = (double) fvector->c[0];
    dvector->c[1] = (double) fvector->c[1];
    dvector->c[2] = (double) fvector->c[2];
}

void getCurrentAccel(VnSensor *imu, vec3f *accf, vec3d *accd) {
    VnSensor_readAccelerationMeasurements(imu, accf);
    vec3ftod(accf, accd);
}

vec3d scaleVector(vec3d vector, double scalar) {
    vec3d scaledVector;
    
    scaledVector.c[0] = vector.c[0] * scalar;
    scaledVector.c[1] = vector.c[1] * scalar;
    scaledVector.c[2] = vector.c[2] * scalar;
    
    return scaledVector;
}

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