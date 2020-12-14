#ifndef _IO_H_
#define _IO_H_ 

#include "macros.h"
#include <string.h> 
#include <stdbool.h>


#define LABEL       50  


void label(char* text); 

void io(char* text, char* value); 

void io_int(char* text, int value); 

#endif 