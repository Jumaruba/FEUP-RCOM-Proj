#ifndef WRITER_H
#define WRITER_H 


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h> 

#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;

/* Macros for the protocol*/ 

#define FLAG            0x7E         

#define CMD_EMI         0x30        /* Command sent by the emissor*/  
#define ANS_EMI         0x01        /* Answer sent by the receptor*/  

#define CMD_REC         0x01        /* Command sent by the emissor*/ 
#define ANS_REC         0x30        /* Aswser sent by the receptor*/ 

#endif 