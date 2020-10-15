#include "./class_02/include/macros.h"  
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int byte_stuffing(char * frame, int* frame_length)
{ 
    char * new_frame ;      
    int extra_space = 0;        /* The extra space needed to be added. */
    int new_frame_length = 0;   /* The new length of the string frame. */ 
    int actual_pos = 0;         /* Position in the new_frame. */ 
    int counter = 0;            

    //  First find all the flags and scapes to avoid multiple reallocs. 
    for (int i = 0 ; i < *frame_length; i++)
        if (frame[i] == FLAG || frame[i] == ESC) extra_space++;  


    new_frame_length = extra_space + *frame_length;  
    new_frame = (char *)malloc(sizeof(char) * new_frame_length);     

    for (int i = 0 ; i< *frame_length; i++){  
        actual_pos = i + counter; 
        if (frame[i] == FLAG){    
            new_frame[actual_pos] =  ESC; 
            new_frame[actual_pos+1] = XOR_STUFFING(FLAG);  

            counter ++; 
        }
        else if (frame[i] == ESC){
            new_frame[actual_pos] = ESC; 
            new_frame[actual_pos+1] = XOR_STUFFING(ESC); 

            counter ++; 
        } 
        else new_frame[actual_pos] = frame[i];  
    } 


    frame = realloc(frame, new_frame_length); 
    * frame_length  = new_frame_length;

    memcpy(frame, new_frame, new_frame_length); 
}

int byte_destuffing(char * frame, int * frame_length){
    
    int new_frame_pos = 0;  
    char * new_frame = (char*)malloc(sizeof(char)*(*frame_length));   

    for (int i = 0 ; i < *frame_length; i++){
        if (frame[i] == ESC){
            if (frame[i+1] == XOR_STUFFING(FLAG))
                new_frame[new_frame_pos] = FLAG; 
            else if (frame[i+1] == XOR_STUFFING(ESC))
                new_frame[new_frame_pos] = ESC;  

            i++;  
        } 
        else new_frame[new_frame_pos] = frame[i]; 
        new_frame_pos ++;
    } 

    memcpy(frame, new_frame, new_frame_pos); 
    *frame_length = new_frame_pos;
    free(new_frame); 
}
int main(int argc, char ** argv){

    char * frame = (char*)malloc(sizeof(char)*5);
    frame[0] = 0x10; 
    frame[1] = FLAG; 
    frame[2] = 0x25; 
    frame[3] = ESC; 
    frame[4] = 0x36; 
    frame[5] = FLAG; 
    frame[6] = FLAG; 
    
    int frame_length = 7; 
    byte_stuffing(frame, &frame_length);  
    byte_destuffing(frame, &frame_length); 
    for (int i = 0 ; i < frame_length; i++)
        printf("%02x\n", frame[i]); 
}