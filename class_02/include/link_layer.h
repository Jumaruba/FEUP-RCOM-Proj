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


 

/* API -----------------------------------------------------------------------*/ 

int llopen(char * port, int flag, struct termios *oldtio, struct termios *newtio); 


/**
 * @brief Send a S (supervised) or U (non numerated) trama.
 * @param ADDR A, the address.
 * @param CMD C, the command.
 * @return int -1 on error, the number of characters transmited otherwise. 
 */
int send_frame_su(int fd, char ADDR, char CMD);


int read_frame_su(int fd, char CMD);  

int read_timeout_frame_su(int fd, char CMD);   


/**
 * @brief It opens the file and set the configurations to transmit the info.
 * @param port Stores the name of the file (e.g. /dev/ttyS10)
 * @param oldtio Previous configurations of the transmission
 * @param newtio New configurations of the transmission
 * @return Returns the file descriptor number
 */
int openDescriptor(char *port, struct termios *oldtio, struct termios *newtio);

/**
 * @brief Prints a string in the hexadecimal form
 * @param s String to be printed
 */
void print_hex(const char *s);

/**
 * @brief Construct a new handle alarm timeout object
 * 
 */
int handle_alarm_timeout(); 


void printSuccess(char* text);

void printError(char* text); 
#endif