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
	char *yourName;
	int errorChek;
	char *messageLine = NULL;
	size_t lineSize = 0;
	size_t charCountMessageLine;
	struct sockaddr_in *clientAddress;

	if (argc < 4)
	{
		printf("Please Provide the Server Address, port to use, and Name to identify yourself\n");
		exit(1);
	}

	address = argv[1];
	port = argv[2];
	yourName = argv[3];
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
		printf("Client connection established!\n");
	}

	printf("Type your Message\n");

	while (true)
	{
		printf("%s: ", yourName);
		charCountMessageLine = getline(&messageLine, &lineSize, stdin);

		if (charCountMessageLine > 0)
		{
			if (strcmp(messageLine, "quit\n") == 0)
			{
				break;
			}
			send(clientSocketFD, messageLine, charCountMessageLine, 0);
		}
	}

	close(clientSocketFD);
	return (0);
}
