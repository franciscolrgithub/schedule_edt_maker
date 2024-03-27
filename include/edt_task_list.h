#ifndef EDT_TASK_LIST_H
#define EDT_TASK_LIST_H

#include "edt_task.h"

/*
** a linked list with sentinel
** the task of the sentinel is null
*/
struct edt_task_list
{
    struct edt_task *task;
    struct edt_task_list *next;
};

struct edt_task_list *create_task_list(void);
void push_back(struct edt_task_list *list, struct edt_task *task);
void free_edt_task_list(struct edt_task_list *list);

#endif /* ! EDT_TASK_LIST_H */
