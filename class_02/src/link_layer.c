#include "../include/link_layer.h"




int llopen(char * port, int flag, struct termios *oldtio, struct termios *newtio){ 
    int fd; 
    if (TRANSMITTER == flag){
        fd = openDescriptor(port, oldtio, newtio); 
    }
    else if (RECEPTOR == flag){
        fd = openDescriptor(port, oldtio, newtio); 
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