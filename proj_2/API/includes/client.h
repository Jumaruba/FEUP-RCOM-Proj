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
#include "utils.h"


/**
 * @brief   Initialized a socket. 
 * 
 * @param ip_addr   IP address. 
 * @param port      If the port is negative or zero, it's used the default port. Otherwise, the port given is used. 
 * @return int      Returns the socket descriptor. 
 */
int init_socket(char* ip_addr, int  port); 

/**
 * @brief Reads and treat the answer of a command. 
 * 
 * @param sock_fd           Socket descriptor. 
 * @param response_code     Response of the code. 
 */
void read_rsp(int sock_fd, char* response_code); 

/**
 * @brief Read the response for the pasv command.
 * 
 * @param sock_fd           Scoket descriptor. 
 * @param response_code     Code response. 
 * @param port              Number of the port. 
 */
void read_psv(int sock_fd, char* response_code, char* port); 

/**
 * @brief Write the command in the socket 
 * 
 * @param sock_fd           Socket descriptor. 
 * @param cmd               Command. 
 * @param data              Data for the command. 
 */
void write_cmd(int sock_fd, char* cmd, char* data); 

/**
 * @brief From the port given by the pasv command get the real port. 
 * 
 * @param port              Port given by the pasv command, i.e "102,40"
 * @param real_port         Returns the real port as string, i.e 102*256+40
 */
void get_real_port(char port[], int* real_port); 

#endif 