/*Non-Canonical Input Processing*/

#include "../include/reader.h"

int fd;
struct termios oldtio, newtio; 
int main(int argc, char **argv) { 
    if ((argc < 2) ||
        ((strcmp("/dev/ttyS10", argv[1]) != 0) &&
         (strcmp("/dev/ttyS11", argv[1]) != 0))) {
        printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
        exit(1);
    }

    fd = llopen(argv[1], RECEPTOR, &oldtio, &newtio);


    tcsetattr(fd, TCSANOW, &oldtio);
    sleep(1);
    close(fd);
    return 0;
}

