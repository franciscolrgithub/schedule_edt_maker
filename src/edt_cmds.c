#include "edt_cmds.h"

#include <stdio.h>
#include <stdlib.h>

#include "edt_append.h"
#include "edt_file.h"
#include "edt_start.h"
#include "edt_task_list.h"

int start_command(char *argv[])
{
    struct edt_task *task = create_edt_task(atoi(argv[2]),
            atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    start(task);
    free_edt_task(task);
    return 0;
}

int append_command(char *argv[])
{
    struct edt_task *task = create_edt_task(atoi(argv[2]),
            atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    append(task);
    free_edt_task(task);
    return 0;
}

int backup_command(void)
{
    struct edt_task_list *list = tasks_from_file("today.schl");
    if (!list)
    {
        fprintf(stderr, "ERROR: Couldn't get tasks from file\n");
        return 1;
    }

    struct edt_task_list *p = list;

    if (!p->task)
    {
        fprintf(stderr, "ERROR: the first element has no task");
        free_edt_task_list(list);
        return 1;
    }

    start_backup(p->task, "backup.schl");
    p = p->next;

    while (p)
    {
        append_backup(p->task, "backup.schl");
        p = p->next;
    }

    free_edt_task_list(list);
    return 0;
}
