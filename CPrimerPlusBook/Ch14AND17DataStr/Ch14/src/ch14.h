/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ch14.h
 * Author: abdullah
 *
 * Created on December 29, 2017, 5:57 PM
 */

#ifndef CH14_H
#define CH14_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define MAXTITL 50
#define MAXAUTH 50
#define MAXBKS 20
#define NAMEMAX 20
#define MAXCOUNT 10
#define MAXITEMS 10
    
struct book {
    char title[MAXTITL];
    char author[MAXAUTH];
    float value;
};

struct utensil {
    char name[NAMEMAX];
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

union school_item {
    struct book book_info;
    struct utensil utensil_info;
};

enum item_type { book = 0, utensil = 1 };   //Even though those assigned values are default, just making it clear.

struct school_item_un {
    enum item_type item;
    union school_item current_item;
};

    extern void print_book(const char name[], const struct book *book_ptr);
    
    extern void print_utensil(const char name[], const struct utensil *ut_ptr);
    
    extern void print_rand(const char name[], const struct rand *rand_ptr);
    
    extern void print_flex(const char name[], const struct flexible_struct *flex_ptr, int size_of_flex);


#ifdef __cplusplus
}
#endif

#endif /* CH14_H */

