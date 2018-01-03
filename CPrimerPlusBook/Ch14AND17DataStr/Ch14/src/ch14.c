/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ch1to10.h"
#include "ch11.h"

#include <stdalign.h>
    
#define MAXTITL 50
#define MAXAUTH 50
#define MAXBKS 20
#define NAMEMAX 20
#define MAXCOUNT 10
#define MAXITEMS 10
#define HIDDENLEN 6

typedef struct {
    char title[MAXTITL];
    char author[MAXAUTH];
    float value;
} BOOK;

typedef struct {
    char name[NAMEMAX];
    float value;
} UTENSIL;

typedef struct {
    double first_val;
    int second_val;
    char third_val;
} RAND;

typedef struct flexible_struct {
    char name[20];
    int random_val;
    double flex_double_arr[];
} FLEX;

typedef union {
    BOOK book_info;
    UTENSIL utensil_info;
} SCHOOLITEMU;

typedef enum { book = 0, utensil = 1 } ITEMTYPE;   //Even though those assigned values are default, just making it clear.

typedef struct {
    ITEMTYPE type;
    SCHOOLITEMU current_item;
} SCHOOLITEMS;

typedef enum pbformat { format0, format1, format2, format3 } PBFORMAT;

typedef void (*PRINTBOOKFUNC)(const BOOK *);

typedef struct {
    char charval;
    alignas(8) int intval;
} DATA;


void print_utensil(const UTENSIL *ut_ptr) {
    printf("%s at $%.2f\n",
            ut_ptr->name, ut_ptr->value);
}

void print_rand(const RAND *rand_ptr) {
    printf("Double Value: %f, Integer Value: %d, Character Value: %c\n",
            rand_ptr->first_val, rand_ptr->second_val, rand_ptr->third_val);
}

void print_flex(const FLEX *flex_ptr, int size_of_flex) {
    printf("Name: %s, Random Value: %d, Double Array: ",
            flex_ptr->name, flex_ptr->random_val);
    print_array_double(flex_ptr->flex_double_arr, size_of_flex);
}

void print_book_f0(const BOOK * book_ptr) {
    printf("%s by %s: $%.2f\n",
            book_ptr->title, book_ptr->author, book_ptr->value);
}

void print_book_f1(const BOOK *book_ptr) {
    printf("%s:%s:$%.2f\n",
            book_ptr->title, book_ptr->author, book_ptr->value);
}
    
void print_book_f2(const BOOK *book_ptr) {
    printf("%s:%s:$%.2f\n",
            book_ptr->author, book_ptr->title, book_ptr->value);
}
    
void print_book_f3(const BOOK *book_ptr) {
    printf("%.2f:%s:%s\n",
            book_ptr->value, book_ptr->author, book_ptr->title);
}
    
void print_book(PRINTBOOKFUNC func, const BOOK *book_ptr) {
    (*func)(book_ptr);
}

void sethidden(DATA *datastruct, char hidden_message[HIDDENLEN]) {
    char *charval = ( (char *) datastruct ) + 1;
//    puts("charval pointer made.");
    
    for(int i=0; i<HIDDENLEN; i++) {
//        if( i == 8 ) {  //Skip intval
//            charval += 4;
//        }
        putchar(hidden_message[i]);
        *charval = hidden_message[i];
//        puts("charval value set.");
        charval += i;
    }
    
    new_line();
//    puts("Success.");
}

char * gethidden(const DATA *datastruct) {
    const char *character = ( (char *) datastruct ) + 1;
    char hidden_message[HIDDENLEN];
    
    for(int i=0; i<HIDDENLEN; i++) {
//        if( i == 7 ) {
//            character += 5;
//        }
        
        hidden_message[i] = *character;
        character += i;
    }
    
    printf("Hidden message in DATA struct: %s\n", hidden_message);
    
    return hidden_message;
}

void print_data_normal(const DATA *datastruct) {
    printf("DATA struct charval: %c, intval: %d\n", datastruct->charval, datastruct->intval);
}
