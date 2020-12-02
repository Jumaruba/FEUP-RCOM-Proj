#include "../includes/input_handler.h"




int input_handler(int argc, char **argv, HostRequestData* data){
	
    char * website = argv[1]; 
	if(strncmp("ftp://", website, 6) != 0){
		PRINT_ERR("Not a ftp:// website\n"); 
        exit(-1); 
	} 
    
    // Get string after ftp://   
    int size_remain_url = strlen(website) - 5; 
    char remain_url[size_remain_url]; 
    memcpy(remain_url, &website[6], size_remain_url); 
    printf("%s\n", remain_url) ; 

    
    // Store website info inside data struct.  
    parse_input(remain_url, data);  
    
	return 0; 
 
} 
void parse_input(char* remain_url, HostRequestData* data){  
    char parameters[6][MAX_STRING_LEN]; 
    split_input(remain_url, parameters);  

}  

void split_input(char* remain_url, char parameters[][MAX_STRING_LEN]){
    char delim[] = ":@";    
    int counter = 0;   

    char * ptr = strtok(remain_url, delim);  


    while(ptr != NULL && counter < 3){
        memcpy(parameters[counter], ptr, strlen(ptr));          // Store parameter.  
        PRINTF("url parameter: %s\n", ptr); 
        counter ++;                          
        ptr = strtok(NULL, delim);                              // Split.   
    }            
    
    // Get the host.
    int first_bar_pos = strcspn(parameters[2], "/"); 
    memcpy(parameters[3], &parameters[2], first_bar_pos); 
    parameters[3][first_bar_pos] = '\0'; 




    printf("%s\n", parameters[2]);
    printf("%s\n", parameters[3]); 


    memcpy(parameters[4], &parameters[2][first_bar_pos+1], MAX_STRING_LEN); 
    printf("%s\n", parameters[4]);
    printf("%d\n", first_bar_pos);
    if (counter < 3){
        PRINT_ERR("Wrong url format ftp://[<user>:<password>@]<host>/<url-path>\n");
        exit(-1); 
    }
}


	

