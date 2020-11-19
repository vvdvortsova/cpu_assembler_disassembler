/**
* @file         cpu.h
* @brief        Headers for a stack machine
* @author       Dvortsova Varvara BSE182 HSE
* @include      assert.h, stdbool.h, math.h, "stack_lib/all_possible_stack.h", "asm_utils.h"
*/
#ifndef CPU_ASSEMBLER_DISASSEMBLER_CPU_H
#define CPU_ASSEMBLER_DISASSEMBLER_CPU_H

#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include "stack_lib/all_possible_stack.h"
#include "asm_utils.h"
#include "asm_ram.h"

#define EPS 1e-9
typedef double register_type;

typedef enum STATE {
    SIMPLE_STATE, /*!< State when all instructions can execute*/
    CALL_STATE, /*!< State when function executes*/
    FUNC_STATE /*!< State when nothing to execute*/
} state;

typedef struct CPU {
    Stack_double* stack;
    Stack_double* returnStack;
    register_type rax;
    register_type rbx;
    state cpuState;
//    register_type regs[4];//array with registers rax rbx rcx rdx todo
}CPU;


/**
 * The method launches the file code for execution into the stack-machine.
 * @param commandsAndArgs
 * @return the success of operation
 */
int countResult(char* fileName);

/**
 * The method initializes the stack-machine
 * @param cpu
 * @return exit_code
 */
int initCPU(CPU* cpu);

/**
 * The destructor for the stack-machine
 * @param cpu
 * @return exit_code
 */
int destructorCPU(CPU* cpu);

/**
 * The method executes all commands in byteCodes
 * @param byteCodes
 * @param size
 * @param cpu
 * @return exit_code
 */
int processMachine(char* byteCodes, size_t size, CPU* cpu, RAM* ram);
/**
* @brief                 Get double values from input stream.
* @param[in]  message[]  The message for user
* @return     number     double value
*/
double getDoubleFromInput(char message[]);

int binaryOp(Stack_double* stack, byte code);

int conditionOp(Stack_double* stack, byte code);

/**
 * The following definitions are from
 * "The art of computer programming" by Knuth.
 * >=
 * @param a
 * @param b
 * @param epsilon
 * @return
 */
bool approximatelyEqual(double a, double b, double epsilon);
bool essentiallyEqual(double a, double b, double epsilon);
bool definitelyGreaterThan(double a, double b, double epsilon);
bool definitelyLessThan(double a, double b, double epsilon);
bool areEqual(double a, double b, double epsilon);

#endif //CPU_ASSEMBLER_DISASSEMBLER_CPU_H
