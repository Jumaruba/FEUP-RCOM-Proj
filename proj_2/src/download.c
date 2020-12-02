#include "../includes/download.h"

int main(int argc, char *argv[])
{

	HostRequestData *data = (HostRequestData *)malloc(sizeof(HostRequestData));

	input_handler(argc, argv, data);
	struct hostent *ent = getIP(data);
	print_ip(ent);

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