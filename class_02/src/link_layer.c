#include "../include/link_layer.h"

int numTransmissions = 0;

int llopen(char *port, int flag, struct termios *oldtio, struct termios *newtio)
{
    int fd;
    int curr_state = 0;

    if (TRANSMITTER == flag)
    {
        fd = openDescriptor(port, oldtio, newtio);

        signal(SIGALRM, handle_alarm_timeout);
        siginterrupt(SIGALRM, 1);

        // SET
        while (curr_state < 5)
        {
            alarm(3);
            int res = send_frame_su(fd, ADDR_CMD_EMI, CMD_SET);
            printSuccess("Written CMD_SET.");
            curr_state = read_timeout_frame_su(fd, CMD_UA);
        }

        if (curr_state == 5)
            alarm_off();
    }

    else if (RECEPTOR == flag)
    {
        fd = openDescriptor(port, oldtio, newtio);

        // SEND FRAME
        read_frame_su(fd, CMD_SET);
        printf("Received CMD_SET with success\n");

        if (send_frame_su(fd, ADDR_ANS_REC, CMD_UA) <= 0)
            printf("Error sending answer to the emissor\n");
    }
    return fd;
}

int llwrite(int fd, char *data, int *data_length)
{
    char * frame; 
    int curr_state = 0 ; 

    if (*data_length < 0) {
        printf("Length must be positive");
        return -1;
    }

    // Creating the info to send
    int frame_length = create_frame_i(data, frame, *data_length, CMD_S0);  


    
}

int llread(int fd, char * buffer){
}

int send_frame_su(int fd, char ADDR, char CMD)
{
    char frame[5];
    frame[0] = FLAG;
    frame[1] = ADDR;
    frame[2] = CMD;
    frame[3] = frame[1] ^ frame[2];
    frame[4] = FLAG;

    int res = write(fd, frame, 5);
    return res;
}

inline int send_frame_i(int fd, char* frame, int frame_length){
    return write(fd, frame, frame_length); 
}
 
int read_frame_su(int fd, char CMD)
{
    int curr_state = 0; /* byte that is being read. From 0 to 4.*/
    char byte;
    while (curr_state < 5)
    {
        read(fd, &byte, 1);
        switch (curr_state)
        {
        // RECEIVE FLAG
        case 0:
            printf("case 0: %02x\n", byte);
            if (byte == FLAG)
                curr_state++;
            break;

        // RECEIVE ADDR
        case 1:
            printf("case 1: %02x\n", byte);
            if (byte == ADDR_CMD_EMI)
                curr_state++;
            else if (byte != FLAG)
                curr_state = 0;
            break;

        // RECEIVE CMD
        case 2:
            printf("case 2: %02x\n", byte);
            if (byte == CMD)
                curr_state++;
            else if (byte == FLAG)
                curr_state = 1;
            else
                curr_state = 0;
            break;
        // RECEIVE BCC
        case 3:
            printf("case 3: %02x\n", byte);
            if (byte == (CMD ^ ADDR_CMD_EMI))
                curr_state++;
            else if (byte == FLAG)
                curr_state = 1;
            else
                curr_state = 0;
            break;

        // RECEIVE FLAG
        case 4:
            printf("case 4: %02x\n", byte);
            if (byte == FLAG)
                curr_state++;
            else
                curr_state = 0;
        }
    }
    return 0;
}

int read_timeout_frame_su(int fd, char CMD)
{
    int curr_state = 0; /* byte that is being read. From 0 to 4.*/
    char byte;
    while (curr_state < 5)
    {
        if (read(fd, &byte, 1) == -1)
            return -1;
        switch (curr_state)
        {
        // RECEIVE FLAG
        case 0:
            printf("case 0: %02x\n", byte);
            if (byte == FLAG)
                curr_state++;
            break;

        // RECEIVE ADDR
        case 1:
            printf("case 1: %02x\n", byte);
            if (byte == ADDR_CMD_EMI)
                curr_state++;
            else if (byte != FLAG)
                curr_state = 0;
            break;

        // RECEIVE CMD
        case 2:
            printf("case 2: %02x\n", byte);
            if (byte == CMD)
                curr_state++;
            else if (byte == FLAG)
                curr_state = 1;
            else
                curr_state = 0;
            break;
        // RECEIVE BCC
        case 3:
            printf("case 3: %02x\n", byte);
            if (byte == (CMD ^ ADDR_CMD_EMI))
                curr_state++;
            else if (byte == FLAG)
                curr_state = 1;
            else
                curr_state = 0;
            break;

        // RECEIVE FLAG
        case 4:
            printf("case 4: %02x\n", byte);
            if (byte == FLAG)
            {
                curr_state++;

                printf("Success reading %x\n", CMD);
            }
            else
                curr_state = 0;
        }
    }

    return curr_state;
}

int read_timeout_frame_i(int fd, char CMD){

}


int openDescriptor(char *port, struct termios *oldtio, struct termios *newtio)
{
    int fd = open(port, O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        printf("%s\n", port);
        perror(port);
        exit(-1);
    }

    if (tcgetattr(fd, oldtio) == -1)
    { /* save current port settings */
        perror("tcgetattr");
        exit(-1);
    }

    bzero(newtio, sizeof(newtio));
    newtio->c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio->c_iflag = IGNPAR;
    newtio->c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio->c_lflag = 0;

    newtio->c_cc[VTIME] = 0; /* inter-character timer unused */
    newtio->c_cc[VMIN] = 1;  /* blocking read until 5 chars received */

    tcflush(fd, TCIOFLUSH);

    if (tcsetattr(fd, TCSANOW, newtio) == -1)
    {
        perror("tcsetattr");
        exit(-1);
    }

    printf("New termios structure set\n");

    return fd;
}

int create_frame_i(char *data, char *frame, int data_length, char CMD)
{ 
    int frame_length = 0;  

    // Stuffing bcc and data.  
    char *BCC2 = (char*)malloc(sizeof(char)); 
    BCC2[0] = 0x00; 
    int bcc_length = 1;  

    create_BCC2(data, BCC2, data_length);  
    byte_stuffing(data, &data_length);  
    byte_stuffing(BCC2, &bcc_length);   

    // Store information 
    frame_length = 5  + bcc_length + data_length;  
    frame = (char*) malloc(sizeof(char)* frame_length); 

    frame[0] = FLAG;
    frame[1] = ADDR_CMD_EMI;
    frame[2] = CMD; 
    frame[3] = frame[1]^frame[2];  
    // BCC 
    memcpy(&frame[4], data, data_length);    
    memcpy(&frame[4 + data_length], BCC2, bcc_length); 

    frame[frame_length-1] = FLAG;   

    return frame_length; 
}

void create_BCC2(char * data, char* buffer, int data_length)
{
    for (int i = 0 ; i < data_length; i++){
        *buffer ^= data[i]; 
    } 
}

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
    free(new_frame);
    return 0; 
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

handle_alarm_timeout()
{
    numTransmissions++;

    printf("Time out #%d\n", numTransmissions);

    if (numTransmissions > TRIES)
    {
        printf("Number of tries exceeded\n");
        exit(-1);
    }
}

void alarm_off()
{
    numTransmissions = 0;
    alarm(0);
}