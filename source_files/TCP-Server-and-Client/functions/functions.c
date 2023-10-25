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
