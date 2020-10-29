#define BAUDRATE B38400
#define MODEMDEVICE "/dev/ttyS1"
#define _POSIX_SOURCE       1


#define FRAME_SIZE      14              /* This size must not be less than 10*/
/* DEBUG MACROS ------------------------------------------------------------------------------------------------*/

#define DEBUG  1            /* Set zero to don't show prints. */ 
#define SHOW_OUTPUT 0       /* Show the information inside the state machines. */
#define PRINT_ERR(format, ...) \
    do{ \
    if (DEBUG) \
    printf("\033[31;1mERR\033[0m: %s:%d\t\t::\033[31;1m" format "\033[0m\n", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    }while(0)
    
#define PRINT_SUC(format, ...) \
    do{ \
    if (DEBUG) \
    printf("\033[32;1mSUC\033[0m: %s:%d\t\t::\033[32;1m" format "\033[0m\n", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    }while(0) 

#define PRINT_NOTE(format, ...) \
    do{ \
    if (DEBUG) \
    printf("\e[1;34mNOTE\e[0m: %s:%d\t\t::\e[1;34m" format "\e[0m\n", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    }while(0)

#define PRINTF(format, ...) \
    do{ \
    if (SHOW_OUTPUT) \
    printf("\e[1;34m"format "\e[0m", ##__VA_ARGS__ ); \
    }while(0)


/* MACROS FOR THE LLOPEN FLAG --------------------------------------------------------------------------------------*/  

#define TRANSMITTER         0
#define RECEPTOR            1 

/* MACROS FOR THE ALARM AND LOOPS---------------------------------------------------------------------------------- */  

#define TRIES               3   /* Tries to read the receptor answers*/ //TODO: do I need this? 
#define TIMEOUT             3   /* Time to wait for the receptor answers*/
#define TRIES_READ          3   // TODO: do I need this? 
/* MACROS FOR THE PROTOCOL-------------------------------------------------------------------------------------------*/

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

/* MACROS FOR THE APPLICATION --------------------------------------------------------------------------------------*/ 

#define CTRL_DATA           1
#define CTRL_START          2 
#define CTRL_END            3 

#define T_FILE_SIZE         0
#define T_FILE_NAME         1
#define T_MD5               2       //TODO: if we have time, create md5 

/* OTHERS  ---------------------------------------------------------------------------------------------------------*/
#define FALSE               0
#define TRUE                1
#define SWITCH(s)           !s
#define BIT(n)              (1 << n)
#define MAX_SIZE_ALLOC      16000     /* Max size of the package */ 
#define DELAY_US            0.2

