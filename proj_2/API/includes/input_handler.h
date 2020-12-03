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
    char file_name[MAX_STRING_LEN];
} HostRequestData;

/**
 * @brief Function that handles the input given by the user
 * 
 * @param argc      Number of arguments. 
 * @param argv      Arguments passed.  
 * @param data      Data structure to store information provided by the user. 
 */
void input_handler(int argc, char **argv, HostRequestData* data); 

/**
 * @brief Treats the url provided and extracts all necessary information. 
 * 
 * @param remain_url        URL without ftp:// 
 * @param remain_url_size      
 * @param data              Data structure to store information provided by the user. 
 */
void parse_input(char* remain_url, int remain_url_size, HostRequestData* data); 

/**
 * @brief IO function to provide a better user interface. 
 * 
 * @param data          Data structure to store information provided by the user. 
 */
void print_data(HostRequestData* data);  


#endif  
