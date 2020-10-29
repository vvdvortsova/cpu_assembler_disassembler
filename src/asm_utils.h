#ifndef CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H
#define CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H

typedef unsigned char byte;

//opcodes
byte PUSH;
byte POP;
byte ADD;
byte SUB;
byte MUL;
byte DIV;
byte SQRT;
byte HLT;
byte OUT;
byte IN;
char* getBuffer(char* fName, int* size, char* FLAG);

#endif //CPU_ASSEMBLER_DISASSEMBLER_ASM_UTILS_H
