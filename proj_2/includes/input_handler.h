#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

typedef struct host_request_data{
    char * user; 
    char * password;  
    char * host; 
    char * path; 
} HostRequestData;
 

int read_input(char* argv, HostRequestData* data); 

#endif 