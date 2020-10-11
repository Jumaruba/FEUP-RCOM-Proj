/*Non-Canonical Input Processing*/

#include "../include/writer.h"

struct termios oldtio, newtio;
LinkLayer *linkLayer;
int main(int argc, char **argv)
{
    int res;
    if ((argc < 2) ||
        ((strcmp("/dev/ttyS10", argv[1]) != 0) &&
         (strcmp("/dev/ttyS11", argv[1]) != 0)))
    {
        printf("Usage:\tnserial SerialPort\n\tex: nserial /dev/ttyS1\n");
        exit(1);
    }

    // SET CONFIGS
    linkLayer = (LinkLayer *)malloc(sizeof(LinkLayer));
    memcpy(linkLayer->port, argv[1], strlen(argv[1]) + 1);
    linkLayer->fd = openDescriptor(linkLayer->port, &oldtio, &newtio);
    printf("%d\n", linkLayer->fd);
    signal(SIGALRM, handle_alarm_timeout);

    // INIT PROTOCOL
    int curr_state;

    alarm(3);
    res = send_SU(linkLayer->fd, ADDR_CMD_EMI, CMD_SET);
    printf("%d bytes written\n", res);
    curr_state = read_timeout_SU(CMD_UA);

    // CLOSE
    if (tcsetattr(linkLayer->fd, TCSANOW, &oldtio) == -1)
    {
        perror("tcsetattr");
        exit(-1);
    }

    close(linkLayer->fd);
    return 0;
}

int read_timeout_SU(char CMD)
{
    int curr_state = 0; /* byte that is being read. From 0 to 4.*/
    char byte;
    while (curr_state < 5 && linkLayer->numTransmissions < TRIES)
    {   
        
        read(linkLayer->fd, &byte, 1);
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
                printf("Success in reading the CMD_UA\n");
            }
            else
                curr_state = 0;
        }
    }

    if (curr_state == 5){
        linkLayer->numTransmissions = 0;
        alarm(0);
        printf("Success reading the %x frame\n", CMD); 
        return 0; 
    }

    return curr_state;
}

handle_alarm_timeout()
{
    linkLayer->numTransmissions++;
    alarm(3);
    printf("Timeout %d\n", linkLayer->numTransmissions);

    if (linkLayer->numTransmissions > TRIES)
    {
        printf("Number of tries exceeded\n");
        exit(-1);
    }
}