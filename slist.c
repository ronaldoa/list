#include "slist.h"
#include "log.h"
#include "interface.h"


SLIST_T *list_create()
{
    SLIST_T *list = NULL;
    list = (SLIST_T *) MY_MALLOC(sizeof(SLIST_T));
    if (NULL == list)
    {
        return NULL;
    }

    list->compare = NULL;
    list->dup = NULL;
    list->free_node = NULL;
    list->release = NULL;
    list->head = NULL;
    list->lenth = 0;

    return list;
}

void list_release(SLIST_T *slist)
{
    SLIST_NODE_T *current = NULL;
    SLIST_NODE_T *next = NULL;

    if (NULL == slist)
    {
        return;
    }

    for (current = slist->head; current != NULL;current = next)
    {
        next = current->next;

        if (slist->free_node != NULL)
        {
            slist->free_node(current->data);
        }
        else
        {
            MY_FREE(current);
        }

        MY_FREE(current);
    }

    MY_FREE(slist);
    slist->lenth = 0;

    return;
}

INT list_add_head(SLIST_T *slist, void *data)
{
    SLIST_NODE_T *new_node = NULL;
    if (NULL == slist)
    {
        return FALSE;
    }
    new_node = (SLIST_NODE_T *)MY_MALLOC(sizeof(SLIST_NODE_T));
    if (NULL == new_node)
    {
        return FALSE;
    }
    new_node->data = data;

    new_node->next = slist->head->next;
    slist->head->next = new_node;

    slist->lenth++;
    return TRUE;
}

INT list_add_tail(SLIST_T *slist, void *data)
{
    SLIST_NODE_T *current = NULL;
    SLIST_NODE_T *new_node = NULL;

    if (NULL == slist)
    {
        return TRUE;
    }

    for (current = slist->head; current->next != NULL; current = current->next)
        ;

    if (NULL == (new_node = (SLIST_NODE_T *)MY_MALLOC(sizeof(SLIST_NODE_T))))
    {
        return FALSE;
    }

    new_node->data = data;
    new_node->next = NULL;
    current->next= new_node;

    slist->lenth++;
    return TRUE;
}


INT list_add_order(SLIST_T *slist, void *data)
{
    SLIST_NODE_T **ptr = NULL;
    SLIST_NODE_T *current = NULL;
    SLIST_NODE_T *new_node = NULL;

    for (ptr = &slist->head; (current = *ptr) != NULL; )
    {
        if (slist->compare != NULL)
        {
            if (slist->compare(data,current->data))
            {
                break;
            }
        }

        ptr = &((*ptr)->next);
    }

    new_node = (SLIST_NODE_T *)MY_MALLOC(sizeof(SLIST_NODE_T));
    if (NULL == new_node)
    {
        return FALSE;
    }
    new_node->data = data;

    new_node->next = current;
    *ptr = new_node;

    slist->lenth++;

    return TRUE;
}

INT list_add_order2(SLIST_T *slist, void *data)
{
    SLIST_NODE_T *pre = NULL;
    SLIST_NODE_T *current = NULL;
    SLIST_NODE_T *new_node = NULL;

    for (current = slist->head; current != NULL; pre = current, current = pre->next)
    {
        if (NULL != slist->compare)
        {
            if (slist->compare(data, current->data))
            {
                break;
            }
        }
    }

    new_node = (SLIST_NODE_T *)MY_MALLOC(sizeof(SLIST_NODE_T));
    if (NULL == new_node)
    {
        return FALSE;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (pre == NULL)
    {
        slist->head = new_node;
    }
    else
    {
        pre->next = new_node;
    }

    new_node->next = current;

    slist->lenth++;

    return TRUE;

}




INT list_del_node(SLIST_T  *slist,del_func func)
{
    SLIST_NODE_T **ptr = NULL;
    SLIST_NODE_T *current = NULL;

    if (NULL == slist)
    {
        return FALSE;
    }

    for (ptr = &(slist->head); (current = *ptr) != NULL;)
    {
        if (func(current->data))
        {
            *ptr = current->next;
            slist->free_node(current->data);
            MY_FREE(current);
            slist->lenth--;
        }
        else
        {
            ptr = &((*ptr)->next);
        }
    }

    return TRUE;
}


INT list_del_node_2(SLIST_T  *slist,del_func func)
{
    SLIST_NODE_T *pre = NULL;
    SLIST_NODE_T *current = NULL;
    if (NULL == slist || NULL == func)
    {
        return FALSE;
    }

    for (current = slist->head; current != NULL;current = pre->next)
    {
        if (func(current->data))
        {
            if (NULL == pre)
            {
                slist->head = current->next;
                slist->free_node(current->data);
                MY_FREE(current);
                slist->lenth--;
            }
            else
            {
                pre->next = current->next;
            }
        }
        else
        {
            pre = current;
        }

    }

    return TRUE;
}


SLIST_T *list_reverse(SLIST_T *list)
{
    SLIST_T *head = NULL;
    SLIST_NODE_T *pre = NULL;
    SLIST_NODE_T *next = NULL;

    head = list;
    pre = list->head;
    next = pre->next;

    for (;next != NULL; next = pre->next)
    {
        pre->next = next->next;
        next->next = head->head;
        head->head = next;
    }
    pre->next = NULL;

    return head;
}
