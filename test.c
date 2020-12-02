
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h> 

int main()
{
    char str[] = "ftp://[<user>:<password>@]<host>/<url-path>"; 
    char delim[] = ":@/";  
    
    
    char * ptr = strtok(str, delim); 
    while(ptr != NULL){
        printf("%s\n", ptr); 
        ptr = strtok(NULL, delim); 
    }

    return 0;
}
 
 
 
    
