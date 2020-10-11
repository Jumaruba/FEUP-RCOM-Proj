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

    testFunction();

    tcsetattr(linkLayer->fd, TCSANOW, &oldtio);
    sleep(1);
    close(fd);
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
