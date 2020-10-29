#ifndef CPU_ASSEMBLER_DISASSEMBLER_CPU_H
#define CPU_ASSEMBLER_DISASSEMBLER_CPU_H

//#include "../includes/stack_lib/all_possible_stack.h"
//#include "asm.vexe.h"

typedef int register_type;

typedef struct CPU {
//    Stack_double stack;
    register_type currentOp;
    register_type rax;// result of program
}CPU;

/**
 * Method takes array with operations and count results
 * using stack and puts it in rax.
 * @param commandsAndArgs
 * @return the success of operation
 */
int countResult(char* fileName);

#endif //CPU_ASSEMBLER_DISASSEMBLER_CPU_H
