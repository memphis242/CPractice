#ifndef CH1TO10_H_INCLUDED
#define CH1TO10_H_INCLUDED

#define DENSITY 62.4    //average human density in lbs per cubic feet
#define PAGES 959   //sample value for practicing format modifiers.
#define ADJUST 7.31 //this is for the first program of Chapter 5 concerning shoe sizes
#define SPACE ' '
#define MONTHS 12

void print_example(int num);    //<-- This is the prototype of the function; this is in the form of ANSI C and beyond.

int print_character_x_times(char c, int x);

void display(char character_to_print, int rows, int columns);

void skip_to_next_line(void);

void trace_memory_addresses(int sample_value);

void other_location(int sample2);

void swap_values(int * x, int * y);

//int array_size(int array_to_be_sized[]);

int sum_int_array(int* arr, int arr_size);

#endif // CH1TO10_H_INCLUDED
