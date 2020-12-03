#include "../includes/input_handler.h"




void input_handler(int argc, char **argv, HostRequestData* data){
	
    if (argc != 2){
        PRINT_ERR("Wrong number of arguments, usage:: ./download // ftp://[<user>:<password>@]<host>/<url-path>"); 
        exit(-1);
    }
    memcpy(data->url, argv[1], strlen(argv[1])); 

    // Checks the presence of ftp://
	if(strncmp("ftp://", data->url, 6) != 0){
		PRINT_ERR("Not a ftp:// website\n"); 
        exit(-1); 
	} 
    
    // Get string after ftp://   
    int size_remain_url = strlen(data->url) - 5; 
    char remain_url[size_remain_url]; 
    memcpy(remain_url, &data->url[6], size_remain_url);  
    
    // Store website info inside data struct.  
    parse_input(remain_url, size_remain_url, data);   

    print_data(data);
    
 
} 

// ftp://[<user>:<password>@]<host>/<url-path>
void parse_input(char* remain_url, int remain_url_size, HostRequestData* data){  
    int curr_state = 0;  
    int curr_pos_parameter = 0; 

    for (int i = 0 ; i < remain_url_size; i++){
        char curr_char = remain_url[i]; 

        switch(curr_state){
            case 0:  
                if (curr_char == ':') {
                    curr_state++;   
                    curr_pos_parameter = 0; 
                }
                else data->user[curr_pos_parameter++] = curr_char; 
            break;   
            
            case 1: 
                if (curr_char == '@') {
                    curr_state++;   
                    curr_pos_parameter = 0; 
                }
                else data->password[curr_pos_parameter++] = curr_char; 
            break;  

            case 2: 
                if (curr_char == '/') { 
                    curr_pos_parameter = 0; 
                    curr_state ++;  
                }
                else data->host[curr_pos_parameter++] = curr_char;  
            break;  

            case 3: 
                data->path[curr_pos_parameter++] = curr_char; 
            break;  
        }
    }
    
    if (curr_state != 3){
        PRINT_ERR("Wrong argument, usage: ftp://[<user>:<password>@]<host>/<url-path>\n"); 
        exit(-1); 
    }

}   


// IO 
void print_data(HostRequestData* data){
    // Output print.  
    label("USER INPUT");
    io("USERNAME", data->user); 
    io("PASSWORD", data->password);  
    io("HOST   ", data->host);  
    io("PATH   ", data->path);  
    io("URL    ", data->url); 
    io("FILENAME", data->file_name);
}