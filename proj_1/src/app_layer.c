#include "../include/app_layer.h" 


int create_dataPackage(char seqNum, char* info, int length, char* data){  

    data[0] = CTRL_DATA; 
    data[1] = seqNum; 
    data[2] = length % 256; 
    data[3] = (int) (length / 256); // L2
    
    memcpy(&data[4], info, length);  
    return 0; 
} 

int create_controlPackage(char C, char T, char * info, int length, char* data){

    data[0] = C;  
    data[1] = T; 
    data[2] = length;  
    
    memcpy(&data[3], info, length);  

}