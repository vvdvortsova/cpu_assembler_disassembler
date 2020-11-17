/**
* @file         vector.c
* @include      "vector.h"
*/
#include "vector.h"

void vectorInit(vector* v) {
    v->capacity = VECTOR_INIT_CAPACITY;
    v->total = 0;
    v->items = malloc(sizeof(void *)* v->capacity);
}

int vectorTotal(vector* v) {
    return v->total;
}

static void vectorResize(vector* v, int capacity) {
#ifdef DEBUG_ON
    printf("vector_resize: %d to %d\n", v->capacity, capacity);
#endif

    void** items = realloc(v->items, sizeof(void*)* capacity);
    if (items) {
        v->items = items;
        v->capacity = capacity;
    }
}

void vectorAdd(vector* v, void* item) {
    if (v->capacity == v->total)
        vectorResize(v, v->capacity * 2);
    v->items[v->total++] = item;
}

void vectorSet(vector* v, int index, void* item) {
    if (index >= 0 && index < v->total)
        v->items[index] = item;
}

void *vectorGet(vector* v, int index) {
    if (index >= 0 && index < v->total)
        return v->items[index];
    return NULL;
}

void vectorDelete(vector* v, int index) {
    if (index < 0 || index >= v->total)
        return;

    v->items[index] = NULL;

    for (int i = index; i < v->total - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->total--;

    if (v->total > 0 && v->total == v->capacity / 4)
        vectorResize(v, v->capacity / 2);
}

void vectorFree(vector* v) {
    free(v->items);
}