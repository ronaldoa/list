#include "log.h"
#include "mem.h"
#include "slist.h"
#include "interface.h"
#include "sysconf.h"

BOOL is_del(void *data)
{
    if (*(int *)data == 5)
    {
        return TRUE;
    }

    return FALSE;
}

void print(void *data)
{
    MY_PRINTF(DBG_INFO,"%d \n", (*(int*)data));
}

void list_print(SLIST_T *slist,print_func print)
{
    for (SLIST_NODE_T *head = slist->head; head!= NULL; head = head->next)
    {
        if (slist->print)
        {
            print(head->data);
        }
    }
}


int main()
{
    SLIST_T *list = NULL;
    int *node = NULL;
    int i;

    init_sys();

    if (NULL == (list = list_create()))
    {
        return 0;
    }
    list->print = list_print;

    for (i = 0; i < 10; i++)
    {
       node = (int *)MY_MALLOC(sizeof(int));
       if (NULL == node)
       {
            return 0;
       }

       *node = i;
       list_add_order(list,(void *)node);
    }

    list->print(list,print);

    list_del_node(list,is_del);

    list->print(list,print);
    list = list_reverse(list);

    list->print(list,print);
}
