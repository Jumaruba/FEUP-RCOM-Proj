#ifndef CLIENT_H_ 
#define CLIENT_H_ 

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <strings.h> 
#include "macros.h"


/**
 * @brief   Initialized a socket. 
 * 
 * @param ip_addr   IP address. 
 * @param port      If the port is negative or zero, it's used the default port. Otherwise, the port given is used. 
 * @return int      Returns the socket descriptor. 
 */
int init_sokect(char* ip_addr, int  port); 

#endif 