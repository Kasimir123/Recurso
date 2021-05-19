#include "parser.h"

char hasNextToken(unsigned char * statement, int size)
{
    unsigned char * found = (unsigned char *)strchr(statement, ' ');

    if (!found || (int)(found - statement) > size) found = (unsigned char *)strchr(statement, ';');

    int space = (int)(found - statement);

    return (space <= size) ? 0 : 1;
}

unsigned char * nextToken(unsigned char ** statement, int * size)
{
    unsigned char * found = (unsigned char *)strchr(*statement, ' ');

    if (!found || (int)(found - *statement) > * size) found = (unsigned char *)strchr(*statement, ';');

    int space = (int)(found - *statement);

    unsigned char * token = (unsigned char *)malloc(space + 1);

    memcpy(token, *statement, space);

    *statement += space + 1;

    *size -= space + 1;

    token[space] = '\x0';

    return token;
}

ExpressionNode * createEndNode(unsigned char * token)
{
    ExpressionNode * node = (ExpressionNode *)malloc(sizeof(ExpressionNode));

    node->root = token;
    node->left = NULL;
    node->right = NULL;

    return node;
}

ExpressionNode * nextExpression(unsigned char * data, int size)
{

    unsigned char * statement = data;

    int statementSize = size;

    enum ExpressionState state = Start;

    unsigned char * token;

    ExpressionNode * node = (ExpressionNode *)malloc(sizeof(ExpressionNode));

    ExpressionNode * cur = node;

    while (state != End)
    {
        switch (state)
        {
            case Start:
                if (!size)
                {
                    cur->root = "";
                    cur->left = NULL;
                    cur->right = NULL;
                    state = End;
                }
                else 
                {
                    cur->left = createEndNode(nextToken(&statement, &size));
                    state = First;
                }
                break;
            case First:
                cur->root = nextToken(&statement, &size);
                state = Root;
                break;
            case Root:
                token = nextToken(&statement, &size);
                if (!hasNextToken(statement, size))
                {
                    cur->right = (ExpressionNode *)malloc(sizeof(ExpressionNode));
                    cur = cur->right;
                    cur->root = nextToken(&statement, &size);
                    cur->left = createEndNode(token);
                }
                else
                {
                    cur->right = createEndNode(token);
                    state = End;
                }
                break;
        }
    }

    return node;
    
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

                ExpressionNode * node = nextExpression(curPos, statementSize);

                printExpressionNode(node);

                printf("\n");

                //free(node);

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