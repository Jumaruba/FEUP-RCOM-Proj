#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"



#define _POSIX_SOURCE 1

#define FALSE 0
#define TRUE 1
#define SWITCH(s)           !s
#define BIT(n)              (1 << n)
#define MAX_SIZE_ARRAY      16383    // The actual max size is 2^16-1, but we're using less bytes to avoid overflow
#define MAX_SIZE 255 /* Max size of the package */ 

/* MACROS FOR THE LLOPEN FLAG ------------------------------------------------------*/  

#define TRANSMITTER         0
#define RECEPTOR            1 

/* MACROS FOR THE ALARM AND LOOPS--------------------------------------------------- */  

#define MAX_REJECTS     3               /* Max number of rejection in the information frame*/
#define TRIES           3               /* Tries to read the receptor answers*/ 
#define TIMEOUT         3               /* Time to wait for the receptor answers*/


/* MACROS FOR THE PROTOCOL----------------------------------------------------------*/

#define FLAG 0x7E
#define ESC 0x7D
#define XOR_STUFFING(N)     (N^0x20)
#define A                   0x03    

/**Command Field*/

#define CMD_SET             0x03        /* SET command*/
#define CMD_DISC            0x0B        /* DISC command*/
#define CMD_UA              0x07        /* UA command*/ 
#define CMD_S(s)            (0x00 | ( s << 6 )) 
#define CMD_RR(r)           (0x05 | ( r << 7 ))
#define CMD_REJ(r)          (0x01 | ( r << 7 ))


