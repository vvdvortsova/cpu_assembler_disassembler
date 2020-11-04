#include "disasm.h"

void disassemblerToFile(char* byteCodes, size_t size, FILE* file) {
    for (size_t i = 0; i < size;) {
        double arg = 0;
        const char* code = getStringOfOpCode(byteCodes[i]);
        if(code == NULL) {
            fprintf(stderr,"Unexpected instruction!\n");
            exit(EXIT_FAILURE);
        }
        switch(byteCodes[i]) {
            case PUSH:
                i++;
                fprintf(file,"%s ",code);
                arg = *(double*)(byteCodes + i);
                i += sizeof(arg);
                fprintf(file, "%g\n", arg);
                break;
            case POPR:
            case PUSHR:
                if(writeMnemonicsToFile(code, byteCodes[i + 1], file) != EXIT_FAILURE) {
                    i += 2;
                    break;
                }
                fprintf(stderr,"Unexpected register or something wrong with file!\n");
                exit(EXIT_FAILURE);
            default:
                ++i;
                fprintf(file,"%s\n",code);
                break;
        }
    }
}

int writeMnemonicsToFile(const char* instruction, byte reg, FILE* file){
    const char* code = NULL;
    fprintf(file,"%s ", instruction);
    code = getStringOfOpCode(reg);
    if(code == NULL){
        fprintf(stderr,"Unexpected register!\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", code);
    return EXIT_SUCCESS;
}





int disAssembler(const char* fileWithByteCode, const char* fileWithMnemonics){
    assert(fileWithByteCode != NULL);
    assert(fileWithMnemonics != NULL);

    int size = 0;
    char* byteCodes = getBuffer(fileWithByteCode, &size, "rb");
    FILE* fileMnemonics = fopen(fileWithMnemonics, "w");

    if(fileMnemonics == NULL){
        fprintf(stderr,"Do not open = %s\n", fileWithMnemonics);
        exit(EXIT_FAILURE);
    }

    disassemblerToFile(byteCodes, size, fileMnemonics);

    fclose(fileMnemonics);
}

int main(int argc, char **argv) {
    if(argc == 3){
        disAssembler(argv[1], argv[2]);
        return 0;
    }
    printf("Pls!Check your arguments!\n");
    exit(EXIT_FAILURE);
}
