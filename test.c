#include "./proj_1/include/macros.h"  
#include "./proj_1/include/link_layer.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int create_controlPackage(char C, byte* nameFile, int length, byte* pack){
    int size_nameFile = strlen(nameFile), curr_pos = 0;  

    pack[0]= C;  
    pack[1] = T_FILE_NAME; 
    pack[2]= strlen(nameFile); 

    if (memcpy(&pack[3] , nameFile, size_nameFile) == NULL){
        PRINT_ERR("Not possible to copy file name"); 
        return -1; 
    }
    
    curr_pos = 3 + size_nameFile;
    char * length_string = (char*)malloc(sizeof(int)); 
    sprintf(length_string, "%d", length);                        // Int to string. 

    pack[curr_pos] = T_FILE_SIZE;   
    pack[curr_pos+1] = strlen(length_string);  

    if (memcpy(&pack[curr_pos+2], length_string, strlen(length_string)) == NULL){
        PRINT_ERR("Not possible to copy size of file"); 
        return -1; 
    }

    PRINT_SUC("Created control package.");  
    return curr_pos + strlen(length_string) + 2; 
} 

int read_controlPackage(char* pack, char* nameFile, int *fileSize, int packSize){
    char * fileSize_string = (char*)malloc(sizeof(int));  

    for (int i = 0 ; i < packSize; i++){ 
        if (T_FILE_NAME == pack[i]){
            i++; 
            int sizeT = pack[i++];  
            printf("sizeoffile %d\n", sizeT); 
            if (memcpy(nameFile, &pack[i], sizeT) == NULL){
                PRINT_ERR("Not possible to parse file name"); 
                return -1; 
            }
            i+= sizeT-1; 
        }
        else if (T_FILE_SIZE == pack[i]){ 
            i++;  
            int sizeT = pack[i++]; 
            if (memcpy(fileSize_string, &pack[i], sizeT) == NULL){
                PRINT_ERR("Not possible to parse size of file"); 
                return -1; 
            } 

            sscanf(fileSize_string, "%d", fileSize);        // Parse the size
            i+= sizeT; 
        }

    } 
    PRINT_SUC("Read control package."); 
    return 0; 
}
    
int main(int argc, char ** argv){

    char *nameFile = "testFile.txt"; 
    char * pack = (char*)malloc(sizeof(char)*MAX_SIZE_ARRAY); 
    int length = create_controlPackage(CTRL_START, nameFile, strlen(nameFile), pack); 
    for (int i = 0 ; i < length; i++) printf("%02x\n", pack[i]);  
    char *name_file = (char*)malloc(sizeof(char)*MAX_SIZE_ARRAY); 
    int fileSize; 
    read_controlPackage(pack, name_file, &fileSize, length ); 
    
    printf("%s\n", name_file); 
    printf("%d\n", fileSize);
    free(name_file);
    free(pack);
    
}
