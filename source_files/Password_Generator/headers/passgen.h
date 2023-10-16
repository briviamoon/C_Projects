#ifndef PASSGEN_H
#define PASSGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *generator(int passLength);
char randomizer(void);
int writeToFile(int passLength, int fileSize, char *fileName);
int countPassInFile(char *fileName);

#endif