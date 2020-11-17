cmake_minimum_required(VERSION 3.15)
project(cpu_assembler_disassembler C)

set(CMAKE_C_STANDARD 11)
add_compile_options(-Wall -Wextra -pedantic -Wfloat-equal -fno-stack-protector)

add_executable(
        stack_machine
        src/stack_lib/all_possible_stack.h
        src/stack_lib/stack.h
        src/stack_lib/stack_errors.c
        src/stack_lib/stack_errors.h
        src/stack_lib/templates.h
        src/cpu.c
        src/cpu.h
        src/asm_utils.c
        src/asm_utils.h
        src/vector.c
        src/vector.h
        src/asm_ram.c
        src/asm_ram.h)

add_executable(
        asm
        src/asm.c
        src/asm.h
        src/asm_utils.c
        src/asm_utils.h
        src/vector.c
        src/vector.h)

add_executable(
        disasm
        src/disasm.c
        src/disasm.h
        src/asm_utils.c
        src/asm_utils.h
        src/vector.c
        src/vector.h)

#add_executable(
#        tests
#        src/disasm.c
#        src/disasm.h
#        src/asm_utils.c
#        src/asm_utils.h
#        src/asm.c
#        src/asm.h
#        src/vector.c
#        src/vector.h
#        src/stack_lib/stack.h
#        src/stack_lib/stack_errors.c
#        src/stack_lib/stack_errors.h
#        src/stack_lib/templates.h
#        src/cpu.c
#        src/cpu.h)

target_link_libraries(stack_machine PRIVATE m)

set(RESOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/test/)
