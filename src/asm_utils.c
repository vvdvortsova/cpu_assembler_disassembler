#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "asm_utils.h"


byte PUSH = 0b00000010;
byte POP = 0b00000011;
byte ADD = 0b00000100;
byte SUB = 0b00000101;
byte MUL = 0b00000110;
byte DIV = 0b00000111;
byte SQRT = 0b00001000;
byte HLT = 0b00001001;
byte IN = 0b00001010;
byte OUT = 0b00001011;

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