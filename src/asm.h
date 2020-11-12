/**
* @file         asm.h
* @brief        Definitions of methods for assembler
* @author       Dvortsova Varvara BSE182 HSE
* @include      stdio.h, stdlib.h, assert.h, string.h, ctype.h, stdbool.h, "asm_utils.h"
*/
#ifndef CPU_ASSEMBLER_DISASSEMBLER_ASM_H
#define CPU_ASSEMBLER_DISASSEMBLER_ASM_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "asm_utils.h"

/*!< defines type for return value of fwrite*/
typedef unsigned long long checkType;

enum ASM_ERRORS{
    INVALID_OP_ERROR = 49,
    INVALID_REG_ERROR = 228
};

/**
 * Method translates file.txt with mnemonics into binary file with byteCode.
 * @param fileWithMnemonics name of input file
 * @param fileWithByteCode  name of output file
 * @return exit_code
 */
int assembler(char* fileWithMnemonics, char* fileWithByteCode);

/**
 * Method returns opCode by string code of mnemonic.
 * @param code
 * @param len  length of string code
 * @return     opCode
 */
byte getOpCodeWithStringOfCode(const char* code, size_t len);

 /**
  * Method returns next mnemonic of char array.
  * @param MnemonicStart
  * @param mnemonicEnd
  * @param endOfFile    the point to the end of file
  */
void getNextMnemonic(char** MnemonicStart, char**  mnemonicEnd, const char* endOfFile);

/**
 * Method return double.
 * @param mnemonicStart
 * @param number
 * @return if cast is success then true
 */
bool getDoubleNumber(char*  mnemonicStart, double* number);

/**
 * Method returns opCode of register by mnemonics.
 * @param code
 * @param len
 * @return
 */
byte getRegistersByMnemonic(const char* code, size_t len);

/**
 * Method writes value opCode and rgCode to file.
 * @param opCode
 * @param rgCode
 * @param file
 * @return exit_code
 */
int writeToFileTWOValues(byte opCode, byte rgCode, FILE* file);

/**
 * The method goes through the byte array for the first time.
 * Collects data about tags, functions and their addresses.
 * @param mnemonicBegin
 * @param mnemonicEnd
 * @param endOfFile
 * @param tags           vector with elements: (function/tag, address)
 * @param countsOfBytes
 * @return               exit_code
 */
int firstWayWithoutWritingInFile(char** mnemonicBegin, char** mnemonicEnd, char* endOfFile, vector* tags, size_t* countsOfBytes);

/**
 * The method iterates over the array a second time.
 * Writes opCodes and addresses of functions in file.
 * Where function then puts "F" byte and where just tag puts "TAG" byte.
 * @param mnemonicBegin
 * @param mnemonicEnd
 * @param endOfFile
 * @param file
 * @param tags          vector with elements: (function/tag, address)
 * @param countsOfBytes
 * @return              exit_code
 */
int secondWayWithWritingToFile(char** mnemonicBegin, char** mnemonicEnd, char* endOfFile, FILE *file, vector* tags, size_t* countsOfBytes);

#endif //CPU_ASSEMBLER_DISASSEMBLER_ASM_H

