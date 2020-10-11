/*Non-Canonical Input Processing*/

#include "../include/writer.h"

struct termios oldtio, newtio;
LinkLayer * linkLayer; 
int main(int argc, char **argv) {
    int res;
    if ((argc < 2) ||
        ((strcmp("/dev/ttyS10", argv[1]) != 0) &&
         (strcmp("/dev/ttyS11", argv[1]) != 0))) {
        printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
        exit(1);
    }
    
    linkLayer = (LinkLayer*)malloc(sizeof(LinkLayer)); 
    memcpy(linkLayer->port, argv[1], strlen(argv[1])+1);
    linkLayer->fd = openDescriptor(linkLayer->port, &oldtio, &newtio);
    printf("%d\n", linkLayer->fd);
    

    res = send_SU(linkLayer->fd, ADDR_CMD_EMI, CMD_SET);
    printf("%d bytes written\n", res);


    if (tcsetattr(linkLayer->fd, TCSANOW, &oldtio) == -1) {
        perror("tcsetattr");
        exit(-1);
    }

    close(linkLayer->fd);
    return 0;
}


