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

/* API -----------------------------------------------------------------------*/ 

int llopen(char * port, int flag, struct termios *oldtio, struct termios *newtio); 

int llwrite(int fd, char * data, int *data_length); 

int llread(int fd, char * buffer, char CMD_expected); 

int llclose(); 

/* AUX API -------------------------------------------------------------------*/ 

int send_frame_su(int fd, char ADDR, char CMD);

inline int send_frame_i(int fd, char * frame, int frame_length); 

int read_frame_su(int fd, char CMD);  

int read_timeout_frame_su(int fd, char CMD);   

int read_timeout_frame_i(int fd, char CMD); 

int create_frame_i(char * data, char * frame, int data_length, char CMD); 

int byte_stuffing(char * frame, int *frame_length); 

int byte_destuffing(char * frame, int * frame_length);

void create_BCC2(char * data, char *buffer, int data_length); 

int openDescriptor(char *port, struct termios *oldtio, struct termios *newtio);

/* ALARM -----------------------------------------------------------------------*/ 

int handle_alarm_timeout(); 

void alarm_off(); 

#endif