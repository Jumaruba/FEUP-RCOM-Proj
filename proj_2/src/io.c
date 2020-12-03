#include "../includes/io.h"


void label(char *text){
    int padding = (LABEL - strlen(text))/2; 

    for (int i = 0; i < padding; i++) PRINTF_WHITE("-"); 
    PRINTF_WHITE("%s", text); 
    for (int i = 0; i < padding; i++) PRINTF_WHITE("-");  
    PRINTF_WHITE("\n");
}

void io(char* text, char* value){
	PRINTF_WHITE("%s \t", text);
	PRINTF_BLUE(" %s\n", value); 
} 

void io_int(char* text, int value){
	PRINTF_WHITE("%s \t", text);
	PRINTF_BLUE(" %d\n", value); 
}