#include <stdio.h>
#include <inttypes.h>   //Note that the stdint.h header file is included in the inttypes header.
#include <string.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>    //This includes bool as an alias for _Bool and true and false as symbolic constants for 1 and 0, resp.
#include <iso646.h>

void print_example(int num) {

    printf("I am a simple ");
    printf("computer.\n");
    printf("My favorite number is %d because it is first.\a", num);

}

int print_character_x_times(char c, int x) {
    int debug_check = 0;

    printf("\n");
    for(int i=0; i<x; i++){
        printf("#");
        debug_check++;
    }

    printf("\n\nSorry but OCTOTHORP RULES ALL!!!");

    return debug_check;
}

void display(char character_to_print, int rows, int columns) {
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            putchar(character_to_print);
        }
        putchar('\n');
    }
    putchar('\n');
}

void skip_to_next_line(void) {
    while(getchar() != '\n') {
        continue;
    }
}

void trace_memory_addresses(int sample_value) {
    printf("Level : %-3d Address: %p\n", sample_value, &sample_value);
    if(sample_value < 5) {
        trace_memory_addresses(sample_value + 1);
    }
}

void other_location(int sample2) {
    int sample1 = sample2;

    printf("In other_location(), sample1 = %d and &sample1 = %p\n", sample1, &sample1);
    printf("In other_location(), sample2 = %d and &sample2 = %p\n", sample2, &sample2);
}

void swap_values(int * x, int * y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

//int array_size(int array_to_be_sized[]) {                 //THIS CAN'T REALLY BE DONE STANDARD IN C!
//    return ((sizeof array_to_be_sized) / sizeof(int));
//}

int sum_int_array(int * arr, int arr_size) {
    int sum = 0;

    for(int i=0; i<arr_size; i++) {
        sum += *(arr + i);
    }

    return sum;
}
