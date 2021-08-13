#include "../Shared/BytecodeFile.h"

typedef struct Function
{
    int startAddress;
    void ** locals;
} Function;

void runProgram(unsigned char * funcOps, unsigned char * opCodes, int length);