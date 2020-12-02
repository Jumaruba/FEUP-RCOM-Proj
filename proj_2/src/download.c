#include "../includes/download.h"


int main(int argc, char *argv[]){ 
	
	HostRequestData * data = (HostRequestData*)malloc(sizeof(HostRequestData));  
	
	input_handler(argc, argv, data);  
	
    return 0;
}
