#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ch1to10.h"
#include "ch11.h"

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
//    char arr[] = MSG;
//    const char* ptr = MSG;
//
//    printf("Address of \"I am a symbolic string message.\": %p\n", "I am a symbolic string message.");
//    printf("Address of MSG: %p\n", MSG);
//    printf("Address of arr: %p\n", arr);
//    printf("Address of ptr: %p\n", ptr);

//QUICK REMINDER OF POINTER NOTATION WITH ARRAYS AND INTIIALIZATION
//    int* int_arr_ptr = (int[4]) {2, 4, 1, 3};
//    print_array(int_arr_ptr, 4);
//
//    const int (*int_2D_arr_ptr) [4] = (int[2][4]) { {1, 2, 3, 4}, {1, 2, 3, 4} }; //WORKS BECAUSE THIS IS A LITERAL
//    print_2D_array_int(int_2D_arr_ptr, 2);
//
//    printf("Size of int_arr_ptr: %zd\n", sizeof int_arr_ptr);
//    printf("Size of int_2D_arr_ptr: %zd\n", sizeof int_2D_arr_ptr);
//
////    int int_arr[2][4] = { {2, 2, 2, 2}, {4, 4, 4, 4} };
////    const int (* ptr_to_int_arr) [4] = int_arr;
//
//    //const int (* ptr_to_int_arr) [4] = { {2, 2, 2, 2}, {4, 4, 4, 4} };
//    //{ {2, 2, 2, 2}, {4, 4, 4, 4} };
////    for(int i=0; i<2; i++) {
////        for(int j=0; j<4; j++) {
////
////            if(i == 0) {
////                ptr_to_int_arr[i][j] = 2;
////            } else {
////                ptr_to_int_arr[i][j] = 4;
////            }
////
////        }
////    }
//
////    print_2D_array_int(int_arr, 2);
////    print_2D_array_int(ptr_to_int_arr, 2);
////
////    printf("\nSize of 2D Integer Array: %zd\n", sizeof int_arr);
////    printf("Size of Pointer to 4-elemnt Integer Arrays: %zd\n", sizeof ptr_to_int_arr);

//MAKING AN ARRAY OF STRINGS
//    const char *arr_of_ptr_to_str_lit[CHAR_ARR_LIM] = { "Hey everyone.", "This. Is. SPARTAAAA!!!",
//                                             "Well carry on then.", "To infinity, and beyond!" };   //Array of pointers to string literals
//    char arr_of_char_arr[CHAR_ARR_LIM][STR_LIM] = { "Hey everyone.", "This. Is. SPARTAAAA!!!",
//                                             "Well carry on then.", "To infinity, and beyond!" };   //Array of char arrays
//    const char (*ptr_to_char_arrs) [55] = (char [4][55]) { {'H', 'e', 'y', ' ', 'e', 'v', 'e', 'r', 'y', 'o', 'n', 'e', '.', '\0'},
//                                        {'T', 'h', 'i', 's', '.', ' ', 'I', 's', '.', ' ', 'S', 'P', 'A', 'R', 'T', 'A', 'A', 'A', 'A', '!', '!', '!', '\0'},
//                                        {'W', 'e', 'l', 'l', ' ', 'c', 'a', 'r', 'r', 'y', ' ', 'o', 'n', ' ', 't', 'h', 'e', 'n', '.', '\0'},
//                                        {'T', 'o', ' ', 'I', 'n', 'f', 'i', 'n', 'i', 't', 'y', ',', ' ', 'a', 'n', 'd', ' ', 'b', 'e', 'y', 'o', 'n', 'd', '!', '\0'} };   //Pointer to char arrays of size STR_LIM
//
////    const char* (*ptr_to_str_ptr) [55] = (char[4][55]) { "Hey everyone.", "This. Is. SPARTAAAA!!!",
////                                        "Well carry on then.", "To infinity, and beyond!" };
//
//
//    printf("Let's compare approaches:\n\n");
////    printf("%-30s%-30s\n", "Array of Pointers to String Literals", "Array of char arrays");
//    printf("%-55s%-55s%-55s\n", "Array of Pointers to String Literals", "Array of char arrays", "Pointer to 55-length char arrays");
//
////    for(int i=0; i<CHAR_ARR_LIM; i++) {
////        printf("%-30s%-30s\n", arr_of_ptr_to_str_lit[i], arr_of_char_arr[i]);
////    }
//
//    for(int i=0; i<CHAR_ARR_LIM; i++) {
//        printf("%-55s%-55s%-55s\n", arr_of_ptr_to_str_lit[i], arr_of_char_arr[i], ptr_to_char_arrs[i]);
//    }
//
//    printf("\nSize of Array of Pointers to String Literals: %zd\n", sizeof arr_of_ptr_to_str_lit);
//    printf("Size of Array of Char Arrays: %zd\n", sizeof arr_of_char_arr);
//    printf("Size of Pointer to 55-length Char Arrays: %zd\n", sizeof ptr_to_char_arrs);

//THE GETS() FUNCTION
//    char new_string[100];     //ALLOCATE MEMORY FOR STRING
//
//    puts("Please enter a string less than 50 characters.");
//    gets(new_string);
//
//    printf("Your string using printf(): ");
//    printf("%s\n", new_string);
//    printf("Your string using puts(): ");
//    puts(new_string);

//THE FGETS() AND FPUTS() FUNCTIONS
//    char new_string[100];     //ALLOCATE MEMORY FOR STRING
//
//    puts("Please enter a string up to a 100 characters.");
//    fgets(new_string, 100, stdin);
//
//    printf("\nThe string you entered: ");
//    fputs(new_string, stdout);

//HOW TO SHOW YOUR SYSTEM USES NEW-LINE BUFFERING --> NEEDS WORK
//A CONSEQUENCE OF FPUTS() NOT APPENDING A NEWLINE CHARACTER (WORKING PAST THE NUMBER OF CHARACTERS REQUESTED OUT OF INPUT)
//    char input_string[2];     //ALLOCATE MEMORY FOR STRING
////    int number_of_loops_before_complete_output
//
//    while ( (fgets(input_string, 2, stdin) != NULL) && (input_string[0] != '\n')) {
//        fputs(input_string, stdout);
//    }

//A COMPLETE STRING INPUT BLOCK OF CODE IN C THAT ENSURES CHARCATER-LIMITS ARE RESPECTED
//    char input_string[10];  //ALLOCATE MEMORY FOR STRING
//    int i=0;
//
//    while( (fgets(input_string, 10, stdin) != NULL) && (input_string[0] != '\n') ) {    //While the input is valid and the first character in the input isn't a newline
//
//        while( (input_string[i] != '\n') && (input_string[i] != '\0') ) {   //Advance to newline or null character
//            i++;
//        }
//
//        if(input_string[i] == '\n') {   //If we've gotten to the end of the line, discard the newline character and replace with null character.
//            input_string[i] = '\0';
//        } else {    //Our char array ended because the input string was too long, so skip over the extra characters into a new line.
//            while( getchar() != '\n') {
//                continue;
//            }
//        }
//
//        puts(input_string);
//    }

//USING THE PREVIOUS SECTION AS A FUNCTION TO READ IN A SINGLE INPUT STRING
//    char str[25];   //ALLOCATE MEMORY FOR STRING
//
//    get_string_input(str, 25);
//
//    puts(str);

//USING THE STRCAT() FUNCTION
//    char addon[11] = "\tLOOOOOOOL";
//    char str_input[100];
//
//    get_string_input(str_input, 100);
//    strcat(str_input, addon);
//
//    puts(str_input);

////TESTING OUT WHAT EXACTY STRLEN() RETURNS
//    char str[100] = "1";      //--> OK. SO, NOTE THAT THE DECLARATION ALLOCATES 100 BYTES FOR STORAGE, BUT THE STRING LITERAL IS JUST 2
                                //BYTES PLUS THE 8 BYTES FOR THE POINTER TO IT. Actually, that was kind of obvious if you think about its implemntation...
//    printf("%zd", strlen(str));

//USING SPRINTF()   --> I'VE BEEN WAITING FOR A FUNCTION LIKE THIS!
//    char first_name[20];
//    char last_name[30];
//    int val;
//
//    printf("Enter your first name: ");
//    get_string_input(first_name, 20);
//    printf("Enter your last name: ");
//    get_string_input(last_name, 30);
//    printf("Enter some number: ");
//    scanf("%d", &val);
//    puts("");
//
//    char output_str[100];
//    sprintf(output_str, "Oh %s %s, you are NUMBER %d!", first_name, last_name, val);
//
//    puts(output_str);

//SORTING STRINGS ALPHABETICALLY
//    printf("Please enter some strings, or just press enter to stop. You are allowed 7 strings.\n");
//
//    char strings[7][100];
//    char* ptrs[7];
//    int num_of_strings = 0;
//
//    //The first condition is to ensure user isn't inputting more strings the strings[][] can handle. Second is to write the user
//    //input into the strings[][] array, and ensuring that it is valid. Third is the quit/stop character check.
//    while( (num_of_strings < 7) && (get_string_input(strings[num_of_strings], 100)) && strings[num_of_strings][0] ) {
//        ptrs[num_of_strings] = strings[num_of_strings];
//        num_of_strings++;
//    }
//
//    sort_str_alph(ptrs, num_of_strings);
//
//    printf("\nHere is the sorted list.\n");
//    for(int i=0; i < num_of_strings; i++) {
//        puts(ptrs[i]);
//    }
//
//    puts("");

    return 0;
}
