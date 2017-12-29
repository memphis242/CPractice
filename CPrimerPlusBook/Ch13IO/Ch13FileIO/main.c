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
//    char file_name[255];
//    char character_read;
//    FILE* file;
//    long last;
//    
//    //Get filename
//    puts("Enter the name of the file to be processed below.");
//    //scanf("%80s", file_content);    //--> NOT GOOD BECAUSE FILE NAMES CAN HAVE SPACES
//    if( get_string_input(file_name, 255) == NULL ) {
//        puts("Failed to read filename. Sorry.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Open file in READ BYTE MODE to be able to use fseek() properly
//    if( (file = fopen(file_name, "rb")) == NULL ) {
//        puts("Failed to open file. Sorry.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Set starting position
//    if( fseek(file, 0L, SEEK_END) ) {               //seek_file() now does this check block.
//        puts("Failed to use fseek() on file.");
//        exit(EXIT_FAILURE);
//    }  //Go to end of file
//    
//    last = ftell(file);
//    
//    //Start going from 1 byte before the last, because the last byte is EOF
//    for(int i=1L; i <= last; i++) {
//        seek_file(file, -i, SEEK_END);
//        character_read = getc(file);
//        if( (character_read != CTRL_Z) && (character_read != '\r') ) {  //MS-DOS files
//            putchar(character_read);
//        }
//    }
//    putchar('\n');
//    
//    //Close file
//    close_file(file);
    
//PREVIOUS PROGRAM BUT WITH FGETPOS() AND FSETPOS() --> NOT SO STRAIGHTFORWARD. NEEDS WORK TO SET POSITION TO LAST BYTE.
//    char file_name[255];
//    char character_read;
//    FILE* file;
//    long last;
//    
//    //Get filename
//    puts("Enter the name of the file to be processed below.");
//    //scanf("%80s", file_content);    //--> NOT GOOD BECAUSE FILE NAMES CAN HAVE SPACES
//    if( get_string_input(file_name, 255) == NULL ) {
//        puts("Failed to read filename. Sorry.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Open file in READ BYTE MODE to be able to use fseek() properly
//    if( (file = fopen(file_name, "rb")) == NULL ) {
//        puts("Failed to open file. Sorry.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Set starting position
//    fpos_t file_position;
//    
//    if( fsetpos(file, file_position) ) {
//        puts("Failed to use fsetpos() on file.");
//        exit(EXIT_FAILURE);
//    }  //Go to end of file
//    
//    last = ftell(file);
//    
//    //Start going from 1 byte before the last, because the last byte is EOF
//    for(int i=1L; i <= last; i++) {
//        seek_file(file, -i, SEEK_END);
//        character_read = getc(file);
//        if( (character_read != CTRL_Z) && (character_read != '\r') ) {  //MS-DOS files
//            putchar(character_read);
//        }
//    }
//    putchar('\n');
//    
//    //Close file
//    close_file(file);
    
//READING THE BINARY FORM OF A LIBREOFFICE WRITER DOCUMENT --> DANGIT. DIDN'T WORK :(
//    FILE* file;
//    
//    //Open file
//    if( (file = fopen("C Notes.odt", "rb")) == NULL ) {
//        puts("Failed to open document.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Echo binary data up to 100th character
//    int count = 0;
//    char input_char;
//    while( (count++ < 100) && (input_char = getc(file)) ) {
//        putchar(input_char);
//    }
//    new_line();
//    
//    if( fclose(file) ) {
//        puts("Failed to close file");
//        exit(EXIT_FAILURE);
//    }
    
//WRITING CHAR DATA TO A FILE THEN ECHOING IT TO STDOUT
//    FILE *file;
//    
//    //Create and open file.
//    if( (file = fopen("char_sample", "w+")) == NULL ) { //FINALLY SOLVED PROBLEM: "w" IS JUST WRITE. "w+" IS READ/WRITE.
//        puts("Failed to open file.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Write char data.
//    int i = 0;
//    while( i < 20 ) {
//        putc('a', file);
//        i++;
//    }
//    
//    //Reset active position in stream to start.
//    rewind(file);
//    
//    //Echo data to stdout
//    char input_char;
//    while( (input_char = getc(file)) != EOF ) {
//        putchar(input_char);
//    }
    
//WRITING AND THEN READING BINARY DATA FROM A CREATED FILE
//    FILE* file;
//    
//    //Create and open file.
//    if( (file = fopen("sample_b_data", "w+")) == NULL ) {
//        puts("Failed to create and open file.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Write data to it.
//    char char_data[11] = "This is d.";
//    double double_data[6] = { 5.2, 1.00, 2.45, 12.6, 1982.11, 0.001 };
//    int int_data[1] = { 9000 };
//    
//    fwrite(char_data, sizeof(char), 11, file);
//    fwrite(double_data, sizeof(double), 6, file);
//    fwrite(int_data, sizeof(int), 1, file);
//    
//    //Echo data from file to stdout
//    rewind(file);
//    
//    puts("The character portion:");
//    char char_buff[11];
//    if( fread(char_buff, sizeof(char), 11, file) == 0 ) {
//        puts("Failed to read char from file.");
//        
//        if( feof(file) ) {
//            puts("It was an EOF.");
//        }
//        if ( ferror(file) ) {
//            puts("It was not an EOF.");
//        }
//        
//        exit(EXIT_FAILURE);
//    }
//    puts(char_buff);
//    new_line();
//    
//    puts("The double portion:");
//    double double_buff[6];
//    if( fread(double_buff, sizeof(double), 6, file) == 0 ) {
//        puts("Failed to read double from file.");
//        exit(EXIT_FAILURE);
//    }
//    print_array_double(double_buff, 6);
//    new_line();
//    
//    puts("The integer portion:");
//    int int_buff[1];
//    if( fread(int_buff, sizeof(int), 1, file) == 0 ) {
//        puts("Failed to read int from file.");
//        exit(EXIT_FAILURE);
//    }
//    print_array_int(int_buff, 1);
//    new_line();
//    
//    if( getc(file) == EOF ) {
//        puts("SUCCESS!");
//    }
    
//READING CONTENT OF SOURCE FILES AND APPENDING TO AN OUTPUT FILE
//    FILE *source, *destination;
//    int files_read = 0;
//    char source_name[255];
//    char destination_name[255];
//    
//    //Get destination file name.
//    puts("Enter the name of the destination file below.");
//    get_string_input(destination_name, 255);
//    
//    //Open file.
//    //Clear File.
//    destination = fopen(destination_name, "w");
//    close_file(destination);
//    //Start
//    if( (destination = fopen(destination_name, "a+")) == NULL ) {
//        puts("Unable to open/create destination file.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Set buffer for file
//    if( setvbuf(destination, NULL, _IOFBF, 4096) ) {
//        puts("Unable to create buffer for destination file.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Get source files and start appending.
//    puts("Enter name of source file (empty line to quit).");
//    while( get_string_input(source_name, 255) && (source_name[0] != '\0') ) {
//        //If same file...
//        if(!strcmp(source_name, destination_name)) {
//            puts("Can't append file to itself.");
//            puts("Try again.");
//            continue;
//        } else if( (source = fopen(source_name, "r")) == NULL ) {
//            puts("Can't open source file.");
//            puts("Try again.");
//            continue;
//        } else {
//            if( setvbuf(source, NULL, _IOFBF, 4096) ) {
//                puts("Could not set buffer for source file.");
//                close_file(source);
//                continue;
//            }
//            
//            append(source, destination);
//            
//            if( ferror(source) ) {
//                puts("There was an error reading the file.");                
//                puts("Try again.");
//                close_file(source);
//                continue;
//            }
////            else if( feof(source) ) {
////                puts("EOF reached.");
////            }
//            
//            close_file(source);
//            files_read++;
//            puts("File appended.");
//            new_line();
//            puts("Next.");
//        }
//    }
//    
//    //Reset active positive of destination stream to start.
//    rewind(destination);
//    
//    //Echo destination stream to stdout
//    char input_char;
//    while( (input_char = getc(destination)) != EOF ) {
//        putchar(input_char);
//    }
    
//RANDOM ACCESS IN BINARY FILES
    double numbers[1000];
    double val;
    int index;
    const char *file_name = "numbers.dat";
    long position;
    FILE *file;
    
    //Initialize double array
    fill_double_array(numbers, 1000, 0, 10000, 0.0523);
    
    //Create and open file
    if( (file = fopen(file_name, "wb")) == NULL ) {
        puts("Could not create/open file.");
        exit(EXIT_FAILURE);
    }
    
    //Write array to file.
    fwrite(numbers, sizeof(double), 1000, file);
    
    //Close file so you can switch mode to read-only.
    close_file(file);
    
    //Open file again as read mode
    if( (file = fopen(file_name, "rb")) == NULL ) {
        puts("Could not reopen file.");
        exit(EXIT_FAILURE);
    }
    
    printf("Enter a number between 0 to 999: ");
    while( (scanf("%d", &index) == 1) && (index > 0) && (index < 999) ) {
        position = (long) (index * sizeof(double));
        fseek(file, position, SEEK_SET);
        fread(&val, sizeof(double), 1, file);
        printf("The value there is: %.4f", val);
        new_line();
        printf("Another one: ");
    }
    
    //Create text-readable version
    FILE *text_file;
    char *text_file_name = "numbers.txt";
    
    if( (text_file = fopen(text_file_name, "w")) == NULL ) {
        puts("Failed to create text file.");
        exit(EXIT_FAILURE);
    }
    
    rewind(file);
    double double_val;
    char string_val[50];
    while( fread(&double_val, sizeof(double), 1, file) ) {
//        printf("%.5f ", double_val);
        sprintf(string_val, "%.4f ", double_val);
//        fputs(string_val, text_file);
        if( fwrite(string_val, sizeof(char), strlen(string_val), text_file) == 0 ) {
            puts("Failed to write to text file.");
            exit(EXIT_FAILURE);
        }
    }
    
    puts("Done!");
    
    return (EXIT_SUCCESS);
}

