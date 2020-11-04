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
    if (strncmp(code, "in",len) == 0)    return IN;
    if (strncmp(code, "out",len) == 0)   return OUT;
    return INVALID_OP_ERROR;
}

byte getRegistersByMnemonic(const char* code, size_t len){
    assert(code != NULL);
    if (strncmp(code, "rax", len) == 0) return RAX;
    return INVALID_REG_ERROR;
}

int writeTokenToFile(char** mnemonicBegin, char** mnemonicEnd, char* endOfFile, FILE *file) {
    size_t lenOfMnemonic = *mnemonicEnd - *mnemonicBegin;
    byte opCode = getOpCodeWithStringOfCode(*mnemonicBegin, lenOfMnemonic);
    byte rgCode;
    if (opCode != INVALID_OP_ERROR) {
        checkType isCorrectWrite;
        switch (opCode) {
            case PUSH:
                getNextMnemonic(mnemonicBegin, mnemonicEnd, endOfFile);
                double number;
                if (getDoubleNumber(*mnemonicBegin, &number)) {
                    checkType isCorrectWrite = fwrite(&opCode, sizeof(byte), 1, file);
                    assert(isCorrectWrite == 1);
                    isCorrectWrite = fwrite(&number, sizeof(number), 1, file);
                    assert(isCorrectWrite == 1);
                    return EXIT_SUCCESS;
                } else {
                    lenOfMnemonic = *mnemonicEnd - *mnemonicBegin;
                    rgCode = getRegistersByMnemonic(*mnemonicBegin, lenOfMnemonic);
                    if (rgCode != INVALID_REG_ERROR) {
                        if (writeToFileTWOValues(PUSHR, rgCode, file) != EXIT_SUCCESS) {
                            fprintf(stderr, "Something went wrong with writing pop!\n");
                            exit(EXIT_FAILURE);
                        }
                        return EXIT_SUCCESS;
                    }
                    fprintf(stderr, "Something went wrong with push!\n");
                    fprintf(stderr, "or error when parsing double value!\n");
                    exit(EXIT_FAILURE);
                    case POP:
                        if (strncmp((const char *) mnemonicEnd, "\n", 1) != 0) {//means that is register
                            getNextMnemonic(mnemonicBegin, mnemonicEnd, endOfFile);
                            lenOfMnemonic = *mnemonicEnd - *mnemonicBegin;
                            rgCode = getRegistersByMnemonic(*mnemonicBegin, lenOfMnemonic);
                            if (rgCode != INVALID_REG_ERROR) {
                                if (writeToFileTWOValues(POPR, rgCode, file) != EXIT_SUCCESS) {
                                    fprintf(stderr, "Something went wrong with writing pop!\n");
                                    exit(EXIT_FAILURE);
                                }
                                return EXIT_SUCCESS;
                            }
                            fprintf(stderr, "Something went wrong with pop!\n");
                            exit(EXIT_FAILURE);
                        }//if just pop
                    default:
                        isCorrectWrite = fwrite(&opCode, sizeof(byte), 1, file);
                        assert(isCorrectWrite == 1);
                        return EXIT_SUCCESS;
                }
        }
    }else{
        fprintf(stderr, "Can't identify the current instruction! mnemonic = %s\n", *mnemonicBegin);
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
        return false;
    }
    return true;
}
int writeToFileTWOValues(byte opCode, byte rgCode, FILE* file){
    checkType isCorrectWrite = fwrite(&opCode, sizeof(byte), 1, file);
    if(isCorrectWrite != 1){
        fprintf(stderr, "Can't write opCode to file!\n");
        return EXIT_FAILURE;
    }
    isCorrectWrite = fwrite(&rgCode, sizeof(byte), 1, file);
    if(isCorrectWrite != 1){
        fprintf(stderr, "Can't write rgCode to file!\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    if(argc == 3){
        assembler(argv[1], argv[2]);
        return EXIT_SUCCESS;
    }
    printf("Pls!Check your arguments!\n");
    exit(EXIT_FAILURE);
}

