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

