#include "compiler.h"
#include <string.h>

// Global Bytecode File
BytecodeFile * bFile;

List * funcNames;

// Checks if the node is an end node
// Can possibly change this to only take expression nodes
char isEndNode(void * node)
{
    switch (*(char *)(node))
    {
        case EXPRESSIONNODE:
            return (((ExpressionNode *)node)->left == NULL && ((ExpressionNode *)node)->right == NULL);
    }
}

// Takes a node and converts it into bytecode
void nodeToBytecode(char * root, List * locals)
{
    // If it is a local variable then we load the value
    if (getElement(locals, root) != -1)
    {
        addOpAndInt(bFile, LOAD, getElement(locals, root));
    }
    // else if it is addition
    else if (!strcmp(root, "+"))
    {
        addOp(bFile, IADD);
    }
    // else if it is subtraction
    else if (!strcmp(root, "-"))
    {
        addOp(bFile, ISUB);
    }
    // else if it is multiplication
    else if (!strcmp(root, "*"))
    {
        addOp(bFile, IMUL);
    }
    // else if it is division
    else if (!strcmp(root, "/"))
    {
        addOp(bFile, IDIV);
    }
    // otherwise assume we are loading a constant
    // currently only supports ints
    else 
    {
        addOpAndInt(bFile, ICONST, atoi(root));
    }
}

// Processes the expression nodes
void processExpressions(ExpressionNode * node, List * locals)
{
    // if it is an assignment node
    if (!strcmp(node->root, "="))
    {
        // if it is an end node 
        if (isEndNode((void *)(node)))
        {
            // we convert the node to bytecode
            nodeToBytecode(node->root, locals);
        }
        // if not an end node
        else
        {
            // process the right node 
            processExpressions(node->right, locals);
        }

        // was an assignment node so we store the left node value
        addOpAndInt(bFile, STORE, getElement(locals, node->left->root));
    }
    // if it is a print node
    else if (node->specialType == PRINTTYPE)
    {
        // if there are values to the right we will want to process them
        if (node->right != NULL) processExpressions(node->right, locals);

        // if the left node is not null we want to convert it to bytecode
        if (node->left != NULL) nodeToBytecode(node->left->root, locals);

        // convert the root node to bytecode
        nodeToBytecode(node->root, locals);

        // add the print opcode
        addOp(bFile, PRINT);
    }
    else if (node->specialType == RETURNTYPE)
    {
        // if there are values to the right we will want to process them
        if (node->right != NULL) processExpressions(node->right, locals);

        // if the left node is not null we want to convert it to bytecode
        if (node->left != NULL) nodeToBytecode(node->left->root, locals);

        // convert the root node to bytecode
        nodeToBytecode(node->root, locals);

        
        addOp(bFile, RET);
    }
    else if (node->specialType == INPUTTYPE)
    {
        addOp(bFile, INPUT);

        addOpAndInt(bFile, STORE, getElement(locals, node->root));
    }
    else if (node && getElement(funcNames, node->root) != -1)
    {
        // // if there are values to the right we will want to process them
        // if (node->right != NULL) processExpressions(node->right, locals);

        // nodeToBytecode(node->root, locals);

        for (int i = 0; i < node->params->count; i++)
            nodeToBytecode(node->params->list[i], locals);

        addOpAndInt(bFile, CALL, getElement(funcNames, node->root));
    }
    // else if it is an end node
    else if (isEndNode((void *)(node)))
    {
        // turn the node to bytecode
        nodeToBytecode(node->root, locals);
    }
    // if none of the above
    else
    {
        // process the right node
        processExpressions(node->right, locals);

        // turn left node to bytecode
        nodeToBytecode(node->left->root, locals);

        // turn right node to bytecode
        nodeToBytecode(node->root, locals);
    }
}

// Compiles the bytecode
void compileBytecode(ProgramNode * programNode)
{
    // initialize the bytecode file
    bFile = initBytecodeFile();

    funcNames = initList();

    // loop through all function nodes in the program
    for (int i = 0; i < programNode->count; i++)
    {
        // gets the current function node
        FunctionNode * cur = programNode->nodes[i];

        addElement(funcNames, cur->name);
    }

    // loop through all function nodes in the program
    for (int i = 0; i < programNode->count; i++)
    {
        // gets the current function node
        FunctionNode * cur = programNode->nodes[i];

        // Sets the address to the current program count (start of function opcodes)
        cur->address = bFile->programCount;

        // adds the function to the function table
        addFunction(bFile, cur);

        for (int j = 0; j < cur->params; j++)
            addOpAndInt(bFile, STORE, cur->params - j - 1);

        // loop through all expression nodes
        for (int j = 0; j < cur->count; j++)

            // process the expression nodes
            processExpressions(cur->nodes[j], cur->locals);

        if (i == 0) addOp(bFile, HALT);
    }

    // prints the bytecode file, for debugging
    printAsLong(bFile);

    // runs the program
    runProgram(bFile->functionData, bFile->programData, bFile->programCount);
}