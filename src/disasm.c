#include "disasm.h"

char* getStringOfOpCode(byte code) {
    if (code == PUSH) return "push";
    if (code == POP)  return "pop";
    if (code == ADD)  return "add";
    if (code == SUB)  return "sub";
    if (code == MUL)  return "mul";
    if (code == DIV)  return "div";
    if (code == SQRT) return "sqrt";
    if (code == HLT)  return "hlt";
    if (code == IN)   return "in";
    if (code == OUT)  return "out";
    else return NULL;
}

void disassemblerToFile(char* instructions, size_t size, FILE* file) {
    for (size_t i = 0; i < size;) {
        double arg = 0;
        char* code = getStringOfOpCode(instructions[i]);
        if(code == NULL) {
            fprintf(stderr,"Unexpected instruction!\n");
            exit(EXIT_FAILURE);
        }
        if(instructions[i] == PUSH){
            i++;
            fprintf(file,"%s ",code);
            arg = *(double*)(instructions + i);
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
    char* instructions = getBuffer(fileWithByteCode, &size, "rb");
    FILE* fileMnemonics = fopen(fileWithMnemonics, "w");

    if(fileMnemonics == NULL){
        fprintf(stderr,"Do not open = %s\n", fileWithMnemonics);
        exit(EXIT_FAILURE);
    }

    disassemblerToFile(instructions, size, fileMnemonics);

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