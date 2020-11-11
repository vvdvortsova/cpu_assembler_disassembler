#ifndef CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H
#define CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


struct tag{
    char* name;
    int position;
};


typedef unsigned char byte;

#define PUSH  0b00000010u
#define POP   0b00000011u
#define ADD   0b00000100u
#define SUB   0b00000101u
#define MUL   0b00000110u
#define DIV   0b00000111u
#define SQRT  0b00001000u
#define HLT   0b00001001u
#define IN    0b00001010u
#define OUT   0b00001011u
#define RAX   0b00001110u
#define RBX   0b00100001u
#define PUSHR 0b0001111u
#define POPR  0b00100000u
#define CALL  0b00100010u
#define RET   0b00100011u
#define F     0b00100100u
#define JMP   0b00100101u
#define JE    0b00100111u
#define JNE   0b00101000u
#define JL    0b00101001u
#define JLE   0b00101010u
#define JG    0b00101011u
#define JGE   0b00101100u



char* getBuffer(char* fName, int* size, char* FLAG);
const char* getStringOfOpCode(byte code);
void printfVector( vector* v);
int findFunctionByAddressInVector(vector* v, int addres, int* index);
#endif //CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H
