#include <stdio.h>
#include "list.h"
#include "interface.h"
#include "sysconf.h"
int main()
{
    int i;
    LIST *list = NULL;

    init_sys();

    list = list_init();

    if (NULL == list)
    {
        printf("error malloc\r\n");
        return 0;
    }

    for (i = 0; i < 10; i++)
    {
        list_insert_node(list,i,compare);
    }

    list_print(list);

    list_remove_node(list,del_fun);

    list_print(list);

    return 0;
}
