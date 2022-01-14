#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "mem.h"

typedef struct _node
{
    int data;
    struct _node *next;
}LIST_NODE;

typedef struct _list
{
    int len;
    LIST_NODE  *head;
}LIST;

#define INIT_LIST(HEAD,TYPE)\
    do{\
        if (NULL != (HEAD = (TYPE *)MY_MALLOC(sizeof(TYPE))))\
        {\
            (HEAD)->head = NULL;\
            (HEAD)->len = 0;\
        }\
    }while(0)
#define INIT_LIST_NODE(NEW,VAL,TYPE)\
    do{\
        if (NULL != (NEW = ((TYPE *)MY_MALLOC(sizeof(TYPE)))))\
        {\
            (NEW)->data = VAL;\
            (NEW)->next = NULL;\
        }\
    }while(0)

#define INSERT_LIST_NODE(pre,current,ref_head,new_node)\
    do{\
        if (NULL == pre)\
        {\
            ref_head->head = new_node;\
        }\
        else\
        {\
            pre->next = new_node;\
        }\
        new_node->next = current;\
    }while(0)

typedef INT (*insert)(LIST_NODE *node);
typedef INT (*del)(LIST_NODE *list_node);

LIST* list_insert_node(LIST *ref_head, int data, insert insert_func);

LIST* list_add_node(LIST *ref_head, int data, insert insert_func);

LIST* list_del_node(LIST* ref_head, del del_func);

LIST* list_remove_node(LIST* ref_head, del del_func);

void list_print(LIST *head);

LIST * list_init();

#endif


