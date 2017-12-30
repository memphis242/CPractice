/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: abdullah
 *
 * Created on December 29, 2017, 5:53 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "src/ch1to10.h"
#include "src/ch11.h"
#include "src/ch14.h"

/*
 * 
 */
int main(int argc, char** argv) {

//FIRST USE OF STRUCT!
//    struct book library;
//    
//    printf("Please enter the book title: ");
//    get_string_input(library.title, MAXTITL);
//    
//    printf("Please enter the author: ");
//    get_string_input(library.author, MAXAUTH);
//    
//    printf("Please enter cost of book: ");
//    scanf("%f", &library.value);
//    
//    //Initializing a book struct
//    struct book book2 = {"Harry Potter", "J.K. Rowling", 19.99 };
//    
//    new_line();
//    printf("%s by %s: $%.2f\n", library.title, library.author, library.value);
//    printf("%s by %s: $%.2f\n", book2.title, book2.author, book2.value);
    
//POINTERS TO STRUCTURES
//    struct book book1 = { "Harry Potter", "J.K. Rowling", 19.99 };
//    struct book *struc_ptr = &book1;
////    char (*str1_ptr) [MAXTITL];
////    char (*str2_ptr) [MAXAUTH];
////    float *float_ptr;
//    
//    printf("%s by %s: $%.2f\n", struc_ptr -> title, (*struc_ptr).author, book1.value);
//    new_line();
//    //Navigating through a structure by typecasting pointers to corresponding values --> DOESN'T WORK EASILY WITH STRINGS
////    printf("%s by %s: $%.2f\n", str1_ptr = (char* [MAXTITL]) (struc_ptr), str2_ptr = (char* [MAXAUTH]) (str1_ptr + 1),
////                                *(float_ptr = (float*) (str2_ptr)));
//    struct rand rand1 = { 5.32, 27, 'c' };
//    
//    struct rand *rand_struct_ptr = &rand1;
//    double *double_ptr = &rand1.first_val;  //--> CAN'T TYPE CAST STRUCTURE POINTER TO PRIMITIVE TYPE POINTER, SO THIS INSTEAD.
//    int *int_ptr = (int*)(double_ptr + 1);
//    char *char_ptr = (char*) (int_ptr + 1);
//    
//    printf("First Value: %f, Second Value: %d, Third Value: %c\n", *(double_ptr), *(int_ptr), *(char_ptr));
//    printf("Address of rand1 Structure: %p\nAddress of double Value: %p\nAddress of int Value: %p\nAddress of char Value: %p\nAddress of rand_struct_ptr + 1: %p\n",
//            rand_struct_ptr, double_ptr, int_ptr, char_ptr, rand_struct_ptr + 1);
//    
//    new_line();
//    printf("Value at Address %p: %c\nValue at Address %p: %c\nValue at Address %p: %c\nNext Address %p should be same as rand_struct_ptr + 1: %p",
//            char_ptr + 1, *(char_ptr + 1), char_ptr + 2, *(char_ptr + 2), char_ptr + 3, *(char_ptr + 3), char_ptr + 4, rand_struct_ptr + 1);
    
//ASSIGNING STRUCTURES TO EACH OTHER
//    struct rand rand1 = { 5.32, 22, 'a' };
//    //struct rand rand2 = { 2.22, 11, 'b' }; --> Next statement doesn't work with this.
//    struct rand rand2 = rand1;
//    
//    print_rand("rand1", &rand1);
//    print_rand("rand2", &rand2);
    
//USING FLEXIBLE ARRAY STRUCTURES
//    struct flexible_struct *flex1 = malloc( sizeof(struct flexible_struct) + (5 * sizeof(double)) );
//    struct flexible_struct *flex2 = malloc( sizeof(struct flexible_struct) + (10 * sizeof(double)) );
//    
//    srand(time(NULL));
//    
//    fill_char_array(flex1->name, 20);
//    flex1->random_val = rand() % 100;
//    fill_double_array(flex1->flex_double_arr, 5, 0, 100, 0.0295);
//    
//    fill_char_array(flex2->name, 20);
//    flex2->random_val = rand() % 100;
//    fill_double_array(flex2->flex_double_arr, 10, 25.2, 37.4, 0.01);
//    
//    print_flex("flex1", flex1, 5);
//    print_flex("flex2", flex2, 10);
    
//SAVING STRUCTURES TO FILES
    FILE* file;
    struct book library[MAXBKS];
    char book_number[MAXBKS + 8];
    int count = 0, new_books = 0;
    int file_count;
    int size = sizeof(struct book);
    
    //OPEN FILE.
    if( (file = fopen("book.dat", "a+b")) == NULL ) {
        puts("Failed to create book.dat file.");
        exit(EXIT_FAILURE);
    }
    
    //GET DATA FOR BOOKS.
    //Show current data. This also sets active position in stream to end.
    while( (count < MAXBKS) && (fread(&library[count], size, 1, file) == 1) ) {
        if(count == 0) {
            puts("Current content of book.dat");
        }
        
        sprintf(book_number, "Book %d: ", count);
        print_book(book_number, &library[count]);
        
        count++;
    }
    
    file_count = count;
    
    if(file_count == MAXBKS) {
        puts("The book.dat file is full.");
        exit(EXIT_FAILURE);
    }
    
    //Get information.
    puts("The below will ask information on the books. Press enter to quit.");
    printf("Book Title: ");
    while( (count < MAXBKS) && (get_string_input(library[count].title, MAXTITL) != NULL) && (library[count].title[0] != '\0') ) {
        printf("Author: ");
        get_string_input(library[count].author, MAXAUTH);
        printf("Price: ");
        scanf("%f", &library[count].value);
        while( getchar() != '\n' ) {
            continue;
        }
        count++;
        new_books++;
        new_line();
        
        if(count < MAXBKS) {
            puts("Next book.");
            printf("Book Title: ");
        }
    }
    
    //APPEND DATA TO FILE.
    if(new_books == 0) {
        puts("No new books added.");
        return (EXIT_SUCCESS);
    }
    
    int index = 0;
    while( (index < new_books) && fwrite(&library[index], size, 1, file) ) {
        index++;
    }
    
    puts("Done.");
    
    return (EXIT_SUCCESS);
}

