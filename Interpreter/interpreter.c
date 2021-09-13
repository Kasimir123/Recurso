#include "interpreter.h"

// Prints the stack, for debugging purposes
void printStack(int * stack)
{
    printf("STACK: [");
    for (int i = 0; i < 10; i++)
        printf("%d ", stack[i]);
    printf("]\n");
}

int getLocal(Function * func, int local)
{
    return func->locals[func->functionCount - 1][local];
}

void setLocal(Function * func, int local, int val)
{
    func->locals[func->functionCount - 1][local] = val;
}

void incrementFunction(Function * func)
{
    func->functionCount++;
    func->localsCount++;
    if (func->localsCount >= func->localsCap)
    {
        // Double capacity
        func->localsCap *= 2;

        // Reallocate the list
        func->locals = (int **)realloc(func->locals, sizeof(int *) * func->localsCap);

        for (int i = func->localsCount + 1; i < func->localsCap; i++)
            func->locals[i] = (int *)malloc(sizeof(int) * 10);
    }
}

void decrementFunction(Function* func)
{
    func->functionCount--;
    func->localsCount--;
}

Function ** initializeFunctions(unsigned char * funcOps)
{

    int cap = 2;
    int count = 1;
    Function ** functions = (Function **)malloc(sizeof(Function *) * cap);

    int i = 0;
    unsigned char op = funcOps[i++];

    while (op == FUNC)
    {
        // declare and intialize values

        unsigned char params[4];
        unsigned char locals[4];
        unsigned char address[4];

        // get next opcode
        op = funcOps[i++];

        // while not func info
        while (op != FUNCINFO)
        {
            // print out function name
            op = funcOps[i++];
        }

        // get local count
        locals[0] = funcOps[i++];
        locals[1] = funcOps[i++];
        locals[2] = funcOps[i++];
        locals[3] = funcOps[i++];

        // get address
        address[0] = funcOps[i++];
        address[1] = funcOps[i++];
        address[2] = funcOps[i++];
        address[3] = funcOps[i++];

        if (count >= cap)
        {
            cap *= 2;
            functions = (Function **)realloc(functions, sizeof(Function *) * cap);
        }

        functions[count - 1] = (Function *)malloc(sizeof(Function));
        functions[count - 1]->startAddress = bytesToInt(address);
        functions[count - 1]->localsCount = 0;
        functions[count - 1]->localsCap = 16;
        functions[count - 1]->functionCount = ((count - 1 == 0) ? 1 : 0);
        functions[count - 1]->locals = (int **)malloc(sizeof(int *) * functions[count - 1]->localsCap);

        for (int i = 0; i < functions[count - 1]->localsCap; i++)
            functions[count - 1]->locals[i] = (int *)malloc(sizeof(int) * 10);

        count++;

        // get the next opcode
        op = funcOps[i++];
    }

    return functions;
}

// runs the program
void runProgram(unsigned char * funcOps, unsigned char * opCodes, int length)
{
    // for debugging
    // printf("\nProgram Runtime:\n\n");
    
    Function ** functions = initializeFunctions(funcOps);

    int ip = 0;
    int sp = 0;
    int rp = 0;
    int stack[10000];
    int cf = 0;
    Return ** retStack = (Return **)malloc(sizeof(Return *) * 100);

    for (int i = 0; i < 100; i++)
        retStack[i] = (Return *)malloc(sizeof(Return));

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

                setLocal(functions[cf], bytesToInt(i), stack[--sp]);
                break;
            case (LOAD):
                i[4];
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                stack[sp++] = getLocal(functions[cf], bytesToInt(i));
                break;
            case (RET):
                decrementFunction(functions[cf]);
                ip = retStack[--rp]->address;
                cf = retStack[--rp]->function;
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

                retStack[rp++]->function = cf;
                retStack[rp++]->address = ip;

                cf = bytesToInt(i);

                ip = functions[cf]->startAddress;
                incrementFunction(functions[cf]);
                break;
            case (INPUT):
                ;
                int inpt;
                scanf("%d", &inpt);
                stack[sp++] = inpt;
                break;
            case (CMP):
                a = stack[--sp];
                b = stack[--sp];
                if (a != b)
                {
                    do {
                        op = opCodes[ip++];
                    }
                    while (op != RET);
                }
                break;
        }

    }
}