#ifndef RISCV32_H
#define RISCV32_H
#include <stdint.h>
#include <stddef.h>
#include "rv32exec.h"

#define RISCV32_INS_COUNT 37 // 10 instructions are omitted
#define INULL -1 // Custom null, since 0 is a valid value but not 1111...1111

typedef enum riscv32_ins_type {
    RISCV32_R,
    RISCV32_I,
    RISCV32_S,
    RISCV32_B,
    RISCV32_U,
    RISCV32_J
} riscv32_ins_type;

struct riscv32_ins {
    char *mnemonic;
    enum riscv32_ins_type ins_type;
    uint8_t opcode;
    uint8_t funct3;
    uint8_t funct7;
    void (*exec_func)(struct VM*, int32_t);
};

static const struct riscv32_ins riscv32_ins_table[] = {
    {"lui",     RISCV32_U,     0b0110111,      INULL,       INULL    ,  rv32exec_lui},
    {"auipc",   RISCV32_U,     0b0010111,      INULL,       INULL    ,  rv32exec_auipc},
    {"jal",     RISCV32_J,     0b1101111,      INULL,       INULL    ,  rv32exec_jal},
    {"jalr",    RISCV32_I,     0b1100111,      0b000,       INULL    ,  rv32exec_jalr},
    {"beq",     RISCV32_B,     0b1100011,      0b000,       INULL    ,  rv32exec_beq},
    {"bne",     RISCV32_B,     0b1100011,      0b001,       INULL    ,  rv32exec_bne},
    {"blt",     RISCV32_B,     0b1100011,      0b100,       INULL    ,  rv32exec_blt},
    {"bge",     RISCV32_B,     0b1100011,      0b101,       INULL    ,  rv32exec_bge},
    {"bltu",    RISCV32_B,     0b1100011,      0b110,       INULL    ,  NULL},
    {"bgeu",    RISCV32_B,     0b1100011,      0b111,       INULL    ,  NULL},
    {"lb",      RISCV32_I,     0b0000011,      0b000,       INULL    ,  NULL},
    {"lh",      RISCV32_I,     0b0000011,      0b001,       INULL    ,  NULL},
    {"lw",      RISCV32_I,     0b0000011,      0b010,       INULL    ,  rv32exec_lw},
    {"lbu",     RISCV32_I,     0b0000011,      0b100,       INULL    ,  NULL},
    {"lhu",     RISCV32_I,     0b0000011,      0b101,       INULL    ,  NULL},
    {"sb",      RISCV32_S,     0b0100011,      0b000,       INULL    ,  NULL},
    {"sh",      RISCV32_S,     0b0100011,      0b001,       INULL    ,  NULL},
    {"sw",      RISCV32_S,     0b0100011,      0b010,       INULL    ,  rv32exec_sw},
    {"addi",    RISCV32_I,     0b0010011,      0b000,       INULL    ,  rv32exec_addi},
    {"slti",    RISCV32_I,     0b0010011,      0b010,       INULL    ,  rv32exec_slti},
    {"sltiu",   RISCV32_I,     0b0010011,      0b011,       INULL    ,  NULL},
    {"xori",    RISCV32_I,     0b0010011,      0b100,       INULL    ,  rv32exec_xori},
    {"ori",     RISCV32_I,     0b0010011,      0b110,       INULL    ,  rv32exec_ori},
    {"andi",    RISCV32_I,     0b0010011,      0b111,       INULL    ,  rv32exec_andi},
    {"slli",    RISCV32_R,     0b0010011,      0b001,       0b0000000,  rv32exec_slli},
    {"srli",    RISCV32_R,     0b0010011,      0b101,       0b0000000,  rv32exec_srli},
    {"srai",    RISCV32_R,     0b0010011,      0b101,       0b0100000,  rv32exec_srai},
    {"add",     RISCV32_R,     0b0110011,      0b000,       0b0000000,  rv32exec_add},
    {"sub",     RISCV32_R,     0b0110011,      0b000,       0b0100000,  rv32exec_sub},
    {"sll",     RISCV32_R,     0b0110011,      0b001,       0b0000000,  rv32exec_sll},
    {"slt",     RISCV32_R,     0b0110011,      0b010,       0b0000000,  rv32exec_slt},
    {"sltu",    RISCV32_R,     0b0110011,      0b011,       0b0000000,  NULL},
    {"xor",     RISCV32_R,     0b0110011,      0b100,       0b0000000,  rv32exec_xor},
    {"srl",     RISCV32_R,     0b0110011,      0b101,       0b0000000,  rv32exec_srl},
    {"sra",     RISCV32_R,     0b0110011,      0b101,       0b0100000,  rv32exec_sra},
    {"or",      RISCV32_R,     0b0110011,      0b110,       0b0000000,  rv32exec_or},
    {"and",     RISCV32_R,     0b0110011,      0b111,       0b0000000,  rv32exec_and},
};

// Get the ins index in the table given opcode, funct3 and funct7
const int riscv32_get_ins_idx(uint8_t opcode, uint8_t funct3, uint8_t funct7);
const struct riscv32_ins* riscv32_get_ins_entry(int32_t word);
#endif
