#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "vmem.h"
#include "vm.h"

// Get VM segment table entry
struct VM_ste* vm_getste(struct VM *vm, vptr ptr) {
    int i;
    for (i = 0; i < SEGTABLE_ENTRY_COUNT; i++) {
        struct VM_ste *ste = &(vm->seg_tbl[i]);
        if (ptr >= ste->start_addr && ptr <= ste->end_addr)
            return ste;
    }
    return NULL;
}

// Translate VM virtual address to real address
void *vm_mem(struct VM *vm, vptr addr) {
    struct VM_ste *ste = vm_getste(vm, addr);
    if (ste == NULL) {
        printf("addr: %08x\n", addr);
        perror("Error translating virtual address. Not within a segment");
        exit(-1);
    }

    vptr offset = addr - ste->start_addr;
    return ste->ptr + offset;
}

// Allocate memory segment
vptr vm_segalloc(struct VM *vm, vptr start_addr, uint32_t size) {
    struct VM_ste *ste;

    int i;
    for (i = 0; i < SEGTABLE_ENTRY_COUNT; i++) {
        ste = &(vm->seg_tbl[i]);
        if (ste->used == 0) {
            break;
        }
    }

    if ((ste->ptr = malloc(size)) == NULL && size != 0) {
        perror("Error allocating VM memory segment");
        exit(-1);
    }

    ste->start_addr = start_addr;
    ste->end_addr = start_addr + size - 1;
    ste->size = size;
    ste->used = 1;

    return ste->start_addr;
}

// Deallocate VM memory segment
void vm_segfree(struct VM *vm, vptr addr) {
    struct VM_ste *ste = vm_getste(vm, addr);
    if (ste == NULL) {
        perror("Error freeing segment. addr not within a segment");
        exit(-1);
    }

    if (ste->start_addr != addr) {
        perror("Error freeing segment. addr not a segment");
        exit(-1);
    }

    free(ste->ptr);
    ste->ptr = NULL;
    ste->used = 0;
}

// Dump memory content, segment by segment
// Up to max_count bytes per segment
void vm_memdump(struct VM *vm, uint32_t max_count) {
    int i;
    for (i = 0; i < SEGTABLE_ENTRY_COUNT; i++) {
        int j;
        struct VM_ste *ste = &(vm->seg_tbl[i]);
        if (ste->used == 0) continue;

        // Print header
        printf("Segment %d\n", i);
        printf("Addr     | ");
        for (j = 0; j < 16; j++) {
            if (j % 2 == 0)
                printf(" ");
            printf("%02x", j);
        }
        printf("\n");
        printf("_________|_________________________________________\n");

        for (j = 0; j < ste->size && j < max_count; j++) {
            vptr vp = ste->start_addr + j;

            if (j != 0 && j % 16 == 0) {
                printf("\n");
            }

            if (j == 0 || j % 16 == 0) {
                printf("%08x | ", vp);
            }

            if (j % 2 == 0) {
                printf(" ");
            }
            unsigned char *p = vm_mem(vm, vp);
            printf("%02x", *p);
        }
        printf("\n\n");
    }
}
