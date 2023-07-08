#ifndef RV32EXEC_H
#define RV32EXEC_H
#include <stdint.h>
#include "vm.h"

// Exec specific instruction
void rv32exec_add(struct VM *vm, int32_t word);
void rv32exec_sub(struct VM *vm, int32_t word);
void rv32exec_addi(struct VM *vm, int32_t word);
void rv32exec_xor(struct VM *vm, int32_t word);
void rv32exec_or(struct VM *vm, int32_t word);
void rv32exec_and(struct VM *vm, int32_t word);
void rv32exec_xori(struct VM *vm, int32_t word);
void rv32exec_ori(struct VM *vm, int32_t word);
void rv32exec_andi(struct VM *vm, int32_t word);
void rv32exec_slli(struct VM *vm, int32_t word);
void rv32exec_srli(struct VM *vm, int32_t word);
void rv32exec_srai(struct VM *vm, int32_t word);
void rv32exec_sll(struct VM *vm, int32_t word);
void rv32exec_srl(struct VM *vm, int32_t word);
void rv32exec_sra(struct VM *vm, int32_t word);
void rv32exec_slti(struct VM *vm, int32_t word);
void rv32exec_slt(struct VM *vm, int32_t word);
void rv32exec_auipc(struct VM *vm, int32_t word);
void rv32exec_lui(struct VM *vm, int32_t word);
void rv32exec_jal(struct VM *vm, int32_t word);
void rv32exec_jalr(struct VM *vm, int32_t word);
void rv32exec_beq(struct VM *vm, int32_t word);
void rv32exec_bne(struct VM *vm, int32_t word);
void rv32exec_blt(struct VM *vm, int32_t word);
void rv32exec_bge(struct VM *vm, int32_t word);
void rv32exec_lw(struct VM *vm, int32_t word);
void rv32exec_sw(struct VM *vm, int32_t word);

// A handy public facade
// Given instruction word and vm, execute the instruction on vm
void rv32exec(struct VM *vm, int32_t word);

#endif
