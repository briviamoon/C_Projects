#include "../headers/server.h"
/**
 * main - initiate Server to Live.
 * Return: 0 if proccess succesful.
 */
int main(int argc, char *argv[])
{
	int clientSocketFD;
	char *port;
	char *address;
	int errorChek;
	char *message;
	char buffer[2048];
	struct sockaddr_in *clientAddress;

	if (argc < 3)
	{
		printf("Please Provide the Server Address and port to use\n");
		exit(1);
	}

	address = argv[1];
	port = argv[2];

	clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocketFD == -1)
	{
		printf("ClientSocket creation Failed\n");
		exit(1);
	}
	else
	{
		printf("ClientSocket creation successfull\n");
	}

	clientAddress = createIPV4Address(atoi(port), address);
	if (clientAddress == NULL)
	{
		printf("ClientSocket Address creation faliled\n");
		exit(1);
	}
	else
	{
		printf("ClientSocket address creation successfull\n");
	}
	errorChek = connect(clientSocketFD, (struct sockaddr *)clientAddress, sizeof(struct sockaddr));

	if (errorChek == 0)
	{
		printf("Client connection up and running!\n");
	}

	message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
	send(clientSocketFD, message, strlen(message), 0);

	recv(clientSocketFD, buffer, 2048, 0);

	printf("From Goorle Server: %s\n", buffer);

	return (0);
}
