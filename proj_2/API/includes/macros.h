#include <stdio.h> 

#define MAX_STRING_LEN          511     // Max size for a string malloc 

#define SERVER_PORT 21              /* Default port*/
#define DEBUG  1            		/* Set zero to don't show prints. */ 
#define SHOW_OUTPUT         1      	/* Shows API default information. */
#define SHOW_TEXT_RESPONSE  1       /* Shows the response text*/ 

// RESPONSES 
// https://en.wikipedia.org/wiki/List_of_FTP_server_return_codes 
#define PSV_PREL        '1'     // Positive preliminary reply. 
#define PSV_COMPL       '2'     // Positive completion. 
#define PSV_INTER       '3'     // Positive intermeduate completion. 
#define NEG_TRANS       '4'     // Negative transitive completion. 
#define NEG_PERMN       '5'     // Negative permanent completion.

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


#define PRINTF_RESPONSE(format, ...) \
    do{ \
    if (SHOW_TEXT_RESPONSE) \
    printf("\033[1;37m"format "\033[0m", ##__VA_ARGS__ ); \
    }while(0)

