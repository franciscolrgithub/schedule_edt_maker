#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edt_format.h"

/*
** Takes an edt_task as parameter and returns the string representation of
** that task
*/
char *task_to_str(struct edt_task *task)
{
    // we compute the length of the final string by adding the length
    // of the base, the digits for the times and the length of the task's name
    char *base = "[ ] | : - : | \n";
    size_t total = strlen(base) + 8 + strlen(task->name);

    char *line = calloc(total + 1, sizeof(char));

    sprintf(line, "[ ] | %02d:%02d - %02d:%02d | %s\n", task->start_time->tm_hour,
            task->start_time->tm_min, task->end_time->tm_hour,
            task->end_time->tm_min, task->name);

    return line;
}
