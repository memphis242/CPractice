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

