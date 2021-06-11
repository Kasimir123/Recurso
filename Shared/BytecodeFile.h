#include "../Shared/StdCalls.h"

#define ISUB '\x01'
#define IMUL '\x02'
#define IADD '\x03' 
#define FADD '\x04'
#define FSUB '\x05'
#define ITOF '\x06'
#define CCONST '\x07'
#define ICONST '\x08'
#define SCONST '\x09'
#define FCONST '\x0A'
#define STORE '\x0B'
#define LOAD '\x0C'
#define HALT '\x0D'
#define RET '\x0E'
#define PRINT '\x0F'
#define POP '\x10'

#define LISUB "ISUB"
#define LIMUL "IMUL"
#define LIADD "IADD" 
#define LFADD "FADD"
#define LFSUB "FSUB"
#define LITOF "ITOF"
#define LCCONST "CCONST"
#define LICONST "ICONST"
#define LSCONST "SCONST"
#define LFCONST "FCONST"
#define LSTORE "STORE"
#define LLOAD "LOAD"
#define LHALT "HALT"
#define LRET "RET"
#define LPRINT "PRINT"
#define LPOP "POP"


typedef struct BytecodeFile
{
    int count;
    int capacity;
    unsigned char * data;
} BytecodeFile;

BytecodeFile * initBytecodeFile();
void addOp(BytecodeFile * bFile, unsigned char op);
void addOps(BytecodeFile * bFile, unsigned char * ops, int size);
void addOpAndInt(BytecodeFile * bFile, unsigned char op, int x);
void printAsLong(BytecodeFile * bFile);