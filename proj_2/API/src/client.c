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

void read_rsp(int sock_fd, char* response_code){
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
                // One line response 
                else if (byte == ' ') {  
                    // Expect another reply before proceeding with a new command
                    if (response_code[0] == PSV_PREL && !exceptions_one_line(response_code)) is_multiple_line = 1; 
                    else is_multiple_line = 0;
                    curr_state = 1;     
                }
                else response_code[index_response++] = byte; 
            break;  

            case 1: 
                // If it's multiple line, goes back to the beggining of state machine.
                if (byte == '\n' && is_multiple_line){
                    index_response = 0; 
                    curr_state = 0; 
                }
                else if (byte == '\n' && !is_multiple_line) curr_state = 2;  
            break; 
        } 
    } 

}

void read_psv(int sock_fd, char* response_code, char* port){
    char byte;  
    int curr_state = 0;  
    int index_response = 0;  
    int comman_index = 0;  

    while(curr_state != 5){
        read(sock_fd, &byte, 1); 
        PRINTF_RESPONSE("%c", byte);   

        switch(curr_state){ 

            // Always one line response. 
            case 0:   
                if (byte == ' ') curr_state++; 
                else response_code[index_response++] = byte; 
            break;     

            // Discard until '(' 
            case 1:  
                if (byte == '(') curr_state++;
            break;  

            // Gets the ip address and discard. 
            case 2:   
                comman_index = byte == ',' ? comman_index+1: comman_index;  
                if (comman_index == 4){
                    curr_state++; 
                    index_response = 0; 
                } 
            break;  

            // Gets the port and store. 
            case 3: 
                if (byte == ')') {
                    curr_state = 4;   
                    port[index_response] = '\0'; 
                }
                else port[index_response++] = byte;  
            break;   
 
            // Waits for the end of line 
            case 4:
                if (byte == '\n') curr_state++; 
            break; 
        } 
    } 
}

void write_cmd(int sock_fd, char* cmd, char* data){
    write(sock_fd, cmd, strlen(cmd)); 
    write(sock_fd, data, strlen(data)); 
    write(sock_fd, "\n", strlen("\n")); 
} 

void get_real_port(char port[], int* real_port){

    char *first_pos = malloc(4); 
    char *second_pos = malloc(4);   
    int first_pos_int, second_pos_int;   

    int index_comman = strcspn(port, ","); 

    // Separate bytes by comman.
    memcpy(first_pos, &port[0], index_comman);
    memcpy(second_pos, &port[index_comman+1], strlen(port)-index_comman); 
 
    // From string to integer. 
    sscanf(first_pos, "%d", &first_pos_int); 
    sscanf(second_pos, "%d", &second_pos_int);

    *real_port = first_pos_int*256 + second_pos_int;  

    // IO 
    PRINT_SUC("Real port calculated\n");  
    io_int("REAL PORT", *real_port);  

    free(first_pos); 
    free(second_pos); 
}
