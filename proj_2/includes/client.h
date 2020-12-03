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
#include <string.h> 
#include "macros.h"
#include "io.h"


/**
 * @brief   Initialized a socket. 
 * 
 * @param ip_addr   IP address. 
 * @param port      If the port is negative or zero, it's used the default port. Otherwise, the port given is used. 
 * @return int      Returns the socket descriptor. 
 */
int init_socket(char* ip_addr, int  port); 

void read_rsp(int sock_fd, char* response_code); 

/**
 * @brief Read the response for the pasv command.
 * 
 * @param sock_fd           Scoket descriptor. 
 * @param response_code     Code response. 
 * @param port              Number of the port. 
 */
void read_psv(int sock_fd, char* response_code, char* port); 

void write_cmd(int sock_fd, char* cmd, char* data); 

void real_port(char port[], char real_port[]); 
 
void calculate_real_port(char* first_pos, char* second_pos, char real_port[]); 
#endif 