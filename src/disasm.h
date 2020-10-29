#ifndef CPU_ASSEMBLER_DISASSEMBLER_DISASM_H
#define CPU_ASSEMBLER_DISASSEMBLER_DISASM_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "asm_utils.h"

/**
 * Methods translates file.vexe with byteCode into file.vara with mnemonics
 * @param fileWithByteCode
 * @param fileWithMnemonics
 * @return
 */
int disAssembler(const char* fileWithByteCode, const char* fileWithMnemonics);

#endif //CPU_ASSEMBLER_DISASSEMBLER_DISASM_H
