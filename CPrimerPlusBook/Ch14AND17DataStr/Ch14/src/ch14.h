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
    
#define MAXTITL 41
#define MAXAUTH 31
#define MAXBKS 20
    
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

    extern void print_book(const char name[], const struct book *book_ptr);
    
    extern void print_rand(const char name[], const struct rand *rand_ptr);
    
    extern void print_flex(const char name[], const struct flexible_struct *flex_ptr, int size_of_flex);


#ifdef __cplusplus
}
#endif

#endif /* CH14_H */

