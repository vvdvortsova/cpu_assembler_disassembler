#ifndef CPU_ASSEMBLER_DISASSEMBLER_VECTOR_H
#define CPU_ASSEMBLER_DISASSEMBLER_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#define VECTOR_INIT_CAPACITY 4

#define VECTOR_INIT(vec) vector vec; vector_init(&vec)
#define VECTOR_ADD(vec, item) vector_add(&vec, (void *) item)
#define VECTOR_SET(vec, id, item) vector_set(&vec, id, (void *) item)
#define VECTOR_GET(vec, type, id) (type) vector_get(&vec, id)
#define VECTOR_DELETE(vec, id) vector_delete(&vec, id)
#define VECTOR_TOTAL(vec) vector_total(&vec)
#define VECTOR_FREE(vec) vector_free(&vec)

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
void *vectorGet(vector* v, int index);
void vectorDelete(vector* v, int index);
void vectorFree(vector* v);

#endif //CPU_ASSEMBLER_DISASSEMBLER_VECTOR_H
