#include "ch1to10.h"

#include <stdio.h>
#include <string.h>

/*
* NOTE! Two flaws with this function:
    * It is silent about out-of-bounds input, and doesn't give the opportunity to re-enter or do something about it. It just ignores the extra characters.
    * It doesn't cope with being sent a size 1, which wouldn't be a string.
*/
char* get_string_input(char* str, int size_of_str) {
    char* return_val;   //WE DON'T ALLOCATE MEMORY BECAUSE THIS POINTER WILL BE SET TO THE PASSED POINTER ARGUMENT
    int i=0;

    return_val = fgets(str, size_of_str, stdin); //FGETS() WILL READ IN INPUT FROM STDIN AND RETURN A PTR EQUIVALENT TO STR IF ALL GOES WELL; OTHERWISE NULL POINTER

    if(return_val) {    //IF RETURN_VAL != NULL
        while(str[i] != '\n' && str[i] != '\0') {   //ADVANCE TO PART OF INPUT THAT IS EITHER A NEWLINE OR NULL CHARACTER
            i++;
        }

        if(str[i] == '\n') {    //IF NEWLINE, ALL INPUT HAS BEEN READ AND SO REPLACE NEWLINE WITH NULL CHARACTER
            str[i] = '\0';
        } else {    //THERE ARE UNREAD CHARACTERS FROM INPUT BECAUSE INPUT WAS TOO LARGE, SO DISCARD EXTRA CHARACTERS
            while(getchar() != '\n') {
                continue;
            }
        }
    }

    return return_val;
}

//char* trim_string(char* str) {        //NEEDS WORK
//    size_t trimmed_size = strlen(str);
//
//
//    trim_string_to_size(str, strlen(str));
//    return str;
//}

void trim_string_to_size(char* str, int desired_size) {
    if(strlen(str) > desired_size) {
        str[desired_size] = '\0';
    }
}

char* str_safe_conc(char* str1, const char* str2, int size_of_1) {
    int size_diff = size_of_1 - (strlen(str2) + 1);

    if( size_diff > 0 ) {
        return strncat(str1, str2, size_diff);
    } else {
        return NULL;
    }
}

void sort_str_alph(char* strings[], int num_of_strings) {   //NOTE FIRST PARAMETER IS OF TYPE ARRAY OF POINTERS-TO-CHAR
    char* temp;     //for switching
    int right_end = num_of_strings, comp_val;

    for(int i=0; i < (right_end - 1); i++) {    //USING SELECTION-SORT
        for(int j = (i + 1); j < right_end; j++) {

            comp_val = strcmp(strings[i], strings[j]);   //RECALL STRCMP() RETURNS > 0 IF FIRST STRING HAS HIGHER ASCII VALUE THAN SECOND, WHICH MEANS REVERSE-ALPHABETICAL
//            printf("%d ", comp_val);

            if( comp_val > 0 ) {    //SWAP
                temp = strings[i];
                strings[i] = strings[j];
                strings[j] = temp;
            }
        }
//        puts("");
    }
}
