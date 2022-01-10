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

INT mem_init();

#ifdef __cplusplus
}
#endif

#endif