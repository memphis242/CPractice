/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: abdullah
 *
 * Created on December 28, 2017, 11:23 PM
 */

#include <stdio.h>
#include <stdlib.h> //for exit() function

#include "../src/ch1to10.h"
#include "../src/ch11.h"
#include "src/ch13.h"

/*
 * 
 */
int main(int argc, char** argv) {

//COUNT NUMBER OF CHARACTERS IN A TEXT FILE
//    char read_char;
//    int character_count = 0;
//    
//    FILE* file_pointer;
//    char file_name[MAX_FILE_LENGTH];
//    
////    int file_name_size;
////    
////    file_name_size = get_file_name(file_name);
//    
//    puts("Please enter a filename below.");
//    get_string_input(file_name, MAX_FILE_LENGTH);
//    new_line();
//    
//    if( (file_pointer = fopen(file_name, "r")) == NULL ) { //IF FAILED TO OPEN FILE WITH FOPEN()
//        puts("Can't open file. Bye.");
//        exit(EXIT_FAILURE);
//    }
//    
//    puts("Your file's characters:");
//    while( (read_char = getc(file_pointer)) != EOF ) {  //ECHO FILE CHARACTERS INTO OUTPUT UNTIL EOF
//        putc(read_char, stdout);
//        character_count++;
//    }
//    new_line();
//    
//    if( fclose(file_pointer) ) {
//        puts("Failed to close file!");
//        exit(EXIT_FAILURE);
//    }
//      
//    printf("File %s has %ul characters.\n", file_name, character_count);

//QUICK CHECK FOR WHERE CURRENT DIRECTORY WOULD BE IF YOU RUN FROM TERMINAL
    //Make new file called currentD.txt and put some characters in it.
//    FILE* file;
//    if( (file = fopen("currentD.txt", "wx")) == NULL) {
//        puts("I couldn't create file. Sorry.");
//        exit(EXIT_FAILURE);
//    }
//    fprintf(file, "This is where the current directory of execution is.");
//    if(fclose(file)) {
//        puts("Error in closing file.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Open file and echo to stdout
//    FILE* file_check;
//    if( (file_check = fopen("currentD.txt", "r")) == NULL) {
//        puts("I couldn't open the file. Sorry.");
//    }
//    char input_char;
//    while( (input_char = getc(file_check)) != EOF ) {
//        putc(input_char, stdout);
//    }
//    if(fclose(file_check)) {
//        puts("Error in closing file.");
//        exit(EXIT_FAILURE);
//    }
    
//COPY CONTENTS OF ONE FILE TO ANOTHER AND ACCEPTING COMMAND-LINE ARGUMENTS
//    FILE* input_file;
//    FILE* output_file;
//    char character_input;
////    char input_file_name[MAX_FILE_LENGTH] = argv[1];
//    char* input_file_name = malloc( 255 * sizeof(char) );
//    input_file_name = argv[1];
//    char output_file_name[MAX_FILE_LENGTH];
//    int character_count = 0;
//    
//    //Check if filename was included
//    if(argc < 2) {
//        fprintf(stderr, "Usage: %s filename\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }
//    
//    //Open file and check for success.
//    if( (input_file = fopen(input_file_name, "r")) == NULL ) {
//        fprintf(stderr, "I couldn't open the file \"%s\"\n", input_file_name);
//        exit(EXIT_FAILURE);
//    }
//    
//    //Set up output file. Here we will call it the same name but with a .red extension instead, hence - 5
//    strncpy(output_file_name, input_file_name, MAX_FILE_LENGTH - 5);
//    output_file_name[MAX_FILE_LENGTH - 5] = '\0';
//    strcat(output_file_name, ".red");
//    
//    //Open output file and check for success
//    if( (output_file = fopen(output_file_name, "w")) == NULL ) {
//        fprintf(stderr, "Can't create output file.\n");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Write to output file
//    while( (character_input = getc(input_file)) != EOF ) {
//        if((character_count++ % 3) == 0) {   //printing every 3rd character
//            putc(character_input, output_file);
//        }
//    }
//    
//    if(fclose(input_file) || fclose(output_file) ) {
//        fprintf(stderr, "Error in closing files.\n");
//        exit(EXIT_FAILURE);
//    }
    
//PRINT THE REVERSE CONTENTS OF A FILE USING FSEEK() AND FTELL()
    char file_name[255];
    char character_read;
    FILE* file;
    long last;
    
    //Get filename
    puts("Enter the name of the file to be processed below.");
    //scanf("%80s", file_content);    //--> NOT GOOD BECAUSE FILE NAMES CAN HAVE SPACES
    if( get_string_input(file_name, 255) == NULL ) {
        puts("Failed to read filename. Sorry.");
        exit(EXIT_FAILURE);
    }
    
    //Open file.
    if( (file = fopen(file_name, "rb")) == NULL ) {
        puts("Failed to open file. Sorry.");
        exit(EXIT_FAILURE);
    }
    
    fseek(file, 0L, SEEK_END);  //Go to end of file
    last = ftell(file);
    for(int i=1L; i <= last; i++) {
        fseek(file, -i, SEEK_END);
        character_read = getc(file);
        if( (character_read != CTRL_Z) && (character_read != '\r') ) {  //MS-DOS files
            putchar(character_read);
        }
    }
    
    putchar('\n');
    fclose(file);
    
    
    return (EXIT_SUCCESS);
}

