#include <zconf.h>
#include <wait.h>
#include "../src/disasm.h"
#include "../src/asm.h"
#include "../src/cpu.h"

/**
 * Macros defines a custom assert function for unit testing
 * @param nameOfMethod   Describe the name Of method where assertTestINT was called
 * @param code           Actual value
 * @param expected       Expected value
 * */
#define assertTestINT( nameOfMethod, code, expected )\
    if((code) == (expected)){\
        printf("[TEST] [ %s ] [PASSED]\n",\
                nameOfMethod);\
    }else{\
        fprintf(stderr, "[TEST] [ %s ] [FAILED]\n",\
                nameOfMethod);\
        fprintf(stderr, "[TEST] expected = %d code = %d \n",expected, code);\
    }

#define  assertFailed(nameOfMethod)\
fprintf(stderr, "[TEST] [ %s ] [FAILED]\n",\
                nameOfMethod);\

/**
 * Macros defines a custom assert function for checking exit code from child process
 * @param nameOfMethod   Describe the name Of method where forkChildAssert was called
 * @param statement      Statement runs in child process
 * */
#define forkChildAssert(nameOfFunction, statement, expectedCode)\
    pid_t ppid = fork();\
    if(ppid < 0){\
        fprintf(stderr, "Failed to create child process\n");\
        assertFailed(nameOfFunction);\
    }\
    else if(ppid == 0){\
    statement\
    }else{\
      int status = 0;\
      waitpid(ppid, &status, 0);\
      if (WIFEXITED(status)){\
        int exitCode = WEXITSTATUS(status);\
        assertTestINT(nameOfFunction, exitCode , expectedCode);\
      }\
    }\


//int main(){
//    assembler("asm.txt","asm");
//}
//
