#include "BytecodeFile.h"

BytecodeFile * initBytecodeFile()
{
    BytecodeFile * bFile = (BytecodeFile *)malloc(sizeof(BytecodeFile));

    bFile->capacity = 1024;
    bFile->count = 0;

    bFile->data = (unsigned char *)malloc(sizeof(unsigned char) * bFile->capacity);
}


void addOp(BytecodeFile * bFile, unsigned char op)
{
    if (bFile->count + 2 >= bFile->capacity)
    {
        bFile->capacity *= 2;
        bFile->data = (unsigned char *)realloc(bFile->data, sizeof(unsigned char) * bFile->capacity);
    }

    bFile->data[bFile->count++] = op;
    bFile->data[bFile->count] = '\x00';
}

void addOps(BytecodeFile * bFile, unsigned char * ops, int size)
{
    if (bFile->count + size + 1 >= bFile->capacity)
    {
        bFile->capacity *= 2;
        bFile->data = (unsigned char *)realloc(bFile->data, sizeof(unsigned char) * bFile->capacity);
    }

    for (int i = 0; i < size; i++)
        bFile->data[bFile->count++] = ops[i];

    bFile->data[bFile->count] = '\x00';
}

void addOpAndInt(BytecodeFile * bFile, unsigned char op, int x)
{
    unsigned char ops[5];
    unsigned char * element = intToBytes(x);
    ops[0] = op;
    ops[1] = element[0];
    ops[2] = element[1];
    ops[3] = element[2];
    ops[4] = element[3];

    addOps(bFile, ops, 5);
}

void printAsLong(BytecodeFile * bFile)
{
    int i = 0;
    while (i < bFile->count)
    {
        unsigned char op = bFile->data[i++];
        unsigned char toInt[4];

        switch (op)
        {
            case (ISUB):
                printf("%s\n", LISUB);
                break;
            case (IMUL):
                printf("%s\n", LIMUL);
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
                
                toInt[0] = bFile->data[i++];
                toInt[1] = bFile->data[i++];
                toInt[2] = bFile->data[i++];
                toInt[3] = bFile->data[i++];
                printf("%s %d\n", LICONST, bytesToInt(toInt));
                break;
            case (SCONST):
                break;
            case (FCONST):
                break;
            case (STORE):
                toInt[0] = bFile->data[i++];
                toInt[1] = bFile->data[i++];
                toInt[2] = bFile->data[i++];
                toInt[3] = bFile->data[i++];
                printf("%s %d\n", LSTORE, bytesToInt(toInt));
                break;
            case (LOAD):
                toInt[0] = bFile->data[i++];
                toInt[1] = bFile->data[i++];
                toInt[2] = bFile->data[i++];
                toInt[3] = bFile->data[i++];
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
        }
    }
}