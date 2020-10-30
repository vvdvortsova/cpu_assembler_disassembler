#include <stdio.h>
#include "src/asm.h"
#include "src/disasm.h"


int main() {
    assembler("../src/test.txt","../src/asm");
    int size;
    char* instructions = getBuffer("../src/asm", &size, "rb");
    printf("%s\n", instructions);

    printf("Hello, World!\n");
    disAssembler("../src/asm","../src/disasm.txt");
    return 0;
}
