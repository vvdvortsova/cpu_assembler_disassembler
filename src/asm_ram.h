#ifndef CPU_ASSEMBLER_DISASSEMBLER_ASM_RAM_H
#define CPU_ASSEMBLER_DISASSEMBLER_ASM_RAM_H

#include "vector.h"
#include "asm_utils.h"

#define canary 0xdeadbeaf

typedef struct RAM {
    long long canaryL;
    double * buffer;
    int capacity;
    long long canaryR;
}RAM;

int initRAM(RAM* ram, int sizeOfRAM);
void destroyRAM(RAM* ram);
double getValueFromRam(RAM* ram, int index);
void writeValueInRamByAddress(RAM* ram, int index, double value);
int verifyRAM(RAM* ram);

#endif //CPU_ASSEMBLER_DISASSEMBLER_ASM_RAM_H
