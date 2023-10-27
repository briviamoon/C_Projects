#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

struct sockaddr_in *createIPV4Address(int port, char *ip);
struct AcceptedClient *acceptIncomingClient(int SocketFD);
void recieveAndPrintData(int socketFD);
void startAcceptingNewConnections(int SocketFD);
void acceptRecievePrint(int socketFD);
void recieveAndPrintDataSeperateThread(struct AcceptedClient *clientSocket);
void *threadFunctionSeperateThreads(void *arg);
void broadcastClientGroup(char *messageLine, int socketFD);
void listenAndPrintMessagesThread(int socketFD);
void *threadFunctionListenPrint(void *arg);
void listenPrint(int socketFD);
void listenAndPrintMessagesThread(int socketFD);


struct AcceptedClient
{
	int acceptedClienSocketFD;
	struct sockaddr_in ClientAddress;
	bool acceptedSuccessfully;
	int error;
} ;



#endif
