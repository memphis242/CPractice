#ifndef CH1TO10_H_INCLUDED
#define CH1TO10_H_INCLUDED

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

void print_example(int num);    //<-- This is the prototype of the function; this is in the form of ANSI C and beyond.

int print_character_x_times(char c, int x);

void display(char character_to_print, int rows, int columns);

void skip_to_next_line(void);

void trace_memory_addresses(int sample_value);

void other_location(int sample2);

void swap_values(int * x, int * y);

//int array_size(int array_to_be_sized[]);

int sum_int_array(int* arr, int arr_size);

void print_line(void);

void newline(void);

void print_title(const char* title);

void interpret_float_bytes_as_characters(float* val);

void interpret_char_bytes_as_float();

void print_ASCII_vals_of_bytes(const char* arr, int arr_size);

void print_array_int(const int arr[], int arr_size);

void print_array_double(const double arr[], int arr_size);

void modify_array_double(double* arr, int arr_size);

void print_2D_array_int(const int (* arr) [COLUMNS], int rows);   //NOTE THE PARAMETER INDICATES POINTER TO CONSTANT INT ARRAYS OF COLUMNS ELEMENTS

void sum_rows_int(int (* arr) [COLUMNS], int rows);

void sum_columns_int(int arr[][COLUMNS], int rows);

void sum_total_2D_int(int (* arr) [COLUMNS], int rows, int* total);

int sum_2D_vla_int(int rows, int columns, const int arr[rows][columns]);

void fill_int_array(int *arr, int size, int min, int max);

void fill_double_array(double *arr, int size, double min, double max, double diff);

void fill_char_array(char *arr, int size);

#endif // CH1TO10_H_INCLUDED
