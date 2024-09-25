#include <stdio.h>
#include <stdint.h>
#include "mmix.h"


uint64_t PC = 0;          
uint8_t memory[MEM_SIZE];
uint64_t registers[256];


// Function to decode and execute a single instruction
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
        case TRAP:
            // Implement trap instruction
            break;
        case FCMP:
            // Implement floating point compare
            break;
        case FDIV:
            // Implement floating point divide
            break;
        case FADD:
            // Implement floating point add
            break;
        case SETH:
            registers[ra] = (uint64_t)rb << 48;
            break;
        case OR:
            registers[ra] = registers[rb] | registers[rc];
            break;
        case ADDU:
            registers[ra] = registers[rb] + registers[rc];
            break;
        case SUBU:
            registers[ra] = registers[rb] - registers[rc];
            break;
        case MULU:
            registers[ra] = registers[rb] * registers[rc];
            break;
        case DIVU:
            if (registers[rc] != 0) {
                registers[ra] = registers[rb] / registers[rc];
            } else {
                // Handle division by zero
            }
            break;
        case FLOT:
            // Implement float conversion
            break;
        case FREM:
            // Implement floating point remainder
            break;
        case FSQRT:
            // Implement floating point square root
            break;
        case LDSF:
            // Implement load short float
            break;
        case STSF:
            // Implement store short float
            break;
        case PUSHJ:
            // Implement push and jump
            break;
        case UNSAVE:
            // Implement unsave registers
            break;
        case SAVE:
            // Implement save registers
            break;
        case SYNC:
            // Implement synchronize
            break;
        case RESUME:
            // Implement resume after interrupt
            break;
        default:
            printf("Unknown opcode: 0x%02X\n", opcode);
            break;
    }
}

// Main loop for fetch-decode-execute cycle
void run() {
    while (1) {
        uint32_t instruction = (memory[PC] << 24) |
                               (memory[PC + 1] << 16) |
                               (memory[PC + 2] << 8) |
                               memory[PC + 3];
        PC += 4;
        execute_instruction(instruction);
    }
}

// Load binary program into memory
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
    run();  // Start the emulation

    return 0;
}

#ifdef MMIX_STANDALONE
int main(int argc, char *argv[]) {
    return mmix_main(argc, argv);
}
#endif