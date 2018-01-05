/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: abdullah
 *
 * Created on December 30, 2017, 10:22 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

#include "src/ch1to10.h"
#include "src/ch11.h"
#include "src/ch14.h"
#include "src/ch15.h"

//Line styles
#define SOLID 0
#define DOTTED 1
#define DASHED 2

//Colors
//Primary
#define BLUE 4
#define GREEN 2
#define RED 1
//Mixed
#define BLACK 0
#define YELLOW (RED | GREEN)
#define MAGENTA (RED | BLUE)
#define CYAN (GREEN | BLUE)
#define WHITE (RED | GREEN | BLUE)

static const char *colors[8] = { "black", "red", "green", "yellow", "blue", "magenta", "cyan", "white" };

typedef struct {
    bool opaque                 : 1;
    unsigned int fill_color     : 3;
    unsigned int                : 4;
    bool show_border            : 1;
    unsigned int border_color   : 3;
    unsigned int border_style   : 2;
    unsigned int                : 2;   
} box;

void showconfig( const box *b );

/*
 * 
 */
int main(int argc, char** argv) {

//PRINTING OUT THE BITS OF AN INTEGER NUMBER
//    char bitstring[CHAR_BIT * sizeof(int) + 1]; //+1 for null character
//    int number;
//    
//    puts("Enter an integer number (assumed to be decimal). Entering a non-numeric character terminates.");
//    printf("Integer number: ");
//    while( scanf("%d", &number) == 1 ) {
//        //Clear rest of input stream through newline because scanf() doesn't do that.
//        while( getchar() != '\n' ) {
//            continue;
//        }
//        itobs(number, bitstring);
//        printf("%d is ", number);
//        printbits(bitstring);
//        putchar('\n');
//        printf("Integer number: ");
//    }
    
//SETTING A DESIRED MASK
//    int bitindex, mask = 0; //Setting mask to 0 so all bits are 0 to begin with.
//    
//    puts("We will set the bits one at a time. For each time, enter which bit, from 31 to 0, to set to 1. It is assumed the rest will be 0s. Enter non-numeric character when you are done.");
//    printf("Which bit? ");
//    while( scanf("%d", &bitindex) ) {
//        //Clear input stream
//        while( getchar() != '\n' ) {
//            continue;
//        }
//        if( bitindex<0 || bitindex>31 ) {
//            puts("Invalid input. Please enter a value between 0 and 31.");
//            printf("Which bit? ");
//            continue;
//        }
//        
//        setbit(&mask, bitindex);
//        printf("Which bit? ");
//    }
//    puts("Done.");
//    
//    new_line();
//    //Print val to be sure.
//    printf("Your mask: ");
//    printbitsofint(mask);
    
//USING BIT FIELDS
//    box newbox = { true, YELLOW, true, GREEN, DASHED };
//    
//    puts("NEWBOX INITIAL SETTINGS:");
//    showconfig(&newbox);
//    new_line();
//    
//    newbox.opaque = false;
//    newbox.fill_color = WHITE;
//    newbox.border_color = MAGENTA;
//    newbox.border_style = SOLID;
//    
//    puts("MODIFIED NEWBOX SETTINGS:");
//    showconfig(&newbox);
    
//SAVING MULTIPLE BYTES OF A DATUM IN A CHAR BUFFER ARRAY AND THEN REVERSING THE PROCESS
//    int16_t val = 16;   //2-byte integer
//    char valparts[2];
//    
//    valparts[0] = (val & 0xFF);     //Get first 8 bits (Bit 0 through 7)
//    valparts[1] = ( (val >> 8) & 0xFF );    //Get next 7 bits (Bit 8 through 15)
//    
//    int16_t retrievedVal = *((int16_t *)(&valparts[0]));    //Retrieve value through pointer magic
//    printf("Retrieved Value: %d", retrievedVal);
    
//SETTING BITS OF MASK THROUGH BOOLEAN ARRAY
    int mask8 = 0;
    int mask16 = 0;
    
    //Desired bit layout in LITTLE-ENDIAN FORM
    bool bits8[8] = { 1, 0, 0, 1, 0, 1, 1, 0 };
    bool bits16[16] = { 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0 };
    
    //Print boolean arrays for check IN BIG-ENDIAN form, as would be printed later on
    for(int i=7; i>=0; i--) {
        printf("%d", bits8[i]);
    }
    new_line();
    for(int i=15; i>=0; i--) {
        printf("%d", bits16[i]);
    }
    new_line();
    new_line();
    
    //Setting single byte and double byte values to corresponding bit layouts above
    mask8 = set_onebyte_mask(bits8);
    mask16 = set_twobyte_mask(bits16);
    
    //Print those out   
    printbitsofint((int) mask8);
    printbitsofint((int) mask16);
    
//    new_line();
//    printf("%zd", sizeof(bool));
    
    return (EXIT_SUCCESS);
}

void showconfig( const box *b ) {
    printf("Box is %s.\n",
            b->opaque == true ? "opaque" : "transparent");
    printf("The fill color is %s.\n",
            colors[b->fill_color]);
    printf("Border %s.\n",
            b->show_border == true ? "shown" : "not shown");
    printf("The border color is %s.\n",
            colors[b->border_color]);
    printf("The border style is ");
    switch(b->border_style)
    {
        case SOLID  : printf("solid.\n"); break;
        case DOTTED : printf("dotted.\n"); break;
        case DASHED : printf("dashed.\n"); break;
        default     : printf("unknown type.\n");
    }
}

