#include "../headers/passgen.h"

int countPassInFile(char *fileName)
{
	int passwordCount = 0;
	char line[256];/*maximum charachter allowed in the line*/
	FILE *file = fopen(fileName, "r");

	if (file == NULL)
	{
		printf("couldn't open %s", fileName);
		return (-1);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		passwordCount++;
	}

	fclose(file);
	return(passwordCount);
}
