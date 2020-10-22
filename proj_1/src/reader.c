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
    char * namefile = (char*)malloc(sizeof(char)*MAX_SIZE_ARRAY);  
    int filesize; 
    read_controlPackage(buffer, namefile, &filesize, length); 
    PRINTF("NAMEFILE: %s\n", namefile); 
    PRINTF("FILESIZE: %d\n", filesize); 

    PRINTF("\n\n"); 


    llclose(fd, RECEPTOR, &oldtio); 
}

