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

    byte * data = (byte*)malloc(sizeof(byte)*5); 

    data[0] = 0x01; 
    data[1] = FLAG; 
    data[2] = ESC; 
    data[3] = 0xA0; 
    data[4] = 0xFF; 

    int length = 5; 
    llwrite(fd, data, &length);
    // CLOSE
    
    llclose(fd, TRANSMITTER, &oldtio); 
}



