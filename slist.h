#ifndef SLIST_H__
#define SLIST_H__

#include "types.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef BOOL (*del_func)(void *data);
typedef void (*print_func)(void *data);

typedef struct _slist_node
{
    struct _slist_node *next;
    void *data;
}SLIST_NODE_T;

typedef struct _slist
{
    INT lenth;
    SLIST_NODE_T *head;
    void* (*dup)(void *(ptr));
    BOOL (*compare)(void *data, void *value);
    void (*release)(struct _slist *list);
    void (*free_node)(void *);
    void (*print)(struct _slist *list,print_func print);
}SLIST_T;

SLIST_T *list_create();
void list_release(SLIST_T *slist);
INT list_add_head(SLIST_T *slist, void *data);
INT list_add_tail(SLIST_T *slist, void *data);
INT list_add_order(SLIST_T *slist, void *data);
INT list_add_order2(SLIST_T *slist, void *data);
INT list_del_node(SLIST_T  *slist,del_func func);
INT list_del_node2(SLIST_T  *slist,del_func func);
SLIST_T *list_reverse(SLIST_T *list);


#ifdef __cplusplus
}
#endif


#endif
