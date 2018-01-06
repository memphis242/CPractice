#include "abutfunc.h"

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

//For when you use scanf()
void eatline() {
    while( getchar() != '\n' ) {
        continue;
    }
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

float sum_float_array(float arr[], int size) {
    float sum = 0.0;
    for(int i=0; i<size; i++) {
        sum += arr[i];
    }
    
    return sum;
}

double sum_double_array(double arr[], int size) {
    double sum = 0.0;
    for(int i=0; i<size; i++) {
        sum += arr[i];
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
        arr[i] =  min + ((rand() % num_of_diff_in_range ) * diff);   //the part before the * diff defines how many diff increments are made to min
    }
}

//NEEDS WORK ON PARTITIONING
void test_distribution_d(double arr[], int arrsize, const double minVal, const double maxVal) {
    float partition_count[10] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    float partition_percentages[10];
    double val, range = maxVal - minVal, increment = range / 10.0;
    
    if( arrsize > 10 ) {
        
        //Count how many values in the array are in each partition
        for(int i=0; i<arrsize; i++) {
            val = arr[i];   //Faster to access variable value than array value ??
            if( (val >= minVal) && (val < (minVal + increment)) ) {
                partition_count[0]++;
            } else if( (val >= (minVal + increment) && (val < (minVal + (2 * increment)))) ) {
                partition_count[1]++;
            } else if( (val >= (minVal + (2 * increment)) && (val < (minVal + (3 * increment)))) ) {
                partition_count[2]++;
            } else if( (val >= (minVal + (3 * increment)) && (val < (minVal + (4 * increment)))) ) {
                partition_count[3]++;
            } else if( (val >= (minVal + (4* increment)) && (val < (minVal + (5 * increment)))) ) {
                partition_count[4]++;
            } else if( (val >= (minVal + (5 * increment)) && (val < (minVal + (6 * increment)))) ) {
                partition_count[5]++;
            } else if( (val >= (minVal + (6 * increment)) && (val < (minVal + (7 * increment)))) ) {
                partition_count[6]++;
            } else if( (val >= (minVal + (7 * increment)) && (val < (minVal + (8 * increment)))) ) {
                partition_count[7]++;
            } else if( (val >= (minVal + (8 * increment)) && (val < (minVal + (9 * increment)))) ) {
                partition_count[8]++;
            } else {
                partition_count[9]++;
            }
        }
        
        //Calculate percentage of total elements in partition i
        for(int i=0; i<10; i++) {
            partition_percentages[i] = (partition_count[i] / ((float) arrsize)) * 100.0;
        }
        
        //Print this out
        puts("The Partition Distribution is as follows:");
        for(int i=0; i<10; i++) {
            printf("\tPartition %d: %.2f%%\n", (i + 1), partition_percentages[i]);
        }
        if( ( 100.0 - sum_float_array(partition_percentages, 10) ) < 0.01) { //Sum is within 0.01 percent from 100; the tolerance is to account for possible data loss.
            puts("Sum is consistent.");
        } else {
            puts("Error state. Sum is inconsistent.");
        }
        newline();
        
    } else {
        puts("Array size needs to be greater than 10 to test distribution.");
        exit(EXIT_FAILURE);
    }
}

void fill_char_array(char *arr, int size) {
    //srand(time(NULL));
    for(int i=0; i<size; i++) {
        arr[i] = (rand() % 94) + 32;    //32 is SPACE. 126, the max, is ~, after which is DEL.
    }
}

//This function tests distribution by splitting the array into 10 partitions for which there is a total order defined
//and prints out a statement that indicates the percentage of members in partition 1, 2, and so on, and accordingly,
//the user concludes how well distributed members are.
//NEEDS WORK ON PARTITIONING!
//_Noreturn void test_distribution(void *arr, int sizeofarr, size_t sizeofmem, int (*comp)(void *val1, void *val2), void *maxVal, void *minVal) {
//    if( sizeofarr > 10 ) {
//        for(int i=0; i < (sizeofarr / sizeofmem); i++) {
//            switch(arr[i]) {
//                case 
//            }
//        }
//    } else {
//        puts("Array size needs to be greater than 10 to test distribution.");
//        exit(EXIT_FAILURE);
//    }
//}

int sumints(int num_of_items, ...) {
    va_list arglist;
    int sum = 0;
    
    va_start(arglist, num_of_items);
    for(int i=0; i<num_of_items; i++) {
        sum += va_arg(arglist, int);
    }
    
    va_end(arglist);
    return sum;
}

double sumdoubles(int num_of_items, ...) {
    va_list arglist;
    double sum = 0.0;
    
    va_start(arglist, num_of_items);
    for(int i=0; i<num_of_items; i++) {
        sum += va_arg(arglist, double);
    }
    
    va_end(arglist);
    return sum;
}

/*
* NOTE! Two flaws with this function:
    * It is silent about out-of-bounds input, and doesn't give the opportunity to re-enter or do something about it. It just ignores the extra characters.
    * It doesn't cope with being sent a size 1, which wouldn't be a string.
*/
char* get_string_input(char* str, int size_of_str) {
    char* return_val;   //WE DON'T ALLOCATE MEMORY BECAUSE THIS POINTER WILL BE SET TO THE PASSED POINTER ARGUMENT
    int i=0;

    return_val = fgets(str, size_of_str, stdin); //FGETS() WILL READ IN INPUT FROM STDIN AND RETURN A PTR EQUIVALENT TO STR IF ALL GOES WELL; OTHERWISE NULL POINTER

    if(return_val) {    //IF RETURN_VAL != NULL
        while(str[i] != '\n' && str[i] != '\0') {   //ADVANCE TO PART OF INPUT THAT IS EITHER A NEWLINE OR NULL CHARACTER
            i++;
        }

        if(str[i] == '\n') {    //IF NEWLINE, ALL INPUT HAS BEEN READ AND SO REPLACE NEWLINE WITH NULL CHARACTER
            str[i] = '\0';
        } else {    //THERE ARE UNREAD CHARACTERS FROM INPUT BECAUSE INPUT WAS TOO LARGE, SO DISCARD EXTRA CHARACTERS
            while(getchar() != '\n') {
                continue;
            }
        }
    }

    return return_val;
}

//char* trim_string(char* str) {        //NEEDS WORK
//    size_t trimmed_size = strlen(str);
//
//
//    trim_string_to_size(str, strlen(str));
//    return str;content
//}

void trim_string_to_size(char* str, int desired_size) {
    if(strlen(str) > desired_size) {
        str[desired_size] = '\0';
    }
}

char* str_safe_conc(char* str1, const char* str2, int size_of_1) {
    int size_diff = size_of_1 - (strlen(str2) + 1);

    if( size_diff > 0 ) {
        return strncat(str1, str2, size_diff);
    } else {
        return NULL;
    }
}

void sort_str_alph(char* strings[], int num_of_strings) {   //NOTE FIRST PARAMETER IS OF TYPE ARRAY OF POINTERS-TO-CHAR
    char* temp;     //for switching
    int right_end = num_of_strings, comp_val;

    for(int i=0; i < (right_end - 1); i++) {    //USING SELECTION-SORT
        for(int j = (i + 1); j < right_end; j++) {

            comp_val = strcmp(strings[i], strings[j]);   //RECALL STRCMP() RETURNS > 0 IF FIRST STRING HAS HIGHER ASCII VALUE THAN SECOND, WHICH MEANS REVERSE-ALPHABETICAL
//            printf("%d ", comp_val);

            if( comp_val > 0 ) {    //SWAP
                temp = strings[i];
                strings[i] = strings[j];
                strings[j] = temp;
            }
        }
//        puts("");
    }
}

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

char *itobs(int number, char *bitstring) {
    const static int size = CHAR_BIT * sizeof(int);
    
    for(int i = (size - 1); i >= 0; i--, number>>=1) {  //Starting from least-significant bit to most; leaving one character at the end for '\0'
        bitstring[i] = (MASK & number) + '0';   //Retrieving what the last bit is then getting the ASCII value of that character
    }
    
    bitstring[size] = '\0'; //So it is a string and not just a char array
    
    return bitstring;
}

void printbits(const char *bitstring) {
    for(int i = 0; bitstring[i] != '\0'; i++) {
        if( i%4 == 0 && i != 0 ) {    //Spacing out 4-bit intervals except for first
            putchar(' ');
        }
        putchar(bitstring[i]);
    }
    newline();
}

void setbit(int *mask, int index) {
    int onebit = 1 << index;
    *mask |= onebit;
}

int set_onebyte_mask(bool bits[]) {
    int mask;
    
    for(int i=0; i<8; i++) {
        if( bits[i] == 1 ) {
            setbit(&mask, i);
        }
    }
    
    return mask;
}

int set_twobyte_mask(bool bits[]) {
    int mask;
    
    for(int i=0; i<16; i++) {
        if( bits[i] == 1 ) {
            setbit(&mask, i);
        }
    }
    
    return mask;
}

void printbitsofint(int number) {
    char bitstring[CHAR_BIT * sizeof(int) + 1];
    itobs(number, bitstring);
    printbits(bitstring);
}

/*
//    TIME t;
//    gettimeofday(&t, NULL);
//    
//    double elapsed;
//    
//    time_t ts0 = t.tv_sec;
//    suseconds_t tn0 = t.tv_usec;
//    double initialTime = (t.tv_sec * 1000) + (t.tv_usec / 1000);
//    
//    
//    while(1) {
//        gettimeofday(&t, NULL);
//        elapsed = ( (t.tv_sec * 1000) + (t.tv_usec / 1000) ) - initialTime;
//        printf("Elapsed Milliseconds: %lf\n", elapsed);
//    }
//    
/*NEVER FREAKEN USE CLOCKS_PER_SEC. ABSOLUTELY DISAPPOINTING.*/
//    clock_t t0 = clock();
//    clock_t t1;
//    double tElapsed;
//    
//    while(1) {
//        tElapsed = ( ((double)( clock() - t0 )) / CLOCKS_PER_SEC) ;
//        printf("Elapsed Time: %lf seconds\n", tElapsed);
////        printf("clock(): %ld\tCLOCKS_PER_SEC: %ld\tTime elapsed: %lf\n", clock(), (CLOCKS_PER_SEC / 100), ((double) (clock() - t0) / (CLOCKS_PER_SEC / 100) ));
//    }
*/
