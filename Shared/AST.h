
// Program Node Struct
typedef struct {

    // type of node this is
    char nodeType;

    // all of the nodes in the program
    void * * nodes;

} ProgramNode;

// Function Node Struct
typedef struct {

    // type of node this is
    char nodeType;

    // Use a char for typing to keep memory usage small
    char returnType;

    // Name of the function
    char * name;

    // Length of the function - 
    // may be able to get rid of this once we do more analysis on
    // memory usage vs runtime speeds
    int nameLen;

    // Start of linked list for parameters
    ParameterNode * firstParam;

    // ****************
    // Pattern Node may be Parameter Node in which case we will need to 
    // add another variable, will need to see as we build program
    // ****************

    // All inner program information
    ProgramNode * inner;

} FunctionNode;

// Parameter Node Struct
typedef struct {

    // type of node this is
    char nodeType;

    // parameter type
    char type;

    // parameter name
    char * name;

    // length of name
    int nameLen;

    // next parameter
    ParameterNode * next;

} ParameterNode;

// Expression Node Struct
typedef struct {

    // type of node this is
    char nodeType;

    // root data
    char * root;

    // root data length
    int rootLen;

    // left node
    ExpressionNode left;

    // right node
    ExpressionNode right;

} ExpressionNode;