#include "../include/link_layer.h"




int llopen(char * port, int flag, struct termios *oldtio, struct termios *newtio){ 
    int fd; 
    if (TRANSMITTER == flag){
        fd = openDescriptor(port, oldtio, newtio); 
    }
    else if (RECEPTOR == flag){
        fd = openDescriptor(port, oldtio, newtio); 

        // SEND FRAME
        read_SU(fd, CMD_SET); 
        printf("Received CMD_SET with success\n");

        if (send_SU(fd, ADDR_ANS_REC, CMD_UA) <= 0)
            printf("Error sending answer to the emissor\n"); 
    }
    return fd;
}


int send_SU(int fd, char ADDR, char CMD) {
    char frame[5];
    frame[0] = FLAG;
    frame[1] = ADDR;
    frame[2] = CMD;
    frame[3] = frame[1] ^ frame[2];
    frame[4] = FLAG;

    int res = write(fd, frame, 5);
    return res;
}

int read_SU(int fd, char CMD){
    int curr_state = 0;            /* byte that is being read. From 0 to 4.*/  
    char byte; 
    while(curr_state < 5){
        read(fd, &byte, 1);  
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



void printSuccess(char* text){
    printf ("\033[32;1m SUCCESS: %s \033[0m\n", text);
}

void printError(char* text){
    printf ("\033[31;1m FAILURE: %s \033[0m\n", text);
}


int openDescriptor(char *port, struct termios *oldtio, struct termios *newtio) {
    int fd = open(port, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        printf("%s\n", port);
        perror(port);
        exit(-1);
    }

    if (tcgetattr(fd, oldtio) == -1) { /* save current port settings */
        perror("tcgetattr");
        exit(-1);
    }

    bzero(newtio, sizeof(newtio));
    newtio->c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio->c_iflag = IGNPAR;
    newtio->c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio->c_lflag = 0;

    newtio->c_cc[VTIME] = 0;   /* inter-character timer unused */
    newtio->c_cc[VMIN] = 1;   /* blocking read until 5 chars received */

    tcflush(fd, TCIOFLUSH);

    if (tcsetattr(fd, TCSANOW, newtio) == -1) {
        perror("tcsetattr");
        exit(-1);
    }

    printf("New termios structure set\n");

    return fd; 
}

void print_hex(const char *s) {
    while (*s)
        printf("%02x", (unsigned int) *s++);
    printf("\n");
}