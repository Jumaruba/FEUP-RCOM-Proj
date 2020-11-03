/*Non-Canonical Input Processing*/

#include "../include/reader.h"

int fd;
int seqNum = 0; 

int main(int argc, char **argv) { 
    
    // Information about the file. 
    char * namefile = (char*)malloc(sizeof(char)*MAX_SIZE_ALLOC);
    char  outputfile[MAX_SIZE_ALLOC]; 
    byte *package = (byte *) malloc(MAX_SIZE_ALLOC*sizeof(byte));  
    byte* info = (byte*)malloc(sizeof(byte)*MAX_SIZE_ALLOC);   
    FILE *fp;
    int length; 

    int filesize;  
    package[0] = 4;  

    u_int8_t received_start = FALSE;  
    // CHECK USAGE  

    if(argc == 3){ 
        strcpy(outputfile, argv[2]);  
        if (strncmp(argv[1], "/dev/ttyS", 9) != 0){ 
            PRINT_ERR("Usage: /dev/ttySX <path_file>");
            exit(-1);
        }  
    }else{
        PRINT_ERR("Usage: /dev/ttySX <path_file>");  
        exit(-1); 
    }

    // SET CHANNEL
    PRINT_NOTE("LLOPEN CALL"); 
    if( (fd = llopen(argv[1], RECEPTOR)) == -1 ) {
        PRINT_ERR("Could not open descriptor on port %s.", argv[1]); 
        exit(-1);
    } 

    //RECEIVE START PACKAGE
    while(received_start != TRUE){
        length = llread(fd, package);    
        if (package[0] == CTRL_START){
            PRINT_SUC("Received package start");  
            read_controlPackage(package, namefile, &filesize, length);  
            received_start = TRUE; 
        } 
    } 

    if( (fp = fopen(outputfile, "wb")) == NULL ) {
        PRINT_ERR("%d", errno); 
        exit(-1);
    }  

    //READ DATA 
    while(TRUE){   
        if ( (length = llread(fd,package)) < 0){
            PRINT_ERR("Could not read file descriptor.");
        }

        if (package[0] == CTRL_DATA){
            length = read_dataPackage(&seqNum, info, package);
            fwrite(info, sizeof(byte), length, fp); 
        }

        memset(info, 0, strlen(info));
        if (package[0] == CTRL_END){
            char *end_outputfile[MAX_SIZE_ALLOC]; 
            int end_filesize; 
            read_controlPackage(package, end_outputfile, &end_filesize, length); 
            if (strcmp(end_outputfile, namefile) != 0)
                PRINT_ERR("End file name: %s :-: Begin file name: %s", end_outputfile, namefile); 
            if (filesize != end_filesize)
                PRINT_ERR("End size: %d :-: Begin size: %d", end_filesize, filesize);
            
            break;
        }  


    }

    printf("NAMEFILE: %s\n", namefile); 
    printf("FILESIZE: %d\n", filesize);   
    
    PRINT_NOTE("LLCLOSE CALL");
    llclose(fd, RECEPTOR); 
    free(info); 
    free(package); 
    free(namefile); 
    
    if( (fclose(fp)) == EOF ) {
        PRINT_ERR("%s", stderr); 
        exit(-1);
    }
}

