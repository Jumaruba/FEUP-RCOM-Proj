#include "../includes/download.h"

int main(int argc, char *argv[])
{

	HostRequestData *data = (HostRequestData *)malloc(sizeof(HostRequestData));

	// Handle data initial data.
	input_handler(argc, argv, data);
	struct hostent *ent = getIP(data);
	print_ip(ent);

	// Init socket.
	char *ip_addr = inet_ntoa(*((struct in_addr *)ent->h_addr));
	int sock_requester = init_socket(ip_addr, 0);

	request_file(sock_requester, data); 

	return 0;
}

void request_file(int sock_fd, HostRequestData *data)
{ 

	// Get the first response code.
	char response_code[3];
	read_rsp(sock_fd, response_code); 

	// Accessing the server must be positive completion. 
	if (response_code[0] != PSV_COMPL){
		PRINT_ERR("Not possible to access website:: %s\n", response_code);
		exit(-1); 
	} 

	// Write the user. 
	write_cmd(sock_fd, "user ", data->user);
	read_rsp(sock_fd, response_code);  

	if (response_code[0] != PSV_INTER){
		PRINT_ERR("Error writing user:: %s\n", response_code); 
		exit(-1); 
	}

	// Write the password. 
	if (response_code[0] != PSV_INTER){
		PRINT_ERR("Error writing pass:: %s\n", response_code); 
		exit(-1);
	}

	


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

// IO functions
void print_ip(struct hostent *ent)
{
	PRINTF_WHITE("IP ADDRESS  \t");
	PRINTF_BLUE(" %s\n", inet_ntoa(*((struct in_addr *)ent->h_addr)));
}
