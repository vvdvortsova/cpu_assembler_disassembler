/**
* @file         asm_ram.h
* @brief        Method describes RAM and methods for controller
* @author       Dvortsova Varvara BSE182 HSE
* @include      asm_utils.h
*/
#ifndef CPU_ASSEMBLER_DISASSEMBLER_ASM_RAM_H
#define CPU_ASSEMBLER_DISASSEMBLER_ASM_RAM_H

#include "asm_utils.h"

#define canary 0xdeadbeaf

/*!< Struct for RAM*/
typedef struct RAM {
    long long canaryL;
    double* buffer;/*!< Buffer with values*/
    int capacity;
    long long canaryR;
}RAM;

/**
 * Method initiate ram with appropriate size.
 * @param ram
 * @param sizeOfRAM
 * @return exit code
 */
int initRAM(RAM* ram, int sizeOfRAM);

void destroyRAM(RAM* ram);
double getValueFromRam(RAM* ram, int index);
void writeValueInRamByAddress(RAM* ram, int index, double value);
int verifyRAM(RAM* ram);

#endif //CPU_ASSEMBLER_DISASSEMBLER_ASM_RAM_H
