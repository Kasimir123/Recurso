#include "../Compiler/compiler.h"
#include "../Shared/StdCalls.h"
#include <string.h>

int fileSize;
unsigned char * fileData;
FunctionNode * curFunction;
ProgramNode * program;