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
    
typedef struct {
    char title[MAXTITL];
    char author[MAXAUTH];
    float value;
} BOOK;

typedef struct {
    char name[NAMEMAX];
    float value;
} UTENSIL;

typedef struct {
    double first_val;
    int second_val;
    char third_val;
} RAND;

typedef struct flexible_struct {
    char name[20];
    int random_val;
    double flex_double_arr[];
} FLEX;

typedef union {
    BOOK book_info;
    UTENSIL utensil_info;
} SCHOOLITEMU;

typedef enum { book = 0, utensil = 1 } ITEMTYPE;   //Even though those assigned values are default, just making it clear.

typedef struct {
    ITEMTYPE type;
    SCHOOLITEMU current_item;
} SCHOOLITEMS;

typedef enum pbformat { format0, format1, format2, format3 } PBFORMAT;

typedef void (*PRINTBOOKFUNC)(const BOOK *);


    
    extern void print_utensil(const UTENSIL *ut_ptr);
    
    extern void print_rand(const RAND *rand_ptr);
    
    extern void print_flex(const FLEX *flex_ptr, int size_of_flex);
    
    extern void print_book_f0(const BOOK *book_ptr);
    
    extern void print_book_f1(const BOOK *book_ptr);
    
    extern void print_book_f2(const BOOK *book_ptr);
    
    extern void print_book_f3(const BOOK *book_ptr);
    
    extern void print_book(PRINTBOOKFUNC, const BOOK *book_ptr);

#ifdef __cplusplus
}
#endif

#endif /* CH14_H */

