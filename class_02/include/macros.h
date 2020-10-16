#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"



#define _POSIX_SOURCE 1
#define FALSE 0
#define TRUE 1

#define BIT(n) (1 << n)
#define MAX_SIZE_ARRAY 16383    // Should be 2^16-1, but using less to avoid overflow

/* MACROS FOR THE LLOPEN FLAG ------------------------------------------------------*/  

#define TRANSMITTER         0
#define RECEPTOR            1 

/* MACROS FOR THE ALARM ----------------------------------------------------------- */  

#define MAX_REJECTS     3
#define TRIES           3               /* Tries to read the receptor answers*/ 
#define TIMEOUT         3               /* Time to wait for the receptor answers*/


/* MACROS FOR THE PROTOCOL----------------------------------------------------------*/

#define FLAG 0x7E
#define ESC 0x7D
#define XOR_STUFFING(N)     (N^0x20)
/*Address Field*/

#define A               0x03    

/**Command Field*/

#define CMD_SET         0x03    /* SET command*/
#define CMD_DISC        0x0B    /* DISC command*/
#define CMD_UA          0x07    /* UA command*/ 

#define SWITCH(s)       !s
#define CMD_S1          0x40    /* S N(1)*/  
#define CMD_S0          0x00    /* S N(0)*/  
#define CMD_S(s)        (0x00 | ( s << 6 ))

#define CMD_RR1         0x85    /* RR*/ 
#define CMD_RR0         0x05    /* RR*/  
#define CMD_RR(r)       (0x05 | ( r << 7 ))

#define CMD_REJ1        0x81    /* REJ*/ 
#define CMD_REJ0        0x01    /* REJ*/ 
#define CMD_REJ(r)      (0x01 | ( r << 7 ))


#define MAX_SIZE 255 /* Max size of the package */
