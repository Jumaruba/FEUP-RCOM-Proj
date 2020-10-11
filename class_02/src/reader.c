/*Non-Canonical Input Processing*/

#include "../include/reader.h"

int fd;
struct termios oldtio, newtio; 
LinkLayer * linkLayer; 
int main(int argc, char **argv) { 
    if ((argc < 2) ||
        ((strcmp("/dev/ttyS10", argv[1]) != 0) &&
         (strcmp("/dev/ttyS11", argv[1]) != 0))) {
        printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
        exit(1);
    }

    linkLayer = (LinkLayer*)malloc(sizeof(LinkLayer)); 
    memcpy(linkLayer->port, argv[1], strlen(argv[1])+1);
    linkLayer->fd = openDescriptor(linkLayer->port, &oldtio, &newtio); 
    printf("%d\n", fd);

    read_SU(CMD_SET); 
    
    tcsetattr(linkLayer->fd, TCSANOW, &oldtio);
    sleep(1);
    close(fd);
    return 0;
}

int read_SU(char CMD){
    int curr_state = 0;            /* byte that is being read. From 0 to 4.*/  
    char byte; 

    while(curr_state < 5){
        read(linkLayer->fd, &byte, 1);  

        switch(curr_state){  
            // RECEIVE FLAG
            case 0: 
                printf("case 0: %02x\n", byte); 
                if (byte == FLAG) 
                    curr_state++;   
                break;  

            // RECEIVE ADDR
            case 1: 
                printf("case 1: %02x\n", byte); 
                if (byte == ADDR_CMD_EMI)
                    curr_state++; 
                else if (byte != FLAG) 
                    curr_state = 0; 
                break;  

            // RECEIVE CMD 
            case 2: 
                printf("case 2: %02x\n", byte); 
                if (byte == CMD)
                    curr_state++; 
                else if (byte == FLAG) 
                    curr_state = 1; 
                else curr_state = 0; 
                break; 
            // RECEIVE BCC 
            case 3:  
                printf("case 3: %02x\n", byte); 
                if (byte == (CMD ^ ADDR_CMD_EMI))
                    curr_state++; 
                else if (byte == FLAG)
                    curr_state = 1; 
                else curr_state = 0; 
                break; 

            // RECEIVE FLAG
            case 4:   
                printf("case 4: %02x\n", byte); 
                if (byte == FLAG)
                    curr_state++; 
                else curr_state = 0; 
        } 
    }
    return 0; 
}

void testFunction() {
    char buf[MAX_SIZE];
    int res;
    int counter = 0;
    int fd = linkLayer->fd; 
    while (STOP == FALSE || counter == 10) {           /* loop for input */
        res = read(fd, buf, 255);       /* returns after 5 chars have been input */
        print_hex(buf);
        printf("writen %d bytes\n", res);
        counter ++;
        if (strcmp(buf, "z") == 0) STOP = TRUE;
    }
}
