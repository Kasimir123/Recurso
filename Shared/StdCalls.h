#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Constants.h"

// Prints an error message to stderr then exits 
void error(char * message);

// Reads in the file path given to the char pointer and 
// sets int pointer to the size of the read data
unsigned char * readFile(char * filePath, int * size);

// Print the specified number of chars
void printfNum(unsigned char * data, int size);

char checkExpressionCharacters(unsigned char * token);

unsigned char * intToBytes(int x);

unsigned char * longLongToBytes(long long x);

int bytesToInt(unsigned char * bytes);

long long bytesToLongLong(unsigned char * bytes);