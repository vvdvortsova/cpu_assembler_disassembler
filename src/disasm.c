#include "disasm.h"

void disassemblerToFile(char* byteCodes, size_t size, FILE* file) {
    for (size_t i = 0; i < size;) {
        double arg = 0;
        char* code = getStringOfOpCode(byteCodes[i]);
        if(code == NULL) {
            fprintf(stderr,"Unexpected instruction!\n");
            exit(EXIT_FAILURE);
        }
        if(byteCodes[i] == PUSH){
            i++;
            fprintf(file,"%s ",code);
            arg = *(double*)(byteCodes + i);
            i += sizeof(arg);
            fprintf(file, "%g\n", arg);
        } else{
            ++i;
            fprintf(file,"%s\n",code);
        }
    }

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
