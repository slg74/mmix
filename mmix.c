/* 
// To generate a simple test program:         
// # echo "48 01 00 01 48 02 00 02 20 03 01 02" > test_program.hex
// # xxd -r -p test_program.hex test_program
// 
// To run:
// # make && ./mmix test_program
//
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mmix.h"
#include "instructions.h"

uint64_t registers[256];
uint8_t memory[MEM_SIZE];
uint64_t PC = 0;

void execute_instruction(uint32_t instruction) {
    uint8_t opcode = (instruction >> 24) & 0xFF;
    uint8_t ra = (instruction >> 16) & 0xFF;
    uint8_t rb = (instruction >> 8) & 0xFF;
    uint8_t rc = instruction & 0xFF;

    switch (opcode) {
        case ADD:
            registers[ra] = registers[rb] + registers[rc];
            break;
        case SUB:
            registers[ra] = registers[rb] - registers[rc];
            break;
        case MUL:
            registers[ra] = registers[rb] * registers[rc];
            break;
        case DIV:
            if (registers[rc] != 0) {
                registers[ra] = registers[rb] / registers[rc];
            } else {
                printf("Error: Division by zero\n");
            }
            break;
        case LDB:
            registers[ra] = memory[registers[rb] + registers[rc]];
            break;
        case STB:
            memory[registers[rb] + registers[rc]] = registers[ra] & 0xFF;
            break;
        case JMP:
            PC = registers[ra];
            break;
        case 0xCF: // RESUME
            // Implement resume after interrupt logic
            break;
        case 0x07: // FADD
            // Floating-point addition
            // Placeholder implementation
            registers[ra] = registers[rb] + registers[rc];
            break;
        case 0x03: // FDIV
            // Floating-point division
            // Placeholder implementation
            if (registers[rc] != 0) {
                registers[ra] = registers[rb] / registers[rc];
            } else {
                printf("Error: Floating-point division by zero\n");
            }
            break;
        case 0x02: // FCMP
            // Floating-point comparison
            // Placeholder implementation
            registers[ra] = (registers[rb] > registers[rc]) ? 1 : ((registers[rb] < registers[rc]) ? -1 : 0);
            break;
        case 0x11: // NEGI
            // Negate immediate
            registers[ra] = -((int64_t)rb);
            break;
        case 0x48: // SETH
            registers[ra] = (uint64_t)rb << 48;
            break;
        case 0xF8: // SYNC
            // Synchronize
            // Placeholder implementation
            break;
        case 0x85: // LDSF
            // Load short float
            // Placeholder implementation
            registers[ra] = *(float*)(memory + registers[rb] + registers[rc]);
            break;
        case 0x0A: // 2ADDU
            registers[ra] = (registers[rb] + registers[rc]) << 1;
            break;
        default:
            printf("Unknown opcode: 0x%02X\n", opcode);
            break;
    }
}

void run() {
    uint32_t max_instructions = 1000;
    uint32_t instruction_count = 0;

    while (instruction_count < max_instructions) {
        if (PC >= MEM_SIZE) {
            printf("Program counter out of bounds. Halting execution.\n");
            break;
        }

        uint32_t instruction = (memory[PC] << 24) |
                               (memory[PC + 1] << 16) |
                               (memory[PC + 2] << 8) |
                               memory[PC + 3];
        PC += 4;

        if (instruction == 0) {
            printf("Reached end of program (null instruction). Halting execution.\n");
            break;
        }

        execute_instruction(instruction);
        instruction_count++;
    }

    if (instruction_count >= max_instructions) {
        printf("Reached maximum instruction count. Halting execution.\n");
    }

    printf("Result: %llu\n", registers[3]);
}

void load_program(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return;
    }
    fread(memory, sizeof(uint8_t), MEM_SIZE, file);
    fclose(file);
}

int mmix_main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <program>\n", argv[0]);
        return 1;
    }

    load_program(argv[1]);
    execute_instructions();
    run();

    return 0;
}

#ifdef MMIX_STANDALONE
int main(int argc, char *argv[]) {
    return mmix_main(argc, argv);
}
#endif