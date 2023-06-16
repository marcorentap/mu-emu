#ifndef VM_H
#define VM_H
#include <stdint.h>
#include <stdio.h>

#define REGISTER_COUNT 32
#define MEMORY_SIZE 0xffff

struct VM {
    int32_t *regfile;
    int32_t pc;
    struct VM_ste *seg_tbl;
};

// Create VM
struct VM* vm_create();

// Frees VM allocated resources
int vm_free(struct VM *self);

// Load instruction file and data file into memory
int vm_load(struct VM *self, FILE* inst_file, FILE* data_file);

/// Run the vm, up to N instructions
int vm_run(struct VM *self, uint32_t N);

// Run one instruction
int vm_step(struct VM *self);

// Dump registers
int vm_regdump(struct VM *self);
#endif
