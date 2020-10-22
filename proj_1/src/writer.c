/*Non-Canonical Input Processing*/

#include "../include/writer.h"

struct termios oldtio, newtio;
int fd;
int seqNum = 0; 

int main(int argc, char **argv) { 
    FILE* fp;  
    int contentSize = 10,  frameLength = 0, actual_contentSize = 0; 
    u_int8_t fileread = 1; 
    
    char * content[contentSize];
    byte* pack[MAX_SIZE_ALLOC];  
    byte* frame_ = (byte*)malloc(sizeof(byte)*MAX_SIZE_ALLOC);
    
    // OPEN FILE  
    byte * namefile = "testFile.txt";       // TODO: delete this later. 
    if (( fp = fopen(namefile, "rb")) == NULL){
        PRINT_ERR("Not possible to open file"); 
        return -1; 
    } 

    // Get size of file. 
    fseek(fp, 0L, SEEK_END); 
    int fileSize = ftell(fp); 

    // Pointer back to the beggining. 
    fseek(fp, 0L, SEEK_SET); 


   // SET CHANNEL 
   install_alarm();
   fd = llopen(argv[1], TRANSMITTER, &oldtio, &newtio);   




    //CONTROL PACKAGE START 
    int size = create_controlPackage(CTRL_START, namefile, fileSize, pack); 
    llwrite(fd, pack, &size);   
    
    while(TRUE){
        if ((actual_contentSize = fread(content, 1, contentSize, fp)) <= 0) { 
            break; 
        }


        if (create_dataPackage(seqNum, content, actual_contentSize, frame_) <0){
            PRINT_ERR("create_dataPackage error"); 
            return -1; 
        }

        
        frameLength = actual_contentSize + 4; 

        if (llwrite(fd, frame_, &frameLength) < 0){
            PRINT_ERR("LLWRITE error"); 
            return -1; 
        }

        seqNum++;    
        if (fileSize - seqNum * contentSize < contentSize ) contentSize = fileSize%contentSize; 
    }
        
    
    //CONTROL PACKAGE END 
    size = create_controlPackage(CTRL_END, namefile, strlen(content), pack); 
    llwrite(fd, pack, &size); 


   //CLOSE
   llclose(fd, TRANSMITTER, &oldtio); 


}

void install_alarm() {
    if (signal(SIGALRM, handle_alarm_timeout) == SIG_ERR)
    {
        PRINT_ERR("Not possible to install signal, SIG_ERR.");
        llclose(fd, CMD_DISC, &oldtio);
    }
    siginterrupt(SIGALRM, TRUE);
}
