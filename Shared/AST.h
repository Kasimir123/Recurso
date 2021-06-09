#include <stdio.h>
#include <stdlib.h>

#define EXPRESSIONNODE 'e'

typedef struct ProgramNode ProgramNode;

typedef struct ParameterNode ParameterNode;

typedef struct ExpressionNode ExpressionNode;

typedef struct FunctionNode FunctionNode;


// Program Node Struct
struct ProgramNode {

    // type of node this is
    char nodeType;

    int capacity;

    int count;

    // all of the nodes in the program
    void * * nodes;

};

// Parameter Node Struct
struct ParameterNode {

    // type of node this is
    char nodeType;

    // parameter type
    char type;

    // parameter name
    char * name;

    // length of name
    int nameLen;

    // next parameter
    ParameterNode * next;

};

// Expression Node Struct
struct ExpressionNode {

    // type of node this is
    char nodeType;

    // root data
    char * root;

    // root data length
    int rootLen;

    // left node
    ExpressionNode * left;

    // right node
    ExpressionNode * right;

};

// Function Node Struct
struct FunctionNode {

    // type of node this is
    char nodeType;

    // Use a char for typing to keep memory usage small
    char returnType;

    // Name of the function
    char * name;

    // Length of the function - 
    // may be able to get rid of this once we do more analysis on
    // memory usage vs runtime speeds
    int nameLen;

    // Start of linked list for parameters
    ParameterNode * firstParam;

    // ****************
    // Pattern Node may be Parameter Node in which case we will need to 
    // add another variable, will need to see as we build program
    // ****************

    // All inner program information
    ProgramNode * inner;

};

enum ExpressionState {Start, First, Root, End};

void printExpressionNode(ExpressionNode * node);

ProgramNode * initProgramNode();

void addElementToProgramNode(ProgramNode * programNode, void * node);

void freeProgramNode(ProgramNode * node);