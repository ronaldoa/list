#ifndef MEM_H_
#define MEM_H_

#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    MEM_SIZE_T next;
    MEM_SIZE_T prev;
    U8_T used;
}MEM_T;

INT init_mem();
void* mem_malloc(MEM_SIZE_T size);
BOOL mem_free(void *mem);
void mem_plug_holes(MEM_T *mem);

#ifdef __cplusplus
}
#endif

#endif
