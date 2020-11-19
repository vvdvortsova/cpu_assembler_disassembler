/**
* @file         disasm.c
* @brief        Disassembler methods
* @author       Dvortsova Varvara BSE182 HSE
* @include      "disasm.h"
*/
#include "disasm.h"


int writeMnemonicsToFile(const char* instruction, byte reg, FILE* file) {
    const char* code = NULL;
    fprintf(file,"%s ", instruction);
    code = getStringOfOpCode(reg);
    if(code == NULL) {
        fprintf(stderr,"Unexpected register!\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s\n", code);
    return EXIT_SUCCESS;
}

int disAssembler(const char* fileWithByteCode, const char* fileWithMnemonics) {
    assert(fileWithByteCode != NULL);
    assert(fileWithMnemonics != NULL);
    vector* tags = calloc(1, sizeof(vector));
    vectorInit(tags);

    int size = 0;
    int countOfFunction = 0;
    int countOfBytes = 0;
    char* byteCodes = getBuffer(fileWithByteCode, &size, "rb");
    FILE* fileMnemonics = fopen(fileWithMnemonics, "w");

    if(fileMnemonics == NULL) {
        fprintf(stderr,"Do not open = %s\n", fileWithMnemonics);
        exit(EXIT_FAILURE);
    }

    disassembleFirstWayToReadTags(byteCodes, size, tags, &countOfFunction, &countOfBytes);
    disassembleSecondWayToWriteTags(byteCodes, size, tags, fileMnemonics, &countOfBytes);

    vectorFree(tags);
    fclose(fileMnemonics);
    return EXIT_SUCCESS;
}


void disassembleSecondWayToWriteTags(char* byteCodes, int size, vector* tags, FILE* file, int* countOfBytes) {
    int i = 0;
    for (i = 0; i < size;) {
        double arg = 0;
        int addr = 0;
        byte funcArg = 0;
        int index = 0;
        const char* code = getStringOfOpCode(byteCodes[i]);
        if(code == NULL) {
            fprintf(stderr,"Unexpected instruction!\n");
            continue;
        }
        switch(byteCodes[i]) {
            case TAG:
            case F:
                index = 0;
                i++;// because of i start from zero
                if(findFunctionByAddressInVector(tags, i, &index) == EXIT_SUCCESS) {
                    struct tag* elem = (struct tag*)vectorGet(tags, index);
                    fprintf(file,"%s", elem->name);
                }
                break;
            case JE:
            case JNE:
            case JL:
            case JLE:
            case JG:
            case JGE:
            case JMP:
            case CALL:
                i++;
                funcArg = (int)(byteCodes[i]);
                fprintf(file,"%s ", code);
                if(findFunctionByAddressInVector(tags, funcArg, &index) == EXIT_SUCCESS) {
                    struct tag* elem = (struct tag*)vectorGet(tags, index);
                    char copy[90];
                    strcpy(copy, elem->name);
                    copy[strlen(copy) - 2] = '\0';
                    fprintf(file,"%s\n", copy);
                } else{
                    fprintf(stderr,"Can't find func name!:(\n");
                    printfVectorWithTags(tags);
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
            case MOV:
                i++;
                fprintf(file,"%s ", code);
                code = getStringOfOpCode(byteCodes[i]);
                fprintf(file,"%s, ", code);
                i++;
                fprintf(file,"[");
                addr = *(int*)(byteCodes + i);
                fprintf(file,"%d", addr);
                fprintf(file,"]\n");
                i += sizeof(addr);
                break;
            case POPR:
            case PUSHR:
                if(writeMnemonicsToFile(code, byteCodes[i + 1], file) != EXIT_FAILURE) {
                    i += 2;
                    break;
                }
                fprintf(stderr,"Unexpected register or something wrong with file!\n");
                exit(EXIT_FAILURE);
            case POP_RAM:
            case PUSH_RAM:
                i++;
                fprintf(file,"%s ", code);
                fprintf(file,"[");
                addr = *(int*)(byteCodes + i);
                fprintf(file,"%d", addr);
                fprintf(file,"]\n");
                i += sizeof(addr);
                break;
            case RET:
            case HLT:
                ++i;
                fprintf(file,"%s\n\n", code);
                break;
            default:
                ++i;
                fprintf(file,"%s\n", code);
                break;
        }
    }
    *countOfBytes = i;
}


void disassembleFirstWayToReadTags(char* byteCodes, int size, vector* tags, int* countOfFunction, int* countOfBytes){
    int i = 0;
    int callPos = 0;
    for (i = 0; i < size;) {
        double arg = 0;
        int addr = 0;
        byte funcArg = 0;
        int index = 0;
        const char* code = getStringOfOpCode(byteCodes[i]);
        if(code == NULL) {
            fprintf(stderr,"Unexpected instruction!\n");
            continue;
        }
        switch(byteCodes[i]) {
            case TAG:
            case F:
                callPos = i;
                i++;// because of i start from zero
                if(findFunctionByAddressInVector(tags, i, &index) != EXIT_SUCCESS){
                    //if we did not find this function in array
                    struct tag* temp = calloc(1, sizeof(struct tag));
                    temp->position = i;
                    temp->name = calloc(1, sizeof(char*));
                    if(byteCodes[callPos] == F){
                        sprintf(temp->name, "f%d:\n",*countOfFunction);
                    } else sprintf(temp->name, "t%d:\n",*countOfFunction);
                    (*countOfFunction) += 1;
                    vectorAdd(tags, temp);
                }
                break;
            case JE:
            case JNE:
            case JL:
            case JLE:
            case JG:
            case JGE:
            case JMP:
            case CALL:
                callPos = i;
                i++;
                funcArg = (int)(byteCodes[i]);
                if(findFunctionByAddressInVector(tags, funcArg, &index) != EXIT_SUCCESS){
                    //if we did not find this function in array
                    struct tag* temp = calloc(1, sizeof(struct tag));
                    temp->position = funcArg;
                    temp->name = calloc(1, sizeof(char*));
                    if(byteCodes[callPos] == CALL){
                        sprintf(temp->name, "f%d:\n",*countOfFunction);
                    }
                    else sprintf(temp->name, "t%d:\n",*countOfFunction);
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
            case MOV:
                //TODO
                i++;//mov
                i++;//reg
                addr = *(int*)(byteCodes + i);
                i += sizeof(addr);
                break;
            case POP_RAM:
            case PUSH_RAM:
                i++;
                addr = *(int*)(byteCodes + i);
                i += sizeof(addr);
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
    printf("Please! Check your arguments!\n");
    exit(EXIT_FAILURE);
}
