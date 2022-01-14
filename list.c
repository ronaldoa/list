#include "list.h"
#include "mem.h"
#include "interface.h"

LIST *list_init()
{
    LIST *list = (LIST*)MY_MALLOC(sizeof(LIST));
    if (NULL == list)
    {
        return NULL;
    }
    list->head = NULL;
    list->len = 0;

    return list;
}

void list_print(LIST *head)
{
    LIST_NODE *temp = NULL;
    for (temp = head->head; temp != NULL; temp = temp->next)
    {
        printf("%d ",temp->data);
    }

    printf("len = %d \n",head->len);
}

LIST* list_add_node(LIST *ref_head, int data, insert insert_func)
{
    LIST_NODE *pre = NULL;
    LIST_NODE *current = NULL;
    LIST_NODE *new_node = NULL;

    if(NULL == ref_head)
        return NULL;

    for (current = ref_head->head;current != NULL && !insert_func(current);)
    {
        pre = current;
        current = pre->next;
    }

    INIT_LIST_NODE(new_node,data,LIST_NODE);

    INSERT_LIST_NODE(pre,current,ref_head,new_node);

    ref_head->len++;

    return ref_head;
}

LIST* list_del_node(LIST* ref_head, del del_func)
{
    LIST_NODE *pre = NULL;
    LIST_NODE *current = NULL;

    if (NULL == ref_head)
    {
        return NULL;
    }

    for (current = ref_head->head; current != NULL;)
    {
        if (del_func(current))
        {
            if (pre == NULL)
                ref_head->head = current->next;
            else
                pre->next = current->next;

            MY_FREE(current);
            ref_head->len--;
        }
        else
        {
            pre = current;
        }

        current = pre->next;
    }

    return ref_head;
}




LIST *list_insert_node(LIST *ref_head, int data, insert insert_func)
{
    LIST_NODE **link = NULL;
    LIST_NODE *current = NULL;
    LIST_NODE *new_node = NULL;

    if (NULL == ref_head)
    {
        return NULL;
    }

    for (link = &(ref_head->head); (current = *link) != NULL; link =&(current->next))
    {
        if (insert_func(current))
            break;
    }


    INIT_LIST_NODE(new_node, data, LIST_NODE);

    new_node->next = current;
    *link = new_node;

    ref_head->len++;

    return ref_head;
}



LIST* list_remove_node(LIST* ref_head, del del_func)
{

    LIST_NODE **current = NULL;
    LIST_NODE *entry = NULL;

    if (NULL == ref_head)
    {
        return NULL;
    }

    for (current = &(ref_head->head); (entry = *current) != NULL;)
    {

        if (del_func(entry))
        {
            *current = entry->next;
            MY_FREE(*current);
            ref_head->len--;
        }
        else
        {
            current = &((*current)->next);
        }
    }

    return ref_head;
}




