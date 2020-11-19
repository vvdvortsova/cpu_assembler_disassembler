#include "asm_ram.h"

int initRAM(RAM* ram, int sizeOfRAM) {
    ram->canaryL = canary;
    ram->capacity = sizeOfRAM;
    ram->buffer = calloc(sizeOfRAM, sizeof(double));
    if(ram->buffer == NULL) {
        printf("Can't allocate memory for RAM!\n");
        return EXIT_FAILURE;
    }
    ram->canaryR = canary;
    return EXIT_SUCCESS;
}

void destroyRAM(RAM* ram) {
    free(ram->buffer);
}


double getValueFromRam(RAM* ram, int index) {
    if(verifyRAM(ram) == EXIT_FAILURE) {
        printf("RAM was corrupted!\n");
        exit(EXIT_FAILURE);
    }
    if((index > ram->capacity) || (index < 0)) {
        printf("RAM SEGV!\n");// my little segv ^_^
        exit(EXIT_FAILURE);
    }
    double result = ram->buffer[index];
    return result;
}

void writeValueInRamByAddress(RAM* ram, int index, double value) {
    if(verifyRAM(ram) == EXIT_FAILURE) {
        printf("RAM was corrupted!\n");
        exit(EXIT_FAILURE);
    }
    if((index > ram->capacity) || (index < 0)) {
        printf("RAM SEGV!\n");// my little segv ^_^
        exit(EXIT_FAILURE);
    }
    ram->buffer[index] = value;
}

int verifyRAM(RAM* ram) {
    if(ram->canaryL != canary) {
        printf("Left canary was corrupted!\n");
        exit(EXIT_FAILURE);
    } else if (ram->canaryR != canary) {
        printf("Right canary was corrupted!\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}