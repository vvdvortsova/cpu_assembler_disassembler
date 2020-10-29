cmake_minimum_required(VERSION 3.15)
project(cpu_assembler_disassembler C)

set(CMAKE_C_STANDARD 11)

add_executable(cpu_assembler_disassembler
        main.c
        src/cpu.c
        src/cpu.h
        src/asm.c
        src/asm.h
        src/disasm.c
        src/disasm.h
        test/test_assembler.c
        src/asm_utils.c
        src/asm_utils.h)

add_executable(asm
        src/asm.c
        src/asm.h
        src/asm_utils.c
        src/asm_utils.h)

add_executable(disasm
        src/disasm.c
        src/disasm.h
        src/asm_utils.c
        src/asm_utils.h)

set(RESOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/asm.txt)