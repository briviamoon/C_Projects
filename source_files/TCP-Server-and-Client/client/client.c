#include "../headers/server.h"

int main()
{
	int socketFD;
	/*char *ip = "192.168.8.137";*/
	char *ip = "142.250.188.46";
	int result;
	char *message;
	char buffer[1024];
	struct sockaddr_in address;

	socketFD = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_port = htons(80);
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr.s_addr);

	result = connect(socketFD, (struct sockaddr *)&address, sizeof(address));

	if (result == 0)
	{
		printf("connection up and running!\n");
	}

	message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
	send(socketFD, message, strlen(message), 0);

	recv(socketFD, buffer, 1024, 0);

	printf("From Goorle Server: %s\n", buffer);

	return (0);
}
