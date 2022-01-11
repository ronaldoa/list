#include <stdio.h>
#include "list.h"
#include "interface.h"
#include "sysconf.h"
int main()
{
    int i;
    LIST *list = NULL;

    init_sys();

    list = init_list();

    if (NULL == list)
    {
        printf("error malloc\r\n");
        return 0;
    }

    for (i = 0; i < 10; i++)
    {
        insert_list(list,i,compare);
    }

    print_list(list);

    return 0;
}
