# High Level Language Parser

## Recurso Code Guidelines:

Recurso will not have any loops at all, everything will be functions and everything that can be done recursviely will be done recursively.

### General Code

#### Internal Functions

All subsequent functions will need to be internal functions and must be either declared within main or within another function:

```
functionA ()
{

}
```

```
functionA ()
{
    functionC ()
    {
        functionE ()
        {

        }
    }

    functionD ()
    {

    }

}

functionB ()
{

}
```

Any functions declared inside another function cannot be used by any external functions and functions can only access functions within themselves:

|functionA|functionB|functionC|functionD|functionE|
|-|-|-|-|-|
|functionC| |functionE| | |
|functionD| | |||

In the example above, functionA can call C and D, functionC can call E, but nothing else can be called.

#### IO

Recurso will have in and out functions for interacting with the user:

```
in(var)
```

Where var is the variable you want to read into.

```
out("message")
```

Where message is whatever you want to output.

#### Constants

Recurso will not allow any global variables, as this can be used to get around the pure mathematical functions. We do however allow constants which will be added through a preprocessor. The formatting for this will be similar to C where you define at the start:

```
#define PI 3.14

out(PI);
```

#### Scope

All variables will be scope only within their functions

### Data Types

I want recurso to support all of the normal datatypes that C does, so it supports signed and unsigned, but also that it includes strings.

### Conditionals

Recurso will not have conditionals, rather it will have pattern matching on functions for exiting.

### Functions

Recurso will have absolutely no loops. All loops must be done using recursive functions. Functions will be declared by the following:

```
<return type> FunctionName (<param1 type> param1Name, <param2 type> param2Name)
{

}
```

Alternatively I want to create a function definition with only types needed, this would auto assign names. 

So rather than function(int param1) you can do function(int) and the first param would automatically be i1. 

#### Pattern Matching

Since there are no loops we have to use recursion for everything, cutting out conditions too makes this rather difficult so we will rely on pattern matching. Currently the grammar for this shall be notated as such:

```
Unmatched Function
<return type> FunctionName (<param1 type> param1Name, <param2 type> param2Name)
{

}

Function with one match - returns 0 if param1Name is 1
int FunctionName (int param1Name, <param2 type> param2Name)(1, param2Name; 0)
{

}

Function with multiple matches - returns 0 if param1Name is 1 or returns 2 if param1Name is 1 and param2Name is 4
int FunctionName (int param1Name, int param2Name)(1, param2Name; 0)(1, 4; 2)
{

}

Seperating on multiple lines is also allowed
int FunctionName (int param1Name, int param2Name)
(1, param2Name; 0)
(1, 4; 2)
{

}
```

Possibly make ordering matter, so it matches the first one it sees, for speed!!

## Intermediate Representation

### Tree Text Representation

In order to test we will make that the parser tree can print out its representation, this is done by noting a tree with a as the root and b and c as the children with:

```
  a
 / \     =>    ( a b c )
b   c

  =
 / \     =>    ( = x 2 )   =>  x = 2
x   2


  =
 / \     =>    ( = x ( + 1 2 ) )    =>  x = 1 + 2
x   +
   / \ 
  1   2
```

### Node Types:

#### General Purpose Node

Possibly will need a general purpose node in order to be used as a placeholder, this will then tell us what type of node it is and then a pointer to that node.

#### Program Node

This node will contain a list of other nodes. This will then contain all the logic of the program in the order it was written in.

#### Function Node

The function node will contain the function return type, name, parameters, and patterns. It will also contain a program node that will keep track of all of its functions and code.

Adding a parameter node, this will be a linked list.

#### Expression Node

The expression node will contain the root data, and then two children. These children can either be values, null, or another expression node.

#### Potential Assignment Node