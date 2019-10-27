#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _list_t
{
    struct _list_node_t * prev; /*!< prev */
    struct _list_node_t * next; /*!< next */
}list_t;

typedef struct _item_list_t
{
    int index;
    int value;
    list_t * list;
}item_list_t;

#define list_entry(ptr, type, number)    \
                    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->number)))

int main()
{
    item_list_t item;
    item.index = 2;
    item.value = 5;

    item_list_t * plist;
    plist = list_entry(&(item.list),item_list_t,list);

    printf("plist->value = %d\n",plist->value);
    printf("plist->index = %d\n",plist->index);

    printf("size = %d\n",sizeof(item));

    return 0;
}
