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

#define COLUMNS 4
#define LINE 80
#define MSG "I am a symbolic string message"
#define MAXLENGTH 81

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

void newline() {
    puts("");
}

void print_line() {
    for(int i=0; i<LINE; i++) {
        putchar('*');
    }
    newline();
}

void print_title(const char* title) {
    print_line();
    puts(title);
    print_line();
}

////Pass float pointer and function will interpret bytes as characters.
////This makes use of the fact that the type of a pointer specifies the number of bytes that are hooked on to the address it is referring to
//void interpret_char_bytes_as_float() {
//    print_line();
////    printf("In function: interpret_char_bytes_as_float()\n\n");
//    printf(__func__);       //CAN ALSO USE __FILE__, __LINE__, and __TIMESTAMP__
//    printf("\n");
//
//    char char_array[4];        //Is array so that we are guaranteed all char bytes are adjacent to each other.
//    printf("Input characters: ");
////    scanf("%c %c %c %c", char_array, char_array + 1, char_array + 2, char_array + 3);
//    *char_array = getchar();
//    *(char_array + 1) = getchar();
//    *(char_array + 2) = getchar();
//    *(char_array + 3) = getchar();  //More convenient to use scanf("%s", char_array);
//
//    printf("Charcaters you inputted: %c %c %c %c\n", char_array[0], char_array[1], char_array[2], char_array[3]);
//
//    float val;
//    float* val_ptr = (float*) char_array;
//    val = *val_ptr; //equivalent to doing val = * ( (float*) char_array)
//
//    printf("\nThe corresponding float value synthesized from adjacent char bytes: %e\n\n", val);
//
//    interpret_float_bytes_as_characters(val_ptr);   //equivalent to just doing &val
//}
//
//void interpret_float_bytes_as_characters(float* val_ptr) {
//    print_line();
////    printf("In function: interpret_float_bytes_as_characters()\n\n");
//    printf(__func__);
//    printf("\n");
//
////    float val = *val_ptr;
////    char* char1 = (char*) val_ptr;
////    char* char2 = char1 + 1;
////    char* char3 = char2 + 1;
////    char* char4 = char3 + 1;
//
////ALL THAT CAN BE REDUCED TO THE FOLLOWING STATAMENT
//    char* char_array = (char*) val_ptr;
//
//    printf("The float value: %e\nThe character represented by the first byte of the value address: %c\n"
//            "The character represented by the second byte of the value address: %c\n"
//            "The character represented by the third byte of the value address: %c\n"
//            "The character represented by the fourth byte of the value address: %c\n", *val_ptr, char_array[0], char_array[1], char_array[2], char_array[3]);
//
//    print_ASCII_vals_of_bytes(char_array, 4);
//}
//
//void print_ASCII_vals_of_bytes(const char* arr, int arr_size) {
//    print_line();
////    printf("In function: print_ASCII_vals_of_bytes()\n\n");
//    printf(__func__);
//    printf("\n");
//
//    for(int i=0; i<arr_size; i++) {
//        printf("ASCII Value of Element %c: %d\n", arr[i], arr[i]);
//    }
//    printf("\n");
//}

void print_array_int(const int arr[], int arr_size) {
    //printf("\nThe integer array as printed from %s: { ", __func__);

    printf("{ ");
    
    for(int i=0; i<arr_size; i++) {

        if(i == (arr_size - 1)) {
            printf("%d", arr[i]);
        } else {
            printf("%d, ", arr[i]);
        }
    }

    puts(" };");
}

void print_array_double(const double arr[], int arr_size) {
    printf("{ ");
    
    for(int i=0; i<arr_size; i++) {        
        if(i == (arr_size - 1)) {
            printf("%3.3f", arr[i]);
        } else {
            printf("%3.3f, ", arr[i]);
        }
    }
    
    puts(" };");
}

void modify_array_double(double* arr, int arr_size) {
    for(int i=0; i<arr_size; i++) {
        *(arr + i) = *(arr + i) * 2.5;
    }
}

void print_2D_array_int(const int (* arr) [COLUMNS], int rows) {
    printf("The 2D Array as printed from %s: { ", __func__);

    for(int i=0; i<rows; i++) {

        printf("{ ");

        for(int j=0; j<COLUMNS; j++) {

            if(j == COLUMNS - 1) {
                printf("%d", arr[i][j]);
            } else {
                printf("%d, ", arr[i][j]);
            }

        }

        if(i == rows - 1) {
            printf(" }");
        } else {
            printf(" }, ");
        }
    }

    printf(" };\n\n");
}

void sum_rows_int(int (* arr) [COLUMNS], int rows) {
    int total = 0;

    for(int i=0; i<rows; i++) {
        printf("Row %d Summed Total: ", i);

        for(int j=0;j<COLUMNS; j++) {
            total += arr[i][j];
        }
        printf("%d\n", total);

        total = 0;
    }

    printf("\n");
}

void sum_columns_int(int arr[][COLUMNS], int rows) {
    int total = 0;

    for(int i=0; i<COLUMNS; i++) {
        printf("Column %d Summed Total: ", i);

        for(int j=0; j<rows; j++) {
            total += arr[j][i];
        }
        printf("%d\n", total);

        total = 0;
    }

    printf("\n");
}

void sum_total_2D_int(int (* arr) [COLUMNS], int rows, int* total) {
    for(int i=0; i<rows; i++) {
        for(int j=0; j<COLUMNS; j++) {
            *total += arr[i][j];
        }
    }
}

int sum_2D_vla_int(int rows, int columns, const int arr[rows][columns]) {
    int sum = 0;
    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            sum += arr[i][j];
        }
    }
    return sum;
}

void fill_int_array(int *arr, int size, int min, int max) {
    //srand(time(NULL));
    int range = max - min;
    
    for(int i=0; i<size; i++) {
        arr[i] = (rand() % range) + min;
    }
}

void fill_double_array(double *arr, int size, double min, double max, double diff) {
    //srand(time(NULL));
    int range = (int) (max - min);
    int num_of_diff_in_range = (int) ( (max - min) / diff );
    
    for(int i=0; i<size; i++) {
        arr[i] = ((rand() % num_of_diff_in_range ) * diff) + min;
    }
}

void fill_char_array(char *arr, int size) {
    //srand(time(NULL));
    for(int i=0; i<size; i++) {
        arr[i] = (rand() % 94) + 32;    //32 is SPACE. 126, the max, is ~, after which is DEL.
    }
}
