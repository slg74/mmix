#include <stdio.h>
#include <stdlib.h>

#include "instructions.h"
#include "mmix.h"

void execute_instructions() {
    // Sample MMIX program
    uint32_t program[] = {
        (ADD << 24) | (3 << 16) | (1 << 8) | 2,  // ADD $3, $1, $2
        (SUB << 24) | (4 << 16) | (3 << 8) | 2,  // SUB $4, $3, $2
        (MUL << 24) | (5 << 16) | (3 << 8) | 4,  // MUL $5, $3, $4
        (DIV << 24) | (6 << 16) | (5 << 8) | 2   // DIV $6, $5, $2
    };

    // Load the program into memory
    for (size_t i = 0; i < sizeof(program) / sizeof(uint32_t); i++) {
        memory[i * 4] = (program[i] >> 24) & 0xFF;
        memory[i * 4 + 1] = (program[i] >> 16) & 0xFF;
        memory[i * 4 + 2] = (program[i] >> 8) & 0xFF;
        memory[i * 4 + 3] = program[i] & 0xFF;
    }

    // Set initial values
    registers[0] = 0;
    registers[1] = 1;
    registers[2] = 2;
    registers[3] = 0;

    // Run the program
    PC = 0;
    for (size_t i = 0; i < sizeof(program) / sizeof(uint32_t); i++) {
        execute_instruction(program[i]);
    }

    // Print results in first 10 registers
    for (int i = 0; i < 10; i++) {
        printf("Result in $%d: %llu\n", i, registers[i]);
    }
    //printf("Result in $1: %llu\n", registers[3]);
    //printf("Result in $2: %llu\n", registers[3]);
    //printf("Result in $3: %llu\n", registers[3]);
    //printf("Result in $4: %llu\n", registers[4]);
    //printf("Result in $5: %llu\n", registers[5]);
    //printf("Result in $6: %llu\n", registers[6]);
}