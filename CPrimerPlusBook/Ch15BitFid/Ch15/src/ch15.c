/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "ch1to10.h"
#include "ch11.h"
#include "ch14.h"

#define MASK 0x1    //Hides all but last bit.

char *itobs(int number, char *bitstring) {
    const static int size = CHAR_BIT * sizeof(int);
    
    for(int i = (size - 1); i >= 0; i--, number>>=1) {  //Starting from least-significant bit to most; leaving one character at the end for '\0'
        bitstring[i] = (MASK & number) + '0';   //Retrieving what the last bit is then getting the ASCII value of that character
    }
    
    bitstring[size] = '\0'; //So it is a string and not just a char array
    
    return bitstring;
}

void printbits(const char *bitstring) {
    for(int i = 0; bitstring[i] != '\0'; i++) {
        if( i%4 == 0 && i != 0 ) {    //Spacing out 4-bit intervals except for first
            putchar(' ');
        }
        putchar(bitstring[i]);
    }
}

void setbit(int *mask, int index) {
    int onebit = 1 << index;
    *mask |= onebit;
}

void printbitsofint(int number) {
    char bitstring[CHAR_BIT * sizeof(int) + 1];
    itobs(number, bitstring);
    printbits(bitstring);
}
