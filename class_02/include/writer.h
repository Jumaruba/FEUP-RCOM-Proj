#ifndef WRITER_H
#define WRITER_H 


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h> 
#include <stdlib.h>
#include "../include/globals.h" 

#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;

 
/**
 * @brief Open the descriptor to send information. 
 * 
 * @param argv 
 * @return int 0 on success. 
 */
int openDescriptor(char** argv);  


/**
 * @brief Send a S (supervised) or U (non numerated) trama.
 * 
 * @param ADDR A, the address.
 * @param CMD C, the command.
 * @return int -1 on error, the number of characters transmited otherwise. 
 */
int send_SU(int fd, char ADDR, char CMD); 



#endif 