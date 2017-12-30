/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>

#include "ch1to10.h"
#include "ch11.h"

#define MAXTITL 41
#define MAXAUTH 31

struct book {
    char title[MAXTITL];
    char author[MAXAUTH];
    float value;
};

struct rand {
    double first_val;
    int second_val;
    char third_val;
};

struct flexible_struct {
    char name[20];
    int random_val;
    double flex_double_arr[];
};

void print_book(const char name[], const struct book * book_ptr) {
    printf("%s: %s by %s: $%.2f\n",
            name, book_ptr->title, book_ptr->author, book_ptr->value);
}

void print_rand(const char name[], const struct rand * rand_ptr) {
    printf("%s: Double Value: %f, Integer Value: %d, Character Value: %c\n",
            name, rand_ptr->first_val, rand_ptr->second_val, rand_ptr->third_val);
}

void print_flex(const char name[], const struct flexible_struct *flex_ptr, int size_of_flex) {
    printf("%s: Name: %s, Random Value: %d, Double Array: ",
            name, flex_ptr->name, flex_ptr->random_val);
    print_array_double(flex_ptr->flex_double_arr, size_of_flex);
}
