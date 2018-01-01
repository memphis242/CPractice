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

#include "src/ch1to10.h"
#include "src/ch11.h"
#include "src/ch14.h"
#include "src/ch15.h"

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
    
//USING FUNCTION MACROS, STRINGIZING (<-- LOL AT THAT NAME), THE ## OPERATOR, AND VARIADIC FUNCTION MACROS
#define SQUARE(X) X*X
#define SQUARE1(X) (X)*(X)
#define SQUARE2(X) ((X)*(X))
#define PRINT(X) printf("The result is %d.\n", X)
#define PRINTSQ(X) printf("The square of " #X " is %d.\n", SQUARE2(X));
#define XNAME(N) x ## N
#define PRINTXN(N) printf("x" #N " is %d\n", x ## N);
#define PRINTMES(X, ...) printf("Message " #X ": " __VA_ARGS__);
    
    int x = 5;
    double y;
    int z;
    
    puts("Note the following are the macro definitions.");
    puts("SQUARE(X) X*X");
    puts("SQUARE1(X) (X)*(X)");
    puts("SQUARE2(X) ((X)*(X))");
    puts("PRINTSQ(X) printf(\"The square of \" #X \"is %d.\\n\", SQUARE2(X));");
    puts("XNAME(N) x ## N");
    puts("PRINTMES(X, ...) printf(\"Message \" #X \": \" __VA_ARGS__);");
    
    newline();
    newline();
    
    printf("x = %d\n", x);
    newline();
    
    z = SQUARE(x);  //Eq. to x*x
    printf("Evaluating SQUARE(X): ");
    PRINT(z);
    newline();
    
    z = SQUARE(2);  //Eq. to 2*2
    printf("Evaluating SQUARE(2): ");
    PRINT(z);
    newline();
    
    printf("Evaluating SQUARE(x+2): ");
    PRINT(SQUARE(x+2)); //Eq. to x+2*x+2, which is eq. to x + (2*x) + 2
    printf("Evaluating SQUARE1(x+2): ");
    PRINT(SQUARE1(x+2));
    printf("Evaluating SQUARE2(x+2): ");
    PRINT(SQUARE2(x+2));
    newline();
    
    printf("Evaluating 100/SQUARE(2): ");
    PRINT(100/SQUARE(2));   //Eq. to 100/2*2, which is eq. to (100 / 2) * 2
    printf("Evaluating 100/SQUARE1(2): ");
    PRINT(100/SQUARE1(2));
    printf("Evaluating 100/SQUARE2(2): ");
    PRINT(100/SQUARE2(2));
    newline();
    
    printf("x is %d.\n", x);
    
    printf("Evaluating SQUARE(++x): ");
    PRINT(SQUARE(++x)); //Eq. to ++x*++x, which is eq. to (++x) * (++x)
    newline();
    
    printf("Evaluating SQUARE(x++): ");
    PRINT(SQUARE(x++)); //Eq. to x++*x++
    newline();
    
    printf("After incrementing, x is %d.\n", x);
    
    printf("Evaluating PRINTSQ(x).\n");
    PRINTSQ(x); //Eq. to printf("The square of " "x" "is %d.\n", ((x)*(x)));
    newline();
    
    puts("Evaluating XNAME(1) = 35");
    int XNAME(1) = 35;
    PRINTXN(1);
    newline();
    
    y = sqrt((double) x);    //--> NOTE! NEEDED TO ADD THE MATH STANDARD LIBRARY IN LINKER OPTIONS OF PROJECT PROPERTIES IN ORDER TO USE VARIABLES INSIDE SQRT() FUNCTION!
                    //GIVES "undefined reference to sqrt" otherwise!
    puts("Evaluating PRINTMES(1, \"x = %d.\\n\", x );");
    PRINTMES(1, "x = %d.\n", x);
    puts("Evaluating PRINTMES(2, \"x = %d, y = %.4f.\\n\", x, y);");
    PRINTMES(2, "x = %d, y = %.4f.\n", x, y);
        
    return (EXIT_SUCCESS);
}

