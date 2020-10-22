/*Non-Canonical Input Processing*/

#include "../include/writer.h"

struct termios oldtio, newtio;
int fd;
int seqNum = 0; 

int main(int argc, char **argv)
{
    int res;
    int packSize = 255, actual_PackSize = 0; 

    // TODO: to define; 

   // SET CHANNEL 
   install_alarm();
   fd = llopen(argv[1], TRANSMITTER, &oldtio, &newtio);   

    
    //create control package 
    //send control package 
    char * content = "juliane e guilherme não gostam de rcom."; 
    char * namefile = "file"; 
    char * pack = (char*)malloc(sizeof(char)*MAX_SIZE_ARRAY); 
    int size = create_controlPackage(CTRL_START, namefile, strlen(content), pack); 
    llwrite(fd, pack, &size); 
    free(pack); 
/*

    while(TRUE){

        char * pack = (char*)malloc(sizeof(char)*packSize);  
        if ((actual_PackSize = get_pack(numTransmission, content, size, packSize, pack)) < 0){  
            PRINT_SUC("End of sending loop"); 
            break;
        }  

        char * frame = (char*)malloc(sizeof(char)*(actual_PackSize+4)); 
        int length = create_dataPackage(numTransmission, pack, actual_PackSize,frame);  

        llwrite(fd, frame, (actual_PackSize + 4)); 

    } 
        */



   // CLOSE
   llclose(fd, TRANSMITTER, &oldtio); 


}

void install_alarm() {
    // Install the alarm.
    if (signal(SIGALRM, handle_alarm_timeout) == SIG_ERR)
    {
        PRINT_ERR("Not possible to install signal, SIG_ERR.");
        llclose(fd, CMD_DISC, &oldtio);
    }
    siginterrupt(SIGALRM, TRUE);
}
