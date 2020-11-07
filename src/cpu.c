#include "cpu.h"


int initCPU(CPU* cpu) {
    StackConstructor_double(cpu->stack,20);
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
            fprintf(stderr,"Unexpected instruction in start of for!\n");
            exit(EXIT_FAILURE);
        }
        double arg1 = 0;
        int addressOfFunction = 0;
        switch(byteCodes[i]){
            case F:
                //do not execute instructions after it before ret
                //after ret cpu->cpuState = simple_state
                cpu->cpuState = FUNC_STATE;
                i++;
                break;
            case JMP:
                cpu->cpuState = JMP_STATE;
                i++;
                //read address
                //push next address in stack
                //jump to function to execute it
                addressOfFunction = *(int*)(byteCodes + i);
                int returnAddress = i + sizeof(int);//we do not add 1 because i begins with zero
                StackPush_double(cpu->stack, returnAddress);
                i = addressOfFunction;//address after "f" byte
                break;
            case RET:
                //look at the top of stack and get address of return point
                //jump to return point
                //or if it was func_state than we turn off it
                if(cpu->cpuState == JMP_STATE){
                    cpu->cpuState = SIMPLE_STATE;
                    addressOfFunction = StackPop_double(cpu->stack);
                    i = addressOfFunction;
                    break;
                } else if (cpu->cpuState == FUNC_STATE){
                    cpu->cpuState = SIMPLE_STATE;
                    i++;
                    break;
                }
                break;
            case PUSHR:
                i++;//opCode
                if(cpu->cpuState != FUNC_STATE){
                    code = getStringOfOpCode(byteCodes[i]);
                    if(code == NULL) {
                        fprintf(stderr,"Unexpected instruction! in push\n");
                        exit(EXIT_FAILURE);
                    }
                    switch (byteCodes[i]) {
                        case RAX:
                            StackPush_double(cpu->stack, cpu->rax);
                            i++;
                            break;
                        case RBX:
                            StackPush_double(cpu->stack, cpu->rbx);
                            i++;
                            break;
                        default:
                            fprintf(stderr,"Unexpected register after push in binary file: %x !\n", code, byteCodes[i]);
                            return EXIT_FAILURE;
                    }
                    break;
                }
                i++;// register
                break;
            case POPR:
                i++;//opCode
                if(cpu->cpuState != FUNC_STATE){
                    code = getStringOfOpCode(byteCodes[i]);
                    if(code == NULL) {
                        fprintf(stderr,"Unexpected instruction in pop!\n");
                        exit(EXIT_FAILURE);
                    }
                    switch (byteCodes[i]){
                        case RAX:
                            arg1 = StackPop_double(cpu->stack);
                            cpu->rax = arg1;
                            i++;
                            break;
                        case RBX:
                            arg1 = StackPop_double(cpu->stack);
                            cpu->rbx = arg1;
                            i++;
                            break;
                        default:
                            fprintf(stderr,"Unexpected register after pop in binary file: %x !\n", code, byteCodes[i]);
                            return EXIT_FAILURE;
                    }
                    break;
                }
                i++;//register
                break;
            case PUSH:
                i++;//opCode
                arg = *(double*)(byteCodes + i);
                if(cpu->cpuState != FUNC_STATE){
                    StackPush_double(cpu->stack,arg);
                }
                i += sizeof(arg);//number
                break;
            case ADD:
            case SUB:
            case DIV:
            case MUL:
                if(cpu->cpuState != FUNC_STATE){
                    if(binaryOp(cpu->stack, byteCodes[i]) == EXIT_FAILURE){
                        fprintf(stderr,"Unexpected command: %s in binary file: %x !\n", code, byteCodes[i]);
                        return EXIT_FAILURE;
                    }
                }
                i++;
                break;
            case POP:
                if(cpu->cpuState != FUNC_STATE) {
                    StackPop_double(cpu->stack);
                }
                i++;
                break;
            case SQRT:
                ++i;
                if(cpu->cpuState != FUNC_STATE) {
                    arg1 = StackPop_double(cpu->stack);
                    if(arg1 < 0){
                        fprintf(stderr,"Sqrt from negative number! %g\n", arg1);
                        return EXIT_FAILURE;
                    }
                    double res = sqrt(arg1);
                    StackPush_double(cpu->stack, res);
                }
                break;
            case OUT:
                ++i;
                if(cpu->cpuState != FUNC_STATE) {
                    arg1 = StackPop_double(cpu->stack);
                    printf("Result = %g\n",arg1);
                    break;
                }
                break;
            case IN:
                ++i;
                if(cpu->cpuState != FUNC_STATE) {
                    arg1 = getDoubleFromInput("Input value pls: ");
                    StackPush_double(cpu->stack, arg1);
                    break;
                }
                break;
            case HLT:
                if(cpu->cpuState != FUNC_STATE) {
                    printf("The program has finished executing in function!\n");
                    return EXIT_SUCCESS;
                }
                printf("The program has finished executing!\n");
                return EXIT_SUCCESS;
            default:
                fprintf(stderr,"Unexpected command: %s in binary file: %x !\n", code, byteCodes[i]);
                return EXIT_FAILURE;

        }
    }
    return EXIT_SUCCESS;
}

int binaryOp(Stack_double* stack, byte code){
    double arg1 = 0;
    double arg2 = 0;
    arg1 = StackPop_double(stack);
    arg2 = StackPop_double(stack);

    switch(code){
        case ADD:
            StackPush_double(stack, (arg1 + arg2));
            break;
        case SUB:
            StackPush_double(stack, (arg1 - arg2));
            break;
        case MUL:
            StackPush_double(stack, (arg1 * arg2));
            break;
        case DIV:
            if(arg2 == 0){
                fprintf(stderr,"Division by zero! %g / %g\n", arg1, arg2);
                return EXIT_FAILURE;
            }
            StackPush_double(stack, (arg1 / arg2));
            break;
        default:
            fprintf(stderr,"Unexpected command: %x in binary file!\n", code);
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}

int countResult(char* fileName) {
    assert(fileName != NULL);
    int size = 0;
    char* byteCodes = getBuffer(fileName, &size, "rb");
    Stack_double stack;
    CPU cpu = { &stack, 0, 0};
    initCPU(&cpu);

    if(byteCodes[size-1] != HLT){
        fprintf(stderr,"The program can't finish executing!\n");
        fprintf(stderr,"Because of the lack of HLT command at the end of binary file!\n");
        return EXIT_FAILURE;
    }
    cpu.cpuState = SIMPLE_STATE;
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

double getDoubleFromInput(char message[]) {
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
