#include "StdCalls.h"

void error(char * message)
{
    // Prints error message to standard error
    fprintf(stderr, "%s\n", message);

    // Exits the program
    exit(EXIT_FAILURE);
}

unsigned char * readFile(char * filePath, int * size)
{
    // Open the file as read binary
    FILE *fd = fopen(filePath, "rb");

    // If the file is not found then error out
    if (!fd) error(FILENOTFOUND);

    // Find the end of the file
    fseek(fd, 0, SEEK_END);

    // Get the file size
    * size = (int)ftell(fd);

    // Rewind to the start of the file
    rewind(fd);

    // Malloc space for the file data
    unsigned char * data = (unsigned char *)malloc(* size);

    // Read the files
    fread(data, 1, * size, fd);

    // Close the file
    fclose(fd);

    // Return the data
    return data;

}

void printfNum(unsigned char * data, int size)
{

    // Allocate space to print
    char * toPrint = (char *)malloc(size + 1);

    // Copy the number of chars to print
    memcpy(toPrint, (char *)data, size);

    toPrint[size] = '\x0';

    // Print the bytes 
    fprintf(stdout, "%s\n", toPrint);

    // Free the space
    free(toPrint);
}

char checkExpressionCharacters(unsigned char * token)
{
    if (token[0] >= 42 && token[0] <= 47) return 0;
    else return 1;
}

// converts and int to bytes
unsigned char * intToBytes(int x)
{
    unsigned char * bytes = (unsigned char *)malloc(sizeof(unsigned char) * 4);

    bytes[0] = (x >> 24) & 0xFF;
    bytes[1] = (x >> 16) & 0xFF;
    bytes[2] = (x >> 8) & 0xFF;
    bytes[3] = x & 0xFF;

    return bytes;
}

unsigned char * longLongToBytes(long long x)
{
    unsigned char * bytes = (unsigned char *)malloc(sizeof(unsigned char) * 8);
    
    bytes[0] = (x >> 56) & 0xFF;
    bytes[1] = (x >> 48) & 0xFF;
    bytes[2] = (x >> 40) & 0xFF;
    bytes[3] = (x >> 32) & 0xFF;
    bytes[4] = (x >> 24) & 0xFF;
    bytes[5] = (x >> 16) & 0xFF;
    bytes[6] = (x >> 8) & 0xFF;
    bytes[7] = x & 0xFF;

    return bytes;
}

// converts bytes to an int
int bytesToInt(unsigned char * bytes)
{
    int x = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
    return x;
}

long long bytesToLongLong(unsigned char * bytes)
{
    long long x = ((long long)bytes[0] << 56) + ((long long)bytes[1] << 48) + ((long long)bytes[2] << 40) + ((long long)bytes[3] << 32) + 
    ((long long)bytes[4] << 24) + ((long long)bytes[5] << 16) + ((long long)bytes[6] << 8) + (long long)bytes[7];
    
    return x;
}