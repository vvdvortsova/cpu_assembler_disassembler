# Stack-Machine

## Description
The first version of machine stack and assembler / disassembler.\
This version of the stack machine is implemented with registers rax/rbx and jmp, call and conditional jmp.


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
| ret| Take address from the return stack and jump to this address |
| jxx tag| Conditional jump instructions|
| push [addr]| Pushes value from RAM by addr into stack |
| pop [addr]| Pops value from stack into RAM by addr |
| move rax, [addr]| Move value from RAM by addr and  |



Also, there are vector to help to create assembler and disassembler\
in vector.c and vector.h

## Conditional jump
| Command | Condition | 
| --- | --- | 
| je tag| op1 == op2 | 
| jne tag| op1 != op2 | 
| jl tag| op1 < op2 |  
| jle tag| op1 <= op2 |  
| jg tag| op1 > op2 |  
| jge tag| op1 >= op2 |  


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
## EXAMPLES
Warning: name of your function must start with "f"\
like: "fswap", "fmove", "frun" and so on
Warning: name of your tag(метка) must start with "t"\
like: "tswap", "tmove", "trun" and so on

To see more examples search in test\

FACTORIAL(5)
```bash
tmain:
push 5
pop [0]
push 0
pop [1]
push [0]
call fact
pop [1]
push [1]
out
hlt

fact:
pop [2]
push 1
push [2]
je tifElse1
push [2]
push 1
push [2]
sub
call fact
pop [4]
push [4]
mul
pop [5]
push [5]
ret

tifElse1:
push 1
ret

>>>
Result = 120
The program has finished executing in function!
```

CALL TAG\
Swap two numbers in stack 
```bash
push 10
push 12
pop rax
pop rbx
call f0
push rax
push rbx
out
out
hlt

f0:
push rax
push rbx
pop rax
pop rbx
ret
```

JMP TAG\
Infinity loop
```bash
tloop:
push 2
out
jmp tloop
hlt
```
JNE TAG
```bash
push 3
push 1
jne tb
tb:
push 3
out
call fm
push -2
push -3
add
out
hlt

fm:
in
out
ret

>>>
Result = 3
Input value pls: 12
Result = 12
Result = -5
```
POP [addr] and PUSH [addr]\
Write 1,2,3,4 in RAM and read it 
```bash
call f1
push [0]
out
push [1]
out
push [2]
out
push [3]
out
hlt

f1:
push 0
pop [0]
push 1
pop [1]
push 2
pop [2]
push 3
pop [3]
ret

>>>
Result = 0
Result = 1
Result = 2
Result = 3
```

MOV example
```bash
push 5
pop rax
push 10
pop rbx
mov rbx, [0]
mov rax, [1]
push [0]
push [1]
add
out
hlt

>>>
Result = 15
```
Using vector
```bash

struct M{
    char* a;
    double b;
};

int main(void) {
    vector* v = calloc(1, sizeof(vector));
    struct M* a1 = calloc(1, sizeof(struct M));
    struct M* a3 = calloc(1, sizeof(struct M));
    a1->a = "awdwa";
    a1->b = 9;
    char mam[90] = "";
    vectorAdd(v, a1);
    struct M* a2 = (struct M* )vectorGet(v, 0);
    strcpy(mam, a2->a)
    printf("copy a  = %s\n",mam);
    printf("a2->a = %s\n",a2->a);

    free(v);
    free(a3);
    free(a2);
    free(a1);
}
```
## Documentation
You can watch documentation by opening
```docs/html/index.html ``` in browser.

## OS
 KUbuntu 18.04
