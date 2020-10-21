/*Non-Canonical Input Processing*/

#include "../include/reader.h"

int fd;
struct termios oldtio, newtio; 
int main(int argc, char **argv) { 
  

    // SET CHANNEL
    fd = llopen(argv[1], RECEPTOR, &oldtio, &newtio); 
    byte *buffer = (byte *) malloc(MAX_SIZE_ARRAY*sizeof(byte)); 


    int length = llread(fd, buffer);   
    PRINTF("\nTRAMA INFO: \n"); 
    for (int i = 0 ; i< length; i++)
        PRINTF("%02x ", buffer[i]); 

    PRINTF("\n\n"); 


    llclose(fd, RECEPTOR, &oldtio); 
}

