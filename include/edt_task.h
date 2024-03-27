#ifndef EDT_TASK_H
#define EDT_TASK_H

#include <time.h>

struct edt_task
{
    struct tm *start_time;
    struct tm *end_time;
    char *name;
};

struct edt_task *create_edt_task(int hour1, int min1, int hour2, int min2,
                                 char *name);
void free_edt_task(struct edt_task *task);
int set_hour_minutes(struct tm *tm, int hour, int min);
void print_edt_task(struct edt_task *task);

#endif /* EDT_TASK_H */
