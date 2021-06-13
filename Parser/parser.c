#include "parser.h"

// checks if another token is present in the statement
char hasNextToken(unsigned char * statement, int size)
{
    // Checks for space seperated tokens
    unsigned char * found = (unsigned char *)strchr(statement, ' ');

    // if no space seperated, look for the semicolon
    if (!found || (int)(found - statement) > size) found = (unsigned char *)strchr(statement, ';');

    // get the space for the token
    int space = (int)(found - statement);

    // return whether or not we have a token
    return (space <= size && space > 0) ? 0 : 1;
}

unsigned char * previewNextToken(unsigned char * statement, int size)
{
    // Checks for space seperated tokens
    unsigned char * found = (unsigned char *)strchr(statement, ' ');

    // if no space seperated, look for the semicolon
    if (!found || (int)(found - statement) > size) found = (unsigned char *)strchr(statement, ';');

    // get the space for the token
    int space = (int)(found - statement);

    // malloc space for the token
    unsigned char * token = (unsigned char *)malloc(space + 1);

    // copy the token from the statement
    memcpy(token, statement, space);

    // end the token string
    token[space] = '\x0';

    // return the token
    return token;
}

char isTokenVariable(unsigned char * token)
{

}



// Gets the next token in the system
unsigned char * nextToken(unsigned char ** statement, int * size)
{
    // Checks for space seperated tokens
    unsigned char * found = (unsigned char *)strchr(*statement, ' ');

    // if no space seperated, look for the semicolon
    if (!found || (int)(found - *statement) > * size) found = (unsigned char *)strchr(*statement, ';');

    // get the space for the token
    int space = (int)(found - *statement);

    // malloc space for the token
    unsigned char * token = (unsigned char *)malloc(space + 1);

    // copy the token from the statement
    memcpy(token, *statement, space);

    // increase statement pointer for next round
    *statement += space + 1;

    // subtract size left in the statement
    *size -= space + 1;

    // end the token string
    token[space] = '\x0';

    // return the token
    return token;
}

// Checks if the next token is a type
void checkIfType(unsigned char ** statement, int * size)
{
    // Preview next token
    unsigned char * token = previewNextToken(* statement, * size);

    // if int
    if (!strcmp(token, "int"))
    {
        // Go to next token
        free(nextToken(statement, size));

        // Adds the next token to the list
        addElement(curFunction->locals, previewNextToken(* statement, * size));
    }

    // free previewed token
    free(token);

}

// Creates an end node for an Expression Node
ExpressionNode * createEndNode(unsigned char * token)
{
    // malloc space for the node 
    ExpressionNode * node = (ExpressionNode *)malloc(sizeof(ExpressionNode));

    // set the root information
    node->root = token;

    // Set left to null
    node->left = NULL;

    // set right to null
    node->right = NULL;

    // set node type
    node->nodeType = EXPRESSIONNODE;

    // return node
    return node;
}

// Handles the next expression and turns it into a node
ExpressionNode * nextExpression(unsigned char * data, int size)
{
    // Get a pointer to the data, new pointer so we can increment it
    unsigned char * statement = data;

    // Get the statement size
    int statementSize = size;

    // set the state to start
    enum ExpressionState state = Start;

    // token pointer
    unsigned char * token;

    // first node 
    ExpressionNode * node = (ExpressionNode *)malloc(sizeof(ExpressionNode));

    // set node type
    node->nodeType = EXPRESSIONNODE;

    // set cur to the first node
    ExpressionNode * cur = node;

    // while loop for the state pattern
    while (state != End)
    {

        // switch on the state
        switch (state)
        {

            // start state
            case Start:
                // check if the statement is empty
                if (!size)
                {
                    // set information to the default
                    cur->root = "";
                    cur->left = NULL;
                    cur->right = NULL;

                    // set state to end
                    state = End;
                }
                else 
                {

                    // Checks if we make a variables
                    checkIfType(&statement, &size);

                    // Create the first node
                    cur->left = createEndNode(nextToken(&statement, &size));

                    // Switch into the first state
                    state = First;
                }
                break;

            // first state
            case First:

                if (!hasNextToken(statement, size))
                {
                    // sets the root to the next token
                    // SECURITY - potential security problem here
                    cur->root = nextToken(&statement, &size);

                    // sets the state to root
                    state = Root;
                }
                else 
                {
                    cur->root = cur->left->root;
                    cur->left = NULL;
                    cur->right = NULL;
                    state = End;
                }

                
                break;

            // root state
            case Root:

                // Gets a token
                // SECURITY - potential security problem here
                token = nextToken(&statement, &size);

                // Checks if we have another token
                if (!hasNextToken(statement, size))
                {
                    // set the right node to a new node
                    cur->right = (ExpressionNode *)malloc(sizeof(ExpressionNode));
                    
                    // set cur to the right node
                    cur = cur->right;

                    // set node type
                    cur->nodeType = EXPRESSIONNODE;

                    // sets the root to the new token
                    cur->root = nextToken(&statement, &size);

                    // Sets left to the end node
                    cur->left = createEndNode(token);
                }
                else
                {
                    // sets right to the end node
                    cur->right = createEndNode(token);

                    // sets state to end
                    state = End;
                }
                break;
        }
    }

    // return the node
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

// Checks to see if the current statement is a print statement
char checkIfPrint(unsigned char * statement, int size)
{
    // if its not long enough we exit
    if (size < 8) return 1;

    // might want to turn into a constant
    char print[7] = "print("; 

    // checks if the statement matches the pattern
    for (int i = 0; i < 5; i++)
        if (print[i] != statement[i]) return 1;

    // if it matched the pattern we return
    return 0;

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

        printf("\nProgram:\n\n");
        printf("%s\n", fileData);

        // Make another pointer for positioning, allows us to free data afterwards
        unsigned char * curPos = fileData;

        // define statement size
        int statementSize;

        // initialize program node
        ProgramNode * program = initProgramNode();

        // initialize the main function node
        FunctionNode * mainFunction = initFunctionNode("main");

        // add the main function to the program node
        addElementToProgramNode(program, (void *)mainFunction);

        // set the current function node
        curFunction = mainFunction;

        // while there is still more to read
        while ((int)(curPos - fileData) < fileSize)
        {

            // read the next statement
            statementSize = nextStatement(&curPos);

            // if we were able to find a statement
            if (statementSize >= 0)
            {

                // declare the expression node
                ExpressionNode * node;

                // if it is not a print
                if (checkIfPrint(curPos, statementSize))
                {
                    // Get the expression node
                    node = nextExpression(curPos, statementSize);

                    // set print to false
                    node->isPrint = 1;
                }
                // if it is a print statement
                else
                {
                    // removes the print statement bytes
                    char * withoutPrint = curPos + 6;

                    // gets the new statement size
                    int newSize = statementSize - 6;

                    // sets the new end of the statement
                    withoutPrint[newSize] = '\x00';

                    // replaces the ) with the semi-colon
                    withoutPrint[newSize - 1] = ';'; 

                    // Gets the expression node
                    node = nextExpression(withoutPrint, newSize - 1);

                    // set is print to true
                    node->isPrint = 0;
                }

                // Add expression node to the function node
                addElementToFunctionNode(curFunction, (void *)node);

                // increase pointer by statement size + 1 (semicolon)
                curPos += statementSize + 1;
            }
            // otherwise exit the loop (no more semicolons found)
            else break;

        }


        // print things for debugging        
        printf("\nFunctions:\n\n");
        for (int i = 0; i < program->count; i++)
        {
            FunctionNode * func = program->nodes[i];
            printf("Name: %s\n", func->name);
            
            printf("\nNodes:\n\n");
            for (int j = 0; j < func->count; j++)
            {
                printExpressionNode(func->nodes[j]);
                printf("\n");
            }
            printf("\nVariables:\n\n");
            for (int j = 0; j < func->locals->count; j++)
            {
                printf("%s\n", func->locals->list[j]);
            }
        }

        
        printf("\nBytecode:\n\n");

        // compile the bytecode
        compileBytecode(program);

        // free file data
        free(fileData);

        // free program node
        freeProgramNode(program);
    }
}