#include "../includes/download.h"

int main(int argc, char *argv[])
{
	char port[10];  
	int real_port; 
	char response_code[4];
	response_code[3] = '\0';  
	FILE* fp; 
	char byte; 
	

	HostRequestData *data = (HostRequestData *)malloc(sizeof(HostRequestData));

	// Handle data initial data.
	input_handler(argc, argv, data);
	struct hostent *ent = getIP(data); 
	io("IP ADDRESS", inet_ntoa(*((struct in_addr *)ent->h_addr))); 
	
	// REQUESTER ------------------------------------------------ 

	// Init socket.
	char *ip_addr = inet_ntoa(*((struct in_addr *)ent->h_addr));
	int sock_requester = init_socket(ip_addr, 0);

	// Request the port 
	request_file(sock_requester, data, port);  
	get_real_port(port, &real_port);  

	// GET FILE --------------------------------------------------

	// Init socket. 
	int sock_reader = init_socket(ip_addr, real_port);
	write_cmd(sock_requester, "retr ", data->path);   
	

	read_rsp(sock_requester, response_code);      
	if (response_code[0] != PSV_COMPL){
		PRINT_ERR("Not possible to transfer the file\n"); 
		exit(-1);
	}
	printf("%s\n", data->file_name);
	if( (fp = fopen(data->file_name, "wb")) == NULL ) {
		PRINT_ERR("%d\n", errno); 
		exit(-1); 
	} 

	while(1){ 
		// received 0, means that the connection has been closed. 
		if (recv(sock_reader, &byte, sizeof(byte), MSG_PEEK | MSG_DONTWAIT) == 0){
			break; 
		}
		read(sock_reader, &byte, 1); 
		fwrite(&byte, 1, 1, fp); 
	}
		
	
	close(sock_requester);
	close(sock_reader);

	return 0;
}

void request_file(int sock_fd, HostRequestData *data, char port[])
{ 
	// Get the first response code.
	char response_code[4]; 
	response_code[3] = '\0';  

	read_rsp(sock_fd, response_code); 

	// Accessing the server must be positive completion. 
	if (response_code[0] != PSV_COMPL){
		PRINT_ERR("Not possible to access website:: %s\n", response_code);
		exit(-1); 
	} 

	// Write the user. 
	write_cmd(sock_fd, "user ", data->user);
	read_rsp(sock_fd, response_code);  

	if (response_code[0] != PSV_INTER && response_code[0] != PSV_COMPL){
		PRINT_ERR("Error writing user:: %s\n", response_code); 
		exit(-1); 
	}else PRINT_SUC("User [OK]!\n");

	// Write the password.  
	write_cmd(sock_fd, "pass ", data->password); 
	read_rsp(sock_fd, response_code); 

	if (response_code[0] != PSV_INTER && response_code[0] != PSV_COMPL){
		PRINT_ERR("Error writing pass:: %s\n", response_code); 
		exit(-1);
	}else PRINT_SUC("Pass [OK]!\n");

	// Enter pasv mode. 
	write_cmd(sock_fd, "pasv", "");
	read_psv(sock_fd, response_code, port); 

	if (response_code[0] != PSV_COMPL){
		PRINT_ERR("Error entering pasv mode:: %s\n", response_code); 
		exit(-1); 
	}else PRINT_SUC("Get port [OK]!\n");

	get_file_name(data); 

	// IO INTERFACE  
	label("IP CALCULATION");
	io("PORT FIELDS", port); 

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

void get_file_name(HostRequestData* data){
	char delim[] = "/"; 

	char * ptr = strtok(data->path, delim);  
	while(ptr != NULL){  
		strcpy(data->file_name, ptr); 
		ptr = strtok(NULL, delim); 
	} 

}