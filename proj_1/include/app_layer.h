#include "link_layer.h" 


int create_dataPackage(int seqNum, byte* info, int length, byte* pack); 

int read_dataPackage(int* seqNum, byte* info, byte* pack);   

int create_controlPackage(byte C, byte* nameFile, int length, byte* pack); 

int read_controlPackage(byte* pack, byte* nameFile, int *fileSize, int packSize);



