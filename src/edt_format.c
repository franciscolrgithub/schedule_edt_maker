#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include "edt_format.h"

/*
** Takes an edt_task as parameter and returns the string representation of
** that task
*/
char *task_to_str(struct edt_task *task)
{
    char *line = NULL;

    asprintf(&line, "[ ] | %02d:%02d - %02d:%02d | %s\n", task->start_time->tm_hour,
            task->start_time->tm_min, task->end_time->tm_hour,
            task->end_time->tm_min, task->name);

    return line;
}
