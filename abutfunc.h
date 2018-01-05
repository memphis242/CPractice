#ifndef ABUTFUNC_H_INCLUDED
#define ABUTFUNC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>   //Note that the stdint.h header file is included in the inttypes header.
#include <string.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>    //This includes bool as an alias for _Bool and true and false as symbolic constants for 1 and 0, resp.
#include <iso646.h>
#include <time.h>
#include <stdarg.h>

#define DENSITY 62.4    //average human density in lbs per cubic feet
#define PAGES 959   //sample value for practicing format modifiers.
#define ADJUST 7.31 //this is for the first program of Chapter 5 concerning shoe sizes
#define SPACE ' '
#define MONTHS 12
#define ROWS 4
#define COLUMNS 4
#define LINE 80
#define MSG "I am a symbolic string message."
#define MAXLENGTH 81
#define STR_LIM 50
#define CHAR_ARR_LIM 4
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



extern void print_example(int num);    //<-- This is the prototype of the function; this is in the form of ANSI C and beyond.

extern int print_character_x_times(char c, int x);

extern void display(char character_to_print, int rows, int columns);

extern void skip_to_next_line(void);

extern void trace_memory_addresses(int sample_value);

extern void other_location(int sample2);

extern void swap_values(int * x, int * y);

//int array_size(int array_to_be_sized[]);

extern int sum_int_array(int* arr, int arr_size);

extern void print_line(void);

extern void newline(void);

extern void print_title(const char* title);

extern void eatline();

extern void interpret_float_bytes_as_characters(float* val);

extern void interpret_char_bytes_as_float();

extern void print_ASCII_vals_of_bytes(const char* arr, int arr_size);

extern void print_array_int(const int arr[], int arr_size);

extern void print_array_double(const double arr[], int arr_size);

extern void modify_array_double(double* arr, int arr_size);

extern void print_2D_array_int(const int (* arr) [COLUMNS], int rows);   //NOTE THE PARAMETER INDICATES POINTER TO CONSTANT INT ARRAYS OF COLUMNS ELEMENTS

extern void sum_rows_int(int (* arr) [COLUMNS], int rows);

extern void sum_columns_int(int arr[][COLUMNS], int rows);

extern void sum_total_2D_int(int (* arr) [COLUMNS], int rows, int* total);

extern int sum_2D_vla_int(int rows, int columns, const int arr[rows][columns]);

extern float sum_float_array(float arr[], int size);

extern double sum_double_array(double arr[], int size);

extern void fill_int_array(int *arr, int size, int min, int max);

extern void fill_double_array(double *arr, int size, double min, double max, double diff);

extern void test_distribution_d(double arr[], int arrsize, const double minVal, const double maxVal);

extern void fill_char_array(char *arr, int size);

extern int sumints(int num_of_items, ...);

extern char* get_string_input(char* str, int size_of_str);

//char* trim_string(char* str);     //NEEDS WORK

extern void trim_string_to_size(char* str, int desired_size);

extern char* str_safe_conc(char* str1, const char* str2, int size_of_1);

extern void sort_str_alph(char* strings[], int num_of_strings);

extern void print_utensil(const UTENSIL *ut_ptr);
    
extern void print_rand(const RAND *rand_ptr);
    
extern void print_flex(const FLEX *flex_ptr, int size_of_flex);
   
extern void print_book_f0(const BOOK *book_ptr);
    
extern void print_book_f1(const BOOK *book_ptr);
    
extern void print_book_f2(const BOOK *book_ptr);
    
extern void print_book_f3(const BOOK *book_ptr);
    
extern void print_book(PRINTBOOKFUNC, const BOOK *book_ptr);

extern char *itobs(int n, char *bitstring);
    
//Prints in big-endian form
extern void printbits(const char *bitstring);
    
extern void setbit(int *mask, int index);
    
//Assumes boolean array is little-endian!
extern int set_onebyte_mask(bool bits[]);
    
//Assumes boolean array is little-endian!
extern int set_twobyte_mask(bool bits[]);
    
extern void printbitsofint(int number);



#endif
