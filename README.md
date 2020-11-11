# Stack-Machine

## Description
The first version of machine stack and assembler / disassembler.\
This version of the stack machine is implemented with registers rax/rbx and jmp.\
Update: jmp work!

| Command | Description |
| --- | --- |
| push num| Pushes num to the top of the stack |
| pop | Pops num from the top of the stack |
| add | Pops two values from the stack and counts sum of its |
| sub | Pops two values from the stack and counts -sum of its |
| mul | Pops two values from the stack and counts product of its |
| div | Pops two values from the stack and counts div of its |
| sqrt | Pops value from the top of stack and counts sqrt(value) |
| in | Waits for input value from the terminal|
| out | Inputs value from the top of the stack|
| hlt | Еnds program execution |
| push rax| Pushes num from register rax to the top of the stack |
| pop rax| Pops num from the top of the stack and put it to the register rax|
| jmp tag| Jump to the follow tag|
| call tag| Jump to the follow tag and execute the body of function. Save return address in returnStack.|
| ret| take address from the return stack and jump to this address |
| jxx tag| conditional jump instructions|


Also, there are vector to help to create assembler and disassembler\
in vector.c and vector.h

## Installing
```bash
git clone https://github.com/vvdvortsova/cpu_assembler_diassembler.git
```
## Structure
- Source project 
    - src/
- Test project
    - test/
- Log file for stack
    - stack_logs.txt
## Run

To run stack machine run program with arg: argv[1] = binary file with assembler
```bash
cmake .
make
./stack_machine masm
```
To run assembler run program with args: argv[1] = .txt file with mnemonics argv, [2] = binary file for output with assembler

```bash
cmake .
make
./asm asm.txt masm
```
To run disassembler run program with args: argv[1] = binary file for output with assembler, argv[2] = .txt file with mnemonics

```bash
cmake .
make
./disasm masm disasm.txt
```
##EXAMPLES
Warning: name your must start with "f"\
like: "fswap", "fmove", "frun" and so on


Swap two numbers in stack 
```bash
push 10
push 12
pop rax
pop rbx
jmp f0
push rax
push rbx
out
out
f0:
push rax
push rbx
pop rax
pop rbx
ret
hlt
```

## Documentation
You can watch documentation by opening
```docs/html/index.html ``` in browser.

## OS
 KUbuntu 18.04
