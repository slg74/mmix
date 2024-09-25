#ifndef MMIX_H
#define MMIX_H

#include <stdint.h>

//#define MEM_SIZE 0x100000000  // 4GB of memory
#define MEM_SIZE 0x1000  // 4KB of memory

extern uint64_t registers[256];
extern uint8_t memory[MEM_SIZE];
extern uint64_t PC;

typedef enum {
    ADD    = 0x20,   // Add
    SUB    = 0x21,   // Subtract
    MUL    = 0x22,   // Multiply
    DIV    = 0x23,   // Divide
    LDB    = 0x80,   // Load byte
    STB    = 0x90,   // Store byte
    JMP    = 0xF0,   // Jump
    TRAP   = 0x00,   // Trap
    FCMP   = 0x02,   // Floating point compare
    FDIV   = 0x03,   // Floating point divide
    FADD   = 0x07,   // Floating point add
    SETH   = 0x48,   // Set high bits
    OR     = 0x52,   // Bitwise OR
    ADDU   = 0x58,   // Add unsigned
    SUBU   = 0x5F,   // Subtract unsigned
    MULU   = 0x67,   // Multiply unsigned
    DIVU   = 0x6E,   // Divide unsigned
    FLOT   = 0x74,   // Float
    FREM   = 0x75,   // Floating point remainder
    FSQRT  = 0x78,   // Floating point square root
    LDSF   = 0x85,   // Load short float
    STSF   = 0xAC,   // Store short float
    PUSHJ  = 0xBC,   // Push and jump
    UNSAVE = 0xD8,   // Unsave registers
    SAVE   = 0xE0,   // Save registers
    SYNC   = 0xF8,   // Synchronize
    RESUME = 0xCF    // Resume after interrupt
} Opcode;


void execute_instruction(uint32_t instruction);

#endif // MMIX_H
