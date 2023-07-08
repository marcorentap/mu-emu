#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "riscv32.h"
#include "rv32bp.h"
#include "vmem.h"
#include "rv32exec.h"
#include "vm.h"

void rv32exec_add(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];
    vm->regfile[rd] = vm_rs1 + vm_rs2;
}

void rv32exec_sub(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];
    vm->regfile[rd] = vm_rs1 - vm_rs2;
}

void rv32exec_addi(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rd = rv32bp_rd(word);
    int32_t immi = rv32bp_immi(word);


    int32_t vm_rs1 = vm->regfile[rs1];
    vm->regfile[rd] = vm_rs1 + immi;
}

void rv32exec_xor(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];
    vm->regfile[rd] = vm_rs1 ^ vm_rs2;
}

void rv32exec_or(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);


    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];
    vm->regfile[rd] = vm_rs1 | vm_rs2;
}

void rv32exec_and(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];
    vm->regfile[rd] = vm_rs1 & vm_rs2;
}

void rv32exec_xori(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rd = rv32bp_rd(word);
    int32_t immi = rv32bp_immi(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    vm->regfile[rd] = vm_rs1 ^ immi;
}

void rv32exec_ori(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rd = rv32bp_rd(word);
    int32_t immi = rv32bp_immi(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    vm->regfile[rd] = vm_rs1 | immi;
}

void rv32exec_andi(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rd = rv32bp_rd(word);
    int32_t immi = rv32bp_immi(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    vm->regfile[rd] = vm_rs1 & immi;
}

void rv32exec_slli(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rd = rv32bp_rd(word);
    int8_t shamt = rv32bp_rs2(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    vm->regfile[rd] = vm_rs1 << shamt;
}

void rv32exec_srli(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rd = rv32bp_rd(word);
    uint8_t shamt = rv32bp_rs2(word);

    uint32_t vm_rs1 = vm->regfile[rs1];
    vm->regfile[rd] = vm_rs1 >> shamt;
}

void rv32exec_srai(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rd = rv32bp_rd(word);
    int32_t shamt = rv32bp_rs2(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    vm->regfile[rd] = (vm_rs1 >> shamt);
}

void rv32exec_sll(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];
    int32_t shamt = vm_rs2 & (0xff >> 3);
    vm->regfile[rd] = (vm_rs1 << shamt);
}

void rv32exec_srl(struct VM *vm, int32_t word) {
    uint8_t rs1 = rv32bp_rs1(word);
    uint8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);

    uint32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];
    int32_t shamt = vm_rs2 & (0xff >> 3);
    vm->regfile[rd] = (vm_rs1 >> shamt);
}

void rv32exec_sra(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];
    int32_t shamt = vm_rs2 & (0xff >> 3);
    vm->regfile[rd] = (vm_rs1 >> shamt);
}

void rv32exec_slti(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int32_t immi = rv32bp_immi(word);
    int8_t rd = rv32bp_rd(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    vm->regfile[rd] = (vm_rs1 < immi);
}

void rv32exec_slt(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];

    vm->regfile[rd] = (vm_rs1 < vm_rs2);
}

void rv32exec_auipc(struct VM *vm, int32_t word) {
    int8_t rd = rv32bp_rd(word);
    int32_t immu = rv32bp_immu(word);

    vm->regfile[rd] = vm->pc + immu;
}

void rv32exec_lui(struct VM *vm, int32_t word) {
    int8_t rd = rv32bp_rd(word);
    int32_t immu = rv32bp_immu(word);

    vm->regfile[rd] = immu;
}

void rv32exec_jal(struct VM *vm, int32_t word) {
    int8_t rd = rv32bp_rd(word);
    int32_t immj = rv32bp_immj(word);

    int32_t next_pc = vm->pc + 4;
    vm->pc += immj;
    vm->regfile[rd] = next_pc;
}

void rv32exec_jalr(struct VM *vm, int32_t word) {
    int8_t rd = rv32bp_rd(word);
    int8_t rs1 = rv32bp_rs1(word);
    int32_t immi = rv32bp_immi(word);

    int32_t next_pc = vm->pc + 4;
    int32_t vm_rs1 = vm->regfile[rs1];
    vm->pc = vm_rs1 + immi;
    vm->regfile[rd] = next_pc;
}

void rv32exec_beq(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int32_t immb = rv32bp_immb(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];

    if (vm_rs1 == vm_rs2) {
        vm->pc += immb;
    }
}

void rv32exec_bne(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int32_t immb = rv32bp_immb(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];

    if (vm_rs1 != vm_rs2) {
        vm->pc += immb;
    }
}

void rv32exec_blt(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int32_t immb = rv32bp_immb(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];

    if (vm_rs1 < vm_rs2) {
        vm->pc += immb;
    }
}

void rv32exec_bge(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int32_t immb = rv32bp_immb(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];

    if (vm_rs1 >= vm_rs2) {
        vm->pc += immb;
    }
}

void rv32exec_lw(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rd = rv32bp_rd(word);
    int32_t immi = rv32bp_immi(word);

    int32_t vm_rs1 = vm->regfile[rs1];

    vptr src = vm_rs1 + immi;
    if (src == 0x20000000) {
        // Mapped to stdin
        char *line = NULL;
        size_t n = 0;
        if (getline(&line, &n, stdin) == -1) {
            perror("Cannot getline for SW instruction");
            free(line);
            exit(-1);
        }

        int data = strtol(line, NULL, 10);
        vm->regfile[rd] = data;
        free(line);
    } else {
        int32_t *p = vm_mem(vm, src);
        vm->regfile[rd] = *p;
    }
}

void rv32exec_sw(struct VM *vm, int32_t word) {
    int8_t rs1 = rv32bp_rs1(word);
    int8_t rs2 = rv32bp_rs2(word);
    int8_t rd = rv32bp_rd(word);
    int32_t imms = rv32bp_imms(word);

    int32_t vm_rs1 = vm->regfile[rs1];
    int32_t vm_rs2 = vm->regfile[rs2];

    vptr dest = vm_rs1 + imms;
    if (dest == 0x20000000) {
        printf("%c", (char) vm_rs2);
    } else {
        int32_t *dest_p = vm_mem(vm, dest);
        *dest_p = vm_rs2;
    }
}

// A handy public facade
// Given instruction word and vm, execute the instruction on vm
void rv32exec(struct VM *vm, int32_t word) {
    const struct riscv32_ins *entry = riscv32_get_ins_entry(word);

    if (entry == NULL) {
        perror("Unknown instruction");
        exit(-1);
    }

    int32_t old_pc = vm->pc;
    entry->exec_func(vm, word);
    vm->regfile[0] = 0; // Restore x0
    if (vm->pc == old_pc) vm->pc += 4;
}
