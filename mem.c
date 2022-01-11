#include "mem.h"
#include "types.h"
#include "cc.h"

U8_T ram_heap[MEM_SIZE_ALIGNED + 2*(SIZEOF_STRUCT_MEM) + MEM_ALIGNMENT];
#define RAM_HEAP_POINT ram_heap

U8_T *ram;
MEM_T *ram_end;

MEM_T *lfree;

INT init_mem()
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

    lfree = (MEM_T *)(void *)ram;

    return TRUE;
}

void * mem_malloc(MEM_SIZE_T size)
{
    MEM_SIZE_T ptr, ptr2;
    MEM_T *mem, *mem2;
    if (0 == size)
    {
        return NULL;
    }

    size = ALIGN_SIZE(size);

    if (size < MIN_SIZE)
    {
        size = MIN_SIZE;
    }

    if (size > MEM_SIZE_ALIGNED)
    {
        return NULL;
    }

    for (ptr = (MEM_SIZE_T)((U8_T *)lfree - ram); ptr < MEM_SIZE_ALIGNED - size;
            ptr = ((MEM_T *)(void*)&ram[ptr])->next)
    {
        mem = (MEM_T *)(void *)&ram[ptr];
        if (!mem->used && (mem->next -(ptr + SIZEOF_STRUCT_MEM)) >= size)
        {
            if (mem->next -(ptr + SIZEOF_STRUCT_MEM) >= size + SIZEOF_STRUCT_MEM + MIN_SIZE_ALIGNED)
            {
                ptr2 = ptr + SIZEOF_STRUCT_MEM + size;

                mem2 = (MEM_T *)(void *)&ram[ptr2];
                mem2->used = 0;

                mem2->next = mem->next;
                mem2->prev = ptr;

                mem->next = ptr2;
                mem->used = 1;
                if (mem2->next != MEM_SIZE_ALIGNED)
                {
                    ((MEM_T *)(void *)&ram[mem2->next])->prev = ptr2;
                }
            }
            else
            {
                mem->used = 1;
            }
        }

        if (lfree == mem)
        {
            MEM_T * cur = mem;
            while (cur->used && cur != ram_end)
            {
                cur = (MEM_T *)(void*)&ram[cur->next];
            }
            lfree = cur;
        }

        return (U8_T*)mem+SIZEOF_STRUCT_MEM;
    }

    return NULL;
}
