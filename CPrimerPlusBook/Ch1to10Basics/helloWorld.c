#include <stdio.h>      //include preprocessor directive that essentially copy pastes the file and takes care of standards concerning that file
                        //Note that it also includes the stddef.h header file, which defines size_t, the alias for the data type of the return value for sizeof
#include <inttypes.h>   //Note that the stdint.h header file is included in the inttypes header.
#include <string.h>
#include <limits.h>
#include <float.h>

#define DENSITY 62.4    //average human density in lbs per cubic feet
#define PAGES 959   //sample value for practicing format modifiers.

void print_example(int num);    //<-- This is the prototype of the function

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
    printf("Here's one way to print a ");
    printf("long string.\n");

    printf("Here's another way to print a \
long string.\n");

    printf("Here's the newest way to print a "
            " long string.\n");     //ANSI C

//    char string_way[3] = "way";   //NOPE. NOT QUITE.
    printf("Here's another " "example of the newest" " way.\n");

    return 0;
}

void print_example(int num) {

    printf("I am a simple ");
    printf("computer.\n");
    printf("My favorite number is %d because it is first.\a", num);

}
