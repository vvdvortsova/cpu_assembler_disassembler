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
        case CALL:  return "call";
        case RET:  return "ret";
        case F:    return "f";
        case JMP:    return "jmp";
        default:   return NULL;
    }
}

void printfVector( vector* v){
    printf("your vector %p\n",(void*)v);
    struct tag* a2 = calloc(1, sizeof(struct tag));
    for (int i = 0; i < v->total; ++i) {
        a2 = (struct tag*)vectorGet(v, i);
        printf("pos = %d fname = %s\n", a2->position, a2->name);
    }
}
int findFunctionByAddressInVector(vector* v, int addres, int* index){
    printf("your vector %p\n",(void*)v);
    struct tag* a2 = calloc(1, sizeof(struct tag));
    for (int i = 0; i < v->total; ++i) {
        a2 = (struct tag*)vectorGet(v, i);
        printf("pos = %d adr = %d\n",a2->position,addres);
        if(a2->position == addres){
            *index = i;
            printf("true! index = %d\n",*index);
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
    if(!file){
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
        if(res != *size){
            fprintf(stderr,"Do not read file to buffer = %s\n", fName);
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);
    return arr;
}