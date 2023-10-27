#include "../headers/server.h"
/**
 * createIPV4Address - creates an IPV address structure
 * @port: port number
 * @ip: pointer to ip address string
 * Return: returns pointer to new structure of IPV4 Address
 */

struct sockaddr_in *createIPV4Address(int port, char *ip)
{
	int result;
	struct sockaddr_in *address;

	address = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
	if (address == NULL)
	{
		return (NULL);
	}

	address->sin_family = AF_INET;
	address->sin_port = htons(port);
	result = inet_pton(AF_INET, ip, &(address->sin_addr.s_addr));
	if (result <= 0)
	{
		free(address);
		return (NULL);
	}
	return (address);
}

/**
 * acceptIncomingClient - creates a structure for client socket in server
 * @serverSocketFD: file descriptor to server socket
 * Return: returns a pointer to new cientSocket structure.
 *
 * Description: creaetes a client address structure
 * - accepts an incoming client conection request
 * - puts information into the cllient client's address structure
 * - builds a structure containing elements of a clientSocket while accepted.
 */
struct AcceptedClient *acceptIncomingClient(int serverSocketFD)
{
	struct sockaddr_in *clientAddress;
	struct AcceptedClient *client;
	unsigned int sizeOfClientAddress;
	int clientSocketFD;

	clientAddress = malloc(sizeof(struct sockaddr_in));
	sizeOfClientAddress = sizeof(struct sockaddr_in);
	clientSocketFD = accept(serverSocketFD, (struct sockaddr *)clientAddress, &sizeOfClientAddress);

	client = malloc(sizeof(struct AcceptedClient));
	client->ClientAddress = *clientAddress;
	client->acceptedClienSockettFD = clientSocketFD;
	client->acceptedSuccessfully = clientSocketFD > 0;

	if (!client->acceptedSuccessfully)
	{
		client->error = clientSocketFD;
	}

	return (client);
}

/**
 * receiveAndPrintData - receives and prints data
 *
 */
void recieveAndPrintData(int socketFD)
{
	int charCountMessageLine;
	char messageLine[2048];

	while (true)
	{
		charCountMessageLine = recv(socketFD, &messageLine, 2048, 0);

		if (charCountMessageLine > 0)
		{
			messageLine[charCountMessageLine] = 0;
			printf("Client: %s\n", messageLine);
		}
		else
		{
			break;
		}
	}

	close(socketFD);
}


/**
 * function that accepts new connections and calls a printing function
 * @SocketFD: server socketFD.
*/
void startAcceptingNewConnections(int serverSocketFD)
{
	while (true)
	{
		struct AcceptedClient *clientSocket;

		/*function creates a srtucture for the the client socket*/
		clientSocket = acceptIncomingClient(serverSocketFD);
		if (clientSocket->error > 0)
		{
			printf("client Socket Connection success\n");
		}
		/*function that receives and prints data*/
		recieveAndPrintDataSeperateThread(clientSocket);
	}
}

/**
 * receiveAndPrintDataSeperateThread - receive and prints data from client
 * @socketFD: clientsocketFD;
*/
void recieveAndPrintDataSeperateThread(struct AcceptedClient *clientSocket)
{
	pthread_t id;
	pthread_create(&id, NULL, threadFunctionSeperateThreads, &clientSocket->acceptedClienSockettFD);
}

void *threadFunctionSeperateThreads(void *arg)
{
	int SocketFD = *((int *)arg);
	recieveAndPrintData(SocketFD);
	return NULL;
}
