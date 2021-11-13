#include "interpreter.h"

// Prints the stack, for debugging purposes
void printStack(int * stack)
{
    printf("STACK: [");
    for (int i = 0; i < 10; i++)
        printf("%d ", stack[i]);
    printf("]\n");
}

long long getLocal(Function * func, int local)
{
    return func->locals[func->functionCount - 1][local];
}

void setLocal(Function * func, int local, long long val)
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
        func->locals = (long long **)realloc(func->locals, sizeof(long long *) * func->localsCap);

        for (int i = func->localsCount; i < func->localsCap; i++)
            func->locals[i] = (long long *)malloc(sizeof(long long) * 10);
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

        // unsigned char params[4];
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
        functions[count - 1]->localsCap = bytesToInt(locals);
        functions[count - 1]->functionCount = ((count - 1 == 0) ? 1 : 0);
        functions[count - 1]->locals = (long long **)malloc(sizeof(long long *) * functions[count - 1]->localsCap);

        for (int i = 0; i < functions[count - 1]->localsCap; i++)
            functions[count - 1]->locals[i] = (long long *)malloc(sizeof(long long) * 20);

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
    long long stack[10000];
    int cf = 0;

    int retCap = 64;
    Return ** retStack = (Return **)malloc(sizeof(Return *) * retCap);

    for (int i = 0; i < retCap; i++)
        retStack[i] = (Return *)malloc(sizeof(Return));

    // main "CPU", continues going until HALT is reached
    while (opCodes[ip] != HALT)
    {
        // Gets the current opcode
        unsigned char op = opCodes[ip++];
        //printStack(stack);
        // printf("Op: %x %x\n", ip - 1, op);
        // printf("[");
        // for (int cc = 0; cc < 350; cc++)
        //     printf("%x, ", opCodes[cc]);

        // printf("]\n");

        // switch between all possible opcodes
        switch (op)
        {
            case (ISUB):;
                long long a = stack[--sp];
                long long b = stack[--sp];
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
            case (OR):;
                a = stack[--sp];
                b = stack[--sp];
                stack[sp++] = a | b;
                break;
            case (AND):;
                a = stack[--sp];
                b = stack[--sp];
                stack[sp++] = a & b;
                break;
            case (XOR):;
                a = stack[--sp];
                b = stack[--sp];
                stack[sp++] = a ^ b;
                break;
            case (FADD):
                break;
            case (ITOF):
                break;
            case (CCONST):
                break;
            case (ICONST):;
                unsigned char l[8];
                l[0] = opCodes[ip++];
                l[1] = opCodes[ip++];
                l[2] = opCodes[ip++];
                l[3] = opCodes[ip++];
                l[4] = opCodes[ip++];
                l[5] = opCodes[ip++];
                l[6] = opCodes[ip++];
                l[7] = opCodes[ip++];

                stack[sp++] = bytesToLongLong(l);
                break;
            case (SCONST):
                break;
            case (FCONST):
                break;
            case (STORE):;
                unsigned char i[4];
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                setLocal(functions[cf], bytesToInt(i), stack[--sp]);
                break;
            case (LOAD):
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                stack[sp++] = getLocal(functions[cf], bytesToInt(i));
                break;
            case (RET):
                decrementFunction(functions[cf]);

                ip = retStack[--rp]->address;
                cf = retStack[rp]->function;
                break;
            case (PRINT):
                printf("%lld\n", stack[--sp]);
                break;
            case (POP):
                stack[--sp];
                break;
            case (CALL):
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                if (rp >= retCap)
                {
                    retCap *= 2;
                    retStack = (Return **)realloc(retStack, sizeof(Return *) * retCap);

                    for (int j = rp; j < retCap; j++)
                        retStack[j] = (Return *)malloc(sizeof(Return));
                }

                retStack[rp]->function = cf;
                retStack[rp]->address = ip;

                rp++;

                cf = bytesToInt(i);

                ip = functions[cf]->startAddress;
                incrementFunction(functions[cf]);
                break;
            case (INPUT):
                ;
                long long inpt;
                scanf("%lld", &inpt);
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
            case (NCMP):
                a = stack[--sp];
                b = stack[--sp];
                if (a == b)
                {
                    do {
                        op = opCodes[ip++];
                    }
                    while (op != RET);
                }
                break;
            case (LTCMP):
                a = stack[--sp];
                b = stack[--sp];
                if (a < b)
                {
                    do {
                        op = opCodes[ip++];
                    }
                    while (op != RET);
                }
                break;
            case (GTCMP):
                a = stack[--sp];
                b = stack[--sp];
                if (a > b)
                {
                    do {
                        op = opCodes[ip++];
                    }
                    while (op != RET);
                }
                break;
            case (JMP):
                
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                ip = bytesToInt(i);
                break;
            case (IJMP):
                ip = (int)stack[--sp];
                break;
            case (INC):
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                opCodes[bytesToInt(i)] += 1;
                break;
            case (DEC):
                
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                // printf("Original: %x ", opCodes[bytesToInt(i)]);

                opCodes[bytesToInt(i)] -= 1;

                // printf("After: %x\n", opCodes[bytesToInt(i)]);
                break;
            case (MOV):

                a = stack[--sp];
                b = stack[--sp];

                opCodes[b] = opCodes[a];
                break;
            case (MEMP):
                
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                stack[sp++] = (opCodes[bytesToInt(i)] << 8) + (opCodes[bytesToInt(i) + 1]);
                break;
            case (CMPJMP):
                
                i[0] = opCodes[ip++];
                i[1] = opCodes[ip++];
                i[2] = opCodes[ip++];
                i[3] = opCodes[ip++];

                a = stack[--sp];
                b = stack[--sp];

                if (a == b)
                    ip = bytesToInt(i);
        }

    }
}