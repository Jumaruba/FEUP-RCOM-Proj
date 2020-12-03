#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include <string.h>   
#include <stdlib.h> 
#include <stdio.h> 
#include "macros.h" 
#include "io.h"

typedef struct host_request_data{
    char user[MAX_STRING_LEN]; 
    char password[MAX_STRING_LEN];  
    char host[MAX_STRING_LEN]; 
    char path[MAX_STRING_LEN*2];  
    char url [MAX_STRING_LEN*5];
} HostRequestData;
 
void input_handler(int argc, char **argv, HostRequestData* data); 

void parse_input(char* remain_url, int remain_url_size, HostRequestData* data); 
 
void print_data(HostRequestData* data);  

#endif  
