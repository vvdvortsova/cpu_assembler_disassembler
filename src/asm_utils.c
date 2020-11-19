/**
* @file         asm_utils.c
* @brief        Helper methods for asm, disasm, cpu
* @author       Dvortsova Varvara BSE182 HSE
* @include      "asm_utils.h"
*/
#include "asm_utils.h"

const char* getStringOfOpCode(byte code) {
    switch (code) {
        case PUSH: return "push";
        case POP:  return "pop";
        case ADD:  return "add";
        case SUB:  return "sub";
        case MUL:  return "mul";
        case DIV:  return "div";
        case SQRT: return "sqrt";
        case HLT:  return "hlt";
        case IN:   return "in";
        case OUT:  return "out";
        case RAX:  return "rax";
        case RBX:  return "rbx";
        case PUSHR:return "push";
        case POPR: return "pop";
        case CALL: return "call";
        case RET:  return "ret";
        case F:    return "f";
        case JMP:  return "jmp";
        case JE:   return "je";
        case JNE:  return "jne";
        case JL:   return "jl";
        case JLE:  return "jle";
        case JG:   return "jg";
        case JGE:  return "jge";
        case TAG:  return "t";
        case PUSH_RAM: return "push";
        case POP_RAM:  return "pop";
        case MOV:      return "mov";
        default:       return NULL;
    }
}

void printfVectorWithTags(vector* v) {
    printf("your vector %p\n",(void*)v);
    struct tag* a2 = NULL;
    for (int i = 0; i < v->total; ++i) {
        a2 = (struct tag*)vectorGet(v, i);
        printf("pos = %d fname = %s\n", a2->position, a2->name);
    }
}

int findFunctionByAddressInVector(vector* v, int addres, int* index) {
    struct tag* a2 = NULL;
    for (int i = 0; i < v->total; ++i) {
        a2 = (struct tag*)vectorGet(v, i);
        if(a2->position == addres){
            *index = i;
            return EXIT_SUCCESS;
        }
    }
    *index = -1;
    return EXIT_FAILURE;
}

char* getBuffer(char* fName, int* size, char* FLAG) {
    assert(fName != NULL);
    assert(size != NULL);
    assert(FLAG != NULL);

    FILE* file = NULL;
    file = fopen(fName, FLAG);
    if(!file) {
        fprintf(stderr,"Do not open = %s\n", fName);
        exit(EXIT_FAILURE);
    }

    // define size of file
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* arr = calloc(*size, *size * sizeof(char));
    if (arr) {
        //read all file in bufferOrigin
        int res = fread(arr, 1, *size, file);
        if(res != *size) {
            fprintf(stderr,"Do not read file to buffer = %s\n", fName);
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);
    return arr;
}