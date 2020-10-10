#include "../include/globals.h"

int send_SU(int fd, char ADDR, char CMD) {
    char trama[5];
    trama[0] = FLAG;
    trama[1] = ADDR;
    trama[2] = CMD;
    trama[3] = trama[1] ^ trama[2];
    trama[4] = FLAG;

    int res = write(fd, trama, 5);
    return res;
}


int openDescriptor(char **argv, struct termios *oldtio, struct termios *newtio, int *fd) {
    *fd = open(argv[1], O_RDWR | O_NOCTTY);
    if (*fd < 0) {
        perror(argv[1]);
        exit(-1);
    }

    if (tcgetattr(*fd, oldtio) == -1) { /* save current port settings */
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

    tcflush(*fd, TCIOFLUSH);

    if (tcsetattr(*fd, TCSANOW, newtio) == -1) {
        perror("tcsetattr");
        exit(-1);
    }

    printf("New termios structure set\n");
}

void print_hex(const char *s) {
    while (*s)
        printf("%02x", (unsigned int) *s++);
    printf("\n");
}