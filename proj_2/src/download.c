#include "../includes/download.h"


int main(int argc, char *argv[]){ 
	
	HostRequestData * data = (HostRequestData*)malloc(sizeof(HostRequestData));  
	
	int statusMessage = input_handler(argc, argv, data);  
	
	printf("%d\n", statusMessage); 
    return 0;
}
