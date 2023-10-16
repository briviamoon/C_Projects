#include "../headers/passgen.h"

char* generator(int passLength)
{
	int i;
	char *password;

	password = (char*)malloc((passLength + 1) * sizeof(char));

	for (i = 0; i < passLength; i++)
	{
		password[i] = randomizer();
	}
	password[i] = '\0';
	return (password);
}

char randomizer()
{
	char bin[] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`~!@#$%^&*()_-+=\\|]}{[':;\"/?.>,<";
	int binLength = sizeof(bin) -1;

	return (bin[rand() % binLength]);
}
