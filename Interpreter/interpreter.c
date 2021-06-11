#include "interpreter.h"

void printStack(int * stack)
{
    printf("STACK: [");
    for (int i = 0; i < 10; i++)
        printf("%d ", stack[i]);
    printf("]\n");
}

void runProgram(unsigned char * opCodes, int length)
{
    printf("\nProgram Runtime:\n\n");
    int ip = 0;
    int sp = 0;
    int stack[10];
    int local[5];

    while (opCodes[ip] != HALT)
    {
        unsigned char op = opCodes[ip++];
        // printStack(stack);

        switch (op)
        {
            case (ISUB):
                break;
            case (IMUL):
                break;
            case (IADD):;
                int a = stack[--sp];
                int b = stack[--sp];
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
        }

    }
}