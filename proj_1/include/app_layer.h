#include "link_layer.h" 

int create_dataPackage(int seqNum, byte* info, int* length, byte* pack); 

int create_controlPackage(char C, byte* info, int length, byte* pack); 

int get_pack(int index, byte* data, int length, int packSize, char* pack); 

