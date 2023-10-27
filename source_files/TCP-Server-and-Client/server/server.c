#include "../headers/server.h"
/**
 * main - creates a server
 * Return: 0 if success
 */

int main(int argc, char *argv[])
{
	int serverSocketFD;
	int errorCheck;
	char *port;
	char *address;
	struct sockaddr_in *serverAddress;

	if (argc < 3)
	{
		printf("Please provide your server Address and Port to use\n");
		exit(1);
	}

	address = argv[1];
	port = argv[2];
	serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);

	if (serverSocketFD == -1)
	{
		printf("ServerSocket creation Failed\n");
		exit(1);
	}

	serverAddress = createIPV4Address(atoi(port), address);

	if (serverAddress == NULL)
	{
		printf("Server Socket address creation failed\n");
		exit(1);
	}

	errorCheck = bind(serverSocketFD, (struct sockaddr *)serverAddress, sizeof(*serverAddress));

	if (errorCheck == 0)
	{
		printf("server Socket bound successfully\n");
	}
	else
	{
		printf("Server Socket Binding failed\n");
		exit(1);
	}

	errorCheck = listen(serverSocketFD, 10);

	if (errorCheck == 0)
	{
		printf("listening for Clients thorugh Server: %s port: %s\n", address, port);
	}
	else
	{
		printf("Failed listening for client\n");
		exit(1);
	}
	/*function that creates a thread for each new connection*/
	startAcceptingNewConnections(serverSocketFD);

	shutdown(serverSocketFD, SHUT_RDWR);

	return (0);
}
