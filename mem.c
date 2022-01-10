#include "mem.h"
#include "types.h"
#include "cc.h"

U8_T ram_heap[MEM_SIZE_ALIGNED + 2*(SIZEOF_STRUCT_MEM) + MEM_ALIGNMENT];
#define RAM_HEAP_POINT ram_heap

U8_T *lfree;
U8_T *ram;
MEM_T *ram_end;


INT mem_init()
{
    MEM_T *mem;
    ram = (U8_T *)ALIGN_MEM(RAM_HEAP_POINT);

    mem = (MEM_T*) ram;
    mem->next = MEM_SIZE_ALIGNED;
    mem->prev = 0;
    mem->used = 0;

    ram_end = (MEM_T*)(void*) &ram[MEM_SIZE_ALIGNED];
    ram_end->next = MEM_SIZE_ALIGNED;
    ram_end->prev = MEM_SIZE_ALIGNED;
    ram_end->used = 1;


    return TRUE;
}

