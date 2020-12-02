#include "../includes/download.h"

int main(int argc, char *argv[])
{

	HostRequestData *data = (HostRequestData *)malloc(sizeof(HostRequestData));

	// Handle data initial data. 
	input_handler(argc, argv, data);
	struct hostent *ent = getIP(data);
	print_ip(ent); 

	// Init socket. 
	char * ip_addr = inet_ntoa(*((struct in_addr *)ent->h_addr)); 
	int sock_requester = init_socket(ip_addr, 0);

	// Get the first response code.
	char response_code[3]; 
	read_rsp(sock_requester, response_code);   

	write_cmd(sock_requester, "user ", data->user); 
	read_rsp(sock_requester, response_code);
	
	printf("\n");
	PRINT_SUC("Response code: %s\n", response_code); 

	return 0;
}

struct hostent *getIP(HostRequestData *data)
{
	struct hostent *ent;

	if ((ent = gethostbyname(data->host)) == NULL)
	{
		PRINT_ERR("Error getting host ip\n");
		exit(1);
	}
	return ent;
}
 
void print_ip(struct hostent *ent)
{
	PRINTF_WHITE("IP ADDRESS  \t");
	PRINTF_BLUE(" %s\n", inet_ntoa(*((struct in_addr *)ent->h_addr)));
}