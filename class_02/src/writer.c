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

    openDescriptor(argv); 

    res = send_SU(fd, ADDR_ANS_EMI, CMD_SET);
    printf("%d bytes written\n", res);

   
    if ( tcsetattr(fd,TCSANOW,&oldtio) == -1) {
      perror("tcsetattr");
      exit(-1);
    }

    close(fd);
    return 0;
}

int openDescriptor(char** argv){

    fd = open(argv[1], O_RDWR | O_NOCTTY ); 

    if (fd <0) {perror(argv[1]); exit(-1); }

    if ( tcgetattr(fd,&oldtio) == -1) { /* save current port settings */
      perror("tcgetattr");
      exit(-1);
    }

    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;

    newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 5;   /* blocking read until 5 chars received */

    tcflush(fd, TCIOFLUSH);

    if ( tcsetattr(fd,TCSANOW,&newtio) == -1) {
      perror("tcsetattr");
      exit(-1);
    }

    printf("New termios structure set\n"); 

    return 0; 
} 

int send_SU(int fd, char ADDR, char CMD){
  char trama[5];  
  trama[0] = FLAG; 
  trama[1] = ADDR;
  trama[2] = CMD;
  trama[3] = trama[1] ^ trama[2]; 
  trama[4] = FLAG; 

  int res = write(fd, trama, 5); 
  return res; 
}