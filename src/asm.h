#ifndef CPU_ASSEMBLER_DISASSEMBLER_ASM_H
#define CPU_ASSEMBLER_DISASSEMBLER_ASM_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "asm_utils.h"

typedef unsigned long long checkType;
enum ASM_ERRORS{
    INVALID_OP_ERROR = 49,
    INVALID_REG_ERROR = 228
};



/**
 * Method translates file.vara with mnemonics into file.vexe with byteCode
 * @param fileWithMnemonics
 * @param fileWithByteCode
 * @return
 */
int assembler(char* fileWithMnemonics, char* fileWithByteCode);
byte getOpCodeWithStringOfCode(const char* code, size_t len);
void getNextMnemonic(char** MnemonicStart, char**  mnemonicEnd, const char* endOfFile);
bool getDoubleNumber(char*  mnemonicStart, double* number);
byte getRegistersByMnemonic(const char* code, size_t len);
int writeToFileTWOValues(byte opCode, byte rgCode, FILE* file);
int firstWayWithoutWritingInFile(char** mnemonicBegin, char** mnemonicEnd, char* endOfFile, vector* tags, size_t* countsOfBytes);
int secondWayWithWritingToFile(char** mnemonicBegin, char** mnemonicEnd, char* endOfFile, FILE *file, vector* tags, size_t* countsOfBytes);

#endif //CPU_ASSEMBLER_DISASSEMBLER_ASM_H

