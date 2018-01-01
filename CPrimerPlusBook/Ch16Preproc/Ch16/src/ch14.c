/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ch1to10.h"
#include "ch11.h"

#define MAXTITL 50
#define MAXAUTH 50
#define MAXBKS 20
#define NAMEMAX 20
#define MAXCOUNT 10
#define MAXITEMS 10

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
