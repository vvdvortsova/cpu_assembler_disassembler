/**
* @file         stack_errors.h
* @brief        Definitions of any types of errors in stack
* @author       Dvortsova Varvara BSE182 HSE
* @include      stdio.h
*/
#ifndef IMMORTAL_STACK_STACK_ERRORS_H
#define IMMORTAL_STACK_STACK_ERRORS_H

#include <stdio.h>
#define ERROR 228
const void * ERROR_PTR;
#define GET_TYPE(X) #X

/*! This is an enum for defining the type of errors of stack  */
enum STACK_ERRORS{
    STACK_OK,
    STACK_NULL_POINTER,
    STACK_BAD_SIZE,
    STACK_BAD_CAPACITY,
    STACK_NULL_STORAGE,
    STACK_ERRPTR_STORAGE,
    STACK_LEFT_CANARY_SONGS,
    STACK_RIGHT_CANARY_SONGS,
    STACK_ALL_CANARY_SONGS,
    STACK_BUFFER_CANARY_LEFT_SONGS,
    STACK_BUFFER_CANARY_RIGHT_SONGS,
    STACK_HASH_INCORRECT,
    STACK_POISON_ERROR,
    STACK_OVERFLOW
};

void printErrorType(int errorType, FILE* file);

void StackPrint_int(int item, FILE* file);
void StackPrint_double(double item, FILE* file);
void StackPrint_char(char item, FILE* file);
void StackPrint_long(long item, FILE* file);
void StackPrint_float(float item, FILE* file);

#endif //IMMORTAL_STACK_STACK_ERRORS_H
