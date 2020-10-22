#include "./proj_1/include/macros.h"  
#include "./proj_1/include/link_layer.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int numTransmission = 0; 
int get_pack(int index, byte* data, int length, int packSize, char* pack){
    if (length < 0){
        PRINT_ERR("Length must be positive"); 
        return -1; 
    }  

    int posInit = packSize* index;  
    if (posInit > length){
        PRINT_NOTE("Initial position must be less then the data length");  
        return -1; 
    }
    int posEnd  = packSize* (index+1) > length? length: packSize* (index+1);  
    int actualPackSize = posEnd - posInit; 

    if (memcpy(pack, &data[posInit], actualPackSize) == NULL){
        PRINT_ERR("Error creating package"); 
        return -1; 
    }

    return actualPackSize; 
}

int create_dataPackage(int seqNum, byte* info, int length, byte* frame){  

    frame[0] = CTRL_DATA; 
    frame[1] = seqNum % 256;  
    frame[2] = length / 256; // L2
    frame[3] = length % 256;

    if (memcpy(&frame[4], info, length) == NULL){
        PRINT_ERR("Error while copying package."); 
        return -1; 
    }

    PRINT_SUC("Created data package");
    return 0; 
} 

int main(int argc, char ** argv){

    char * content = "juliane e guilherme não gostam de fazer o trabalho de RCOM porque  é extremamente chato.\n"; 
    
    int size = strlen(content); 
    int packSize = 4; 
    int actual_PackSize = 0; 
    char * finalContent = (char*)malloc(sizeof(char)*MAX_SIZE_ARRAY); 
    while(TRUE){

        char * pack = (char*)malloc(sizeof(char)*packSize);  
        if ((actual_PackSize = get_pack(numTransmission, content, size, packSize, pack)) < 0){  
            PRINT_SUC("End of sending loop"); 
            break;
        }  

        char * frame = (char*)malloc(sizeof(char)*(actual_PackSize+4)); 
        int length = create_dataPackage(numTransmission, pack, actual_PackSize,frame);  
        
        
        for (int i = 0 ; i < actual_PackSize +4; i++)
            printf("%02x ", frame[i]); 
        printf("\n"); 
        for (int i = 0 ; i < actual_PackSize+4; i++){
            if (i <4) printf("   "); 
            else printf("%c ", pack[i-4]);
        }
            
        printf("\n");


        numTransmission ++; 
        
    }
   
    
}
