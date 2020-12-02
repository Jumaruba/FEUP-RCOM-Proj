#include "../includes/client.h"

int init_socket(char *ip_addr, int port)
{
    int sockfd;
    struct sockaddr_in server_addr;
    int actual_port = port <= 0 ? SERVER_PORT : port; 

    
    /*server address handling*/
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_addr); /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(actual_port);        /*server TCP port must be network byte ordered */

    /*open an TCP socket*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        PRINT_ERR("Not possible to open socket\n");
        exit(0);
    }

    /*connect to the server*/
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        PRINT_ERR("Not possible to connect to socket\n");
        exit(0);
    }

    return sockfd; 
} 


void read_response(int sock_fd, char* response_code){
    char byte;  
    int curr_state = 0;  
    int index_response = 0;  
    int is_multiple_line = 0;       // If it's a multiple line response. 

    while(curr_state != 2){
        read(sock_fd, &byte, 1); 
        PRINTF_RESPONSE("%c", byte);   

        switch(curr_state){
            case 0:   
                // It's a multiple line response. 
                if (byte == '-'){ 
                    is_multiple_line = 1; 
                    curr_state = 1; 
                } 
                else if (byte == ' ') { 
                    is_multiple_line = 0;
                    curr_state = 1;     
                }
                else response_code[index_response++] = byte; 
            break;  

            case 1: 
                if (byte == '\n' && is_multiple_line){
                    index_response = 0; 
                    curr_state = 0; 
                }
                else if (byte == '\n' && !is_multiple_line) curr_state = 2; 
            break; 
        } 
    } 

}