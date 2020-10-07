#ifndef GLOBALS_H 
#define GLOBALS_H

#define BYTE            1

#define BIT(n)                  1 << n 

/* MACROS FOR THE PROTOCOL*/ 

#define FLAG                    0x7E         

/*Address Field*/ 

#define ADDR_CMD_EMI            0x30        /* Command sent by the emissor*/  
#define ADDR_ANS_EMI            0x01        /* Answer sent by the receptor*/  

#define ADDR_CMD_REC            0x01        /* Command sent by the emissor*/ 
#define ADDR_ANS_REC            0x30        /* Aswser sent by the receptor*/ 

/**Command Field*/ 

#define CMD_SET                 0x03
#define CMD_DISC                0x0B

/*Ans Field*/ 
#define CMD_UA                  0x07
#define ANS_RR(n)               0x05 | BIT(n) 
#define ANS_REJ(n)              0x01 | BIT(n) 

#endif 