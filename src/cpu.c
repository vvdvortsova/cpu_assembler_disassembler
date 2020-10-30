#include "cpu.h"


int initCPU(CPU* cpu) {
    StackConstructor_double(cpu->stack,20);
    //TODO: add regs
    return EXIT_SUCCESS;
}

int destructorCPU(CPU* cpu) {
    StackDestructor_double(cpu->stack);
    return EXIT_SUCCESS;
}

int processMachine(char* byteCodes, size_t size, CPU* cpu) {
    for (size_t i = 0; i < size;) {
        double arg = 0;
        char* code = getStringOfOpCode(byteCodes[i]);
        if(code == NULL) {
            fprintf(stderr,"Unexpected instruction!\n");
            exit(EXIT_FAILURE);
        }
        if(byteCodes[i] == PUSH) {
            cpu->currentOp = PUSH;
            i++;
            arg = *(double*)(byteCodes + i);
            StackPush_double(cpu->stack,arg);
            i += sizeof(arg);
        } else if(byteCodes[i] == ADD) {
            ++i;
            cpu->currentOp = ADD;
            double arg1 = StackPop_double(cpu->stack);
            double arg2 = StackPop_double(cpu->stack);
            StackPush_double(cpu->stack, (arg1 + arg2));
        } else if(byteCodes[i] == SUB) {
            ++i;
            cpu->currentOp = SUB;
            double arg1 = StackPop_double(cpu->stack);
            double arg2 = StackPop_double(cpu->stack);
            StackPush_double(cpu->stack, (arg1 - arg2));
        } else if(byteCodes[i] == MUL) {
            ++i;
            cpu->currentOp = MUL;
            double arg1 = StackPop_double(cpu->stack);
            double arg2 = StackPop_double(cpu->stack);
            StackPush_double(cpu->stack, (arg1 * arg2));

        }else if(byteCodes[i] == DIV) {
            ++i;
            cpu->currentOp = DIV;
            double arg1 = StackPop_double(cpu->stack);
            double arg2 = StackPop_double(cpu->stack);
            //TODO:check
            StackPush_double(cpu->stack, (arg1 / arg2));
        } else if(byteCodes[i] == SQRT) {
            ++i;
            cpu->currentOp = SQRT;
            double arg1 = StackPop_double(cpu->stack);
            double res = sqrt(arg1);
            //TODO:check
            StackPush_double(cpu->stack, res);
        } else if(byteCodes[i] == OUT) {//TODO let it work))
            ++i;
            cpu->currentOp = OUT;
            double arg1 = StackPop_double(cpu->stack);
            printf("%g\n",arg1);
        }
        else if(byteCodes[i] == IN) { //TODO: how to?
            ++i;
            cpu->currentOp = IN;
            //TODO
        }
        else if(byteCodes[i] == HLT) {
            ++i;
            double arg1 = StackPop_double(cpu->stack);
            printf("result = %g\n", arg1);
            cpu->currentOp = HLT;
            printf("The program has finished executing!\n");
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}



int countResult(char* fileName) {
    assert(fileName != NULL);
    int size = 0;
    char* byteCodes = getBuffer(fileName, &size, "rb");
    Stack_double stack;
    CPU cpu = { &stack, 0, 0};
    initCPU(&cpu);

    if(processMachine(byteCodes, size, &cpu) != EXIT_SUCCESS){
        fprintf(stderr,"The program has not finished executing!\n");
        return EXIT_FAILURE;
    }

    destructorCPU(&cpu);
    return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
    if(argc == 2){
        countResult(argv[1]);
        return 0;
    }
    printf("Pls!Check your arguments!\n");
    exit(EXIT_FAILURE);

}