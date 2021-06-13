#include "../Shared/BytecodeFile.h"

typedef struct Function
{
    int startAddress;
    void ** locals;
} Function;

void runProgram(unsigned char * opCodes, int length);