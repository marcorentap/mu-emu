#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "riscv32.h"
#include "rv32bp.h"

// Check header file for interface details.
// Only descriptions for internal functions and implementation details can be found here

// Slices bits from instruction word, with sign extension
int32_t rv32bp_bitrange(int32_t word, int32_t start, int32_t end) {
    int32_t lmask = ~0 << start; // Mask from start to leftmost bit
    int32_t rmask = ~((~0 << end) << 1); // Mask from start to rightmost bit
    int32_t mask = lmask & rmask;
    return (mask & (int32_t) word) >> start;
}

int32_t rv32bp_opcode(int32_t word) {
    return rv32bp_bitrange(word, 0, 6);
}

int8_t rv32bp_funct3(int32_t word) {
    return rv32bp_bitrange(word, 12, 14);
}

int8_t rv32bp_funct7(int32_t word) {
    return rv32bp_bitrange(word, 25, 31);
}

uint8_t rv32bp_rd(int32_t word) {
    return rv32bp_bitrange(word, 7, 11);
}

uint8_t rv32bp_rs1(int32_t word) {
    return rv32bp_bitrange(word, 15, 19);
}

uint8_t rv32bp_rs2(int32_t word) {
    return rv32bp_bitrange(word, 20, 24);
}

// immstart and immend correspond to the indexes of imm's bits imm[immstart:immend];
// bitstart correspond to the bit position of the slice relative to the word
int32_t get_imm_partition(int32_t word, int8_t immstart, int8_t immend, int8_t bitstart) {
    int8_t length = immend - immstart + 1;
    int32_t mask = ~(-1 << (length));
    return (rv32bp_bitrange(word, bitstart, bitstart + length - 1) & mask) << immstart;
}

// Similar to get_imm_partition, but if immend is the leftmost bit of imm, then use this
int32_t get_leftmost_imm_partition(int32_t word, int8_t immstart, int8_t immend, int8_t bitstart) {
    int8_t length = immend - immstart + 1;
    int32_t mask = ~(-1 << length);
    // Don't mask to keep leftmost 1's for negative numbers
    return rv32bp_bitrange(word, bitstart, bitstart + length - 1) << immstart;
}

int32_t rv32bp_imms(int32_t word) {
    int32_t bits0_4 = get_imm_partition(word, 0, 4, 7);
    int32_t bits5_11 = get_leftmost_imm_partition(word, 5, 11, 25);
    return bits0_4 + bits5_11;
}

int32_t rv32bp_immi(int32_t word) {
    return get_leftmost_imm_partition(word, 0, 11, 20);
}

int32_t rv32bp_immb(int32_t word) {
    int32_t bits1_4 = get_imm_partition(word, 1, 4, 8);
    int32_t bits5_10 = get_imm_partition(word, 5, 10, 25);
    int32_t bits11 = get_imm_partition(word, 11, 11, 7);
    int32_t bits12 = get_leftmost_imm_partition(word, 12, 12, 31);

    return bits1_4 + bits5_10 + bits11 + bits12;
}

int32_t rv32bp_immu(int32_t word) {
    int32_t bits12_31 = get_leftmost_imm_partition(word, 12, 31, 12);
    return bits12_31;
}

int32_t rv32bp_immj(int32_t word) {
    int32_t bits1_10 = get_imm_partition(word, 1, 10, 21);
    int32_t bits11 = get_imm_partition(word, 11, 11, 20);
    int32_t bits12_19 = get_imm_partition(word, 12, 19, 12);
    int32_t bits20 = get_leftmost_imm_partition(word, 20, 20, 31);

    return bits1_10 + bits11 + bits12_19 + bits20;
}
