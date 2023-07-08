#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "rv32disasm.h"
#include "riscv32.h"
#include "rv32exec.h"
#include "vmem.h"
#include "vm.h"

off_t get_file_size(FILE* file) {
    struct stat *statbuf;
    if ((statbuf = malloc(sizeof(struct stat))) == NULL) {
        perror("Error allocating statbuf");
        exit(-1);
    }

    fstat(fileno(file), statbuf);
    off_t size = statbuf->st_size;
    free(statbuf);
    return size;
}

// Initialize VM
int vm_init(struct VM *self) {
    if ((self->regfile = calloc(REGISTER_COUNT, sizeof(vptr))) == NULL) {
        perror("Error allocating VM register file");
        exit(-1);
    }
    if ((self->seg_tbl = calloc(SEGTABLE_ENTRY_COUNT, sizeof(struct VM_ste))) == NULL) {
        perror("Error allocating VM register file");
        exit(-1);
    }

    self->pc = 0;

    return 0;
}

// Create VM
struct VM* vm_create() {
    struct VM* vm;
    if ((vm = malloc(sizeof(struct VM))) == NULL) {
        perror("Error allocating VM struct");
        exit(-1);
    }

    vm_init(vm);
    return vm;
}

// Frees VM allocated resources
int vm_free(struct VM *self) {
    int i;
    for (i = 0; i < SEGTABLE_ENTRY_COUNT; i++) {
        vptr seg = self->seg_tbl[i].start_addr;
        vm_segfree(self, seg);
    }

    free(self->regfile);
    free(self->seg_tbl);
}

// Execute program
int vm_load(struct VM *self, FILE* inst_file, FILE* data_file) {
    // Load inst segment
    if (inst_file != NULL) {
        off_t file_size = get_file_size(inst_file);
        vptr seg_p = vm_segalloc(self, 0x00000000, file_size);
        if (fread(vm_mem(self, seg_p), 1, file_size, inst_file) < file_size) {
            perror("Error writing instruction file to VM memory");
            exit(-1);
        }
    }

    // Load data segment
    if (data_file != NULL) {
        off_t file_size = get_file_size(data_file);
        vptr seg_p = vm_segalloc(self, 0x10000000, 0x10000);
        // data segment is initialized to ff
        memset(vm_mem(self, seg_p), 0xff, 0x10000);
        if (fread(vm_mem(self, seg_p), 1, file_size, data_file) < file_size) {
            perror("Error writing data file to VM memory");
            exit(-1);
        }
    }

    // Reset pc
    self->pc = 0x0;

    return 0;
}

int vm_regdump(struct VM *self) {
    int i;
    printf("PC: 0x%08x (inst %d)\n", self->pc, self->pc/4);
    for (i = 0; i < REGISTER_COUNT; i++) {
        if (i != 0 && i % 4 == 0) {
            printf("\n");
        }
        if (i < 10) {
            printf("x%d:  0x%08x ", i, self->regfile[i]);
        } else {
            printf("x%d: 0x%08x ", i, self->regfile[i]);
        }
    }

    printf("\n");
    return 0;
}

// Run all instructions, up to N instructions
int vm_run(struct VM *self, uint32_t N) {
    int i;
    struct VM_ste *inst_ste = vm_getste(self, 0);
    for (i = 0; i < N; i++) {
        int32_t *inst = vm_mem(self, self->pc);
        if (inst == NULL) break;
        rv32exec(self, *inst);

        // Reached end of instructions
        if (self->pc > inst_ste->end_addr) break;
    }
}

// Run one instruction
int vm_step(struct VM *self) {
    int32_t *inst = vm_mem(self, self->pc);
    rv32exec(self, *inst);
    return 0;
}
