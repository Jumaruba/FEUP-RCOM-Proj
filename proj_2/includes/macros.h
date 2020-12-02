#include <stdio.h> 

#define MAX_STRING_LEN          511     // Max size for a string malloc 

#define SERVER_PORT 6000
#define SERVER_ADDR "192.168.28.96"         // router address 


#define DEBUG  1            		/* Set zero to don't show prints. */ 
#define SHOW_OUTPUT 1      			/* Show the information inside the state machines. */

#define PRINT_ERR(format, ...) \
    do{ \
    if (DEBUG) \
    printf("\033[31;1mERR\033[0m: %s:%d\t\t::\033[31;1m" format "\033[0m", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    }while(0)
    
#define PRINT_SUC(format, ...) \
    do{ \
    if (DEBUG) \
    printf("\033[32;1mSUC\033[0m: %s:%d\t\t::\033[32;1m" format "\033[0m", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    }while(0) 

#define PRINT_NOTE(format, ...) \
    do{ \
    if (DEBUG) \
    printf("\e[1;34mNOTE\e[0m: %s:%d\t\t::\e[1;34m" format "\e[0m", __FILE__, __LINE__, ##__VA_ARGS__ ); \
    }while(0)

#define PRINTF_BLUE(format, ...) \
    do{ \
    if (SHOW_OUTPUT) \
    printf("\e[1;34m"format "\e[0m", ##__VA_ARGS__ ); \
    }while(0)


#define PRINTF_WHITE(format, ...) \
    do{ \
    if (SHOW_OUTPUT) \
    printf("\033[1;37m"format "\033[0m", ##__VA_ARGS__ ); \
    }while(0)
