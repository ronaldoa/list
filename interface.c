#include "interface.h"
#include "mem.h"

INT compare(INT data, INT cur)
{
    if (data <= cur)
        return TRUE;
    else
        return FALSE;
}
