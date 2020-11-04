#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "asm_utils.h"



const char* getStringOfOpCode(byte code) {
    switch (code){
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
        default:   return NULL;
    }
}

char* getBuffer(char* fName, int* size, char* FLAG){
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