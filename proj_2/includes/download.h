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

struct hostent * getIP(HostRequestData *data);

void request_file(int sock_fd, HostRequestData* data, char port[]); 


#endif 
