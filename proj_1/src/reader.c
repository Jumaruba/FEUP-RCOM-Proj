/*Non-Canonical Input Processing*/

#include "../include/reader.h"

int fd;
struct termios oldtio, newtio;
int seqNum = 0; 

int main(int argc, char **argv) { 
    
    // Information about the file. 
    char * namefile = (char*)malloc(sizeof(char)*MAX_SIZE_ALLOC);   
    byte *package = (byte *) malloc(MAX_SIZE_ALLOC*sizeof(byte));  
    byte* info = (byte*)malloc(sizeof(byte)*MAX_SIZE_ALLOC);   

    int filesize;  
    package[0] = 4;  

    u_int8_t received_start = FALSE; 

    // SET CHANNEL
    PRINT_NOTE("LLOPEN CALL"); 
    fd = llopen(argv[1], RECEPTOR, &oldtio, &newtio);  

    //RECEIVE START PACKAGE
    while(received_start != TRUE){
        int length = llread(fd, package);    
        if (package[0] == CTRL_START){
            PRINT_SUC("Received package start");  
            read_controlPackage(package, namefile, &filesize, length);  
            received_start = TRUE; 
        } 
    } 

    

    //READ DATA 
    while(TRUE){ 
        llread(fd,package);  

        if (package[0] == CTRL_DATA){
            read_dataPackage(&seqNum, info, package);
            printf("%s\n", info); 

        }

        memset(info, 0, strlen(info));
        if (package[0] == CTRL_END) break; 


    }


    free(info); 
    free(package);  

    printf("NAMEFILE: %s\n", namefile); 
    printf("FILESIZE: %d\n", filesize);  


    PRINT_NOTE("LLCLOSE CALL");
    llclose(fd, RECEPTOR, &oldtio); 
}

