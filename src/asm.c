#include "asm.h"

byte getOpCodeWithStringOfCode(const char* code, size_t len) {
    assert(code != NULL);
    if (strncmp(code, "push", len) == 0) return PUSH;
    if (strncmp(code, "pop", len) == 0)  return POP;
    if (strncmp(code, "add", len) == 0)  return ADD;
    if (strncmp(code, "sub", len) == 0)  return SUB;
    if (strncmp(code, "mul", len) == 0)  return MUL;
    if (strncmp(code, "div", len) == 0)  return DIV;
    if (strncmp(code, "sqrt", len) == 0) return SQRT;
    if (strncmp(code, "hlt", len) == 0)  return HLT;
    if (strcmp(code, "in") == 0)         return IN;
    if (strcmp(code, "out") == 0)        return OUT;
    return INVALID_OP_ERROR;
}


int writeTokenToFile(char** mnemonicBegin, char** mnemonicEnd, char* endOfFile, FILE *file) {
    size_t lenOfMnemonic = *mnemonicEnd - *mnemonicBegin;
    byte opCode = getOpCodeWithStringOfCode(*mnemonicBegin, lenOfMnemonic);
    if (opCode != INVALID_OP_ERROR) {
        if (opCode == PUSH) {
            //TODO add registers
            getNextMnemonic(mnemonicBegin, mnemonicEnd, endOfFile);
            double number;
            if (getDoubleNumber(*mnemonicBegin, &number)) {
                checkType isCorrectWrite = fwrite(&opCode, sizeof(byte), 1, file);
                assert(isCorrectWrite == 1);
                isCorrectWrite = fwrite(&number, sizeof(number), 1, file);
                assert(isCorrectWrite == 1);
                return EXIT_SUCCESS;
            } else {
                fprintf(stderr, "Something went wrong with push!\n");
                exit(EXIT_FAILURE);
            }
        } else{
            checkType isCorrectWrite = fwrite(&opCode, sizeof(byte), 1, file);
            assert(isCorrectWrite == 1);
            return EXIT_SUCCESS;
        }
    } else{
        fprintf(stderr, "Can't identify the current instruction!\n");
        exit(EXIT_FAILURE);
    }
}

int assembler(char* fileWithMnemonics, char* fileWithByteCode) {
    assert(fileWithByteCode != NULL);
    assert(fileWithMnemonics != NULL);

    int size = 0;
    //get array with disasmCode and args
    char *disasmCode = getBuffer(fileWithMnemonics, &size, "r");
    //open binary file to write opcodes
    FILE *fileByte = fopen(fileWithByteCode, "wb");
    if (fileByte == NULL) {
        fprintf(stderr, "Do not open = %s\n", fileWithByteCode);
        exit(EXIT_FAILURE);
    }

    char* pointToTheEnd = disasmCode + size;
    char* mnemonicBegin = disasmCode;
    char* mnemonicEnd   = disasmCode;

    for (; mnemonicEnd < pointToTheEnd;) {
        while (isspace(*mnemonicEnd) == 0) {
            mnemonicEnd++;
            if (mnemonicEnd >= pointToTheEnd)
                break;
        }
        if (writeTokenToFile(&mnemonicBegin, &mnemonicEnd, pointToTheEnd, fileByte) != 0) {
            fprintf(stderr, "Invalid instruction in assembler function!\n");
            exit(EXIT_FAILURE);
        }
        while (isspace(*mnemonicEnd) != 0)
            mnemonicEnd++;
        mnemonicBegin = mnemonicEnd;
    }

    free(disasmCode);
    fclose(fileByte);
    return EXIT_SUCCESS;
}

void getNextMnemonic(char** MnemonicStart, char** mnemonicEnd, const char* endOfFile) {
    while (isspace(**mnemonicEnd) != 0)
        (*mnemonicEnd)++;

    *MnemonicStart = *mnemonicEnd;
    while (isspace(**mnemonicEnd) == 0) {
        (*mnemonicEnd)++;
        if (*mnemonicEnd >= endOfFile)
            break;
    }
}

bool getDoubleNumber(char* mnemonicStart, double* number) {
    char *endPtr = NULL;
    //cast string to double
    *number = strtod(mnemonicStart, &endPtr);
    if (endPtr == mnemonicStart) {
        fprintf(stderr, "Error when parsing double value\n");
        return false;
    }
    return true;
}

int main(int argc, char** argv) {
    if(argc == 3){
        assembler(argv[1], argv[2]);
        return EXIT_SUCCESS;
    }
    printf("Pls!Check your arguments!\n");
    exit(EXIT_FAILURE);
}

