/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vectorNAVinterface.h
 * Author: abdullah
 *
 * Created on January 5, 2018, 12:37 AM
 */

#ifndef VECTORNAVINTERFACE_H
#define VECTORNAVINTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
    
typedef struct termios SERIALPORT;

int openport(void);

SERIALPORT * setup_comport(int comport);

void setup_comport_config(int file_descriptor, SERIALPORT *config);

int pollcomport(int comport, unsigned char *buf, int size);

int sendbyte(int comport_number, unsigned char byte);

int sendbuf(int comport, unsigned char *buf, int size);

void flushRX(int comport_number);

void flushTX(int comport_number);

void flushRXTX(int comport_number);

void closeport(int file_descriptor);


#ifdef __cplusplus
}
#endif

#endif /* VECTORNAVINTERFACE_H */

