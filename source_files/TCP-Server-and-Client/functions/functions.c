#include "../headers/server.h"

struct AcceptedClient clientGroup[10];
int acceptedClientCount = 0;
pthread_mutex_t clientGroupMutex = PTHREAD_MUTEX_INITIALIZER;

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
	client->acceptedClienSocketFD = clientSocketFD;
	client->acceptedSuccessfully = clientSocketFD > 0;

	if (!client->acceptedSuccessfully)
	{
		client->error = clientSocketFD;
	}

	return (client);
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
		clientGroup[acceptedClientCount++] = *clientSocket;
		/*function that receives and prints data*/
		recieveAndPrintDataSeperateThread(clientSocket);
	}
}

/**
 * receiveAndPrintDataSeperateThread - receive and prints data from client
 * @clientSocket: pointer to structure of accepted client socket
 */
void recieveAndPrintDataSeperateThread(struct AcceptedClient *clientSocket)
{
	pthread_t id;
	pthread_create(&id, NULL, threadFunctionSeperateThreads, &clientSocket->acceptedClienSocketFD);
}
/**
 * threadFunctionSeperateTreads - calls receive & print function
 * @arg: void argument
 * Description: function substitutes void argument with socketFD arg
 * this is because the pthread_create function accepts a par of type void
 * then passes a socketFD file into it. the passed argument is then switched
 * and passed to our true intended function call
 */
void *threadFunctionSeperateThreads(void *arg)
{
	int SocketFD = *((int *)arg);
	recieveAndPrintData(SocketFD);
	return NULL;
}

/**
 * receiveAndPrintData - receives and prints data
 */
void recieveAndPrintData(int clientSocketFD)
{
	size_t charCountMessageLine;
	char messageLine[2048];

	while (true)
	{
		charCountMessageLine = recv(clientSocketFD, &messageLine, 2048, 0);

		if (charCountMessageLine > 0)
		{
			messageLine[charCountMessageLine] = 0;
			printf("Client: %s\n", messageLine);
			
			pthread_mutex_lock(&clientGroupMutex);
            broadcastClientGroup(messageLine, clientSocketFD);
            pthread_mutex_unlock(&clientGroupMutex);
		}
		if (charCountMessageLine == 0)
		{
			break;
		}
	}

	close(clientSocketFD);
}


/**
 * sends the 
*/
void broadcastClientGroup(char *messageLine, int socketFD)
{
	int i;

	for (i = 0; i < acceptedClientCount; i++)
	{
		if (clientGroup[i].acceptedClienSocketFD != socketFD)
		{
			send(clientGroup[i].acceptedClienSocketFD, messageLine, strlen(messageLine), 0);
		}
	}
}


/**
 * listenAndPrintMessagesThread - create's a thead of listeners & printers
 * @socketFD: socket File Dscriptor 
*/
void listenAndPrintMessagesThread(int socketFD)
{
	pthread_t id;

	pthread_create(&id, NULL, threadFunctionListenPrint, &socketFD);
}

/**
 * threadFunctioListenPrint - calls ListenPrint(...) function
 * @arg: void argument
 * Description: function substitutes void argument with socketFD arg
 * this is because the pthread_create function accepts a par of type void
 * then passes a socketFD file into it. the passed argument is then switched
 * and passed to our true intended function call
 */
void *threadFunctionListenPrint(void *arg)
{
	int socketFD = *((int *)arg);
	listenPrint(socketFD);
	return NULL;
}


/**
 * listenPrint - listens & prints broadcast message.
 * @clientSocketFD: client's socket file descriptor
*/
void listenPrint(int clientSocketFD)
{	int charCountbuffer;
	char buffer[2048];

	while (true)
	{
		charCountbuffer = recv(clientSocketFD, buffer, 2048, 0);

		if (charCountbuffer > 0)
		{
			buffer[charCountbuffer] = 0;
			printf("Other Client: %s\n", buffer);
		}
		if (charCountbuffer == 0)
		{
			break;
		}
	}

	close(clientSocketFD);
}
