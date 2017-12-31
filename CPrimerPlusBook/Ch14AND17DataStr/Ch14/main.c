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
//    BOOK library;
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
//    BOOK book2 = {"Harry Potter", "J.K. Rowling", 19.99 };
//    
//    new_line();
//    printf("%s by %s: $%.2f\n", library.title, library.author, library.value);
//    printf("%s by %s: $%.2f\n", book2.title, book2.author, book2.value);
    
//POINTERS TO STRUCTURES
//    BOOK book1 = { "Harry Potter", "J.K. Rowling", 19.99 };
//    BOOK *struc_ptr = &book1;
////    char (*str1_ptr) [MAXTITL];
////    char (*str2_ptr) [MAXAUTH];
////    float *float_ptr;
//    
//    printf("%s by %s: $%.2f\n", struc_ptr -> title, (*struc_ptr).author, book1.value);
//    new_line();
//    //Navigating through a structure by typecasting pointers to corresponding values --> DOESN'T WORK EASILY WITH STRINGS
////    printf("%s by %s: $%.2f\n", str1_ptr = (char* [MAXTITL]) (struc_ptr), str2_ptr = (char* [MAXAUTH]) (str1_ptr + 1),
////                                *(float_ptr = (float*) (str2_ptr)));
//    RAND rand1 = { 5.32, 27, 'c' };
//    
//    RAND *rand_struct_ptr = &rand1;
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
//    RAND rand1 = { 5.32, 22, 'a' };
//    //RAND rand2 = { 2.22, 11, 'b' }; --> Next statement doesn't work with this.
//    RAND rand rand2 = rand1;
//    
//    print_rand("rand1", &rand1);
//    print_rand("rand2", &rand2);
    
//USING FLEXIBLE ARRAY STRUCTURES
//    FLEX *flex1 = malloc( sizeof(FLEX) + (5 * sizeof(double)) );
//    FLEX *flex2 = malloc( sizeof(FLEX) + (10 * sizeof(double)) );
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
//    FILE* file;
//    BOOK library[MAXBKS];
//    char book_number[MAXBKS + 8];
//    int count = 0, new_books = 0;
//    int file_count;
//    int size = sizeof(BOOK);
//    
//    //OPEN FILE.
//    if( (file = fopen("book.dat", "a+b")) == NULL ) {
//        puts("Failed to create book.dat file.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //GET DATA FOR BOOKS.
//    //Show current data. This also sets active position in stream to end.
//    while( (count < MAXBKS) && (fread(&library[count], size, 1, file) == 1) ) {
//        if(count == 0) {
//            puts("Current content of book.dat");
//        }
//        
//        sprintf(book_number, "Book %d: ", count);
//        print_book(book_number, &library[count]);
//        
//        count++;
//    }
//    
//    file_count = count;
//    
//    if(file_count == MAXBKS) {
//        puts("The book.dat file is full.");
//        exit(EXIT_FAILURE);
//    }
//    
//    //Get information.
//    puts("The below will ask information on the books. Press enter to quit.");
//    printf("Book Title: ");
//    while( (count < MAXBKS) && (get_string_input(library[count].title, MAXTITL) != NULL) && (library[count].title[0] != '\0') ) {
//        printf("Author: ");
//        get_string_input(library[count].author, MAXAUTH);
//        printf("Price: ");
//        scanf("%f", &library[count].value);
//        while( getchar() != '\n' ) {
//            continue;
//        }
//        count++;
//        new_books++;
//        new_line();
//        
//        if(count < MAXBKS) {
//            puts("Next book.");
//            printf("Book Title: ");
//        }
//    }
//    
//    //APPEND DATA TO FILE.
//    if(new_books == 0) {
//        puts("No new books added.");
//        return (EXIT_SUCCESS);
//    }
//    
//    int index = 0;
//    while( (index < new_books) && fwrite(&library[index], size, 1, file) ) {
//        index++;
//    }
//    
//    puts("Done.");
    
//USING UNIONS AND ENUMERATIONS AND SAVING IN A FILE --> NEEDS A LOT OF WORK
    FILE *file;
    const char file_name[] = "schoolinv.dat";
    SCHOOLITEMS inventory[MAXITEMS];   //Representing the school inventory of a student
    int item_count = 0, book_count = 0, ut_count = 0;
    
    //OPEN FILE
    if( (file = fopen(file_name, "a+")) == NULL ) {
        puts("Failed to open/create schoolinv.dat.");
        exit(EXIT_FAILURE);
    }
    
    //READ CURRENT STATE OF FILE
    //The following assumes that only book or utensil structures are stored in the inventory.
    puts("Current inventory.");
    while( (item_count < MAXITEMS) && (fread(&inventory[item_count], sizeof(SCHOOLITEMS), 1, file) == 1) ) {
        //THE FOLLOWING METHOD OF TYPE CHECKING OF UNIONS IS CALLED UNION TAGGING
        //If book
        if( inventory[item_count].type == book ) {
            book_count++;
            
            print_book(print_book_f0, &inventory[item_count].current_item.book_info);
            
            item_count++;
        
            //Else utensil
        } else if( inventory[item_count].type == utensil ) {
            ut_count++;
            
            print_utensil(&inventory[item_count].current_item.utensil_info);
            
            item_count++;
            
        } else {
            puts("Corrupted file.");
            exit(EXIT_FAILURE);
        }
    }
    
    if(item_count == 0) {
        puts("Inventory was empty.");
    } else if(item_count == MAXITEMS) {
        puts("Inventory is full.");
        goto exit;
    }
    new_line();
    
    
    
    //GET NEW ITEMS
    int prev_item_count = item_count;   //Will use to check if new items added or not
    
    ITEMTYPE user_input_en;
    int user_input = 2;  //Setting to a val that isn't 0 or 1 because need to check valid entry or not first
    int fail_count = 0;  //fail_count is to limit number of invalid tries for first question.
    char input_char;
    
    puts("Let's begin adding to the inventory.");
    fputs("First new item. A book (0) or a utensil (1)? (q to quit) ", stdout);  //Just practicing with fputs() instead of printf();
    while( item_count < MAXITEMS ) {
        //While input is invalid. --> SEEMS TO WORK EXCEPT FOR JUST ENTER '\0'
        while( (scanf("%d", &user_input) == 0) || (((user_input_en = user_input) != book) && (user_input_en != utensil)) ) {
            
            //Using this because using scanf() instead of get_string_input() because not string data input
            //and if invalid entry, scanf() leaves input in stream. Need to clear first.
            while( (input_char = getchar()) != '\n' ) {
                if( input_char == 'q' ) {  //Exit case. Assumes user ONLY entered q but would work if q was anywhere in the input stream.
                    goto exit;   //Using goto here because it would be more complicated to get out of the loops here.
                }
            }
            
            //Limiting amount of invalid tries.
            fail_count++;
            if( fail_count == MAXCOUNT ) {
                puts("Too many invalid tries. Goodbye.");
                exit(EXIT_FAILURE);
            }            

            //Try again.
            puts("Invalid entry. Please enter again.");
            fputs("Book (0) or Utensil (1)? ", stdout);
        }
        
        //Clear line because of scanf()
        while( getchar() != '\n' ) {
            continue;
        }

        //If book
        if( user_input_en == book ) {
            inventory[item_count].type = book; //VERY IMPORTANT TO ENSURE TYPE CHECKING ACTUALLY WORKS!
            
            //Get info
            printf("Book Title: ");
            get_string_input(inventory[item_count].current_item.book_info.title, MAXTITL);
            printf("Author: ");
            get_string_input(inventory[item_count].current_item.book_info.author, MAXAUTH);
            
            //Since potential false entry type, extra lines of code for this one.
            printf("Value: ");
            int val_fail_count = 0; //Limit number of invalid tries.
            while( (scanf("%f", &inventory[item_count].current_item.book_info.value) == 0) && (val_fail_count <= MAXCOUNT) ) {
                //Limiting number of invalid tries here.
                if( val_fail_count == MAXCOUNT ) {
                    puts("Too many invalid tries. Goodbye.");
                    exit(EXIT_FAILURE);
                }
                val_fail_count++;
                
                //Take up any invalid characters that scanf() left in input stream to reposition active position in input stream.
                while( getchar() != '\n' ) {
                    continue;
                }
                
                //Try again.
                puts("Invalid input. Try again.");
                printf("Value: ");
            }
            
            puts("Item successfully entered.");
            book_count++;
            item_count++;
        }
        
        //Else utensil
        else {
            inventory[item_count].type = utensil;  //VERY IMPORTANT TO ENSURE TYPE CHECKING ACTUALLY WORKS!
            
            //Get info
            printf("Utensil Name: ");
            get_string_input(inventory[item_count].current_item.utensil_info.name, NAMEMAX);
            
            //Same as for book, since potential false entry type, extra lines of code to handle that.
            printf("Utensil Value: ");
            int val_fail_count = 0; //Limit number of invalid tries.
            while( (scanf("%f", &inventory[item_count].current_item.utensil_info.value) == 0) && (val_fail_count <= MAXCOUNT) ) {
                //Limiting number of invalid tries here.
                if( val_fail_count == MAXCOUNT ) {
                    puts("Too many invalid tries. Goodbye.");
                    exit(EXIT_FAILURE);
                }
                val_fail_count++;
                
                //Take up any invalid characters that scanf() left in input stream to reposition active position in input stream.
                while( getchar() != '\n' ) {
                    continue;
                }
                
                //Try again.
                puts("Invalid input. Try again.");
                printf("Value: ");
            }
            puts("Item successfully entered.");
            ut_count++;
            item_count++;
        }
        
        new_line();
        puts("Next item");
        printf("Book (0) or Utensil (1)? (q to exit) ");
    }
    
    exit: puts("Exited.");
    
    //WRITE NEW ITEMS TO FILE (APPEND)
    if( item_count == prev_item_count ) {
        puts("No new items added.");
        return (EXIT_SUCCESS);
    } else if( book_count + ut_count != item_count ) {
        puts("Error state! Book counts and Utensil counts don't add up!");
        exit(EXIT_FAILURE);
    } else {
        new_line();
        puts("Appending new items to file...");
        
        while( (prev_item_count < item_count) && (fwrite(&inventory[prev_item_count], sizeof(SCHOOLITEMS), 1, file) == 1) ) {
            prev_item_count++;
        }
    }
    
    puts("Done.");
    
//USING FUNCTION POINTERS
//    PBFORMAT format;
//    PRINTBOOKFUNC functions[4] = { print_book_f0, print_book_f1, print_book_f2, print_book_f3 };
//    
//    //MAKE A NEW BOOK
//    BOOK newbook;
//    printf("Title: ");
//    get_string_input(newbook.title, MAXTITL);
//    printf("Author: ");
//    get_string_input(newbook.author, MAXTITL);
//    printf("Price: ");
//    while( scanf("%f", &newbook.value) != 1 ) {
//        while( getchar() != '\n') {
//            continue;
//        }
//        
//        puts("Invalid input. Try again.");        
//        printf("Price: ");        
//    }
//    
//    int userinput;
//    printf("What format would you like to use? 0, 1, 2, or 3? ");
//    while( (scanf("%d", &userinput) != 1) || (userinput > 3 || userinput < 0) ) {
//        puts("Invalid input. Try again.");
//        printf("0, 1, 2, or 3? ");
//    }
//    format = userinput;
//    print_book(functions[format], &newbook);
    
//QUICK TEST FOR PASSING STRUCTURE POINTER
//    RAND rand1 = { 5.23, 17, 'a' };
//    print_rand(&rand1);
//    
//    BOOK book1 = { "aaaaaaaaa", "ccccccccc", 19.99 };
//    print_book_f0(&book1);
    
    return (EXIT_SUCCESS);
}

