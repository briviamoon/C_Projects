#include "../headers/passgen.h"

int writeToFile(int passLength, int fileSize, char *fileName)
{
	char *password;
	double numberOfPass;
	int counter;
	FILE *file = fopen(fileName, "a");

	numberOfPass = ((fileSize * 1024 * 1024) / passLength);

	for (counter = 0; counter < numberOfPass; counter++)
	{
		password = generator(passLength);

		fprintf(file, "%s\n", password);

		free(password);
	}

	fclose(file);
	return (0);
}

// 						/*CKECKING FOR REPEATING PASSWORDS AND AVOIDING THEM*/
// 			/*note that this section is a break from the continuation of the one above*/
// /*THIS SECTION COUNTS THE NUMBER OF PASSWORDS AND ASSIGNS MEMORY TO COMPARE AND SIGNAL UNIQUE PASSWORDS*/

// 	/*now I read the list op passwords existing in file*/
// 	int passwordCount;
// 	char line[passLength + 2]; /*for \n and '\0'*/
// 	char **existingPasswords;
// 	int j, i;

// 	passwordCount = countPassInFile(fileName);
// 	/*allocating memory to the exiating passwords*/
// 	existingPasswords = malloc(passwordCount * sizeof(char*));

// 	for (i = 0; i < numberOfPass; i++)
// 	{
// 		password = generator(passLength);

// 		/*check if pass ia unique*/
// 		int isinique = 1;
// 		for (j = 0; j < passwordCount; j++)
// 		{
// 			if (strcmp(existingPasswords[j], password) == 0)
// 			{
// 				isinique = 0;
// 				break;
// 			}
// 		}

// 		if (isinique)
// 		{
// 		fprintf(file, "%s\n", password);

// 		/*store list of existing passwords*/
// 		existingPasswords[passwordCount] = strdup(password);
// 		passwordCount++;
// 		}

// 		free(password);
// 	}

// 	fclose(file);

// 	for(i = 0; i < passwordCount; i++)
// 	{
// 		free(existingPasswords[i]);
// 	}
// 	free(existingPasswords);

// 	return(0);
// }