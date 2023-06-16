#ifndef VMEM_H
#define VMEM_H
#include <stdint.h>
#include "vm.h"

#define SEGTABLE_ENTRY_COUNT 8

// Virtual pointer
typedef uint32_t vptr;

// Segment Table Entry
// Stores info about a memory segment
struct VM_ste {
    void *ptr; // Pointer to allocated block in real memory
    vptr start_addr; // In virtual memory
    vptr end_addr; // In virtual memory
    vptr size;
    int used; // 0 indicates free, 1 indicates used
};

struct VM;

// Get VM segment table entry
struct VM_ste *vm_getste(struct VM *vm, vptr addr);

// Translate VM virtual address to real address
void *vm_mem(struct VM *vm, vptr addr);

// Allocate VM memory segment
vptr vm_segalloc(struct VM *vm, vptr start_addr, uint32_t size);

// Deallocate VM memory segment
void vm_segfree(struct VM *vm, vptr addr);

// Dump memory content
void vm_memdump(struct VM *vm, uint32_t maxcount);
#endif
