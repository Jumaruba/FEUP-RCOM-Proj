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
#include <errno.h>

 
typedef unsigned char byte; 

/* API -----------------------------------------------------------------------*/ 
/**
 * @brief Set the port configuration and establish the connecction. 
 * 
 * @param port String containing the path of the string.
 * @param flag The plot of the caller, i.e TRANSMITTER, RECEPTOR
 * @return int -1 in case of error, number of the file descriptor otherwise. 
 */
int llopen(byte * port, int flag); 

int llwrite(int fd, byte* data, int *data_length); 

int llread(int fd, byte * data); 

int llclose(int fd, int flag); 

/* AUX API -------------------------------------------------------------------*/ 

/* Read and send frames */ 

int read_frame_supervision(int fd, byte *CMD, int r);  

int read_frame_not_supervision(int fd, byte CMD);  

int send_frame_nnsp(int fd, byte ADDR, byte CMD);  

int read_frame_i(int fd, byte *buffer, byte *CMD); 

/* Create information frame */ 

int create_frame_i(byte * data, byte * frame, int data_length, byte CMD); 

int byte_stuffing(byte * frame, int *frame_length); 

int byte_destuffing(byte * frame, int * frame_length);

void create_BCC2(byte * data, byte *buffer, int data_length); 


/* ALARM -----------------------------------------------------------------------*/ 

void install_alarm();  

int handle_alarm_timeout();    

void alarm_off(); 

/* OTHERS ---------------------------------------------------------------------*/ 

int openDescriptor(byte *port, struct termios *oldtio, struct termios *newtio);


#endif
