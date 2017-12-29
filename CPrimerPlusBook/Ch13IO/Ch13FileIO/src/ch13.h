/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ch13.h
 * Author: abdullah
 *
 * Created on December 28, 2017, 11:42 PM
 */

#ifndef CH13_H
#define CH13_H

#ifdef __cplusplus
extern "C" {
#endif

    #define MAX_FILE_LENGTH 255
    #define CTRL_Z '\032'
    

//    extern int get_file_name(char* file_str);
    extern char* fget_string_input(char* str, int size_of_str, FILE* file);
    
    extern void seek_file(FILE* file, long offset, int starting_position);
    
    extern void close_file(FILE* file);
    
    extern void set_start_end(FILE* file, fpos_t* file_start, fpos_t* file_end);
    
    extern void append(FILE* source, FILE* destination);


#ifdef __cplusplus
}
#endif

#endif /* CH13_H */

