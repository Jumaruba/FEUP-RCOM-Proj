#include "../include/utils.h"

void print_hex(char *s, int length) { 
    for (int i = 0 ; i < length; i++ )
        printf("%02x\n", s[i]);
    printf("\n");
}

