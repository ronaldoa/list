#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "list.h"
#include "types.h"
#include "mem.h"

#ifndef MY_MALLOC
#define MY_MALLOC mem_malloc
#endif
#ifndef MY_FREE
#define MY_FREE mem_free
#endif

INT compare ( LIST_NODE *node);
INT del_fun( LIST_NODE *node);

#endif
