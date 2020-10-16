/*Non-Canonical Input Processing*/

#include "../include/writer.h"

struct termios oldtio, newtio;
int fd;  

int main(int argc, char **argv)
{
    int res;
    if ((argc < 2) ||
        ((strcmp("/dev/ttyS10", argv[1]) != 0) &&
         (strcmp("/dev/ttyS11", argv[1]) != 0)))
    {
        printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
        exit(1);
    }

    // SET CHANNEL 
    fd = llopen(argv[1], TRANSMITTER, &oldtio, &newtio); 

    byte * data = (byte*)malloc(sizeof(byte)*3); 
    data[0] = 0xA0; 
    data[1] = ESC; 
    data[2] = ESC; 
    int length = 3; 
    llwrite(fd , data, &length);  

    // CLOSE
    
    if (tcsetattr(fd, TCSANOW, &oldtio) == -1)
    {
        perror("tcsetattr");
        exit(-1);
    }
    close(fd);
    return 0;
}



