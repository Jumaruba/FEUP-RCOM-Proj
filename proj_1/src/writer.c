/*Non-Canonical Input Processing*/

#include "../include/writer.h"

struct termios oldtio, newtio;
int fd;
int numTransmissions = 0;  
int seqNum = 0; 

int main(int argc, char **argv)
{
    int res;

   // SET CHANNEL 
   install_alarm();
   fd = llopen(argv[1], TRANSMITTER, &oldtio, &newtio);   

    
    //create control package 
    //send control package 


   while(TRUE){ 
       //get package 
       //send package 
       //check index 
   }

   //send llclose 

   byte *data = (byte *)malloc(sizeof(byte) * 5); 
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

void install_alarm() {
    // Install the alarm.
    if (signal(SIGALRM, handle_alarm_timeout) == SIG_ERR)
    {
        PRINT_ERR("Not possible to install signal, SIG_ERR.");
        llclose(fd, CMD_DISC, &oldtio);
    }
    siginterrupt(SIGALRM, TRUE);
}
