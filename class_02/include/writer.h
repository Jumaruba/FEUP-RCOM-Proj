#ifndef WRITER_H
#define WRITER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "globals.h" 

volatile int STOP = FALSE;

#define TRIES           3               /* Tries to read the receptor answers*/ 
#define TIMEOUT         3               /* Time to wait for the receptor answers*/

/**
 * @brief Read reader answer sent due a previous command frame.
 * 
 * @param CMD The command expected. 
 * @return int 0 in case of sucess, 1 otherwise.  
 */
int read_timeout_SU(char CMD);   

/**
 * @brief Construct a new handle alarm timeout object
 * 
 */
handle_alarm_timeout(); 


#endif