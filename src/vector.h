/**
* @file         vector.h
* @include      stdio.h, stdlib.h
*/
#ifndef CPU_ASSEMBLER_DISASSEMBLER_VECTOR_H
#define CPU_ASSEMBLER_DISASSEMBLER_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#define VECTOR_INIT_CAPACITY 4


typedef struct vector {
    void** items;
    int capacity;
    int total;
} vector;

void vectorInit(vector* v);
int vectorTotal(vector* v);
static void vectorResize(vector* v, int cap);
void vectorAdd(vector* v, void* item);
void vectorSet(vector* v, int index, void* item);
void* vectorGet(vector* v, int index);
void vectorDelete(vector* v, int index);
void vectorFree(vector* v);

#endif //CPU_ASSEMBLER_DISASSEMBLER_VECTOR_H
