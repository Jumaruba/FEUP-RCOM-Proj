#ifndef GLOBALS_H
#define GLOBALS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macros.h"


typedef struct linkLayer
{
    char port[20];                 /* Trasnmission port /dev/ttySx, x = 0, 1*/
    int fd;                        /* File descritor*/ 
    int baudRate;                  /* Max vel of transmission*/
    unsigned int sequenceNumber;   /* Number of the frame sequence i = 0,1*/
    unsigned int timeout;          /* Value to wait for the answer*/
    unsigned int numTransmissions; /* Number of tries for a filed transmission*/

    char frame[MAX_SIZE];          
} LinkLayer; 


/* API -----------------------------------------------------------------------*/ 

int llopen(char * port, int flag, struct termios *oldtio, struct termios *newtio); 


/**
 * @brief Send a S (supervised) or U (non numerated) trama.
 * @param ADDR A, the address.
 * @param CMD C, the command.
 * @return int -1 on error, the number of characters transmited otherwise. 
 */
int send_SU(int fd, char ADDR, char CMD);

void printSuccess(char* text);

void printError(char* text); 

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
#endif