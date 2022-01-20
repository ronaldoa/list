#ifndef _CC_H
#define _CC_H
#include "types.h"

#define MEM_ALIGNMENT 4
#define ALIGNED MEM_ALIGNMENT
#define MIN_SIZE 12

#define MEM_SIZE (1024*1024)
#define MIN_SIZE_ALIGNED ALIGN_SIZE(MIN_SIZE)

#define ALIGN_BUFFER(size) ((size) + ALIGNED - 1)

#define ALIGN_SIZE(size) (((size) + ALIGNED -1) & ~(ALIGNED -1))

#define ALIGN_MEM(addr) (void *)(((MEM_SIZE_T)(addr) + ALIGNED - 1) & ~(MEM_SIZE_T)(ALIGNED -1))

#define SIZEOF_STRUCT_MEM ALIGN_SIZE(sizeof(MEM_T))

#define DECLARE_MEM(mem, size) U8_T mem[ALIGNE_BUFFER(size)]

#define MEM_SIZE_ALIGNED ALIGN_SIZE(MEM_SIZE)


#endif
