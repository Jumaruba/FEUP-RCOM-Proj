/*Non-Canonical Input Processing*/

#include "../include/writer.h" 

int fd; 
struct termios oldtio,newtio; 

int main(int argc, char** argv)
{
    int c, res;
    char buf[255];
    int i, sum = 0, speed = 0;
    
    if ( (argc < 2) || 
  	     ((strcmp("/dev/ttyS10", argv[1])!=0) && 
  	      (strcmp("/dev/ttyS11", argv[1])!=0) )) {
      printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
      exit(1);
    }

    openDescriptor(argv, &oldtio, &newtio, &fd); 

    res = send_SU(fd, ADDR_ANS_EMI, CMD_SET);
    printf("%d bytes written\n", res);

   
    if ( tcsetattr(fd,TCSANOW,&oldtio) == -1) {
      perror("tcsetattr");
      exit(-1);
    }

    close(fd);
    return 0;
}


