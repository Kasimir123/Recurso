#include "AST.h"

// Print expression node
void printExpressionNode(ExpressionNode * node)
{

    if (!node->isPrint) fprintf(stdout, "print ");

    // If left and right nodes are null then print root
    if (node->left == NULL && node->right == NULL) fprintf(stdout, "%s ", node->root);
    // else
    else 
    {
        // print root
        fprintf(stdout, "( %s ", node->root);

        // print left node
        printExpressionNode(node->left);

        // print right node
        printExpressionNode(node->right);

        // print closing )
        fprintf(stdout, ") ");
    }
}

// Initializes the ProgramNode
ProgramNode * initProgramNode()
{
    // Mallocs the ProgramNode
    ProgramNode * programNode = (ProgramNode *)malloc(sizeof(ProgramNode));

    // Capacity
    programNode->capacity = 5;
    
    // Count
    programNode->count = 0;

    // Malloc nodes list
    programNode->nodes = (void **)malloc(sizeof(void *) * programNode->capacity);

    // Return ProgramNode
    return programNode;
}

// Add element to ProgramNode
void addElementToProgramNode(ProgramNode * programNode, void * node)
{
    // Check if at capacity
    if (programNode->count >= programNode->capacity)
    {
        // Double capacity
        programNode->capacity *= 2;

        // Reallocate the list
        programNode->nodes = (void **)realloc(programNode->nodes, sizeof(void *) * programNode->capacity);
    }
    
    // Add the node
    programNode->nodes[programNode->count] = node;

    // Increase counter
    programNode->count++;
}

// free expression node
void freeExpressionNode(ExpressionNode * node)
{
    // if left exists then free it
    if (node->left != NULL) freeExpressionNode(node->left);

    // if right exists then free it
    if (node->right != NULL) freeExpressionNode(node->right);

    // free the root data
    free(node->root);

    // free the node
    free(node);
}

// free the program node
void freeProgramNode(ProgramNode * node)
{
    // loop through all nodes
    for (int i = 0; i < node->count; i++)
    {
        // switch between node types
        switch(*(char *)(node->nodes[i]))
        {
            // expression node type
            case EXPRESSIONNODE:

                // free expression node
                freeExpressionNode(node->nodes[i]);
                break;
        }
    }


    // // loop through remainder of node space
    // for (int i = node->count; i < node->capacity; i++)
    //     // free the empty nodes
    //     free(node->nodes[i]);

    // free nodes array
    free(node->nodes);

    // free node
    free(node);
}