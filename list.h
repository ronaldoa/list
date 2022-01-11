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

typedef int (*insert)(int data,int value);
typedef int (*del)(LIST_NODE *list_node);

LIST* add_list(LIST *ref_head, int data, insert insert_func);

LIST* insert_list(LIST *ref_head, int data, insert insert_func);

LIST* list_del(LIST* ref_head, del del_func);

LIST* list_del_1(LIST* ref_head, del del_func);

void print_list(LIST *head);

LIST * init_list();

#endif


