#include "../include/app_layer.h" 



int get_infoSlice(int index, byte* data, int length, int packSize, byte* pack){ 

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

int read_dataPackage(int* seqNum, byte* info, byte* pack){
    
    *seqNum = pack[1]; 
    int infoSize = pack[2]*256 + pack[3]; 

    if (memcpy(info, &pack[4], infoSize) == NULL){
        PRINT_ERR("Error parsing info."); 
        return -1; 
    }

    return infoSize; 
}

int create_controlPackage(byte C, byte* nameFile, int length, byte* pack){
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

int read_controlPackage(byte* pack, byte* nameFile, int *fileSize, int packSize){
    char * fileSize_string = (char*)malloc(sizeof(int));  

    for (int i = 0 ; i < packSize; i++){ 
        if (T_FILE_NAME == pack[i]){
            i++; 
            int sizeT = pack[i++];  
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
    free(fileSize_string);
    return 0; 
}

