#ifndef GLOBALS_H
#define GLOBALS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1
#define FALSE 0
#define TRUE 1
#define BYTE 1

#define BIT(n) 1 << n

/* MACROS FOR THE PROTOCOL*/

#define FLAG 0x7E

/*Address Field*/

#define ADDR_CMD_EMI 0x30 /* Command sent by the emissor*/
#define ADDR_ANS_EMI 0x01 /* Answer sent by the receptor*/

#define ADDR_CMD_REC 0x01 /* Command sent by the emissor*/
#define ADDR_ANS_REC 0x30 /* Aswser sent by the receptor*/

/**Command Field*/

#define CMD_SET 0x03  /* SET command*/
#define CMD_DISC 0x0B /* DISC command*/

/*Ans Field*/
#define CMD_UA 0x07 /* UA command*/
#define ANS_RR(n) 0x05 | BIT(n)
#define ANS_REJ(n) 0x01 | BIT(n)

#define MAX_SIZE 255 /* Max size of the package */

typedef struct linkLayer
{
    char port[20];                 /* Trasnmission port /dev/ttySx, x = 0, 1*/
    int fd;                        /* File descritor*/ 
    int baudRate;                  /* Max vel of transmission*/
    unsigned int sequenceNumber;   /* Number of the frame sequence i = 0,1*/
    unsigned int timeout;          /* Value to wait for the answer*/
    unsigned int numTransmissions; /* Number of tries until now to read a failed transmission*/

    char frame[MAX_SIZE];          
} LinkLayer; 

/**
 * @brief Send a S (supervised) or U (non numerated) trama.
 * @param ADDR A, the address.
 * @param CMD C, the command.
 * @return int -1 on error, the number of characters transmited otherwise. 
 */
int send_SU(int fd, char ADDR, char CMD);

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