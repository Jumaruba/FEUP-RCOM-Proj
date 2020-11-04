#include "../include/link_layer.h"

int numTransmissions = 0; 
int fd_transmitter = 0; 
struct termios oldtio_transmitter; 
struct termios oldtio_receiver; 

int llopen(byte *port, int flag)
{
    int fd = -1;
    int res = -1;
    struct termios newtio; 

    if (flag != TRANSMITTER && flag != RECEPTOR){
        PRINT_ERR("Actual flag %d. Must be 1 or 0.", flag); 
        return -1; 
    }

    if (TRANSMITTER == flag) { 
        
        // Set the file descriptor. 
        fd = openDescriptor(port, &oldtio_transmitter, &newtio); 
        fd_transmitter = fd;  

        // Establishment of the connection.  
        while (res != 0) { 
            alarm(3);
            if (send_frame_nnsp(fd, A, CMD_SET) < 0)
                PRINT_ERR("Not possible to send CMD_SET. Sending again after timeout..."); 
            else PRINT_SUC("Written CMD_SET.");
            
            if((res = read_frame_not_supervision(fd, CMD_UA)) >= 0)
                PRINT_SUC("Received UA.");
        }

        if (res == 0) alarm_off();
    }

    else if (RECEPTOR == flag)
    {
        //Set the file descriptor. 
        fd = openDescriptor(port, &oldtio_receiver, &newtio); 

        while(res < 0){
            // Establishment of the connection. 
            read_frame_not_supervision(fd, CMD_SET);
            PRINT_SUC("Received CMD_SET with success.");

            if ((res = send_frame_nnsp(fd, A, CMD_UA)) < 0)
                PRINT_ERR("Error sending answer to the emissor.");
        } 
    }
    return fd;
}

int llwrite(int fd, byte *data, int *data_length) {
    static int s_writer = 0; 
    int res = -1 ;  
    byte CMD;  
    
    byte * frame  = (byte*) malloc(MAX_SIZE_ALLOC*sizeof(byte));    // Alloc max size.  

    // Check input function errors.
    if (*data_length < 0) {
        PRINT_ERR("Length must be positive, actual: %d", *data_length);
        return -1;
    }

    // Creating the info to send.
    int frame_length = create_frame_i(data, frame, *data_length, CMD_S(s_writer));     
    
    // Send info. 
    while(res != 0){
        alarm(3); 
        if ((res = write(fd, frame, frame_length)) < 0) 
            PRINT_ERR("Not possible to write info frame. Sending again after timeout..."); 
        else PRINT_SUC("Sent frame with S=%d", s_writer); 
        
        if ((res = read_frame_supervision(fd, &CMD, !s_writer)) < 0) {
            PRINT_ERR("Not possible to read info frame. Sending again..."); 
            s_writer = SWITCH(s_writer);
            continue; 
        }
        else PRINT_SUC("Read CDM=%02x with R=%d", CMD, !s_writer); 

        if (CMD == (CMD_REJ(!s_writer) || CMD_REJ(s_writer))){
            continue; 
        }
        if (res >= 0){  
            alarm_off();
            s_writer = SWITCH(s_writer); 
            return 0; 
        }
        
    } 
    
}

int llread(int fd, byte * data){   
    int data_length = -1; 
    static int s_reader = 0, curr_s = 0; 
    byte  check_BCC2, CMD; 

    // Will not leave the loop until has a new message. 
    while(TRUE){  
        if ((data_length = read_frame_i(fd, data, &CMD)) < 0){
            PRINT_ERR("Not possible to read information frame. Sending CMD_REJ..."); 
            sleep(DELAY_US); 
            PRINT_NOTE("Trying to read again."); 
            continue; 
        }else PRINT_SUC("Received CMD_S=%02x, S=%d", CMD_S(s_reader), s_reader);  

        // Get the s received. 
        if (CMD == CMD_S(0)) curr_s = 0; 
        else if (CMD == CMD_S(1)) curr_s = 1; 

        byte_destuffing(data, &data_length);   

        // Check the bcc2.  
        check_BCC2 = 0x00; 
        create_BCC2(data, &check_BCC2, data_length-1);  

        // If wrong bcc2 send CMD REJ. 
        if (check_BCC2 != data[data_length-1]) { 
            PRINT_ERR("Wrong bcc2. Expected: %02x, Received: %02x.", check_BCC2, data[data_length-1]); 
            PRINT_NOTE("Sending CMD_REJ.");   
            send_frame_nnsp(fd, A, CMD_REJ(!curr_s)); 
            continue; 
        }else PRINT_SUC("BCC2 ok!");   

        // It's not the desired message. 
        if (CMD != CMD_S(s_reader)){ 
            printf("Undesired message s_reader %d", s_reader); 
            PRINT_SUC("Sending RR %d", !s_reader);
            send_frame_nnsp(fd, A, CMD_RR(!s_reader)); 
            continue;       // Discard the message. 
        } 

        // Desired message, save the info. 
        if (send_frame_nnsp(fd, A, CMD_RR(!s_reader)) > 0){
            PRINT_SUC("CMD_RR with R=%d sent.", !s_reader);  
            s_reader = SWITCH(s_reader); 
            return data_length;
        }
        
    }
    return -1;
}

int llclose(int fd, int flag){ 

    int res = -1; 

    if (flag != TRANSMITTER && flag != RECEPTOR){
        PRINT_ERR("Invalid flag.");
        exit(-1); 
    }

    if (flag == TRANSMITTER){ 
        while(res < 0){                   
            alarm(3); 
            if ((res = send_frame_nnsp(fd, A, CMD_DISC)) < 0){
                PRINT_ERR("Failed sending CMD_DISC. Sending again...");  
                sleep(DELAY_US);   /* Wait a little before sending again.*/  
            }else PRINT_SUC("Sent CMD_DISC.");   
            
            if((res = read_frame_not_supervision(fd, CMD_DISC)) < 0){
                PRINT_ERR("Failed in receive CMD_DISC. Sending CMD_DISC again...");   
                continue; 
            } else {
                PRINT_SUC("Read CMD_DISC.");  
                alarm_off(); 
            }

            // Here doesn't matter if it was sent or not. The emissor must turn off.   
            if (send_frame_nnsp(fd, A, CMD_UA) < 0 ){
                PRINT_ERR("Failed in sending CMD_UA. Turning off...");
            }
            else{ 
                sleep(1);
                PRINT_SUC("Sent CMD_UA."); 
            }
            
        } 
        
        return closeDescriptor(fd, &oldtio_transmitter); 

    }else if (flag == RECEPTOR){    
        while(res < 0){
            if((res = read_frame_not_supervision(fd, CMD_DISC)) < 0){
                PRINT_ERR("Failed reading CMD_DISC"); 
                continue; 
            } else PRINT_SUC("Read CMD_DISC");  

            if ((res = send_frame_nnsp(fd, A, CMD_DISC)) < 0){
                PRINT_ERR("Failed sending CMD_DISC. Reading CMD_DISC again...");   
                continue; 
            } else PRINT_SUC("Sent CMD_DISC");   

            if ((res = read_frame_not_supervision(fd, CMD_UA))){
                PRINT_ERR("Not able to receive CMD_UA. Reading CMD_DISC again..."); 
                continue; 
            }else PRINT_SUC("Received CMD_UA");

		    sleep(1);
            return closeDescriptor(fd, &oldtio_receiver); 
        }
    } 
    return -1; 
}

int read_frame_supervision(int fd, byte *CMD, int r){
   int curr_state = 0; /* byte that is being read. From 0 to 4.*/
    byte byte;

    PRINTF("--READ SUPERVISION FRAME [RR, REJ]--\n"); 
    while (TRUE)
    {
        if (read(fd, &byte, 1) == -1) 
            return -1;

        switch (curr_state)
        {
        // RECEIVE FLAG
        case 0: 

            PRINTF("case 0: %02x\n", byte);
            if (byte == FLAG)
                curr_state++;
            break;

        // RECEIVE ADDR
        case 1:
            PRINTF("case 1: %02x\n", byte);
            if (byte == A)
                curr_state++;
            else if (byte != FLAG)
                curr_state = 0;
            break;

        // RECEIVE CMD
        case 2:
            PRINTF("case 2: %02x\n", byte);
            if (byte == CMD_REJ(r) || byte == CMD_RR(r) || byte == CMD_REJ(!r)){
                *CMD = byte; 
                curr_state++;
            } 
            else if (byte == FLAG)
                curr_state = 1;
            else
                curr_state = 0;
            break;
        // RECEIVE BCC
        case 3:
            PRINTF("case 3: %02x\n", byte);
            if (byte == (*CMD ^ A))
                curr_state++;
            else if (byte == FLAG)
                curr_state = 1;
            else
                curr_state = 0;
            break;

        // RECEIVE FLAG
        case 4:
            PRINTF("case 4: %02x\n", byte);
            if (byte == FLAG) 
                return 0; 
            else
                curr_state = 0;
        }
    }
    return curr_state;
}

int read_frame_not_supervision(int fd, byte CMD)
{
    int curr_state = 0; /* byte that is being read. From 0 to 4.*/
    byte data;
    PRINTF("--READ NOT SUPERVISION FRAME [UA, DISC, SET]--\n");
    while (TRUE) { 

        if (read(fd, &data, 1) == -1) 
            return -1; 

        switch (curr_state) { 

        // RECEIVE FLAG
        case 0: 

            PRINTF("case 0: %02x\n", data);
            if (data == FLAG)
                curr_state++;
            break;

        // RECEIVE ADDR
        case 1:
            PRINTF("case 1: %02x\n", data);
            if (data == A)
                curr_state++;
            else if (data != FLAG)
                curr_state = 0;
            break;

        // RECEIVE CMD
        case 2:
            PRINTF("case 2: %02x\n", data);
            if (data == CMD)
                curr_state++;
            else if (data == FLAG)
                curr_state = 1;
            else
                curr_state = 0;
            break;
        // RECEIVE BCC
        case 3:
            PRINTF("case 3: %02x\n", data);
            if (data == (CMD ^ A))
                curr_state++;
            else if (data == FLAG)
                curr_state = 1;
            else
                curr_state = 0;
            break;

        // RECEIVE FLAG
        case 4:
            PRINTF("case 4: %02x\n", data);
            if (data == FLAG) return 0; 
            else curr_state = 0;
        }
    }
    return -1;
}

int send_frame_nnsp(int fd, byte ADDR, byte CMD)
{
    byte frame[5];
    frame[0] = FLAG;
    frame[1] = ADDR;
    frame[2] = CMD;
    frame[3] = frame[1] ^ frame[2];
    frame[4] = FLAG;

    return write(fd, frame, 5);
}

int read_frame_i(int fd, byte *buffer, byte *CMD){
    int curr_state= 0, info_length = -1; 
    byte byte; 

    PRINTF("--READ FRAME I--\n"); 
    while(curr_state < 5){
        if (read(fd, &byte, 1) == -1)
            return -1; 

        switch (curr_state)
        { 
            // RECEIVE FLAG
            case 0: 
                info_length = 0; 
                PRINTF("case 0: %02x\n", byte);
                if (FLAG == byte) 
                    curr_state ++;  
                break; 
            // RECEIVE ADDR 
            case 1: 
                PRINTF("case 1: %02x\n", byte); 
                if (A == byte)
                    curr_state ++; 
                else if (FLAG != byte) 
                    curr_state = 0;  
                
                break; 

            // RECEIVE CMD
            case 2: 
                PRINTF("case 2: %02x\n", byte);  
                if (byte == CMD_S(0) || byte == CMD_S(1)){ 
                    *CMD = byte; 
                    curr_state++; 
                }
                else if (byte == FLAG) 
                    curr_state = 1; 
                else curr_state = 0;

                break; 

            // RECEIVE BCC1
            case 3: 
                PRINTF("case 3: %02x\n", byte);    
                if (byte == (*CMD ^ A))
                    curr_state ++; 
                else if (byte == FLAG) 
                    curr_state = 1; 
                else if (*CMD == CMD_S(0)){
                    send_frame_nnsp(fd, A, CMD_REJ(1)); 
                    curr_state = 0; 
                }
                else if (*CMD == CMD_S(1)){
                    send_frame_nnsp(fd, A, CMD_REJ(0));  
                    curr_state = 0; 
                } 
                break;
            // RECEIVE INFO 
            case 4:
                PRINTF("case 4: %02x\n", byte);
                if (byte != FLAG){
                    buffer[info_length++] = byte;  
                }
                else curr_state ++; 
            
        } 
    }
    return info_length;
}

int create_frame_i(byte *data, byte *frame, int data_length, byte CMD)
{ 
    int frame_length = 0, bcc_length = 1;   

    // Stuffing bcc2 and data.  
    byte *BCC2 = (byte*)malloc(sizeof(byte)); 
    BCC2[0] = 0x00; 

    create_BCC2(data, BCC2, data_length);  
    byte_stuffing(data, &data_length);  
    byte_stuffing(BCC2, &bcc_length);   

    // Store information 
    frame_length = 5  + bcc_length + data_length;  
    frame[0] = FLAG;
    frame[1] = A;
    frame[2] = CMD; 
    frame[3] = frame[1]^frame[2];  
    // BCC 
    memcpy(&frame[4], data, data_length);    
    memcpy(&frame[4 + data_length], BCC2, bcc_length); 

    frame[frame_length-1] = FLAG;   

    PRINT_NOTE("Created frame i"); 
    return frame_length; 
}

void create_BCC2(byte * data, byte* buffer, int data_length)
{
    for (int i = 0 ; i < data_length; i++){
        *buffer ^= data[i]; 
    } 
}

int byte_stuffing(byte * frame, int* frame_length)
{ 
    byte * new_frame ;      
    int extra_space = 0;        /* The extra space needed to be added to the frame. */
    int new_frame_length = 0;   /* The new length of the string frame (extra + length). */ 
    int actual_pos = 0;         /* Position in the new_frame. */ 
    int counter = 0;            /* Number of escapes and flags found in the second iteration. */

    //  First find all the flags and scapes to avoid multiple reallocs. 
    for (int i = 0 ; i < *frame_length; i++)
        if (frame[i] == FLAG || frame[i] == ESC) extra_space++;  


    new_frame_length = extra_space + *frame_length;  
    new_frame = (byte *)malloc(sizeof(byte) * new_frame_length);     

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


    //frame = realloc(frame, new_frame_length); 
    * frame_length  = new_frame_length;

    memcpy(frame, new_frame, new_frame_length); 
    free(new_frame);
    return 0; 
}

int byte_destuffing(byte * frame, int * frame_length){
    
    int new_frame_pos = 0;  
    byte * new_frame = (byte*)malloc(sizeof(byte)*(*frame_length));   

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

int openDescriptor(byte *port, struct termios *oldtio, struct termios *newtio)
{
    int fd = -1; 
    if((fd = open(port, O_RDWR | O_NOCTTY)) < 0) {
        PRINT_ERR("Invalid port: %s", port);
        exit(-1); 
    }

    if (tcgetattr(fd, oldtio) == -1) { 
        PRINT_ERR("tcgetattr.");
        exit(-1);
    }

    bzero(newtio, sizeof(newtio));
    newtio->c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
    newtio->c_iflag = IGNPAR;
    newtio->c_oflag = 0;

    /* set input mode (non-canonical, no echo,...) */
    newtio->c_lflag = 0;

    newtio->c_cc[VTIME] = 0; /* inter-character timer unused */
    newtio->c_cc[VMIN] = 1;  /* blocking read until 1 chars received */

    tcflush(fd, TCIOFLUSH);

    if (tcsetattr(fd, TCSANOW, newtio) == -1) {
        PRINT_ERR("tcsetattr");
        exit(-1);
    }

    PRINT_SUC("Function openDescriptor executed with success."); 

    return fd;
}

int closeDescriptor(int fd, struct termios * oldtio){
    PRINT_NOTE("Closing descriptor");
    if (tcsetattr(fd, TCSANOW, oldtio) == -1) {
        perror("tcsetattr");
        exit(-1);
    }
    PRINT_SUC("Restoured oldtio");
    return close(fd);
}

void install_alarm() {
    if (signal(SIGALRM, handle_alarm_timeout) == SIG_ERR)
    {
        PRINT_ERR("Not possible to install signal, SIG_ERR.");
        llclose(fd_transmitter, CMD_DISC);
    }
    siginterrupt(SIGALRM, TRUE);
}


handle_alarm_timeout() {
    numTransmissions++;
    
    PRINT_ERR("Time out #%d", numTransmissions); 

    if (numTransmissions > TRIES)
    {
        PRINT_ERR("Number of tries exceeded\n");    
        closeDescriptor(fd_transmitter, &oldtio_transmitter); 
        exit(-1);
    }
}  


void alarm_off() {
    numTransmissions = 0; 
    alarm(0);
}
