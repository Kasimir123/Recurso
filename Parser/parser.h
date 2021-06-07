#include "../Shared/StdCalls.h"
#include "../Shared/AST.h"
#include "list.h"

// Constants struct
typedef struct Constants 
{
    // List of int variables
    List * ints;
} Constants;

Constants * constants;