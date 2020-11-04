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
        double arg1 = 0;
        double arg2 = 0;
        switch(byteCodes[i]){
            case PUSH:
                cpu->currentOp = PUSH;
                i++;
                arg = *(double*)(byteCodes + i);
                StackPush_double(cpu->stack,arg);
                i += sizeof(arg);
                break;
            case ADD:
                ++i;
                cpu->currentOp = ADD;
                arg1 = StackPop_double(cpu->stack);
                arg2 = StackPop_double(cpu->stack);
                StackPush_double(cpu->stack, (arg1 + arg2));
                break;
            case SUB:
                ++i;
                cpu->currentOp = SUB;
                arg1 = StackPop_double(cpu->stack);
                arg2 = StackPop_double(cpu->stack);
                StackPush_double(cpu->stack, (arg1 - arg2));
                break;
            case MUL:
                ++i;
                cpu->currentOp = MUL;
                arg1 = StackPop_double(cpu->stack);
                arg2 = StackPop_double(cpu->stack);
                StackPush_double(cpu->stack, (arg1 * arg2));
                break;
            case DIV:
                ++i;
                cpu->currentOp = DIV;
                arg1 = StackPop_double(cpu->stack);
                arg2 = StackPop_double(cpu->stack);
                //TODO:check
                StackPush_double(cpu->stack, (arg1 / arg2));
                break;
            case SQRT:
                ++i;
                cpu->currentOp = SQRT;
                arg1 = StackPop_double(cpu->stack);
                double res = sqrt(arg1);
                //TODO:check
                StackPush_double(cpu->stack, res);
                break;
            case OUT:
                ++i;
                cpu->currentOp = OUT;
                arg1 = StackPop_double(cpu->stack);
                printf("Result = %g\n",arg1);
                break;
            case IN:
                ++i;
                cpu->currentOp = IN;
                arg1 = getDoubleFromInput("Input value pls: ");
                StackPush_double(cpu->stack, arg1);
                break;
            case HLT:
                ++i;
                cpu->currentOp = HLT;
                printf("The program has finished executing!\n");
                return EXIT_SUCCESS;
            default:
                fprintf(stderr,"Unexpected command: %s in binary file: %x !\n", code, byteCodes[i]);
                return EXIT_FAILURE;

        }
    }

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

double getDoubleFromInput(char message[]){
    double number;
    printf("%s", message);
    int correctInput = scanf("%lg", &number);
    while(correctInput != 1){
        while (getchar() != EOF && getchar() != '\n' && getchar() != '\0');
        printf("Wrong input,try again\n%s", message);
        correctInput = scanf("%lg", &number);
    }
    return number;
}
