#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int static_extern_var;

void function_without_header(void);

void static_var_ex(void) {
    static int static_var = 1;
    int non_static_var = 1;
    char output_string[100];   //just to practice with sprintf()

    printf("Initial Value of Static Variable: %d\tInitial Value of Non-Static Variable: %d\n", static_var, non_static_var);
    puts("");

    sprintf(output_string, "Static variable: %d\tNon-Static Variable: %d", static_var, non_static_var);

    static_var++;
    non_static_var++;

    puts(output_string);

    puts("");
}

void print_external(void) {
    printf("static_extern_var: %d\n", static_extern_var);
}

static void useless_function(void) {
    puts("I am pretty much usless. I'm just here to demonstrate what a static function is.");
}

void function_without_header(void) {
    puts("You are calling this external function without a header defined. This means you are in the same directory.");
}
