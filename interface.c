#include "interface.h"
#include "list.h"
#include "mem.h"

INT compare(LIST_NODE * cur)
{
    if (100 <= cur->data)
        return TRUE;
    else
        return FALSE;
}

INT del_fun(LIST_NODE *node)
{
    if (node->data == 5)
        return TRUE;
    else
        return FALSE;
}
