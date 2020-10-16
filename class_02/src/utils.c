#include "../include/utils.h"

void print_hex(char *s) {
    while (*s)
        printf("%02x", (unsigned int) *s++);
    printf("\n");
}

void printSuccess(char* text){
    printf ("\033[32;1mSUCCESS: %s \033[0m\n", text);
}

void printError(char* text){
    printf ("\033[31;1mFAILURE: %s \033[0m\n", text);
}