#include "./proj_1/include/macros.h"  
#include "./proj_1/include/link_layer.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char ** argv){
    FILE* fp; 
    int packSize = 10; 
    int actual_contentSize; 
    int continue_reading; 

    
    if (( fp = fopen("testFile.txt", "rb")) < 0){
        PRINT_ERR("Not possible to open file"); 
        return -1; 
    }

    fseek(fp, 0L, SEEK_END); 
    int sz = ftell(fp);
    char * content = (char*)malloc(sizeof(char)*packSize); 
    fseek(fp, 0L, SEEK_SET); 

    while(continue_reading){ 
        actual_contentSize = fread(content, 1, packSize, fp); 
        printf("actual content Size %d\n", actual_contentSize);
        if (actual_contentSize  <=0 ) continue_reading = 0; 
        printf("%s\n\n", content); 
        fseek(fp, SEEK_CUR, packSize); 
    }
    printf("\n");

    printf("%d\n", sz); 
    fclose(fp);
    
}
