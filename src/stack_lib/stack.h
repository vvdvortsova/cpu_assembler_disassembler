/**
* @file         stack.h
* @brief        Definitions of methods for stack
* @author       Dvortsova Varvara BSE182 HSE
* @include      stdio.h, stdlib.h, assert.h, string.h, templates.h, stack_errors.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "templates.h"
#include "stack_errors.h"

#define CANARY_CHECK/*!< defines canary defence*/
#define HASH_CHECK/*!< defines hash defence*/

#define FILE_DUMP "stack_logs.txt"/*!< defines name of file to log dumps*/
#define MAX_SIZE_OF_FILE 20000//20kb /*!< defines max size of file to log dumps*/
#define CANARY_VALUE 0xDADBE
#define CANARY_BUFFER_VALUE 0x141E
#define POISON 0xD
#define HASH_CONST 228
#ifdef  T


/**
 * Macros define custom STACK_DUMP function for getting info in stderr or file stack_lib_errors.txt
 * @param[in] stack typedef struct STACK(Stack,T)
 * @param[in] T             the type
 * @param[in] errorType     the type of Error
**/
#define STACK_DUMP(stack, T, errorType)\
  FILE* file = NULL;\
  file = fopen(FILE_DUMP, "a");\
  if (!file){\
    printf("failed to open file %s",FILE_DUMP);\
    exit(EXIT_FAILURE);\
  }\
  fseek(file, 0, SEEK_END);\
  int size = ftell(file);\
  fseek(file, 0, SEEK_SET);\
  if(size > MAX_SIZE_OF_FILE){\
      fclose(fopen(FILE_DUMP, "w"));\
      file = fopen(FILE_DUMP, "a");\
  }\
  if(stack != NULL){\
        fprintf(file, "DUMP START=============\n");\
        fprintf(file, "\tSTACK[T = %s] STACK[%p] %s(%d) \n", GET_TYPE(T), (void*)stack, __FILE__, __LINE__);\
        fprintf(file, "\tsize = %zd\n", stack->size);\
        fprintf(file, "\tcapacity = %zd\n", stack->capacity);\
        fprintf(file, "items: \n");\
        for (int i = 0; i < stack->size; ++i) {\
            fprintf(file, "\t*[%d] = ", i);\
            STACK(StackPrint, T)(stack->storage[i], file);\
            fprintf(file, "\n");\
            }\
        printErrorType(errorType, file);\
        fprintf(file,"DUMP END=============\n");\
        fclose(file);\
        fprintf(stderr, "DUMP JUMPED!\n");\
  }\
  else{\
        fprintf(file,"You broke the DUMP :(!\n");\
  }\



typedef uint64_t  canary_size;
typedef uint32_t  hash_size;

/**
* @brief  Struct is implementing a stack
*/
typedef struct STACK(Stack, T){
#ifdef CANARY_CHECK
    canary_size canaryLeft;
#endif
    ssize_t size;
    ssize_t capacity;
    T* storage;
#ifdef CANARY_CHECK
    #ifdef HASH_CHECK
    hash_size canaryHash;
    #endif
    canary_size canaryRight;
#endif
}STACK(Stack, T);

/**
* @brief       Method counts the hash of the buffer
* @param[in]   stack
 */
hash_size STACK(StackBufferHash, T)(STACK(Stack, T)* stack){
    hash_size hash = 0;
    char* buffer = (char*) stack->storage;
    for (int i = 0; i < stack->size; i++){
        hash += HASH_CONST * hash  + *buffer++ + 42;
    }
    return hash;
}

/**
* @brief       Method counts the hash of stack
* @details     Method do not count the current value of hash
*              and makes it zero
* @param[in]   stack
 */
#ifdef HASH_CHECK
hash_size STACK(StackHash, T)(STACK(Stack, T)* stack){
#ifdef CANARY_CHECK
    hash_size tmp = stack->canaryHash;
    stack->canaryHash = 0;
    //count hash
    hash_size sum = 0;
    sum += (stack->canaryLeft) * HASH_CONST;
    sum += (stack->canaryRight) * HASH_CONST;
    sum += (stack->canaryHash) * HASH_CONST;
    sum += (stack->size) * HASH_CONST;
    sum += (stack->capacity) * HASH_CONST;
    sum += stack->size * sizeof(*stack->storage);
    // get storage hash
    sum += STACK(StackBufferHash, T)(stack);
    stack->canaryHash = tmp;
    return sum;
#endif
}
#endif


/**
* @brief       Method verifies the stack fields
* @param[in]   stack
* @param[in]   afterOperationOrNo  flag to runs checking after or before any operations of stack
 */
int STACK(StackOk, T)(STACK(Stack, T)* stack, int afterOperationOrNo){
    if(stack == NULL)
        return STACK_NULL_POINTER;
    else if(stack->storage == NULL)
        return STACK_NULL_STORAGE;
    else if(stack->storage == (T*)ERROR_PTR)
        return STACK_ERRPTR_STORAGE;
    else if(stack->size < 0 )
        return STACK_BAD_SIZE;
    else if(stack->capacity < 0 )
        return STACK_BAD_CAPACITY;
    else if(stack->size > stack->capacity)
        return STACK_OVERFLOW;
#ifdef CANARY_CHECK

    if (stack->canaryLeft != CANARY_VALUE && stack->canaryRight != CANARY_VALUE)
            return STACK_ALL_CANARY_SONGS;
    else if (stack->canaryLeft != CANARY_VALUE)
            return STACK_LEFT_CANARY_SONGS;
    else if (stack->canaryRight != CANARY_VALUE)
            return  STACK_RIGHT_CANARY_SONGS;
    else if(*((canary_size*)stack->storage - 1) != CANARY_BUFFER_VALUE)
        return STACK_BUFFER_CANARY_LEFT_SONGS;
    else if(*(canary_size*)(stack->storage + stack->capacity) != CANARY_BUFFER_VALUE){
        return STACK_BUFFER_CANARY_RIGHT_SONGS;
    }

#ifdef HASH_CHECK
        hash_size checkHash = STACK(StackHash, T)(stack);
        if(afterOperationOrNo == 0){
            if (checkHash != stack->canaryHash)
                return STACK_HASH_INCORRECT;
        }
#endif

#endif
    //checking POISON
    for(int i = stack->size; i < stack->capacity; ++i)
        if(stack->storage[i] != POISON){
            return STACK_POISON_ERROR;
        }

    return STACK_OK;
}

/**
* @brief       Method verifies the stack fields and calls dump
* @param[in]   stack
* @param[in]   afterOperationOrNo  flag to runs checking after or before any operations of stack
 */
void STACK(StackOkOrDump, T)(STACK(Stack,T)* stack, int afterOperationOrNo) {
    int resError = STACK(StackOk, T)(stack, afterOperationOrNo);
    if (resError != STACK_OK){
            STACK_DUMP(stack, T, resError);
            exit(EXIT_FAILURE);
    }
}
/**
* @brief       Method creates the stack and initializes fields of the stack
* @param[in]   stack
* @param[in]   ssize_t capacity
 */
int STACK(StackConstructor, T)(STACK(Stack, T)* stack, ssize_t capacity){
    if(stack == NULL){
        fprintf(stderr, "STACK is null\n");
        exit(EXIT_FAILURE);
    }
    stack->size = 0;
    stack->capacity = capacity;
#ifdef CANARY_CHECK
    stack->canaryLeft = CANARY_VALUE;
    stack->canaryRight = CANARY_VALUE;

    void* temp = calloc(capacity * sizeof(T) + 2 * sizeof(canary_size), 1);
    stack->storage = (T*)(temp + sizeof(canary_size));

    canary_size* canaryLeft  = (canary_size*)((char*)stack->storage - sizeof(canary_size));
    canary_size* canaryRight = (canary_size*)((char*)stack->storage + capacity * sizeof(T));

    *canaryLeft  = CANARY_BUFFER_VALUE;
    *canaryRight = CANARY_BUFFER_VALUE;

#else
    stack->storage = (T*)calloc(capacity, sizeof(T*));
#endif

#ifdef HASH_CHECK
    stack->canaryHash = STACK(StackHash, T)(stack);
#endif
    for(int i = 0; i < capacity; ++i)
        stack->storage[i] = POISON;
    if(!stack->storage){
        fprintf(stderr, "Constructor: can't to calloc memory to storage!\n");
        exit(EXIT_FAILURE);
    }
    return STACK_OK;
}

/**
* @brief       Method destroys the stack and "breaks down" all fields of the stack
* @param[in]   stack
* @param[in]   ssize_t capacity
* @param[in]   ssize_t size
 */
int STACK(StackDestructor, T)(STACK(Stack, T)* stack){
    STACK(StackOkOrDump, T)(stack, 0);
    if(!stack || !stack->storage)
        return STACK_NULL_POINTER;
    stack->size = -1;
    stack->capacity = -1;
#ifdef  CANARY_CHECK
    free((canary_size *)stack->storage - 1);
    #ifdef HASH_CHECK
        stack->canaryHash = -1;
#endif
#else
    free(stack->storage);
#endif
    stack->storage = (T*)ERROR_PTR;
    return STACK_OK;
}

/**
* @brief       Method checks the size of the stack
* @param[in]   stack
 */
int STACK(StackIsEmpty, T)(STACK(Stack, T)* stack){
    STACK(StackOkOrDump, T)(stack, 0);
    return (stack->size <= 0);
}
/**
* @brief       Method returns the size of the stack
* @param[in]   stack
 */
int STACK(StackSize, T)(STACK(Stack, T)* stack){
    STACK(StackOkOrDump, T)(stack, 0);
    return stack->size;
}

/**
* @brief       Method pushes the value of T type to the top of the stack
* @param[in]   stack
* @param[in]   T value
 */
int STACK(StackPush, T)(STACK(Stack, T)* stack, T value){
    STACK(StackOkOrDump, T)(stack,0);

    if(stack->size == stack->capacity){
        stack->capacity *= 2;
#ifdef CANARY_CHECK
        void* tmp = realloc((canary_size*)stack->storage - 1, stack->capacity * sizeof(T) + 2 * sizeof(canary_size));
#else
        T* tmp = (T*)realloc(stack->storage, stack->capacity * sizeof(T));
#endif
        if(!tmp){
            printf("Realloc FAILED!\n");
            exit(EXIT_FAILURE);
        }else{
#ifdef CANARY_CHECK
            stack->storage = (T*)(tmp + sizeof(canary_size));
            canary_size* canaryLeft  = (canary_size*)((char*)stack->storage - sizeof(canary_size));
            canary_size* canaryRight = (canary_size*)((char*)stack->storage + stack->capacity * sizeof(T));
            *canaryLeft  = CANARY_BUFFER_VALUE;
            *canaryRight = CANARY_BUFFER_VALUE;
#else
            stack->storage = tmp;
#endif
            for(int i = stack->size; i < stack->capacity; ++i)
                stack->storage[i] = POISON;
        }
    }
    stack->storage[stack->size++] = value;
#ifdef HASH_CHECK
    stack->canaryHash = STACK(StackHash, T)(stack);
#endif
    STACK(StackOkOrDump, T)(stack, 1);
    return STACK_OK;
}

/**
* @brief      Method gets the value of T type from the top of the stack
* @param[in]  stack
* return   T  value
 */
T  STACK(StackPop, T)(STACK(Stack, T)* stack){
    STACK(StackOkOrDump, T)(stack, 0);
    if(stack->size >= 1){
        T elem = stack->storage[stack->size - 1];
        stack->storage[--stack->size] = POISON;
#ifdef HASH_CHECK
        stack->canaryHash = STACK(StackHash, T)(stack);
#endif
        return elem;
    }
    fprintf(stderr,"Pop: size < 0\n");
    exit(EXIT_FAILURE);
}


#endif

