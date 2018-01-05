/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ch15.h
 * Author: abdullah
 *
 * Created on December 30, 2017, 10:24 PM
 */



#ifndef CH15_H
#define CH15_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdbool.h>

    extern char *itobs(int n, char *bitstring);
    
    //Prints in big-endian form
    extern void printbits(const char *bitstring);
    
    extern void setbit(int *mask, int index);
    
    //Assumes boolean array is little-endian!
    extern int set_onebyte_mask(bool bits[]);
    
    //Assumes boolean array is little-endian!
    extern int set_twobyte_mask(bool bits[]);
    
    extern void printbitsofint(int number);


#ifdef __cplusplus
}
#endif

#endif /* CH15_H */

