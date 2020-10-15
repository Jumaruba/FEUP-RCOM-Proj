#include "../include/utils.h"

void print_hex(const char *s) {
    while (*s)
        printf("%02x", (unsigned int) *s++);
    printf("\n");
}

void printSuccess(char* text){
    printf ("\033[32;1m SUCCESS: %s \033[0m\n", text);
}

void printError(char* text){
    printf ("\033[31;1m FAILURE: %s \033[0m\n", text);
}