#ifndef RV32DISASM_H
#define RV32DISASM_H
#include <stdint.h>

// Disassemble a given word of instruction. Write into the buffer
void rv32disasm(char *buf, uint32_t word);
#endif
