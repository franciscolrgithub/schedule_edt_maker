#include "edt_task_list.h"

#include <stdio.h>
#include <stdlib.h>

struct edt_task_list *create_task_list(void)
{
    struct edt_task_list *new = malloc(sizeof(struct edt_task_list));
    if (!new)
    {
        fprintf(stderr, "ERROR: Couldn't allocate the new edt_task_list with \
                with malloc()\n");
        return NULL;
    }

    new->task = NULL;
    new->next = NULL;

    return new;
}

void push_back(struct edt_task_list *list, struct edt_task *task)
{
    if (!list || !task)
    {
        fprintf(stderr, "WARNG: Tried to push_back a null list or task\n");
        return;
    }

    if (!list->task)
    {
        list->task = task;
        return;
    }
    struct edt_task_list *new = malloc(sizeof(struct edt_task_list));
    if (!new)
    {
        fprintf(stderr, "WARNG: Couldn't malloc() the new task_list");
        return;
    }

    new->next = NULL;
    new->task = task;

    // we know for sure that list is not null
    struct edt_task_list *p = list;
    while (p->next)
    {
        p = p->next;
    }

    // p->next is null, so we're at the end of the linked list
    p->next = new;;
    // we make sure that "task" is the last one
    // we could just suppose the programmer make sure task->next is NULL
    if (new->next)
    {
        fprintf(stderr, "WARNG: push_back() called with a non null task->next\
                , making task->next NULL...");
        new->next = NULL;
        fprintf(stderr, "done\n");
    }
}

void free_edt_task_list(struct edt_task_list *list)
{
    if (!list)
    {
        return;
    }

    struct edt_task_list *p = list;
    struct edt_task_list *p2 = p;
    while (p)
    {
        p = p->next;
        free_edt_task(p2->task);
        free(p2);
        p2 = p;
    }
}

void print_edt_task_list(struct edt_task_list *list)
{
    if (!list)
    {
        return;
    }

    struct edt_task_list *p = list;
    while (p)
    {
        print_edt_task(p->task);
        p = p->next;
    }
}
