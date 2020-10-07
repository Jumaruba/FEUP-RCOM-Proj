#ifndef WRITER_H
#define WRITER_H 


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h> 
#include <stdlib.h>

#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

volatile int STOP=FALSE;

/**
 * @brief Send first 3 bytes of the header : FLAG, ADDRESS FIELD, COMMAND FIELD
 * 
 * @param CMD Command field
 * @param ADDR Address field
 * @return int -1 in case of error, the number of bytes written otherwise
 */
int send_header(char ADDR, char CMD); 


#endif 