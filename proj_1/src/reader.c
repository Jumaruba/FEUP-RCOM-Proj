/*Non-Canonical Input Processing*/

#include "../include/reader.h"

int fd;
struct termios oldtio, newtio;
int seqNum = 0; 

int main(int argc, char **argv) { 
    
    // Information about the file. 
    char * namefile = (char*)malloc(sizeof(char)*MAX_SIZE_ALLOC);
    char * outputfile = (char*)malloc(sizeof(char)*MAX_SIZE_ALLOC);   
    byte *package = (byte *) malloc(MAX_SIZE_ALLOC*sizeof(byte));  
    byte* info = (byte*)malloc(sizeof(byte)*MAX_SIZE_ALLOC);   
    FILE *fp;

    int filesize;  
    package[0] = 4;  

    u_int8_t received_start = FALSE; 

    // CHECK USAGE 
    char firstLetters[9];
    if(argc == 3){
        strcpy(outputfile, argv[2]);
        strncpy(firstLetters, argv[1], 9); 
        if (strcmp(firstLetters, "/dev/ttyS") != 0){
            PRINT_ERR("Usage: /dev/ttySX <path_file>");
            exit(-1);
        }
    }else if(argc == 2){
        outputfile = namefile; 
        strncpy(firstLetters, argv[1], 9); 
        if (strcmp(firstLetters, "/dev/ttyS") != 0){
            PRINT_ERR("Usage: /dev/ttySX <path_file>");
            exit(-1);
        }
    }else{
        PRINT_ERR("Usage: /dev/ttySX <path_file>");  
        exit(-1); 
    }

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

    fp = fopen(outputfile, "w");

    //READ DATA 
    while(TRUE){ 
        llread(fd,package);  
        if (package[0] == CTRL_DATA){
            read_dataPackage(&seqNum, info, package);
            fputs(info, fp); 
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

