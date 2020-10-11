#ifndef READER_H
#define READER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "globals.h"

volatile int STOP = FALSE;

/**
 * @brief Read a supervision frame or a non enumerated frame.
 * 
 * @param CMD The command expected. 
 * @return int 0 in case of sucess. 
 */
int read_SU(char CMD);  

/**
 * @brief Function to help with tests. It just prints what it's supposed to. In a near future will be deleted.
 */
void testFunction();
#endif