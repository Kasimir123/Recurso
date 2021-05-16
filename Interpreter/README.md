# Bytecode Interpreter

## Interpreter Machine Architecture

Since we will be simulating a computer, the interpreter will require the following:

### CPU

- Simulated CPU
- Instruction "Dispatcher", basically a while loop with a big switch statement on the bytecodes

```c
short bytecode = bytecodes[ip];
while (bytecode != <stop code> && ip < bytecodesLength)
{
    ip++;
    switch (bytecode) {
        case <some code>: <do something>;
    }
    bytecode = bytecodes[ip];
}
```

### Code Memory

- Holds the instructions and operands
- Most likely a byte array
- All addresses will be integers

### Constant Pool

- Anything that cannot be stored as a 4 byte operand goes here
- Strings, Floating-Point numbers, function symbols..

### Instruction Pointer Register 

- Special-Purpose Register that points at the next instruction to execute

### Frame Pointer Register

- Special-Purpose Register that points to the top of the function call stack

### Stack Pointer Register

- Special-Purpose Register that points to the top of the operand stack

### Function Call Stack

- Stack that holds function call return addresses, parameters, and local variables

### Operand Stack

- temporary values get pushed here

## Bytecode Assembler

- Need to figure out how we want to convert the bytecode assembly the compiler makes into opcodes that fit into 4 bytes each.

## Stack Based Bytecode Interpreter Pattern

The design pattern our interpreter will use

## Optimizing Interpreter Speed

As we develop we will probably need to write some assembly code and fine tune it to improve speed, writing the interpreter in c so hopefully it won't slow down too much.

