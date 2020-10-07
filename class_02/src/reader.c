/*Non-Canonical Input Processing*/

#include "../include/reader.h"

int fd; 
struct termios oldtio,newtio; 

int main(int argc, char** argv)
{
    int c, res; 

    char buf;
    unsigned int bytes;

    if ( (argc < 2) ||
  	     ((strcmp("/dev/ttyS10", argv[1])!=0) &&
  	      (strcmp("/dev/ttyS11", argv[1])!=0) )) {
      printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
      exit(1);
    }

    openDescriptor(argv,&oldtio, &newtio, &fd); 
    
    while (STOP==FALSE) {           /* loop for input */
      res = read(fd,&buf,1);       /* returns after 5 chars have been input */
      printf(":%x:%d\n", buf & 0xff, res);

      /* TODO: checa bits */ 

      bytes = write(fd,buf,res); 	/* returns to the emissor the message*/
      if (buf=='z') STOP=TRUE;
    }


    tcsetattr(fd,TCSANOW,&oldtio);
    sleep(1);
    close(fd);
    return 0;
}
