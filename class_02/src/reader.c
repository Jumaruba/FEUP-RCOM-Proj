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

    // SET CHANNEL
    fd = llopen(argv[1], RECEPTOR, &oldtio, &newtio); 
    byte *buffer = (byte *) malloc(MAX_SIZE_ARRAY*sizeof(byte)); 
    int length = llread(fd, buffer);  



    printf("\n TRAMA INFO: \n"); 
    for (int i = 0 ; i< length; i++)
        printf("%02x\n", buffer[i]); 

    length = llread(fd, buffer);   
    printf("\n TRAMA INFO: \n"); 
    for (int i = 0 ; i< length; i++)
        printf("%02x\n", buffer[i]); 


    tcsetattr(fd, TCSANOW, &oldtio);
    sleep(1);
    close(fd);
    return 0;
}

