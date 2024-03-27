#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edt_append.h"
#include "edt_start.h"
#include "edt_task_list.h"
#include "edt_file.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <command> ...\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0)
    {
        // usage: ./edt_maker start hour1 min1 hour2 min2 name
        //              0       1     2    3     4    5    6
        struct edt_task *task = create_edt_task(atoi(argv[2]),
                atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
        start(task);
        free_edt_task(task);
    }

    else if (strcmp(argv[1], "append") == 0)
    {
        // usage: ./edt_maker append hour1 min1 hour2 min2 name
        //              0       1     2    3     4    5    6
        struct edt_task *task = create_edt_task(atoi(argv[2]),
                atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
        append(task);
        free_edt_task(task);
    }

    else if (strcmp(argv[1], "backup") == 0)
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
    }

    return 0;
}
