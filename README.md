# Recurso
Recurso Programming Language

Recurso is a stack based interpreted functional programming language I created for K3RN3LCTF. 

## Interpreter

## High level opcodes

These are the original opcodes in the Recurso programming language

#### ISUB

Pops the stack twice, subtracts 2nd item on stack from the 1st item on the stack, then pushes them back onto the stack.

#### IMUL

Pops the stack twice, multiplies the two values and pushes them onto the stack.

#### IDIV 

Pops the stack twice, divides 2nd item on stack from the 1st item on the stack, then pushes them back onto the stack.

#### IADD

Pops the stack twice, adds the two values and pushes them onto the stack.

#### OR

Pops the stack twice, ors the two values and pushes them onto the stack.

#### AND

Pops the stack twice, ands the two values and pushes them onto the stack.

#### XOR

Pops the stack twice, xors the two values and pushes them onto the stack.

#### ICONST

Reads the next 8 bytes, converts them to long long, and pushes them onto the stack.

#### STORE

Reads the next 4 bytes, converts them to an int, then pops the stack and stores the value from the stack into the corresponding local variable.

#### LOAD

Reads the next 4 bytes, converts them to an int, then uses that int to get the local variable and pushes to the stack.

#### RET

Calls decrement function to get the last function on the call stack, sets ip to the address and current function to the function.

#### PRINT

Pops the stack and prints out the number.

#### POP

Pops a value from the stack and discards it.

#### CALL

Reads the next 4 bytes, converts to an int, and uses that to call the selected function. Sets the address of the return stack to the current ip.

#### INPUT

Reads in a long long and pushes to the stack.

#### CMP

Pops 2 values off the stack, and checks if they are equal to each other, if they are not equal then continue till we find a return.

#### NCMP

Pops 2 values off the stack, and checks if they are equal to each other, if they are equal then continue till we find a return.

#### LTCMP

Pops 2 values off the stack, and compares them to each other, if the 1st value is less than the 2nd value then continue till we find a return.

#### GTCMP

Pops 2 values off the stack, and compares them to each other, if the 1st value is greater than the 2nd value then continue till we find a return.


## Assembly opcodes

These opcodes were added so that I could do custom assembly with a bit more power

#### JMP

Reads next 4 bytes, converts to int, and sets ip to that value.

#### IJMP

Pops stack and sets ip to that value.

#### INC

Reads next 4 bytes, converts to int, and increases the value of the opcode at that location.

#### DEC

Reads next 4 bytes, converts to int, and decreases the value of the opcode at that location.

#### MOV

Pops 2 values from the stack and sets the opcode at the 2nd location with the one from the 1st location.

#### MEMP

Reads next 4 bytes, then reads the opcode at that location and the next opcode, converts them to an integer, and pushes to the stack.

#### CMPJMP

Reads next 4 bytes, pops 2 values from the stack, if they are equal then set ip to the value of the number we read.