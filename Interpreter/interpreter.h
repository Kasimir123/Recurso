#include "../Shared/BytecodeFile.h"

typedef struct Function
{
    int startAddress;

    long long ** locals;

    int localsCap;

    int localsCount;

    int functionCount;

} Function;

typedef struct Return
{
    int address;
    int function;
} Return;

void runProgram(unsigned char * funcOps, unsigned char * opCodes, int length);