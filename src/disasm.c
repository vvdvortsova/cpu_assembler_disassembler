#include "disasm.h"


int writeMnemonicsToFile(const char* instruction, byte reg, FILE* file){
    const char* code = NULL;
    fprintf(file,"%s ", instruction);
    code = getStringOfOpCode(reg);
    if(code == NULL){
        fprintf(stderr,"Unexpected register!\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", code);
    return EXIT_SUCCESS;
}

int disAssembler(const char* fileWithByteCode, const char* fileWithMnemonics){
    assert(fileWithByteCode != NULL);
    assert(fileWithMnemonics != NULL);
    vector* tags = calloc(1, sizeof(vector));
    vectorInit(tags);


    int size = 0;
    int countOfFunction = 0;
    int countOfBytes = 0;
    char* byteCodes = getBuffer(fileWithByteCode, &size, "rb");
    FILE* fileMnemonics = fopen(fileWithMnemonics, "w");

    if(fileMnemonics == NULL){
        fprintf(stderr,"Do not open = %s\n", fileWithMnemonics);
        exit(EXIT_FAILURE);
    }

//    disassemblerToFile(byteCodes, size, fileMnemonics);
    disassembleFirstWayToReadTags(byteCodes, size, tags, &countOfFunction, &countOfBytes);
    printf("Print Vector before creating tags\n");
    printfVector(tags);

    printf("size = %d countOfBytes = %d\n",size,countOfBytes);

    disassembleSecondWayToWriteTags(byteCodes, size, tags, fileMnemonics, &countOfBytes);


        vectorFree(tags);
    fclose(fileMnemonics);
    return EXIT_SUCCESS;
}


void disassembleSecondWayToWriteTags(char* byteCodes, int size, vector* tags, FILE* file, int* countOfBytes){
    int i = 0;
    for (i = 0; i < size;) {
        double arg = 0;
        byte funcArg = 0;
        int index = 0;
        const char* code = getStringOfOpCode(byteCodes[i]);
        if(code == NULL) {
            fprintf(stderr,"Unexpected instruction!\n");
            continue;
        }
        switch(byteCodes[i]) {
            case F:
                index = 0;
                i++;// because of i start from zero
                printf("f %d\n", i);
                if(findFunctionByAddressInVector(tags, i, &index) == EXIT_SUCCESS) {
                    printf("in f %d\n", i);
                    struct tag* elem = (struct tag*)vectorGet(tags, index);
                    fprintf(file,"%s", elem->name);
                }
                break;
            case JMP:
                printf("jmp %d\n", i);
                i++;
                funcArg = (int)(byteCodes[i]);
                printf("jmp address %d\n", funcArg);
                fprintf(file,"%s ", code);
                if(findFunctionByAddressInVector(tags, funcArg, &index) == EXIT_SUCCESS) {
                    printf("in jmp %d\n", i);
                    struct tag* elem = (struct tag*)vectorGet(tags, index);
                    char copy[90];
                    strcpy(copy, elem->name);
                    copy[strlen(copy) - 2] = '\0';
                    fprintf(file,"%s\n", copy);
                } else{
                    fprintf(stderr,"Can't find func name!:(\n");
                    printfVector(tags);
                }
                i+= sizeof(int);
                break;
            case PUSH:
                i++;
                fprintf(file,"%s ", code);
                arg = *(double*)(byteCodes + i);
                fprintf(file,"%g\n", arg);
                i += sizeof(arg);
                break;
            case POPR:
            case PUSHR:
                if(writeMnemonicsToFile(code, byteCodes[i + 1], file) != EXIT_FAILURE) {
                    i += 2;
                    break;
                }
                fprintf(stderr,"Unexpected register or something wrong with file!\n");
                exit(EXIT_FAILURE);
            default:
                ++i;
                fprintf(file,"%s\n", code);
                break;
        }
    }
    *countOfBytes = i;
}

/**
 * Короче, если нам попадается функция, то чекаем, если она в векторе, иначе добавляем
 * также увеличиваем счетчик фукций, ибо названия у нас будут свои
 * @param byteCodes
 * @param size
 * @param tags
 * @param countOfFunction
 * @param countOfBytes
 */
void disassembleFirstWayToReadTags(char* byteCodes, int size, vector* tags, int* countOfFunction, int* countOfBytes){
    int i = 0;
    for (i = 0; i < size;) {
        double arg = 0;
        byte funcArg = 0;
        int index = 0;
        const char* code = getStringOfOpCode(byteCodes[i]);
        if(code == NULL) {
            fprintf(stderr,"Unexpected instruction!\n");
            continue;
        }
        switch(byteCodes[i]) {
            case F:
                i++;// because of i start from zero
                printf("f %d\n", i);
                if(findFunctionByAddressInVector(tags, i, &index) != EXIT_SUCCESS){
                    //if we did not find this function in array
                    struct tag* temp = calloc(1, sizeof(struct tag));
                    temp->position = i;
                    temp->name = calloc(1, sizeof(char*));
                    sprintf(temp->name, "f%d:\n",*countOfFunction);
                    (*countOfFunction) += 1;
                    vectorAdd(tags, temp);
                }
                break;
            case JMP:
                printf("jmp %d\n", i);
                i++;
                funcArg = (int)(byteCodes[i]);
                printf("jmp address %d\n", funcArg);
                if(findFunctionByAddressInVector(tags, funcArg, &index) != EXIT_SUCCESS){
                    //if we did not find this function in array
                    struct tag* temp = calloc(1, sizeof(struct tag));
                    temp->position = funcArg;
                    temp->name = calloc(1, sizeof(char*));
                    sprintf(temp->name, "f%d:\n",*countOfFunction);
                    (*countOfFunction) += 1;
                    vectorAdd(tags, temp);
                }
                i+= sizeof(int);
                break;
            case PUSH:
                i++;
                arg = *(double*)(byteCodes + i);
                i += sizeof(arg);
                break;
            default:
                ++i;
                break;
        }
    }
    *countOfBytes = i;
}



int main(int argc, char **argv) {
    if(argc == 3){
        disAssembler(argv[1], argv[2]);
        return 0;
    }
    printf("Pls!Check your arguments!\n");
    exit(EXIT_FAILURE);
}
