#include "../includes/utils.h"


bool exceptions_one_line(char *code){
	//150, 125
	return 
		(*(code) == '1' && *(code+1) == '5' && *(code+2) == '0')
		|| (*(code) == '1' && *(code+1) == '2' && *(code+2) == '5')
	;
}