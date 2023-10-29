#include "../headers/socket.h"

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
 * function that accepts new connections and calls a printing function
 * @SocketFD: server socketFD.
 * Description: Function waits for client connections
 * and calls acceptincomingClient() function.
 * The Client group structure elements are filled by
 * socket structures of the incoming clients.
 * The function then calls the receiveAndPrintDataSeperateThread() function
 * to create threads of individual client packets.
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
		/*function to add a new client to the client group*/
		addClientsToGroup(*clientSocket);
		/*function that receives and prints data*/
		recieveAndPrintDataSeperateThread(clientSocket);
	}
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
	client->acceptedClientSocketFD = clientSocketFD;
	client->acceptedSuccessfully = clientSocketFD > 0;

	if (!client->acceptedSuccessfully)
	{
		client->error = clientSocketFD;
	}

	return (client);
}

/**
 * addClientsToGroup - adds a new client to a group of clients
 * @newClient: new client to add to group.
 * Description: This function adds a new client to a client group
 * While locking the action in a mutex and unlocking after.
 */
void addClientsToGroup(struct AcceptedClient newClient)
{
	pthread_mutex_lock(&clientGroupMutex);

	if (acceptedClientCount < MAXIMUM_CLIENTS)
	{
		clientGroup[acceptedClientCount++] = newClient;
	}
	else
	{
		printf("Sorry! the server is full, try again later\n");
	}
	pthread_mutex_unlock(&clientGroupMutex);
}

/**
 * receiveAndPrintDataSeperateThread - receive and prints data from client
 * @clientSocket: pointer to structure of accepted client socket
 * Description: This function creates a thread of client messages
 * by calling the threadFunctionSeperateThreads() function.
 */
void recieveAndPrintDataSeperateThread(struct AcceptedClient *clientSocket)
{
	pthread_t id;
	pthread_create(&id, NULL, threadFunctionSeperateThreads, &clientSocket->acceptedClientSocketFD);
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
 * @clientSocketFD: server-side client socket file descriptor
 * Description: the function waits for client data
 * and prints it to the stndard output. The function calls
 * a broadcastClientGroup() function wrapped in lock & unlock mutex
 * to broadcast the a cliet message to every other client.
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
			messageLine[charCountMessageLine] = '\0';
			printf("Client: %s\n", messageLine);

			pthread_mutex_lock(&clientGroupMutex);
			broadcastClientGroup(messageLine, clientSocketFD);
			pthread_mutex_unlock(&clientGroupMutex);
		}
		else if (charCountMessageLine == 0)
		{
			printf("Client Disconected\n");
			break;
		}
		else
		{
			perror("recv");
			break;
		}
	}

	close(clientSocketFD);
}

/**
 * broadcastClientGroup - broadcasts a client's data.
 * @messageLine: string of data to send.
 * @socketFD: socket file descriptor.
 * Description: the function calls a send function that
 * formats and broadcasts client data to everyother client in clientGroup.
 */
void broadcastClientGroup(char *messageLine, int socketFD)
{
	int i;

	for (i = 0; i < acceptedClientCount; i++)
	{
		if (clientGroup[i].acceptedClientSocketFD != socketFD)
		{
			send(clientGroup[i].acceptedClientSocketFD, messageLine, strlen(messageLine), 0);
		}
	}
}

/**
 * listenAndPrintMessagesThread - create's a thead to print client data
 * @socketFD: socket File Dscriptor
 * Description: creates threads to listen and print client data.
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
 * listenPrint - listens & prints broadcasted data.
 * @clientSocketFD: client's socket file descriptor.
 * Description: waits for server to brodcast message
 * and fills to a buffer then prints and closes the socket.
 */
void listenPrint(int clientSocketFD)
{
	int charCountbuffer;
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
