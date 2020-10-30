#ifndef CPU_ASSEMBLER_DISASSEMBLER_CPU_H
#define CPU_ASSEMBLER_DISASSEMBLER_CPU_H

#include <math.h>
#include <assert.h>
#include "stack_lib/all_possible_stack.h"
#include "asm_utils.h"

typedef int register_type;

typedef struct CPU {
    Stack_double* stack;
    register_type currentOp;
    register_type rax;// result of program
}CPU;


/**
 * @param commandsAndArgs
 * @return the success of operation
 */
int countResult(char* fileName);
int initCPU(CPU* cpu);
int destructorCPU(CPU* cpu);
int processMachine(char* byteCodes, size_t size, CPU* cpu);

#endif //CPU_ASSEMBLER_DISASSEMBLER_CPU_H
