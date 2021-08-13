#include "interpreter.h"

// Prints the stack, for debugging purposes
void printStack(int * stack)
{
    printf("STACK: [");
    for (int i = 0; i < 10; i++)
        printf("%d ", stack[i]);
    printf("]\n");
}

Function ** initializeFunctions(BytecodeFile * bFile)
{
    
}

// runs the program
void runProgram(unsigned char * funcOps, unsigned char * opCodes, int length)
{
    // for debugging
    printf("\nProgram Runtime:\n\n");


    int numOfFuncs = 1;
    
    Function ** functions = (Function **)malloc(sizeof(Function *) * numOfFuncs);

    int ip = 0;
    int sp = 0;
    int stack[10];
    int local[5];

    // main "CPU", continues going until HALT is reached
    while (opCodes[ip] != HALT)
    {
        // Gets the current opcode
        unsigned char op = opCodes[ip++];
        //printStack(stack);

        // switch between all possible opcodes
        switch (op)
        {
            case (ISUB):;
                int a = stack[--sp];
                int b = stack[--sp];
                stack[sp++] = a - b;
                break;
            case (IMUL):
                a = stack[--sp];
                b = stack[--sp];
                stack[sp++] = a * b;
                break;
            case (IDIV):
                a = stack[--sp];
                b = stack[--sp];
                stack[sp++] = a / b;
                break;
            case (IADD):;
                a = stack[--sp];
                b = stack[--sp];
                stack[sp++] = a + b;
                break;
            case (FADD):
                break;
            case (ITOF):
                break;
            case (CCONST):
                break;
            case (ICONST):;
                unsigned char i[4];
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                stack[sp++] = bytesToInt(i);
                break;
            case (SCONST):
                break;
            case (FCONST):
                break;
            case (STORE):
                i[4];
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                local[bytesToInt(i)] = stack[--sp];
                break;
            case (LOAD):
                i[4];
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                stack[sp++] = local[bytesToInt(i)];
                break;
            case (RET):
                break;
            case (PRINT):
                printf("%d\n", stack[--sp]);
                break;
            case (POP):
                break;
            case (CALL):
                i[4];
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                break;
        }

    }
}