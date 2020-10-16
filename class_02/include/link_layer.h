#ifndef GLOBALS_H
#define GLOBALS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "macros.h"
#include "utils.h"

 
typedef enum STATES{
    START_STATE,
    FLAG_STATE, 
    ADDR_STATE, 
    CMD_STATE, 
    BBC1_STATE, 
    INFO_STATE, 
    SEVEND_STATE, 
    BBC2_STATE, 
} ;


typedef unsigned char byte; 

/* API -----------------------------------------------------------------------*/ 

int llopen(byte * port, int flag, struct termios *oldtio, struct termios *newtio); 

int llwrite(int fd, byte* data, int *data_length); 

int llread(int fd, byte * buffer); 

int llclose(); 

/* AUX API -------------------------------------------------------------------*/ 

/* Read and send frames */ 

int send_frame_nnsp(int fd, byte ADDR, byte CMD); 

int read_frame_i(int fd, byte *buffer, byte CMD); 

int read_frame_nn(int fd, byte CMD);  

int read_frame_timeout_nn(int fd, byte *CMD); 

int read_frame_timeout_sp(int fd, byte CMD);   

/* Create information frame */ 

int create_frame_i(byte * data, byte * frame, int data_length, byte CMD); 

int byte_stuffing(byte * frame, int *frame_length); 

int byte_destuffing(byte * frame, int * frame_length);

void create_BCC2(byte * data, byte *buffer, int data_length); 


/* ALARM -----------------------------------------------------------------------*/ 

int handle_alarm_timeout(); 

void alarm_off(); 

/* OTHERS ---------------------------------------------------------------------*/ 

int openDescriptor(byte *port, struct termios *oldtio, struct termios *newtio);


#endif