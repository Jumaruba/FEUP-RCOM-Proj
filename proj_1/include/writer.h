#ifndef WRITER_H
#define WRITER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "app_layer.h" 

volatile int STOP = FALSE;

void open_file(byte* nameFile); 

size_t get_fileSize(); 

#endif