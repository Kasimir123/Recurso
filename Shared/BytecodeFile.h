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
#define JMP '\x1E'
#define IJMP '\x1F'
#define INC '\x20'
#define DEC '\x21'
#define MOV '\x22'
#define MEMP '\x23'
#define CMPJMP '\x24'



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