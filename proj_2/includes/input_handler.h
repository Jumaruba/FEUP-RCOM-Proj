#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include <string.h>   
#include <stdlib.h> 
#include <stdio.h> 
#include "macros.h"

typedef struct host_request_data{
    char * user; 
    char * password;  
    char * host; 
    char * path; 
} HostRequestData;
 
int input_handler(int argc, char **argv, HostRequestData* data); 

void parse_input(char* remain_url, HostRequestData* data); 

void split_input(char* remain_url, char parameters[][MAX_STRING_LEN]); 
#endif  
