
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define LIST_POISON1    NULL
#define LIST_POISON2    NULL

/*
 * Simple doubly linked list implementation.
 *
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

struct list_head {
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_add(struct list_head *new,
                  struct list_head *prev,
                  struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}


/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}


/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}

/**
 * list_del - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    entry->next = LIST_POISON1;
    entry->prev = LIST_POISON2;
}

/**
 * list_replace - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
static inline void list_replace(struct list_head *old,
                struct list_head *new)
{
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}

static inline void list_replace_init(struct list_head *old,
                    struct list_head *new)
{
    list_replace(old, new);
    INIT_LIST_HEAD(old);
}

/**
 * list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 */
static inline void list_del_init(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
    INIT_LIST_HEAD(entry);
}

/**
 * list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 */
static inline void list_move(struct list_head *list, struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void list_move_tail(struct list_head *list,
                  struct list_head *head)
{
    __list_del(list->prev, list->next);
    list_add_tail(list, head);
}

/**
 * list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static inline int list_is_last(const struct list_head *list,
                const struct list_head *head)
{
    return list->next == head;
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}

/**
 * list_empty_careful - tests whether a list is empty and not being modified
 * @head: the list to test
 *
 * Description:
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * NOTE: using list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * if another CPU could re-list_add() it.
 */
static inline int list_empty_careful(const struct list_head *head)
{
    struct list_head *next = head->next;
    return (next == head) && (next == head->prev);
}

#define __list_for_each(pos, head) \
                    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_first_entry(ptr, type, member) \
                    list_entry((ptr)->next, type, member)
#define list_entry(ptr, type, number)    \
                    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->number)))


typedef struct _item_t
{
    int index;
    int value;
    struct list_head list;
}item_t;

uint8_t data[128];

int main(void)
{
    item_t * pitem = (item_t *)data;
    item_t * pitem_start = (item_t *)data;

    struct list_head * list_old = &pitem->list;

    for(int i = 0;i < 8; i++)
    {
        pitem->index = i;
        pitem->value = 0x80 + i;
        INIT_LIST_HEAD(&pitem->list);

        if(i != 0)
        {
            list_add(&pitem->list,list_old);
        }
        list_old = &pitem->list;

        pitem ++;
    }

    // 遍历
    item_t * item_pos;
    struct list_head * list_pos;
    __list_for_each(list_pos,&pitem_start->list)
    {
        item_pos = list_entry(list_pos,item_t,list);
        printf("item->index = %02x\n",item_pos->index);
        printf("item->value = %02x\n",item_pos->value);
    }

#if 0
    // 删除特定数据
    // 这种情况是没有办法删除的... data顺序结构
    __list_for_each(list_pos,&pitem_start->list)
    {
        item_pos = list_entry(list_pos,item_t,list);
        if(item_pos->index == 0x03)
        {
            item_pos->index = 0xFF;
            item_pos->value = 0xFF;
            list_del(&item_pos->list);
        }
    }

    // 遍历
    __list_for_each(list_pos,&pitem_start->list)
    {
        item_pos = list_entry(list_pos,item_t,list);
        printf("item->index = %02x\n",item_pos->index);
        printf("item->value = %02x\n",item_pos->value);
    }
#endif

    return 0;
}
