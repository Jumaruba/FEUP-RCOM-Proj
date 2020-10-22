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

    if (( fp = fopen("testFile.txt", "r")) < 0){
        PRINT_ERR("Not possible to open file"); 
        return -1; 
    }

    fseek(fp, 0L, SEEK_END); 
    int sz = ftell(fp);

    char * content = (char*)malloc(sizeof(char)*packSize); 
    fseek(fp, 0L, SEEK_SET); 

    while(fgets(content, packSize, fp)){
        printf("%s", content); 
        fseek(fp, SEEK_CUR, packSize); 
    }
    printf("\n");

    printf("%d\n", sz); 
    fclose(fp);
    
}
