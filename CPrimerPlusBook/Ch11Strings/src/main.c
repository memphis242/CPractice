#include <stdio.h>
#include <stdlib.h>

#include "ch1to10.h"

int main()
{
//CHAPTER 11 CHARACTER STRINGS AND STRING FUNCTIONS - INTRO PROGRAM
//    char words[MAXLENGTH] = "I am a string in a char array.";
//    const char* sptr = "Something is pointing at me.";
//
//    puts("Here are some strings:\n");
//    puts(words);
//    puts(sptr);
//    puts(MSG);
//
//    words[8] = 'p';
//    puts(words);

//QUICK REVIEW OF CHAR STRINGS
//    printf("%s, %p, %c\n", "We", "are", *"family.");

//DIFFERENCE BETWEEN POINTER VERSION OF STRING AND ARRAY VERSION OF STRING DECLARATIONS
    char arr[] = MSG;
    const char* ptr = MSG;

    printf("Address of \"I am a symbolic string message.\": %p\n", "I am a symbolic string message.");
    printf("Address of MSG: %p\n", MSG);
    printf("Address of arr: %p\n", arr);
    printf("Address of ptr: %p\n", ptr);

    return 0;
}
