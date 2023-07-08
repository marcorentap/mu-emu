#ifndef RV32DISASM_H
#define RV32DISASM_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rv32bp.h"
#include "riscv32.h"

// Check header file for interface details.
// Only descriptions for internal functions and implementation details can be found here

/*
const struct riscv32_ins* get_ins_entry(int32_t word) {
    int8_t opcode = rv32bp_opcode(word);
    int8_t funct3  = rv32bp_funct3(word);
    int8_t funct7  = rv32bp_funct7(word);
    const int ins_idx = riscv32_get_ins_idx(opcode, funct3, funct7);
    
    if (ins_idx == -1) return NULL;
    else return &riscv32_ins_table[ins_idx];
}
*/

// Disassemble R-type instruction
void rv32disasm_r(char *buf, int32_t word) {
    int8_t rd = rv32bp_rd(word);
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t opcode = rv32bp_opcode(word);

    const struct riscv32_ins *entry = riscv32_get_ins_entry(word);
    if (entry != NULL) {
        char *mnemonic = entry->mnemonic;
        if (opcode == 0b0010011) {
            // Shift instructions
            sprintf(buf, "%s x%d, x%d, %d", mnemonic, rd, rs1, rs2);
            return;
        } else {
            sprintf(buf, "%s x%d, x%d, x%d", mnemonic, rd, rs1, rs2);
            return;
        }
    }

    strcpy(buf, "unknown instruction");
}

// Disassemble I-type instruction
void rv32disasm_i(char *buf, int32_t word) {
    int8_t rd = rv32bp_rd(word);
    int8_t rs1 = rv32bp_rs1(word);
    int32_t immi = rv32bp_immi(word);
    int8_t opcode = rv32bp_opcode(word);

    const struct riscv32_ins *entry = riscv32_get_ins_entry(word);
    if (entry != NULL) {
        char *mnemonic = entry->mnemonic;
        if (opcode == 0b0000011) {
            // Load instructions
            sprintf(buf, "%s x%d, %d(x%d)", mnemonic, rd, immi, rs1);
            return;
        } else if (opcode == 0b0010011) {
            // Logic instructions
            sprintf(buf, "%s x%d, x%d, %d", mnemonic, rd, rs1, immi);
            return;
        } else if (opcode == 0b1100111) {
            // jalr, weirdo
            sprintf(buf, "%s x%d, %d(x%d)", mnemonic, rd, immi, rs1);
            return;
        }
    }

    strcpy(buf, "unknown instruction");
}

// Disassemble S-type instruction
void rv32disasm_s(char *buf, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int32_t imms = rv32bp_imms(word);
    int8_t opcode = rv32bp_opcode(word);

    const struct riscv32_ins* entry = riscv32_get_ins_entry(word);
    if (entry != NULL) {
        char *mnemonic = entry->mnemonic;
        if (opcode == 0b0100011) {
            // Shift instructions
            sprintf(buf, "%s x%d, %d(x%d)", mnemonic, rs2, imms, rs1);
            return;
        }
    }

    strcpy(buf, "unknown instruction");
}

// Disassemble B-type instruction
void rv32disasm_b(char *buf, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int32_t immb = rv32bp_immb(word);
    int8_t opcode = rv32bp_opcode(word);

    const struct riscv32_ins* entry = riscv32_get_ins_entry(word);
    if (entry != NULL) {
        char *mnemonic = entry->mnemonic;
        if (opcode == 0b1100011) {
            // Branch instructions
            sprintf(buf, "%s x%d, x%d, %d", mnemonic, rs1, rs2, immb);
            return;
        }
    }

    strcpy(buf, "unknown instruction");
}

// Disassemble U-type instruction
void rv32disasm_u(char *buf, int32_t word) {
    int8_t rd = rv32bp_rd(word);
    int32_t immu = rv32bp_immu(word);
    int8_t opcode = rv32bp_opcode(word);

    const struct riscv32_ins* entry = riscv32_get_ins_entry(word);
    if (entry != NULL) {
        char *mnemonic = entry->mnemonic;
        sprintf(buf, "%s x%d, %d", mnemonic, rd, immu);
        return;
    }

    strcpy(buf, "unknown instruction");
}

// Disassemble J-type instruction
void rv32disasm_j(char *buf, int32_t word) {
    int8_t rd = rv32bp_rd(word);
    int32_t immj = rv32bp_immj(word);
    int8_t opcode = rv32bp_opcode(word);

    const struct riscv32_ins* entry = riscv32_get_ins_entry(word);
    if (entry != NULL) {
        char *mnemonic = entry->mnemonic;
        sprintf(buf, "%s x%d, %d", mnemonic, rd, immj);
        return;
    }

    strcpy(buf, "unknown instruction");
}

// A handy public facade
// Given instruction word, determine the type then use the proper disassembly function
void rv32disasm(char *buf,int32_t word) {
    const struct riscv32_ins *entry = riscv32_get_ins_entry(word);

    if (entry == NULL) {
        strcpy(buf, "unknown instruction");
        return;
    }

    switch (entry->ins_type) {
        case RISCV32_R:
            rv32disasm_r(buf, word);
            break;
        case RISCV32_I:
            rv32disasm_i(buf, word);
            break;
        case RISCV32_S:
            rv32disasm_s(buf, word);
            break;
        case RISCV32_B:
            rv32disasm_b(buf, word);
            break;
        case RISCV32_U:
            rv32disasm_u(buf, word);
            break;
        case RISCV32_J:
            rv32disasm_j(buf, word);
            break;
        default:
            strcpy(buf, "unknown instruction");
    }
}
#endif
