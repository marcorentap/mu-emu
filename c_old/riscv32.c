#include <stdint.h>
#include "riscv32.h"
#include "rv32bp.h"
#include <stdio.h>

// Check header file for interface details.
// Only descriptions for internal functions and implementation details can be found here

// Create an array of indexes with range 0..size-1
void create_idx_filter(int idx_filter[]) {
    int i;
    for (i = 0; i < RISCV32_INS_COUNT; i++) {
        idx_filter[i] = 1;
    }
}

// Debugging function, prints the mnemonic that is valid inside the filter
void print_filtered_ins(int idx_filter[]) {
    int i;
    printf("Filter: ");
    for (i = 0; i < RISCV32_INS_COUNT; i++) {
        if (idx_filter[i] > 0) {
            printf("%s ", riscv32_ins_table[i].mnemonic);
        }
    }
    printf("\n");
}

// Invalid elements are -1
int count_valid_index(int idx_filter[]) {
    int nvalid = 0;
    int i;
    for (i = 0; i < RISCV32_INS_COUNT; i++) {
        if (idx_filter[i] >= 0)
            nvalid++;
    }
    
    return nvalid;
}

// Get first valid index
int get_first_valid_index(int idx_filter[]) {
    int i;
    for (i = 0; i < RISCV32_INS_COUNT; i++) {
        if (idx_filter[i] >= 0)
            return i;
    }

    return -1;
}

// Filter instruction by opcode
int riscv32_filter_opcode(int idx_filter[], uint8_t opcode) {
    int i;
    for (i = 0; i < RISCV32_INS_COUNT; i++) {
        if (idx_filter[i] >= 0) {
            if (riscv32_ins_table[i].opcode != opcode)
                idx_filter[i] = -1;
        }
    }
    return count_valid_index(idx_filter);
}

// Filter instruction by funct3
int riscv32_filter_funct3(int idx_filter[], uint8_t funct3) {
    int i;
    for (i = 0; i < RISCV32_INS_COUNT; i++) {
        if (idx_filter >= 0) {
            if (riscv32_ins_table[i].funct3 != funct3)
                idx_filter[i] = -1;
        }
    }
    return count_valid_index(idx_filter);
}

// Filter instruction by funct7
int riscv32_filter_funct7(int idx_filter[], uint8_t funct7) {
    int i;
    for (i = 0; i < RISCV32_INS_COUNT; i++) {
        if (idx_filter >= 0) {
            if (riscv32_ins_table[i].funct7 != funct7)
                idx_filter[i] = -1;
        }
    }
    return count_valid_index(idx_filter);
}

// Filters the instruction table from riscv32.h until 1 instruction is found
const int riscv32_get_ins_idx(uint8_t opcode, uint8_t funct3, uint8_t funct7) {
    int nvalid;
    int valid_idx;
    int idx_filter[RISCV32_INS_COUNT];
    create_idx_filter(idx_filter);

    nvalid = riscv32_filter_opcode(idx_filter, opcode);
    if (nvalid > 1) {
        nvalid = riscv32_filter_funct3(idx_filter, funct3);
    }

    if (nvalid > 1) {
        nvalid = riscv32_filter_funct7(idx_filter, funct7);
    }

    if (nvalid == 1) {
        valid_idx = get_first_valid_index(idx_filter);
    } else {
        return -1;
    }

    return valid_idx;
}

const struct riscv32_ins* riscv32_get_ins_entry(int32_t word) {
    int8_t opcode = rv32bp_opcode(word);
    int8_t funct3  = rv32bp_funct3(word);
    int8_t funct7  = rv32bp_funct7(word);
    const int ins_idx = riscv32_get_ins_idx(opcode, funct3, funct7);
    
    if (ins_idx == -1) return NULL;
    else return &riscv32_ins_table[ins_idx];
}
