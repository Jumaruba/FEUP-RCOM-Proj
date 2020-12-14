#ifndef DOWNLOAD_H
#define DOWNLOAD_H 

#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include "input_handler.h"
#include "client.h"
#include "io.h"
#include "utils.h"

struct hostent * getIP(HostRequestData *data);

/**
 * @brief Identification steps to access the website by ftp. 
 * 
 * @param sock_fd   Socket file descriptor. 
 * @param data      Data structure with information provided by the user. 
 * @param port      Port in format i.e 410,30, where the client will access and retrieve file.
 */
void identification(int sock_fd, HostRequestData* data, char port[]); 

/**
 * @brief Get the file name. 
 * 
 * @param data Data structure with information provided by the user. 
 */
void get_file_name(HostRequestData* data) ; 

#endif 
