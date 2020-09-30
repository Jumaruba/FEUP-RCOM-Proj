/*Non-Canonical Input Processing*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

#define BAUDRATE B38400                 // Setting the bit rate. The B0 bit  cc,,rate is used to terminate the connection 
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
#define MAX 255

volatile int STOP=FALSE;

int main(int argc, char** argv)
{
    int fd,c, res;
    struct termios oldtio,newtio;
    char buf[MAX] = {'\0'};
    int i, sum = 0, speed = 0;
    
    if ( (argc < 2) || 
  	     ((strcmp("/dev/ttyS0", argv[1])!=0) && 
  	      (strcmp("/dev/ttyS1", argv[1])!=0) )) {
      printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
      exit(1);
    }

  /*
    Open serial port device for reading and writing and not as controlling tty
    because we don't want to get killed if linenoise sends CTRL-C.
  */

    fd = open(argv[1], O_RDWR | O_NOCTTY );
    if (fd <0) {perror(argv[1]); exit(-1); }

    if ( tcgetattr(fd,&oldtio) == -1) {       /* save current port settings */
      perror("tcgetattr");
      exit(-1);
    }

    bzero(&newtio, sizeof(newtio));           // cleans all the structure to zero 

    /*
      CS8 - 	is the characther size mask 
      CLOCAL - 	ignore modem control lines 
      CREAD - 	enable receiver 
    */
    newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD; 

	/*
	 * IGNPAR - ignore parity errors
	 */ 
    newtio.c_iflag = IGNPAR; 

	/*
	 * c_oflag - this is the output mode
	 */ 
    newtio.c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio.c_lflag = 0;
	
    newtio.c_cc[VTIME]    = 0;   /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 5;   /* blocking read until 5 chars received */



  /* 
    VTIME e VMIN devem ser alterados de forma a proteger com um temporizador a 
    leitura do(s) proximo(s) caracter(es)
  */

	
	/* 
	 * Descarta a informação escrita para o fd 
	 * TCIFLUSH - Descarta informação recebida, mas não lida
	 * TCOFLUSH - Descarta informação escrita, mas não transmitida 
	 * TCIOFLUSH - Faz os dois ultimos pontos
	 */

    tcflush(fd, TCIOFLUSH);
	

    if ( tcsetattr(fd,TCSANOW,&newtio) == -1) {
      perror("tcsetattr");
      exit(-1);
    }
    sleep(1);

    printf("New termios structure set\n");

    if (gets(buf) != NULL){
		printf("Error with gets\n"); 
		exit(-1); 
	} 

    printf("%d\n", strlen(buf));
    
    res = write(fd,buf, strlen(buf) + 1);  

  	if (res < 0){
		printf("Error while write\n"); 
		exit(-1); 
	} 

    printf("%d bytes written\n", res); 


  /* 
    O ciclo FOR e as instru��es seguintes devem ser alterados de modo a respeitar 
    o indicado no gui�o 
  */

   
    if ( tcsetattr(fd,TCSANOW,&oldtio) == -1) {
      perror("tcsetattr");
      exit(-1);
    }
    sleep(1);


    close(fd);
    return 0;
}
