# Recurso
Recurso Programming Language

Wiki is disabled on private repo so need to use readme for now :/

## High Level Language Parser

This component will read in the high level programming language and fill in an internal data structure that is representative of the program. This datastructure will then be passed to the Bytecode Compiler.

### High Level Language Reader

Reads in the code.

### Intermediate Representation Generation

Generates the data structure.

## Bytecode Compiler

This component will take the internal data structure that we generated and write our own bytecode, this will then either output it as a file or it will send it to the interpreter.

### Bytecode Generator/Translator

Takes the data structure and creates the bytecode.

## Bytecode Interpreter

This component will read in the bytecode and then run it, since this will practically be a virtual machine the bytecode can then be run on any machine we have set up the interpreter for.

### Bytecode Reader

Reads in the bytecode.

### Interpreter (VM Implementation)

Interprets the bytecode, most likely a stack-based bytecode interpreter. will need to decide what to cnvert the bytecode into.
