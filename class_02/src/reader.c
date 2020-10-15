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
    fd = llopen(argv[1], RECEPTOR, &oldtio, &newtio);

    // SET TRANSMISSION 
    read_SU(fd, CMD_SET); 
    printf("Received CMD_SET with success\n");

    if (send_SU(fd, ADDR_ANS_REC, CMD_UA) <= 0)
        printf("Error sending answer to the emissor\n"); 


    tcsetattr(fd, TCSANOW, &oldtio);
    sleep(1);
    close(fd);
    return 0;
}

