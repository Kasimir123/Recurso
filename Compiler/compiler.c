#include "compiler.h"
#include <string.h>

BytecodeFile * bFile;

char isEndNode(void * node)
{
    switch (*(char *)(node))
    {
        case EXPRESSIONNODE:
            return (((ExpressionNode *)node)->left == NULL && ((ExpressionNode *)node)->right == NULL);
    }
}

void nodeToBytecode(ExpressionNode * node, List * ints)
{
    if (getElement(ints, node->root) != -1)
    {
        addOpAndInt(bFile, LOAD, getElement(ints, node->root));
    }
    else if (!strcmp(node->root, "+"))
    {
        addOp(bFile, IADD);
    }
    else if (!strcmp(node->root, "-"))
    {
        addOp(bFile, ISUB);
    }
    else if (!strcmp(node->root, "*"))
    {
        addOp(bFile, IMUL);
    }
    else 
    {
        addOpAndInt(bFile, ICONST, atoi(node->root));
    }
}

void processExpressions(ExpressionNode * node, List * ints)
{
    if (!strcmp(node->root, "="))
    {
        if (isEndNode((void *)(node)))
        {
            nodeToBytecode(node, ints);
        }
        else
        {
            processExpressions(node->right, ints);
        }

        addOpAndInt(bFile, STORE, getElement(ints, node->left->root));
    }
    else if (!node->isPrint)
    {
        if (node->right != NULL) processExpressions(node->right, ints);
        if (node->left != NULL) nodeToBytecode(node->left, ints);
        nodeToBytecode(node, ints);
        addOp(bFile, PRINT);
    }
    else if (isEndNode((void *)(node)))
    {
        nodeToBytecode(node, ints);
    }
    else
    {
        processExpressions(node->right, ints);
        nodeToBytecode(node->left, ints);
        nodeToBytecode(node, ints);
    }
}

void compileBytecode(ProgramNode * programNode, List * ints)
{
    bFile = initBytecodeFile();

    for (int i = 0; i < programNode->count; i++)
        processExpressions(programNode->nodes[i], ints);
    addOp(bFile, HALT);

    printAsLong(bFile);
    runProgram(bFile->data, bFile->count);
}