#include "edt_append.h"

#include <stdio.h>
#include <stdlib.h>

#include "edt_format.h"

int append(struct edt_task *task)
{
    FILE *today_file = fopen("today.schl", "a+");
    if (!today_file)
    {
        return -1;
    }

    char *line = task_to_str(task);

    fputs(line, today_file);

    free(line);
    fclose(today_file);

    return 0;
}

int append_backup(struct edt_task *task, char *filename)
{
    if (!filename)
    {
        fprintf(stderr, "ERROR: No filename given\n");
        return -1;
    }

    FILE *today_file = fopen(filename, "a+");
    if (!today_file)
    {
        return -1;
    }

    char *line = task_to_str(task);

    fputs(line, today_file);

    free(line);
    fclose(today_file);

    return 0;
}
