#ifndef RV32BP_H
#define RV32BP_H
#include <stdint.h>
#include "riscv32.h"

// rv32bp -> RISC-V 32 bit binary parser

// Get the start..end bits of word. The range starts from 0, and is inclusive.
int32_t rv32bp_bitrange(int32_t word, int32_t start, int32_t end);

// Get the opcode bits of word
int32_t rv32bp_opcode(int32_t word);

// Get the funct3 bits of word
int8_t rv32bp_funct3(int32_t word);

// Get the funct7 bits of word
int8_t rv32bp_funct7(int32_t word);

// Get the rd bits of word
uint8_t rv32bp_rd(int32_t word);

// Get the rs1 bits of word
uint8_t rv32bp_rs1(int32_t word);

// Get the rs2 bits of word
uint8_t rv32bp_rs2(int32_t word);

// Get i-type immediate value of word
int32_t rv32bp_immi(int32_t word);

// Get s-type immediate value of word
int32_t rv32bp_imms(int32_t word);

// Get b-type immediate value of word
int32_t rv32bp_immb(int32_t word);

// Get u-type immediate value of word
int32_t rv32bp_immu(int32_t word);

// Get j-type immediate value of word
int32_t rv32bp_immj(int32_t word);

#endif
