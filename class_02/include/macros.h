#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"



#define _POSIX_SOURCE       1



#define DEBUG  1            /* Set zero to don't show prints*/ 

#define PRINT_ERR(format, ...) \
    do{ \
    if (DEBUG) \
    printf("\033[31;1mERR\033[0m: %s:%d\t::\033[31;1m" format "\033[0m\n", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    }while(0)
    
#define PRINT_SUC(format, ...) \
    do{ \
    if (DEBUG) \
    printf("\033[32;1mSUC\033[0m: %s:%d\t::\033[32;1m" format "\033[0m\n", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    }while(0)
    

#define FALSE               0
#define TRUE                1
#define SWITCH(s)           !s
#define BIT(n)              (1 << n)
#define MAX_SIZE_ARRAY      16383   // The actual max size is 2^16-1, but we're using less bytes to avoid overflow
#define MAX_SIZE            255     /* Max size of the package */ 
#define DELAY_US            0.2
/* MACROS FOR THE LLOPEN FLAG ------------------------------------------------------*/  

#define TRANSMITTER         0
#define RECEPTOR            1 

/* MACROS FOR THE ALARM AND LOOPS--------------------------------------------------- */  

#define TRIES               3   /* Tries to read the receptor answers*/ //TODO: do I need this? 
#define TIMEOUT             3   /* Time to wait for the receptor answers*/
#define TRIES_SEND          3   /* Tries to send the message */ //TODO: do I need this?  
#define TRIES_READ          3 
/* MACROS FOR THE PROTOCOL----------------------------------------------------------*/

#define FLAG                0x7E
#define ESC                 0x7D
#define XOR_STUFFING(N)     (N^0x20)
#define A                   0x03    

/**Command Field*/

#define CMD_SET             0x03        /* SET command*/
#define CMD_DISC            0x0B        /* DISC command*/
#define CMD_UA              0x07        /* UA command*/ 
#define CMD_S(s)            (0x00 | ( s << 6 )) 
#define CMD_RR(r)           (0x05 | ( r << 7 ))
#define CMD_REJ(r)          (0x01 | ( r << 7 ))


