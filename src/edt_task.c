#define _POSIX_C_SOURCE 200809L

#include "edt_task.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct edt_task *create_edt_task(int hour1, int min1, int hour2, int min2,
                                 char *name)
{
    struct tm *start_time = malloc(sizeof(struct tm));
    if (!start_time)
    {
        return NULL;
    }

    struct tm *end_time = malloc(sizeof(struct tm));
    if (!end_time)
    {
        free(start_time);
        return NULL;
    }

    int shm1 = set_hour_minutes(start_time, hour1, min1);
    if (shm1 == -1)
    {
        free(start_time);
        free(end_time);
        return NULL;
    }

    int shm2 = set_hour_minutes(end_time, hour2, min2);
    if (shm2 == -1)
    {
        free(start_time);
        free(end_time);
        return NULL;
    }

    struct edt_task *new_task = malloc(sizeof(struct edt_task));
    if (!new_task)
    {
        free(start_time);
        free(end_time);
        return NULL;
    }

    new_task->start_time = start_time;
    new_task->end_time = end_time;
    new_task->name = strdup(name);

    return new_task;
}

void free_edt_task(struct edt_task *task)
{
    free(task->start_time);
    free(task->end_time);
    free(task->name);

    free(task);
}

int set_hour_minutes(struct tm *tm, int hour, int min)
{
    if (!tm || hour > 23 || hour < 0 || min > 59 || min < 0)
    {
        return -1;
    }

    tm->tm_hour = hour;
    tm->tm_min = min;

    return 0;
}

void print_edt_task(struct edt_task *task)
{
    if (!task)
    {
        return;
    }

    printf("Printing Task %p\n", (void*) task);
    printf("Hour: %d Min: %d\n", task->start_time->tm_hour, task->end_time->tm_min);
    printf("Name: %s\n", task->name);
}
