#include "parser.h"

unsigned char * nextToken(unsigned char * data, int * size, int * currentChar)
{

} 

ExpressionNode nextExpression(unsigned char * data, int * size, int * currentChar, enum ExpressionState state)
{
    switch (state)
    {
        case Start:
            break;
        case First:
            break;
        case Root:
            break;
        case Temp:
            break;
        case RightRoot:
            break;
        case End:
            break;
    }
}

// Gets the next statement
int nextStatement(unsigned char ** data)
{
    
    // Ignore new lines
    while (**data == '\n' || **data == '\xd') (*data)++;

    // Get the next semicolon
    unsigned char * found = (unsigned char *)strchr(*data, ';');

    // Return distance to semicolon, if none then return -1
    return found ? (int)(found - *data) : -1;
}

int main(int argc, char * argv[])
{

    // If we have a file path and that path contains .rec
    if (argc == 2 && strstr(argv[1], ".rec"))
    {

        // Filesize
        int fileSize;

        // Read in the file data
        unsigned char * fileData = readFile(argv[1], &fileSize);

        // Make another pointer for positioning, allows us to free data afterwards
        unsigned char * curPos = fileData;

        // define statement size
        int statementSize;

        // while there is still more to read
        while ((int)(curPos - fileData) < fileSize)
        {

            // read the next statement
            statementSize = nextStatement(&curPos);

            // if we were able to find a statement
            if (statementSize >= 0)
            {

                printf("%d => ", statementSize);

                printfNum(curPos, statementSize);

                // increase pointer by statement size + 1 (semicolon)
                curPos += statementSize + 1;
            }
            // otherwise exit the loop (no more semicolons found)
            else break;

        }

        // free file data
        free(fileData);
    }
}