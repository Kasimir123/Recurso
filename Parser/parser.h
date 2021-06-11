#include "../Compiler/compiler.h"
#include "../Shared/StdCalls.h"
#include <string.h>

// Constants struct
typedef struct Constants 
{
    // List of int variables
    List * ints;
} Constants;

Constants * constants;