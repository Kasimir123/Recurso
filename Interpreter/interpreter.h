#include "../Shared/BytecodeFile.h"

typedef struct Function
{
    int startAddress;
    int locals[10];
} Function;

typedef struct Return
{
    int address;
    int function;
} Return;

void runProgram(unsigned char * funcOps, unsigned char * opCodes, int length);