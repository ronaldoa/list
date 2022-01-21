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

BOOL list_compare(void *data, void *value)
{
    return (*(int *)data) >= (*(int *)value);
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

void list_free(void *data)
{
    MY_FREE(data);
}

int test_slist()
{
    SLIST_T *list = NULL;
    int *node = NULL;
    int i;
    int array[10] = {9,5,67,3,4,2,3,1,0,7};

#if 1
////////////////////////////////////////////
    if (NULL == (list = list_create()))
    {
        printf("error%d\r\n",__LINE__);
        return 0;
    }
    list->print = list_print;
    list->compare = list_compare;
    list->free_node = list_free;
////////////////////////////////////////////////////
    for (i = 0; i< 9;i++)
    {
        node = (int *)MY_MALLOC(sizeof(int));
        if (NULL == node)
        {
            printf("error%d\r\n",__LINE__);
            return 0;
        }

        *node = array[i];
        list_add_order(list,(void *)node);
    }

    list_print(list,print);
//////////////////////////////////////////////////
    list_release(list);
#endif

#if 1
//////////////////////////////////////////////////
    if (NULL == (list = list_create()))
    {
        printf("error%d\r\n",__LINE__);
        return 0;
    }
    list->print = list_print;
    list->compare = list_compare;
    list->free_node = list_free;

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
    /////////////////////////////////////////////////

    list_del_node(list,is_del);

    list->print(list,print);
    ///////////////////////////////////////////////////
    list = list_reverse(list);

    list->print(list,print);
    ///////////////////////////////////////////////////
#endif
}
