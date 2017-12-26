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

//int array_size(int array_to_be_sized[]) {                 //THIS CAN'T REALLY BE DONE STANDARDIZED IN C! LOOK TO CHARACTER STRING ARRAYS FOR THE ONLY IMPLEMENTATION
//    return ((sizeof array_to_be_sized) / sizeof(int));
//}

int sum_int_array(int * arr, int arr_size) {
    int sum = 0;

    for(int i=0; i<arr_size; i++) {
        sum += *(arr + i);
    }

    return sum;
}

//Pass float pointer and function will interpret bytes as characters.
//This makes use of the fact that the type of a pointer specifies the number of bytes that are hooked on to the address it is referring to
void interpret_float_bytes_as_characters(float val) {
    float* val_ptr = &val;
    char* char1 = (char*) val_ptr;
    char* char2 = char1 + 1;
    char* char3 = char2 + 1;
    char* char4 = char3 + 1;

    printf("The float value: %.2e\nThe character represented by the first byte of the value address: %c\n"
            "The character represented by the second byte of the value address: %c\n"
            "The character represented by the third byte of the value address: %c\n"
            "The character represented by the fourth byte of the value address: %c\n", *val_ptr, *char1, *char2, *char3, *char4);
}

void interpret_char_bytes_as_float() {
    char* char_array[4];        //Is array so that we are guaranteed all char bytes are adjacent to each other.
    printf("Your characters: ");
//    scanf("%c %c %c %c", char_array, char_array + 1, char_array + 2, char_array + 3);
    *char_array = getchar();
    *(char_array + 1) = getchar();
    *(char_array + 2) = getchar();
    *(char_array + 3) = getchar();

    float val;
    float* val_ptr = (float*) char_array;
    val = *val_ptr;
    printf("The corresponding float value when connecting the addresses of the characters together: %e\n\n", val);

    interpret_float_bytes_as_characters(val);
}

void print_array(int* arr, int arr_size) {
    for(int i=0; i<arr_size; i++) {
        if(i == (arr_size - 1)) {
            printf("%d\n", *(arr + i));
        } else {
            printf("%d, ", *(arr + i));
        }
    }
}
