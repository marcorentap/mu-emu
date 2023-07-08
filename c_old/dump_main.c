#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rv32disasm.h"
#include "riscv32.h"
#include "vm.h"
#include "vmem.h"

int print_registers(struct VM *vm) {

    int i;
    for (i = 0; i < REGISTER_COUNT; i++) {
        printf("x%d: 0x%08x\n", i, vm->regfile[i]);
    }
}

int main(int argc, char* argv[]) {
    FILE *inst_file = NULL;
    FILE *data_file = NULL;
    int n_inst;

    if (argc < 3) {
        exit(-1);
    }

    if (argc == 3) {
        inst_file = fopen(argv[1], "r");
        n_inst = strtol(argv[2], NULL, 10);
    }

    if (argc == 4) {
        inst_file = fopen(argv[1], "r");
        data_file = fopen(argv[2], "r");
        n_inst = strtol(argv[3], NULL, 10);
    }

    struct VM *vm = vm_create();
    vm_load(vm, inst_file, data_file);

    vm_run(vm, n_inst);
    vm_regdump(vm);
    vm_memdump(vm, 0xa0);
    vm_free(vm);
    return 0;
}
