#include "BytecodeFile.h"

// initializes the bytecode file
BytecodeFile *initBytecodeFile()
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
}

// turns a function node into bytes
unsigned char *functionNodeToChars(FunctionNode *function)
{
    // malloc space for the bytes, gets size from: .name.44
    unsigned char *functionBytes = (char *)malloc(sizeof(unsigned char) * (function->nameLen + 10));

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

// prints the function data
void printfunctionData(BytecodeFile *bFile)
{
    int i = 0;
    unsigned char op = bFile->functionData[i++];

    // loop through all the files
    while (op == FUNC)
    {
        // declare and intialize values

        unsigned char params[4];
        unsigned char locals[4];
        unsigned char address[4];
        // print .
        printf(".");

        // get next opcode
        op = bFile->functionData[i++];

        // while not func info
        while (op != FUNCINFO)
        {
            // print out function name
            printf("%c", op);
            op = bFile->functionData[i++];
        }

        // get local count
        locals[0] = bFile->functionData[i++];
        locals[1] = bFile->functionData[i++];
        locals[2] = bFile->functionData[i++];
        locals[3] = bFile->functionData[i++];

        // get address
        address[0] = bFile->functionData[i++];
        address[1] = bFile->functionData[i++];
        address[2] = bFile->functionData[i++];
        address[3] = bFile->functionData[i++];

        // print the rest of the information
        printf(" locals=%d address=0x%04x\n", bytesToInt(locals), bytesToInt(address));

        // get the next opcode
        op = bFile->functionData[i++];
    }
}

// print out the program data
void printProgramData(BytecodeFile *bFile)
{
    int i = 0;

    // while there are still opcodes
    while (i < bFile->programCount)
    {
        // get next opcode
        unsigned char op = bFile->programData[i++];

        // declare to int structure
        unsigned char toInt[4];

        // prints out the instruction address
        printf("0x%04x ", i - 1);

        // switch and do different things based on opcode
        switch (op)
        {
        case (ISUB):
            printf("%s\n", LISUB);
            break;
        case (IMUL):
            printf("%s\n", LIMUL);
            break;
        case (IDIV):
            printf("%s\n", LIDIV);
            break;
        case (IADD):
            printf("%s\n", LIADD);
            break;
        case (FADD):
            printf("%s\n", LFADD);
            break;
        case (ITOF):
            break;
        case (CCONST):
            break;
        case (ICONST):

            toInt[0] = bFile->programData[i++];
            toInt[1] = bFile->programData[i++];
            toInt[2] = bFile->programData[i++];
            toInt[3] = bFile->programData[i++];
            printf("%s %d\n", LICONST, bytesToInt(toInt));
            break;
        case (SCONST):
            break;
        case (FCONST):
            break;
        case (STORE):
            toInt[0] = bFile->programData[i++];
            toInt[1] = bFile->programData[i++];
            toInt[2] = bFile->programData[i++];
            toInt[3] = bFile->programData[i++];
            printf("%s %d\n", LSTORE, bytesToInt(toInt));
            break;
        case (LOAD):
            toInt[0] = bFile->programData[i++];
            toInt[1] = bFile->programData[i++];
            toInt[2] = bFile->programData[i++];
            toInt[3] = bFile->programData[i++];
            printf("%s %d\n", LLOAD, bytesToInt(toInt));
            break;
        case (HALT):
            printf("%s\n", LHALT);
            break;
        case (RET):
            printf("%s\n", LRET);
            break;
        case (PRINT):
            printf("%s\n", LPRINT);
            break;
        case (POP):
            printf("%s\n", LPOP);
            break;
        case (CALL):
            toInt[0] = bFile->programData[i++];
            toInt[1] = bFile->programData[i++];
            toInt[2] = bFile->programData[i++];
            toInt[3] = bFile->programData[i++];
            printf("%s %d\n", LCALL, bytesToInt(toInt));
            break;
        case (INPUT):
            printf("%s\n", LINPUT);
            break;
        }
    }
}

// prints the bytecode in pretty form
void printAsLong(BytecodeFile *bFile)
{
    // prints the function data
    printfunctionData(bFile);

    // prints the program data
    printProgramData(bFile);
}