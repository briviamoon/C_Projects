#include "../headers/passgen.h"

/**
 * Description: this program is a project meant
 *				to create 100,000,000 passwords
 *				and append them to a file.
 *				This is for Educational purposes.
 */

int main(void)
{
	srand(time(NULL));

	int passLength;
	int fileSize;
	char *fileName = NULL;
	char buffer[256]; /*temporary buffer to store user's input*/

	printf("\t\t----------------------------------------------------------\n");
	printf("\t\t##########################################################\n");
	printf("\t\t                       PASSWORD WIZZARD                   \n");
	printf("\t\t       generate any number of passwerds of any length     \n");
	printf("\t\t            program was writen by *Brivia Allan*          \n");
	printf("\t\t           THIS IS FOR EDUCATIONAL PURPOSES ONLY\\^^/\n");
	printf("\t\t##########################################################\n");
	printf("\t\t----------------------------------------------------------\n\n\n\n");

	printf("\tHow many random Passwords would you like to generate?\n||number of passwords is denoted as\n||\tN = (F * 1024kb * 1024byts) / L\n||\tF = file size\n||\tL = password length\n||\tEnter size of the file in mbs here : ");
	scanf("%d", &fileSize);
	printf("\tWrite down The length of your password: ");
	scanf("%d", &passLength);

	/*I'll dynamicaly allocate memory for he file Name*/
	printf("\tWrite down your destination file name: ");
	if (scanf("%255s", buffer) == 1)
	{
		/*255 is the limit to the chars in buffer to prevent buffer overflow*/
		fileName = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
		if (fileName != NULL)
		{
			/*no to coppy file name fom buffe to allocated memmory*/
			strcpy(fileName, buffer);
		}
		else
		{
			printf("Memory alloc for fileName failed");
			return (1);
		}
	}
	else
	{
		printf("Invalid input. Please enter a valid file name.\n");
		return (1);
	}

	if (writeToFile(passLength, fileSize, fileName) == 0)
	{
		printf("\t\t\t#######HURRAY#######\n\tPasswords Written to file successfulty\n");
		printf("\tFollow this and many other C projects ghthub: https://github.com/briviamoon/C_Projects/\n");
	}

	return (0);
}
