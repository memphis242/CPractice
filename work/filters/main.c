#include <stdio.h>
#include <stdint.h>


///* H(z): ( 0.004171885074355z + 0.003917814880455 ) / ( z^2 + -1.820114481352049z + 0.828204181306860 )
// * --> yn + a1*yn-1 a2*yn-2 = b1*xn-1 + b2*xn-2
// */
//
//// Coefficients using double precision
//static double b1 = 0.004171885074355f;
//static double b2 = 0.003917814880455f;
//static double a0 = 1.0f;
//static double a1 = -1.820114481352049f;
//static double a2 = 0.828204181306860f;
//
///* Coefficients using Q3.12 fixed-point integers, allowing range of -8 to 7.999755859375,
// * in steps of 2^-12 ~ 0.000244
// * Recall that A = a * 2^QF --> i.e., the fixed-point integer representation is
// * the actual value scaled by 2 raised to the number of fractional bits
// */
//static int16_t B1 = 17; // when rescaled back down, error of about -2.15e-4
//static int16_t B2 = 16; // when rescaled back down, error of about -0.12e-4
//static int16_t A0 = 4096; // no error
//static int16_t A1 = -7456; // when rescaled back down, error of about -0.20e-4
//static int16_t A2 = 3392; // when rescaled back down, error of about -0.08e-4
//
///* Input using Q10.5 fixed-point integers, allowing range of -1024 to 1023.96875
// * in steps of 2^-5 ~ 0.03125
// */
//static float in = 500.0;
//static int16_t input_signal = 16000; // representing 500.0A
//static int16_t X[3] = {0, 0, 0};
//static double x[3] = {0.0, 0.0, 0.0};
//
///* Output using Q10.5 fixed-point integers, allowing range of -1024 to 1023.96875
// * in steps of 2^-5 ~ 0.03125
// */
//static int64_t Y[3] = {0, 0, 0};
//static double y[3] = {0.0, 0.0, 0.0};
//
///* Output using Q18.29 fixed-point integers --> using 64-bit, so in actuality, Q35.29
// * NOTE! The input products are Q14.17 --> Q15.17 BUTTTT since yvals are used, those will
// * be Q18.29 --> Q19.29!
// */
//static int16_t output[3] = {0, 0, 0};
//static int64_t ACC = 0;
//static double out_fixpt_est = 0.0f;

int main(void){

//    // Just testing if right shifting a signed number works the way I want it to...
//    int8_t num1 = -100;
//    int8_t num2 = num1 >> 2;
//    printf("Expected:\t%d\nActual:\t\t%d\n\n", num1/4, num2);


    /*************************************************************/
    // Now let's first try out a first-order IIR fixed-point filter implementation
    double a1 = -0.5f;
    double b0 = 1.0f;
    double b1 = 0.5f;

    int8_t A1 = -1;
    int8_t B0 = 2;
    int8_t B1 = 1;

//    double xin = 7.9375f;
//    int8_t XIN = 127;
    double xin = 2.0f;
    int8_t XIN = 32;

    double xvals[2] = {0.0f, 0.0f};
    int8_t XVALS[2] = {0, 0};
    double yvals[2] = {0.0f, 0.0f};
    int8_t YVALS[2] = {0.0f, 0.0f};

    int16_t ACC = 0;

    double out_est_fixpt = 0.0f;

    for(uint8_t i=0; i<20; i++){

        // fixed-point
        XVALS[1] = XVALS[0];
        XVALS[0] = XIN;
        // double-precision
        xvals[1] = xvals[0];
        xvals[0] = xin;

        // Now shift around outputs
        // fixed-point
        YVALS[1] = YVALS[0];
        ACC = -((int16_t) A1)*YVALS[1] + ((int16_t) B0)*XVALS[0] + ((int16_t) B1)*XVALS[1];
        YVALS[0] = (int8_t) (ACC >> 1);
//        Y[0] = -A1*Y[1] - A2*Y[2] + B1*X[1] + B2*X[2];
        // double-precision
        yvals[2] = yvals[1];
        yvals[1] = yvals[0];
        yvals[0] = -a1*yvals[1] + b0*xvals[0] + b1*xvals[1];

        out_est_fixpt = (double)YVALS[0] / 16.0;    // Get resulting fixed-point output converted to real value and compare

        printf("Fixed-point result:\t%.6f\nDouble-precision result:\t%.6f\n\n", out_est_fixpt, yvals[0]);

    }


//    for(uint16_t i=0; i<3000u; i++){
//
//        // Shifting in next input, for both fixed-point and double-precision arrays
//        // fixed-point
//        X[2] = X[1];
//        X[1] = X[0];
//        X[0] = input_signal;
//        // double-precision
//        x[2] = x[1];
//        x[1] = x[0];
//        x[0] = in;
//
//        // Now shift around outputs
//        // fixed-point
//        Y[2] = Y[1];
//        Y[1] = Y[0];
//        ACC = -((int64_t) A1)*Y[1] - ((int64_t) A2)*Y[2] + ((int64_t) B1)*X[1] + ((int64_t) B2)*X[2];
//        Y[0] = (int16_t) (ACC >> 12);
////        Y[0] = -A1*Y[1] - A2*Y[2] + B1*X[1] + B2*X[2];
//        // double-precision
//        y[2] = y[1];
//        y[1] = y[0];
//        y[0] = -a1*y[1] - a2*y[2] + b1*x[1] + b2*x[2];
//
//        out_fixpt_est = (double)Y[0] / 131072.0;    // Get resulting fixed-point output converted to real value and compare
//
////        if(i%128 == 0) printf("Fixed-point result:\t%.6f\nDouble-precision result:\t%.6f\n\n", out_fixpt_est, y[0]);
//
//
//    }
//
//    printf("Last fixed-point result:\t%.6f\nLast double-precision result:\t%.6f\n\n", out_fixpt_est, y[0]);

    return 0;
}