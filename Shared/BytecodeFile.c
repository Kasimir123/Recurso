#include "BytecodeFile.h"

// initializes the bytecode file
BytecodeFile * initBytecodeFile()
{
    // mallocs the bytecode file
    BytecodeFile *bFile = (BytecodeFile *)malloc(sizeof(BytecodeFile));

    // sets capacity
    bFile->programCapacity = 1024;
    bFile->functionCapacity = 1024;

    // sets count
    bFile->programCount = 0;
    bFile->functionCount = 0;

    // mallocs data
    bFile->programData = (unsigned char *)malloc(sizeof(unsigned char) * bFile->programCapacity);
    bFile->functionData = (unsigned char *)malloc(sizeof(unsigned char) * bFile->functionCapacity);

    return bFile;
}

BytecodeFile * initBytecodeFileWithFile(char * filename)
{
    // mallocs the bytecode file
    BytecodeFile *bFile = (BytecodeFile *)malloc(sizeof(BytecodeFile));

    FILE * fd = fopen(filename, "rb");

    fread(&(bFile->functionCount), sizeof(int), 1, fd);

    bFile->functionData = (unsigned char *)malloc(sizeof(unsigned char) * (bFile->functionCount + 1));

    fread(bFile->functionData, sizeof(char), bFile->functionCount, fd);

    bFile->programCapacity = 1024;

    bFile->programData = (unsigned char *)malloc(sizeof(unsigned char) * (bFile->programCapacity + 1));

    int readCount = fread(bFile->programData, sizeof(char), 1024, fd);

    while (readCount == 1024)
    {
        bFile->programCount += readCount;
        bFile->programCapacity += 1024;
        bFile->programData = (unsigned char *)realloc(bFile->programData, sizeof(unsigned char) * (bFile->programCapacity + 1));
        readCount = fread(bFile->programData + bFile->programCount, sizeof(char), 1024, fd);
    }

    bFile->programCount += readCount;

    fclose(fd);

    return bFile;
}

void saveBytecode(BytecodeFile * bFile, char * filename)
{
    FILE * fd = fopen(filename, "wb");

    fwrite(&(bFile->functionCount), sizeof(int), 1, fd);
    fwrite(bFile->functionData, sizeof(char), bFile->functionCount, fd);
    fwrite(bFile->programData, sizeof(char), bFile->programCount, fd);

    fclose(fd);
}

// turns a function node into bytes
unsigned char *functionNodeToChars(FunctionNode *function)
{
    // malloc space for the bytes, gets size from: .name.44
    unsigned char *functionBytes = (unsigned char *)malloc(sizeof(unsigned char) * (function->nameLen + 10));

    // gets current position
    int cur = 0;

    // sets first node as func byte
    functionBytes[cur++] = FUNC;

    // copies the name
    for (int i = 0; i < function->nameLen; i++)
        functionBytes[cur++] = function->name[i];

    // sets the next node as the func info byte
    functionBytes[cur++] = FUNCINFO;

    // gets the bytes for locals and address from int
    unsigned char *locals = intToBytes(function->locals->count);
    unsigned char *address = intToBytes(function->address);

    // sets bytes
    functionBytes[cur++] = locals[0];
    functionBytes[cur++] = locals[1];
    functionBytes[cur++] = locals[2];
    functionBytes[cur++] = locals[3];

    functionBytes[cur++] = address[0];
    functionBytes[cur++] = address[1];
    functionBytes[cur++] = address[2];
    functionBytes[cur++] = address[3];

    // return bytes
    return functionBytes;
}

// adds the function to the bytecode file
void addFunction(BytecodeFile *bFile, FunctionNode *function)
{
    // checks if we need to reallocate for the space needed
    if (bFile->functionCount + function->nameLen + 11 >= bFile->functionCapacity)
    {
        // doubles capacity
        bFile->functionCapacity *= 2;

        // reallocates memory
        bFile->functionData = (unsigned char *)realloc(bFile->functionData, sizeof(unsigned char) * bFile->functionCapacity);
    }

    // Gets the bytes representing the function
    unsigned char *functionData = functionNodeToChars(function);

    // copies the data into the file
    for (int i = 0; i < function->nameLen + 10; i++)
        bFile->functionData[bFile->functionCount++] = functionData[i];

    // frees the function data
    free(functionData);
}

// Add opcode to the file
void addOp(BytecodeFile *bFile, unsigned char op)
{
    // check if we need to reallocate and allocate if needed
    if (bFile->programCount + 2 >= bFile->programCapacity)
    {
        bFile->programCapacity *= 2;
        bFile->programData = (unsigned char *)realloc(bFile->programData, sizeof(unsigned char) * bFile->programCapacity);
    }

    // copy opcode and string terminator
    bFile->programData[bFile->programCount++] = op;
    bFile->programData[bFile->programCount] = '\x00';
}

// Add several opcodes
void addOps(BytecodeFile *bFile, unsigned char *ops, int size)
{
    // check if we need to reallocate and allocate if needed
    if (bFile->programCount + size + 1 >= bFile->programCapacity)
    {
        bFile->programCapacity *= 2;
        bFile->programData = (unsigned char *)realloc(bFile->programData, sizeof(unsigned char) * bFile->programCapacity);
    }

    // copy the opcodes
    for (int i = 0; i < size; i++)
        bFile->programData[bFile->programCount++] = ops[i];

    // add string terminator
    bFile->programData[bFile->programCount] = '\x00';
}

// add an opcode and an int
void addOpAndInt(BytecodeFile *bFile, unsigned char op, int x)
{
    // initialize opcodes
    unsigned char ops[5];

    // get the bytes representing the int
    unsigned char *element = intToBytes(x);

    // copy the ops
    ops[0] = op;
    ops[1] = element[0];
    ops[2] = element[1];
    ops[3] = element[2];
    ops[4] = element[3];

    // add the ops
    addOps(bFile, ops, 5);
}

void addOpAndLongLong(BytecodeFile *bFile, unsigned char op, long long x)
{
    // initialize opcodes
    unsigned char ops[9];

    // get the bytes representing the int
    unsigned char *element = longLongToBytes(x);

    // copy the ops
    ops[0] = op;
    ops[1] = element[0];
    ops[2] = element[1];
    ops[3] = element[2];
    ops[4] = element[3];
    ops[5] = element[4];
    ops[6] = element[5];
    ops[7] = element[6];
    ops[8] = element[7];

    // add the ops
    addOps(bFile, ops, 9);
}