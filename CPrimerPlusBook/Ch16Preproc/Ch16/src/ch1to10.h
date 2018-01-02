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

#endif // CH1TO10_H_INCLUDED
