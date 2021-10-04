#include "../Shared/StdCalls.h"
#include "../Shared/AST.h"

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
#define FUNC '\x11'
#define FUNCINFO '\x12'
#define IDIV '\x13'
#define FDIV '\x14'
#define CALL '\x15'
#define INPUT '\x16'
#define CMP '\x17'
#define OR '\x18'
#define AND '\x19'
#define XOR '\x1A'
#define NCMP '\x1B'
#define LTCMP '\x1C'
#define GTCMP '\x1D'

#define LISUB "ISUB"
#define LIMUL "IMUL"
#define LIADD "IADD" 
#define LFADD "FADD"
#define LFSUB "FSUB"
#define LITOF "ITOF"
#define LIDIV "LDIV"
#define LFDIV "LFDIV"
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
#define LFUNC "."
#define LPARAMS "Params="
#define LLOCALS "Locals="
#define LCALL "CALL"
#define LINPUT "INPUT"
#define LCMP "CMP"
#define LOR "OR"
#define LAND "AND"
#define LXOR "XOR"
#define LNCMP "NCMP"
#define LLTCMP "LTCMP"
#define LGTCMP "GTCMP"



typedef struct BytecodeFile
{
    int programCount;
    int programCapacity;
    int functionCount;
    int functionCapacity;
    unsigned char * functionData;
    unsigned char * programData;
} BytecodeFile;

BytecodeFile * initBytecodeFile();
BytecodeFile * initBytecodeFileWithFile(char * filename);
void saveBytecode(BytecodeFile * bFile, char * filename);
void addFunction(BytecodeFile * bFile, FunctionNode * function);
void addOp(BytecodeFile * bFile, unsigned char op);
void addOps(BytecodeFile * bFile, unsigned char * ops, int size);
void addOpAndInt(BytecodeFile * bFile, unsigned char op, int x);
void addOpAndLongLong(BytecodeFile *bFile, unsigned char op, long long x);
void printAsLong(BytecodeFile * bFile);