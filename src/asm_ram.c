#include "asm_ram.h"

int initRAM(RAM* ram, int sizeOfRAM) {
    ram->canaryL = canary;
    ram->canaryR = canary;
    ram->buffer = calloc(1, sizeof(vector));
    vectorInit(ram->buffer);
    if(ram->buffer == NULL) {
        printf("Can't allocate memory for RAM!\n");
        return EXIT_FAILURE;
    }
    vectorResize(ram->buffer, sizeOfRAM);
    return EXIT_SUCCESS;
}

void destroyRAM(RAM* ram) {
    vectorFree(ram->buffer);
}

double getValueFromRam(RAM* ram, int index) {
    if(verifyRAM(ram) == EXIT_FAILURE) {
        printf("RAM was corrupted!\n");
        exit(EXIT_FAILURE);
    }
    if((index >= vectorTotal(ram->buffer)) || (index < 0)) {
        printf("RAM SEGV!\n");// my little segv ^_^
        exit(EXIT_FAILURE);
    }
    double result = *(double*)vectorGet(ram->buffer, index);
    return result;
}

int writeValueInRamByAddress(RAM* ram, int index, double value) {
    if(verifyRAM(ram) == EXIT_FAILURE) {
        printf("RAM was corrupted!\n");
        exit(EXIT_FAILURE);
    }
    if((index >= vectorTotal(ram->buffer)) || (index < 0)) {
        printf("RAM SEGV!\n");// my little segv ^_^
        exit(EXIT_FAILURE);
    }

    vectorSet(ram->buffer, index, &value);

    if(verifyRAM(ram) == EXIT_FAILURE) {
        printf("RAM was corrupted!\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
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