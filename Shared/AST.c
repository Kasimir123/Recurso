#include "AST.h"

void printExpressionNode(ExpressionNode * node)
{
    if (node->left == NULL && node->right == NULL) fprintf(stdout, "%s ", node->root);
    
    else 
    {
        fprintf(stdout, "( %s ", node->root);
        printExpressionNode(node->left);
        printExpressionNode(node->right);
        fprintf(stdout, ") ");
    }
}

