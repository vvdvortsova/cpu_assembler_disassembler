#ifndef CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H
#define CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H


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
#define PUSHR 0b0001111u
#define POPR  0b00100000u



char* getBuffer(char* fName, int* size, char* FLAG);
const char* getStringOfOpCode(byte code);
#endif //CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H
