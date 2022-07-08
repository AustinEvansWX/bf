# Brainfuck Compiler written in C

Implemented Brainfuck according to this [spec](https://github.com/brain-lang/brainfuck/blob/master/brainfuck.md).

## Usage:

```
mkdir build
gcc -o build/bf bf.c
./build/bf fibbonacci.bf
```

## Note:

I have modified the output instruction to be two different instructions instead of just one.

`.` Outputs to `stdout` as an **ASCII character**.
`:` Outputs to `stdout` as a **Decimal**.

## Fibbonacci

```bf
>+
[
[->+>+<<]
>>[-<<+>>]
<<<[->>+<<]>>:
>++++++++++.----------<
]
```
