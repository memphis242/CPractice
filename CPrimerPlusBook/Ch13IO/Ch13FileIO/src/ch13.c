/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h> //for exit() function

#include "../../src/ch1to10.h"
#include "../../src/ch11.h"


// int get_file_name(char* file_str){
//        
//        //Just to make efficient use of space at the expense of speed (Y), want to make sure the filename string is exact.
//        char temp_str[300];    //LATER CHANGE THAT NUMBER TO SYSTEM MAX FOR CHARACTERS IN A FILENAME; PROBABLY SOME MACRO DEFINED FOR THAT
//        puts("Please enter a filename below.");
//        if( !get_string_input(temp_str, 200) ) {
//            puts("Failed to get string input. Bye.");
//            exit(EXIT_FAILURE);
//        }
//        
//        int length_of_file_name = strlen(temp_str);
//        file_str = (char*) (malloc( (length_of_file_name + 1) * sizeof(char) ));
//        strncpy(file_str, temp_str, length_of_file_name + 1);
//     
//     if( !get_string_input(file_str, 255) ) {
//         puts("Failed to get string input. Bye.");
//         exit(EXIT_FAILURE);
//     }
//     
//        
//        
//        return length_of_file_name + 1;       
// }

char* fget_string_input(char* str, int size_of_str, FILE* file) {
    char* return_val;   //WE DON'T ALLOCATE MEMORY BECAUSE THIS POINTER WILL BE SET TO THE PASSED POINTER ARGUMENT
    int i=0;

    return_val = fgets(str, size_of_str, file); //FGETS() WILL READ IN INPUT FROM STDIN AND RETURN A PTR EQUIVALENT TO STR IF ALL GOES WELL; OTHERWISE NULL POINTER

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

void seek_file(FILE* file, long offset, int starting_position) {
    if( fseek(file, offset, starting_position) ) {
        puts("Could not use fseek().");
        exit(EXIT_FAILURE);
    }
}

void close_file(FILE* file) {
    if( fclose(file) ) {
        puts("Unable to close file.");
        exit(EXIT_FAILURE);
    }
}

//file should have been opened in "rb" mode already!
void set_start_end(FILE* file, fpos_t* file_start, fpos_t* file_end) {
    rewind(file);
    fgetpos(file, file_start);
    
    while( getc(file) != EOF ) {
        continue;
    }
    
    fgetpos(file, file_end);
}

void append(FILE* source, FILE* destination) {
    size_t num_of_bytes;
    static char temp_buff[4096];
    
    while( num_of_bytes = fread(temp_buff, 1, 4096, source) ) {
        fwrite(temp_buff, sizeof(char), num_of_bytes, destination);
    }
}
