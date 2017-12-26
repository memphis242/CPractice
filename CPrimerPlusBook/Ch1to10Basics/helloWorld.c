#include <stdio.h>      //include preprocessor directive that essentially copy pastes the file and takes care of standards concerning that file
                        //Note that it also includes the stddef.h header file, which defines size_t, the alias for the data type of the return value for sizeof
#include <inttypes.h>   //Note that the stdint.h header file is included in the inttypes header.
#include <string.h>
#include <limits.h>
#include <float.h>
#include <stdbool.h>    //This includes bool as an alias for _Bool and true and false as symbolic constants for 1 and 0, resp.
#include <iso646.h>     //This allows the use of aliases for && (and), || (or), and ! (not).

#include "ch1to10.h"    //This is the header file for this project

//#define DENSITY 62.4    //average human density in lbs per cubic feet
//#define PAGES 959   //sample value for practicing format modifiers.
//#define ADJUST 7.31 //this is for the first program of Chapter 5 concerning shoe sizes
//#define SPACE ' '
//
//void print_example(int num);    //<-- This is the prototype of the function; this is in the form of ANSI C and beyond.
//int print_character_x_times(char c, int x);
//void display(char character_to_print, int rows, int columns);
//void skip_to_next_line(void);
//void trace_memory_addresses(int sample_value);

int main(void)
{
//  HELLO WORLD!
//    printf("Hello world!\n");

//  USE OF ANOTHER FUNCTION AND PRINTF()
//    int num = 1;
//
//    print_example(num);

//  USING SCANF() AND SOME ARITHMETIC
//    float weight, value;
//
//    printf("Are you worth your weight in platinum?\n");
//    printf("Let's check it out.\n\n");
//
//    printf("\tPlease enter your weight in pounds: ");
//    scanf("%f", &weight);
//
//    value = 1700.0 * weight * 14.5833;
//
//    printf("\nYour weight in platinum is worth $%.2f.", value);
//    printf("\nYou are easily worth that! If platinum prices drop,");
//    printf(" eat more to maintain your value.\n");

//  PECULIAR BOOK THING
//    printf("%d", ten);    --> Doesn't work, though the book uses it ...?

//  CONVERTING BETWEEN NUMBER SYSTEMS
//    int integer_decimal_number;
//
//    printf("Please enter an integer decimal number and I will output for you its octal and hexadecimal forms: ");
//    scanf("%d", &integer_decimal_number);
//
//    printf("\n\tDecimal form: %d\n\tOctal form: %#o\n\tHexadecimal form: %#x\n\n", integer_decimal_number, integer_decimal_number, integer_decimal_number);

//DIFFERENCES BETWEEN INTEGER LITERALS FOR 32-BIT SYSTEM. NOTE! YOUR SYSTEM IS 64-BIT SO THE FIRST PRINT LINE SHOWS THE SAME FOR BOTH.
//ALSO SHOWS THE SAME FOR LAST 2 LINES.
//    unsigned int unsigned_integer = 30000000;   //30 million
//    short short_integer = 200;
//    long long_integer = 65537;
//    long long long_long_integer = 12345678908642;
//
//    printf("Unsigned Integer: %u\tNOT INTEGER: %d\n", unsigned_integer, unsigned_integer);
//    printf("Short Integer: %hd\tALSO INTEGER: %d\n", short_integer, short_integer);
//    printf("Long Integer: %ld\tNOT SHORT INTEGER: %hd\n", long_integer, long_integer);
//    printf("Long Long Integer: %lld\tNOT LONG INTEGER: %ld\n", long_long_integer, long_long_integer);

//SOME ASCII AND HOW THE CHARACTER DATA TYPE WORKS
//    char input;
//
//    printf("Please specify a character and I will give you its ASCII code in decimal integer form: ");
//    scanf("%c", &input);
//
//    printf("\n\tYour character %c is %d in decimal integer ASCII form.\n", input, input);

//SPECIFYING BIT-LENGTH EXAMPLE FOR INTEGER TYPES
//    int32_t integer_32_bit = 45933945;  //signed 32-bit integer
//    int16_t integer_16_bit = 20000;
//
//    printf("First, assume int32_t is an alias for int.");
//    printf("\n\tinteger_32_bit = %d\tinteger_16_bit = %d", integer_32_bit, integer_16_bit);
//    printf("\nNOTE that if int is defined to be 32 bits, then the integer_16_bit value was printed using more memory space than needed..");
//    printf("\n\nNow, let's not make any assumptions. We want to guarantee that what we are printing is a 32-bit value.");
//    printf("\n\tinteger_32_bit = %" PRId32 "\tinteger_16_bit = %" PRId16 "\n", integer_32_bit, integer_16_bit);

//WORKING WITH FLOATS AND FLOAT LITERALS, ALONG WITH C99 HEXADECIMAL FORMAT OF FLOATING-POINT LITERALS
//    float float_val = 32000.0;
//    double double_val = 2.14e9;
//    long double long_double_val = 5.32e-5;
//
//    printf("%f can be written as %e (decimal exponent form) or %a (hexadecimal exponent form).", float_val, float_val, float_val);
//    printf("\nFurthermore, the following are forms of floating-point values:\n\tFloat Value: %f\n\tDouble Value: %f\n\tLong Double Value: %Lf\n", float_val, double_val, long_double_val);

//TESTING OUT BIT SIZES OF TYPES USING SIZEOF()
//    printf("Type int has a size of %zd bytes, or %zd bits.\n", sizeof(int), sizeof(int) * 8);
//    printf("Type char has a size of %zd bytes, or %zd bits.\n", sizeof(char), sizeof(char) * 8);
//    printf("Type long has a size of %zd bytes, or %zd bits.\n", sizeof(long), sizeof(long) * 8);
//    printf("Type long long has a size of %zd bytes, or %zd bits.\n", sizeof(long long), sizeof(long) * 8);
//    printf("Type float has a size of %zd bytes, or %zd bits.\n", sizeof(float), sizeof(float) * 8);
//    printf("Type double has a size of %zd bytes, or %zd bits.\n", sizeof(double), sizeof(double) * 8);
//    printf("Type long double has a size of %zd bytes, or %zd bits.\n", sizeof(long double), sizeof(long double) * 8);

//PROGRAMMING EXERCISE 1 OF CHAPTER 3 - CHECKING WHAT THE SYSTEM DOES WITH OVERFLOW & UNDERFLOW OF INTEGER AND FLOATING-POINT TYPES --> ANSWER: INTEGER OVERFLOW/UNDERFLOW WRAPS AROUND I BELIEVE, FLOAT OVERFLOW GOES INF, AND FLOAT UNDERFLOW GOES 0.
//    signed int test_integer_over = 2147483647; //2^31 - 1
//    printf("Signed Integer Overflow Test for 2,147,483,647 * 100 ((2^(31) - 1) * 100): %d\n\n", test_integer_over * 100);
//
//    signed int test_integer_under = -2147483647;    //-2^31 + 1
//    printf("Signed Integer Underflow Test for -2,147,483,647 * 100 ((-2^(31) + 1) * 100): %d\n\n", test_integer_under * 100);
//
//    unsigned int test_u_integer_over = 4294967296;  //2^32 - 1
//    printf("Unsigned Integer Overflow Test for 4,294,967,296 * 100 ((2^(32) - 1) * 100): %ud\n\n", test_u_integer_over * 100);
//
//    unsigned int test_u_integer_under = -4294967296;
//    printf("Unsigned Integer Underflow Test for 4,294,967,296 * 100 ((2^(32) - 1) * 100): %ud\n\n", test_u_integer_under * 100);
//
//    float test_float_over = 2.147483647e40;    //2^31 - 1
//    printf("Floating Point Overflow Test for 2.147483647e40: %f\n\n", test_float_over * 10000.000000);
//
//    float test_float_under = 0.00001e-40;
//    printf("Floating Point Underflow (Subnormal) Test for 0.00001e-40: %f\n\n", test_float_under);

//CHAPTER 4'S INITIAL PROGRAM, PRESENTING THE USE OF STRINGS AS CHARACTER ARRAYS, USING THE %s FORMAT SPECIFIER, AND USING THE #define PREPROCESSOR DIRECTIVE FOR DENSITY.
//    float weight, volume;
//    unsigned short size, letters;
//    char name[40];
//
//    printf("Hi! What's your first name?\t");
//    scanf("%s", name);
//
//    printf("%s, what is your weight in pounds?\t", name);
//    scanf("%f", &weight);
//
//    size = sizeof name;
//    letters = strlen(name);
//
//    volume = weight / DENSITY;
//
//    printf("Well, %s, your volume is %2.2f cubic feet.\n", name, volume);
//    printf("Also, your first name has %d letters, and we have %d bytes to store it.\n", letters, size);

//ASSIGNING STRINGS WITHOUT THE USE OF scanf() --> OK, SO MAKING A STRING EASY. THE COMPILER TAKES CARE OF FILLING THE CHARACTER ARRAY AND APPENDING THE NULL CHARACTER AT THE END. HOWEVER, THIS SIZEOF STUFF IS NOT SO STRAIGHTFORWARD... --> FIXED IT!
//    char string_example[40] = "This is a string example.";
//
////    signed size_t actual_size = 0, unused_size;
////    for(int i=0; i<(sizeof string_example); i++){
////        if(string_example[i] != '\0'){
////            actual_size++;
////        } else{
////            break;
////        }
////    }
////    unused_size = (sizeof string_example) - actual_size;
//
//    printf("%s The size of the character array is %zd. There are %zd used charcaters and %zd unused characters.", string_example, sizeof string_example, strlen(string_example), (sizeof string_example) - strlen(string_example));

//SEEING THE VALUES IN limits.h & float.h
//    printf("Maximum integer value: %d\n", INT_MAX);
//    printf("Minimum integer value: %d\n", INT_MIN);
//    printf("Maximum float value: %e\n", FLT_MAX);
//    printf("Minimum float value: %e\n", FLT_MIN);

//USING FORMAT MODIFIERS
//    printf("*%d+*\n", PAGES);
//    printf("*%2d*\n", PAGES);
//    printf("*%10d*\n", PAGES);
//    printf("*%-10d*\n", PAGES);
//    printf("*%010d*\n", PAGES);
//    printf("*%-5.3d*\n", 2);

//SPREADING A PRINTF STATEMENT OVER SEVERAL LINES FOR EASIER READABILITY
//    printf("Here's one way to print a ");
//    printf("long string.\n");
//
//    printf("Here's another way to print a \
//long string.\n");
//
//    printf("Here's the newest way to print a "
//            " long string.\n");     //ANSI C
//
////    char string_way[3] = "way";   //NOPE. NOT QUITE.
//    printf("Here's another " "example of the newest" " way.\n");

//USING THE '*' PLACEHOLDER WITH PRINTF() AND SCANF()
//    unsigned int field_width;
//
//    printf("What would you like the field width to be? (I am going to skip over your first character): ");
//    scanf("%*c%d", &field_width);
//
//    int sample_value;
//    printf("What value would you like to print at this specified field width? ");
//    scanf("%d", &sample_value);
//
//    printf("\n\tHere is your value formatted as you said: *%*d*\n", field_width, sample_value);

//FIRST PROGRAM OF CHAPTER 5. HERE IS THE FIRST USE OF THE WHILE LOOP
//    const double SCALE = 0.333;
//    double shoe, foot;
//
//    printf("Shoe Size (Men's)     Foot Length (Inches)\n");
//
//    shoe = 3.0;
//    while(shoe < 18.5){
//        foot = (SCALE * shoe) + ADJUST;
//        printf("%10.2f %15.5f inches\n", shoe, foot);
//        shoe += 0.01;
//    }
//
//    printf("\nIf the shoe fits...\n");

//TABLE OF SQUARES UP TO A CERTAIN NUMBER IN DISCRETE JUMPS SPECIFIED BY USER
//    float start_number, end_number, square_of_number;
//
//    printf("This is a program to display a table of squares.\n\n");
//
//    printf("Where would you like to start? ");
//    scanf("%f", &start_number);
//    printf("Where would you like to end? ");
//    scanf("%f", &end_number);
//
//    float discrete_jump;
//    printf("What would you like the discrete jumps between numbers to be? ");
//    scanf("%f", &discrete_jump);
//
//    printf("\n   Number          Square\n");
//    for(float number_to_square=start_number; number_to_square<end_number; number_to_square+=discrete_jump){
//
//        square_of_number = number_to_square * number_to_square;
//
//        if(discrete_jump == 1){
//            printf("     %-8.0f        %-8.0f\n", number_to_square, square_of_number);
//        } else{
//            printf("  %8.5f        %8.5f\n", number_to_square, square_of_number);
//        }
//    }

//DIFFERENCE BETWEEN PREFIX AND POSTFIX FORM OF INCREMENTATION OPERATOR (SAME APPLIES TO DECREMENTATION)
//    int i = 1, j = 1;
//    int a = ++i, b = j++;
//
//    printf("Using i = 1 and a = ++i, i = %d, a = %d\n", i, a);
//    printf("Using j = 1 and b = j++, j = %d, b = %d\n", j, b);

//THE SIDE EFFECTS OF IMPLICIT TYPE CONVERSIONS
//    char character_val;
//    int integer_val;
//    float float_val;
//
//    float_val = integer_val = character_val = 'C';
//    printf("Assigning all variables C, character_val = %c, integer_val = %d, float_val = %2.2f\n", character_val, integer_val, float_val);
//
//    character_val++;
//    integer_val = float_val + 2 * character_val;
//    float_val = 2.0 * character_val + integer_val;
//    printf("\nAdding one to the character_val, and doing various operations on the other two, character_val = %c, integer_val = %d, float_val = %2.2f\n", character_val, integer_val, float_val);
//
//    character_val = 1623;
//    printf("\n\nAssining 1623 to character_val, now the character_val = %c\n", character_val);
//
//    character_val = 80.89;
//    printf("\nAssigning 80.89 to character_val, now the character_val = %c\n", character_val);

//FIRST USE OF FUNCTIONS WITH PARAMETERS
//    char character_val;
//    int number_of_times;
//
//    printf("What character would you like to print? ");
//    scanf("%c", &character_val);
//    printf("How many times? ");
//    scanf("%d", &number_of_times);
//
//    printf("\n\nYour character was printed %d times.\n", print_character_x_times(character_val, number_of_times));

//INTERESTING NOTE ON THE WHILE LOOP. WITH THE KNOWLEDGE THAT ';' ON A LINE IS CONSIDERED A STATEMENT ON ITS OWN, THE FOLLOWING
//IS EQUIVALENT TO THE COMMENTED PART PROCEEDING IT.

//    unsigned short int n = 0;
//
//    while(n++ < 3); //NOTE THIS ALSO IS ANOTHER DEMONSTRATION OF HOW INCREMENTATION WORKS. RECALL WHAT SEQUENCE POINTS ARE. FIRST THE CONDITION IS TESTED, THEN N IS INCREMENTED.
//    printf("%2d", n);
//
//    printf("\nProgram done.");
//
////    while(n++ < 3){ ;}
////    printf("%2d", n);
////
////    printf("\nProgram done.");

//SOMETHING TO NOTE ABOUT HOW C EXPRESSIONS ALWAYS HAVE A VALUE.

//    unsigned short int n;
//
//    printf("%d\n", n = 5 - 2);
//
//    //ALSO
//
//    unsigned short int m = 5 + (n = 5 + 3) * 2;
//
//    printf("%d\n", m);

//FIRST-USE OF BOOLEAN VARIABLES
//    bool is_good;
//    char character_read;
//
//    printf("Are you good m8? (y/n) ");
//    scanf("%c", &character_read);
//
//    if(character_read == 'y'){
//        is_good = true;
//    } else{
//        is_good = false;
//    }
//
//    if(is_good){
//        printf("\nRight on man!\n");
//    } else{
//        printf("\nBe strong. Believe.\n");
//    }

//USE OF THE COMMA OPERATOR
//    for(int i = 0, j = 0; i < 10; i++){
//        j = i * i;
//        printf("%-3d\t%-3d\n", i, j);
//    }
//    int x;
//    printf("%d", (x = 5,3));

//    int y = (x = 3), (int z = 5 * 2 - 3) + 5;

//USE OF GETCHAR() AND PUTCHAR()
//    char character;
//
//    //NOTE IF THERE IS NO INPUT, GETCHAR() WAITS FOR YOU TO PUT INPUT AND HIT ENTER.
//    while((character = getchar()) != '\n'){     //NOTE THE FIRST PART OF THE CONDITION DEMONSTRATES THE VALUE OF AN ASSIGNMENT EXPRESSION
//        if(isalpha(character)) {
//            putchar(character + 1);
//        } else {
//            putchar(character);
//        }
//    }
//
//    putchar(character);

//SHOWING THAT LOGICAL OPERATORS ARE SEQUENCE POINTS
//    int i=0, j=0;
//
//    if(i++ == 0 && 1 / i == 1){ //Note how this works because the postfix incrementation occurs after the equality check.
//        putchar(i + 65);
//    }
//
//    if(++j == 0 && 1 / i == 1){ //Note how this doesn't work because the prefix incrementation occurs before the equality check
//        putchar(j + 75);
//    }

//FIRST-USE OF THE CONDITIONAL OPERATOR
//    int x = (1 > 2) ? 50 : 60;
//    int y = (1 < 2) ? 50 : 60;
//    printf("%-3d%-3d", x, y);

//CHAPTER 8 INTRODUCTORY PROGRAM - ECHOING KEYBOARD INPUT TO CONSOLE
//    int character;
//    while((character = getchar()) != '\n'){
//        putchar(character);
//    }

//USING EOF FOR INPUT - REWRITING THE ECHOING PROGRAM WITH EOF
//    printf("%d", EOF);  //--> prints -1.
//    int character;
//    while((character = getchar()) != EOF) {     //NOTE THAT CTRL+D IS THE EOF FOR KEYBOARD INPUT.
//        putchar(character);
//    }

//MIXING INPUTS AND ACCOUNTING FOR THE DIFFERENCES BETWEEN SCANF() AND GETCHAR()
//    int character, rows, columns;   //this program will print a certain character in a certain number of rows and columns using display()
//
//    printf("Type in what charcter you want to print along with how many rows and columns you wish: ");
//    while((character = getchar()) != '\n') {
//        if(scanf("%d %d", &rows, &columns) != 2){       //FOR SOME REASON, THERE SEEMS TO BE IN ISSUE WHEN THE NUMBERS ARE NEXT TO EACH OTHER.
//            break;
//        }
//
//        display((char) character, rows, columns);
//
//        skip_to_next_line();
//
//        printf("Do it again! Or just enter to quit: ");
//    }
//
//    printf("Done.");

//CHAPTER 9 RECURSION PRACTICE
//    trace_memory_addresses(0);

//CHAPTER 9 SHOWING WHERE VARIABLES AND THEIR VALUES/ADDRESSES ARE STORED
//    int sample1 = 2, sample2 = 50;
//
//    printf("In main(), sample1 = %d and &sample1 = %p\n", sample1, &sample1);
//    printf("In main(), sample2 = %d and &sample2 = %p\n", sample2, &sample2);
//
//    other_location(sample2);

//USING POINTERS FOR THE FIRST TIME!!! WE SEEK TO SWAP TWO VARIABLE'S VALUES USING AN EXTERNAL FUNCTION.
//    int x=5, y=10;
//
//    printf("Initially, x = %d, y = %d.\n", x, y);
//    swap_values(&x, &y);
//    printf("Now, after swapping, x = %d, y = %d.", x, y);

//CHAPTER 10 USE OF DESIGNATED INITIALIZERS FOR ARRAY INITIALIZATION
//    int days[MONTHS] = {31, 28, [4] = 31, 30, 31, [1] = 29};
//    for(int i=0; i<MONTHS; i++) {
//        if(i == MONTHS - 1) {
//            printf("%3d\n", days[i]);
//        } else {
//            printf("%3d, ", days[i]);
//        }
//    }
//    printf("\n");

//RELATING THE ARRAYS TO POINTERS!
//    short array_short[5];
//    short * pointer_to_array_short;
//    char array_char[5];
//    char * pointer_to_array_char;
//
//    pointer_to_array_short = array_short;
//    pointer_to_array_char = array_char;
//
//    printf("%23s %15s\n", "short", "char");
//    for(int i=0; i<5; i++) {
//        printf("Pointers + %d: %10p %10p\n", i, pointer_to_array_short + i, pointer_to_array_char + i);
//    }

//USING ARRAYS AS ARGUMENTS/PARAMETERS
    int sample_array[5] = {1, 3, 5};
    printf("Sum of the elements of the array: %d\n", sum_int_array(sample_array, 5));

    return 0;
}

//void print_example(int num) {
//
//    printf("I am a simple ");
//    printf("computer.\n");
//    printf("My favorite number is %d because it is first.\a", num);
//
//}
//
//int print_character_x_times(char c, int x) {
//    int debug_check = 0;
//
//    printf("\n");
//    for(int i=0; i<x; i++){
//        printf("#");
//        debug_check++;
//    }
//
//    printf("\n\nSorry but OCTOTHORP RULES ALL!!!");
//
//    return debug_check;
//}
//
//void display(char character_to_print, int rows, int columns) {
//    for(int i=0; i<rows; i++){
//        for(int j=0; j<columns; j++){
//            putchar(character_to_print);
//        }
//        putchar('\n');
//    }
//    putchar('\n');
//}
//
//void skip_to_next_line(void){
//    while(getchar() != '\n') {
//        continue;
//    }
//}
//
//void trace_memory_addresses(int sample_value) {
//    printf("Level : %-3d Address: %p\n", sample_value, &sample_value);
//    if(sample_value < 5) {
//        trace_memory_addresses(sample_value + 1);
//    }
//}
