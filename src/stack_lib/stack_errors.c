/**
* @file         stack_errors.c
* @author       Dvortsova Varvara BSE182 HSE
*/
#include "stack_errors.h"
const void * ERROR_PTR = (void *)ERROR;

void printErrorType(int errorType, FILE* file){
    switch(errorType){
      case 1:
            fprintf(file, "\terrorType  = STACK_NULL_POINTER\n");
            break;
      case 2:
            fprintf(file, "\terrorType  = STACK_BAD_SIZE\n");
            break;
      case 3:
            fprintf(file, "\terrorType  = STACK_BAD_CAPACITY\n");
            break;
      case 4:
            fprintf(file, "\terrorType  = STACK_NULL_STORAGE\n");
            break;
      case 5:
            fprintf(file, "\terrorType  = STACK_ERRPTR_STORAGE\n");
            break;
      case 6:
            fprintf(file, "\terrorType  = STACK_LEFT_CANARY_SONGS\n");
            break;
      case 7:
            fprintf(file, "\terrorType  = STACK_RIGHT_CANARY_SONGS\n");
            break;
      case 8:
            fprintf(file, "\terrorType  = STACK_ALL_CANARY_SONGS\n");
            break;
      case 9:
            fprintf(file, "\terrorType  = STACK_BUFFER_CANARY_LEFT_SONGS\n");
            break;
      case 10:
            fprintf(file, "\terrorType  = STACK_BUFFER_CANARY_RIGHT_SONGS\n");
            break;
      case 11:
            fprintf(file, "\terrorType  =  STACK_HASH_INCORRECT\n");
            break;
      case 12:
            fprintf(file, "\terrorType  =  STACK_POISON_ERROR\n");
            break;
      case 13:
            fprintf(file, "\terrorType  =  STACK_OVERFLOW\n");
            break;
  }
}


void StackPrint_int(int item, FILE* file){
    fprintf(file, "%d", item);
}

void StackPrint_double(double item, FILE* file){
    fprintf(file, "%f", item);
}

void StackPrint_char(char item, FILE* file){
    fprintf(file, "%c", item);
}

void StackPrint_long(long item, FILE* file){
    fprintf(file, "%ld", item);
}

void StackPrint_float(float item, FILE* file){
    fprintf(file, "%f", item);
}