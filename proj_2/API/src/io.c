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

bool exceptions_one_line(char *code){
	//150, 125
	return 
		(*(code) == '1' && *(code+1) == '5' && *(code+2) == '0')
		|| (*(code) == '1' && *(code+1) == '2' && *(code+2) == '5')
	;
}