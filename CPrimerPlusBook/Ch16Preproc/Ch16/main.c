/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: abdullah
 *
 * Created on December 31, 2017, 2:41 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <tgmath.h>
#include <time.h>

#include "src/ch1to10.h"
#include "src/ch11.h"
#include "src/ch14.h"
#include "src/ch15.h"

void whyme();

int mycomp(const void *val1, const void *val2);

/*
 * 
 */
int main(int argc, char** argv) {

//USING THE #define PREPROCESSOR DIRECTIVE
//    //Preprocessor directives may be placed anywhere in code and are visible from where they are placed to the end of a file
//#define PX printf("X is %d\n", x)
//    //You can split a string literal over multiple lines using \, as we've seen before. The compiler removes this and puts it into one logical line before the preprocessor.
//#define STRINGLIT "This is a quo\
//te."
//#define TWO 2
//    //Nested macros.
//#define FOUR TWO*TWO
//    
//    int x = TWO;
//    PX;
//    x = FOUR;   //Note, as far as the preprocessor is concerned, this is just replaced by 2*2. The compiler handles evaluation of expressions at compile time.
//    PX;
//    printf("%s", STRINGLIT);
    
//USING FUNCTION MACROS, STRINGIZING (<-- LOL AT THAT NAME), THE ## OPERATOR, VARIADIC FUNCTION MACROS, #IFDEF, #ELSE, #ENDIF
//#define SQUARE(X) X*X
//#define SQUARE1(X) (X)*(X)
//#define SQUARE2(X) ((X)*(X))
//#define PRINT(X) printf("The result is %d.\n", X)
//#define PRINTSQ(X) printf("The square of " #X " is %d.\n", SQUARE2(X));
//#define XNAME(N) x ## N
//#define PRINTXN(N) printf("x" #N " is %d\n", x ## N);
//#define PRINTMES(X, ...) printf("Message " #X ": " __VA_ARGS__);
//    
//    int x = 5;
//    double y;
//    int z;
//    
//    puts("Note the following are the macro definitions.");
//    puts("SQUARE(X) X*X");
//    puts("SQUARE1(X) (X)*(X)");
//    puts("SQUARE2(X) ((X)*(X))");
//    puts("PRINTSQ(X) printf(\"The square of \" #X \"is %d.\\n\", SQUARE2(X));");
//    puts("XNAME(N) x ## N");
//    puts("PRINTMES(X, ...) printf(\"Message \" #X \": \" __VA_ARGS__);");
//    
//    newline();
//    newline();
//    
//    printf("x = %d\n", x);
//    newline();
//    
//#ifdef SQUARE   --> IF THE MACRO IDENTIFIER SQUARE IS DEFINED
//    z = SQUARE(x);  //Eq. to x*x
//    printf("Evaluating SQUARE(X): ");
//    PRINT(z);
//    newline();
//#endif
//    
//#undef SQUARE   //--> UNDEFINE SQUARE TO SEE IF NEXT CHUNK OF CODE WORKS
//    
//#ifdef SQUARE
//    int a = SQUARE(x);  //Eq. to x*x
//    printf("Evaluating SQUARE(X): ");
//    PRINT(z);
//    newline();
//#else           //--> SINCE WE UNDEFINED SQUARE, AND THE PREVIOUS CHUNK WITH THE IFDEF SHOULDN'T COMPILE, THEN REDEFINE AGAIN.
//#define SQUARE(X) X*X
//#endif
//    
//    z = SQUARE(2);  //Eq. to 2*2
//    printf("Evaluating SQUARE(2): ");
//    PRINT(z);
//    newline();
//    
//    printf("Evaluating SQUARE(x+2): ");
//    PRINT(SQUARE(x+2)); //Eq. to x+2*x+2, which is eq. to x + (2*x) + 2
//    printf("Evaluating SQUARE1(x+2): ");
//    PRINT(SQUARE1(x+2));
//    printf("Evaluating SQUARE2(x+2): ");
//    PRINT(SQUARE2(x+2));
//    newline();
//    
//    printf("Evaluating 100/SQUARE(2): ");
//    PRINT(100/SQUARE(2));   //Eq. to 100/2*2, which is eq. to (100 / 2) * 2
//    printf("Evaluating 100/SQUARE1(2): ");
//    PRINT(100/SQUARE1(2));
//    printf("Evaluating 100/SQUARE2(2): ");
//    PRINT(100/SQUARE2(2));
//    newline();
//    
//    printf("x is %d.\n", x);
//    
//    printf("Evaluating SQUARE(++x): ");
//    PRINT(SQUARE(++x)); //Eq. to ++x*++x, which is eq. to (++x) * (++x)
//    newline();
//    
//    printf("Evaluating SQUARE(x++): ");
//    PRINT(SQUARE(x++)); //Eq. to x++*x++
//    newline();
//    
//    printf("After incrementing, x is %d.\n", x);
//    
//    printf("Evaluating PRINTSQ(x).\n");
//    PRINTSQ(x); //Eq. to printf("The square of " "x" "is %d.\n", ((x)*(x)));
//    newline();
//    
//    puts("Evaluating XNAME(1) = 35");
//    int XNAME(1) = 35;
//    PRINTXN(1);
//    newline();
//    
//    y = sqrt((double) x);     //--> NOTE! NEEDED TO ADD THE MATH STANDARD LIBRARY IN LINKER OPTIONS OF PROJECT PROPERTIES IN ORDER TO USE VARIABLES INSIDE SQRT() FUNCTION!
//                              //GIVES "undefined reference to sqrt" otherwise!
                                //--> NOTE THIS ERROR MEANS THE LINKER CAN'T FIND WHERE THE SOURCE CODE DEFINING THE MATH.H HEADER FILE IS LOCATED
//    puts("Evaluating PRINTMES(1, \"x = %d.\\n\", x );");
//    PRINTMES(1, "x = %d.\n", x);
//    puts("Evaluating PRINTMES(2, \"x = %d, y = %.4f.\\n\", x, y);");
//    PRINTMES(2, "x = %d, y = %.4f.\n", x, y);
    
 //USING C PREDEFINED MACROS
//    printf("The file is %s.\n", __FILE__);
//    printf("The date is %s.\n", __DATE__);
//    printf("The time is %s.\n", __TIME__);
//    printf("The version is %ld.\n", __STDC_VERSION__);
//    printf("This is line %d.\n", __LINE__);
//    printf("This function is %s.\n", __func__);
//    whyme();
    
//USING A GENERIC SELECTION EXPRESSION AND USING THE MOST EFFICIENT TYPES FOR MATH FUNCTIONS
//    typedef struct {
//        int ival;
//        double dval;
//        char cval1;
//        char cval2;
//    } STypes;
//    
//    typedef union {
//        int ival;
//        char cval;
//    } UTypes;
//
//#define MYTYPE(X) _Generic((X),\
//    int: "int",\
//    double: "double",\
//    char: "char",\
//    STypes: "Structure STypes",\
//    UTypes: "Union UTypes",\
//    default: "other"\
//    )
//    
//    STypes s = { 1, 1.0, 'a', 'A' };
//    UTypes u = { 5 };
//    int i = 3;
//    double d = 3.1415;
//    char c = 'b';
//    
//    printf("Testing out generic function macro: #define MYTYPE(X) _Generic((X),"\
//            "int: \"int\", double: \"double\", char: \"char\", STypes: \"Structure STypes\", UTypes: \"Union UTypes\", default: \"other\"\n");
//    newline();
//    
//    printf("STypes s is of type %s.\n", MYTYPE(s));
//    printf("UTypes u is of type %s\n", MYTYPE(u));
//    printf("int i is of type %s\n", MYTYPE(i));
//    printf("double d is of type %s\n", MYTYPE(d));
//    printf("char c is of type %s\n", MYTYPE(c));
//    
//#define SQRT(X) _Generic((X),\
//    float: sqrtf(X),\
//    long double: sqrtl(X),\
//    default: sqrt(X))
//    
//    newline();
//    float x = 2.0F;
//    double xx = 2.0;
//    long double xxx = 2.0L;
//    
//    long double y = SQRT(x);
//    long double yy = SQRT(xx);
//    long double yyy = SQRT(xxx);
//    
//    printf("Using the generic macro function definition #define SQRT(X) _Generic((X),"\
//            "float: sqrtf(X), long double: sqrtl(X), default: sqrt(X))\n");
//    printf("x = 2.0F, xx = 2.0, and xxx = 2.0L\n");
//    printf("%10s%.25Lf\n", "y = " , y);
//    printf("%10s%.25Lf\n", "yy = ", yy);
//    printf("%10s%.25Lf\n", "yyy = ", yyy);
    
//USING THE QSORT() STANDARD FUNCTION OF STDLIB.H
#define ARRSIZE 500000
    
    srand( time(NULL) +  clock());
    
    double arrayd[ARRSIZE];
    fill_double_array(arrayd, ARRSIZE, 0.0, 150.0, 0.287);
    
    puts("The Double Array Before qsort(): ");
    print_array_double(arrayd, ARRSIZE);
    
    qsort(arrayd, ARRSIZE, sizeof(double), mycomp);
    
    newline();
    puts("The Double Array After qsort()");
    print_array_double(arrayd, ARRSIZE);
    
    newline();
    test_distribution_d(arrayd, ARRSIZE, arrayd[0], arrayd[ARRSIZE - 1]);
    
    newline();
    printf("Number of Items in Array: %d\n", ARRSIZE);
    printf("Number of Clock Ticks for Runtime: %ld\n", clock());
        
    return (EXIT_SUCCESS);
}

void whyme() {
    printf("This function is %s.\n", __func__);
    printf("This is line %d.\n", __LINE__);
}

int mycomp(const void *val1, const void *val2) {
    const double *d1 = (double *) val1;
    const double *d2 = (double *) val2;
    
    if( *d1 > *d2 ) {
        return 1;
    } else if( *d1 == *d2 ) {
        return 0;
    } else {
        return -1;
    }
}
