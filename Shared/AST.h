#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define EXPRESSIONNODE 'e'
#define NOSPECIAL 0
#define PRINTTYPE 1
#define RETURNTYPE 2
#define INPUTTYPE 3
#define FUNCTIONTYPE 4


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

    char specialType;

    // root data
    char * root;

    // root data length
    int rootLen;

    // left node
    ExpressionNode * left;

    // right node
    ExpressionNode * right;

    List * params;

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

    int address;

    int params;

    // Start of linked list for parameters
    List * locals;

    int capacity;

    int count;

    // all of the nodes in the program
    void * * nodes;

    List * patternMatches;

};

enum ExpressionState {Start, First, Root, End};

ProgramNode * initProgramNode();

FunctionNode * initFunctionNode(char * name);

void addElementToFunctionNode(FunctionNode * functionNode, void * node);

void addElementToProgramNode(ProgramNode * programNode, void * node);

void freeProgramNode(ProgramNode * node);