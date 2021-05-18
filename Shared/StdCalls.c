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