#include "../headers/server.h"
/**
 * main - initiate Server to Live.
 * Return: 0 if proccess succesful.
*/
int main(void)
{
	int socketFD;
	/*char *ip = "192.168.8.137";*/
	char *ip = "142.250.188.46";
	int res;
	char *message;
	char buffer[1024];
	struct sockaddr_in *address = createIPV4Address(80, ip);

	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	res = connect(socketFD, (struct sockaddr *)address, sizeof(struct sockaddr));

	if (res == 0)
	{
		printf("connection up and running!\n");
	}

	message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
	send(socketFD, message, strlen(message), 0);

	recv(socketFD, buffer, 1024, 0);

	printf("From Goorle Server: %s\n", buffer);

	return (0);
}
