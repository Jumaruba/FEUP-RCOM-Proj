#include "../include/utils.h"

void print_hex(char *s) {
    while (*s)
        printf("%02x", (unsigned int) *s++);
    printf("\n");
}

