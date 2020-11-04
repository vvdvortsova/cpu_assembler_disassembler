#ifndef CPU_ASSEMBLER_DISASSEMBLER_CPU_H
#define CPU_ASSEMBLER_DISASSEMBLER_CPU_H

#include <math.h>
#include <assert.h>
#include "stack_lib/all_possible_stack.h"
#include "asm_utils.h"

typedef double register_type;

typedef struct CPU {
    Stack_double* stack;
    register_type currentOp;
    register_type rax;
//    register_type regs[4];//array with registers rax rbx rcx rdx
}CPU;


/**
 * @param commandsAndArgs
 * @return the success of operation
 */
int countResult(char* fileName);
int initCPU(CPU* cpu);
int destructorCPU(CPU* cpu);
int processMachine(char* byteCodes, size_t size, CPU* cpu);
/**
* @brief                 Get double values from input stream for quadratic equation
* @param[in]  message[]  The message for user
* @return     number     double value
*/
double getDoubleFromInput(char message[]);

#endif //CPU_ASSEMBLER_DISASSEMBLER_CPU_H
