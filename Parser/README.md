# High Level Language Parser

## Recurso Code Guidelines:

Recurso will not have any loops at all, everything will be functions and everything that can be done recursviely will be done recursively.

### General Code

#### Required Main Function

Recurso will require all code to be within the main function. This will look like the following:

```
main ()
{

}
```

#### Internal Functions

All subsequent functions will need to be internal functions and must be either declared within main or within another function:

```
main ()
{
    functionA ()
    {

    }
}
```

```
main ()
{
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

main ()
{
    out(PI);
}
```

### Data Types

I want recurso to support all of the normal datatypes that C does, so it supports signed and unsigned, but also that it includes strings.

### Conditionals

Recurso will have If, Felse, and Else.

If is your regular if statement, Felse is else if and must come after if or another felse, and else if your else statement that must come after if or felse. There can be nothing after else.

### Functions

Recurso will have absolutely no loops. All loops must be done using recursive functions. Functions will be declared by the following:

```
<return type> FunctionName (<param1 type> param1Name, <param2 type> param2Name)
{

}
```

Alternatively I want to create a function definition with only types needed, this would auto assign names. 

So rather than function(int param1) you can do function(int) and the first param would automatically be i1. 

## Intermediate Representation