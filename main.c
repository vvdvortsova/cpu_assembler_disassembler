#include <stdio.h>
#include "src/asm.h"
#include "src/disasm.h"


int main() {
    assembler("../src/test.vara","../src/asm.vexe");
    int size;
    char* instructions = getBuffer("../src/asm.vexe", &size, "rb");
    printf("%s\n", instructions);

    printf("Hello, World!\n");
    disAssembler("../src/asm.vexe","../src/disasm.txt");
    return 0;
}
