#define _POSIX_C_SOURCE 200809L
#include "edt_file.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edt_task_list.h"

typedef int (*matcher_func)(char *);

int is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int is_time(char *str)
{
    if (strlen(str) < 5)
    {
        return 0;
    }

    if (!is_digit(str[0]) || !is_digit(str[1]))
    {
        return 0;
    }

    if (str[2] != ':')
    {
        return 0;
    }

    if (!is_digit(str[3]) || !is_digit(str[4]))
    {
        return 0;
    }

    return 1;
}

size_t find_char(char *str, char c)
{
    size_t i = 0;
    while (str[i] != 0 && str[i] != c)
    {
        i++;
    }

    return i;
}
size_t find_matching(char *str, matcher_func matcher)
{
    size_t i = 0;
    while (str[i] != 0 && !matcher(str + i))
    {
        i++;
    }

    return i;
}

void set_time_from_str(char *str, struct edt_task *task, int nb_time)
{
    str[2] = 0;
    int hour = atoi(str);
    str[2] = ':';
    char bckp = str[5];
    str[5] = 0;
    int min = atoi(str + 3);
    str[5] = bckp;

    if (nb_time == 1)
    {
        set_hour_minutes(task->start_time, hour, min);
    }
    else
    {
        set_hour_minutes(task->end_time, hour, min);
    }
}

void set_name_from_str(char *str, struct edt_task *task)
{
    size_t len = strlen(str);
    char *new_name = calloc(len + 1, sizeof(char));
    if (!new_name)
    {
        fprintf(stderr, "ERROR: Couldn't allocate new name with calloc()");
        return;
    }

    // - 1 because we skip the \n
    strncpy(new_name, str, len - 1);

    free(task->name);
    task->name = new_name;
}

struct edt_task *stotask(char *str)
{
    if (!str)
    {
        fprintf(stderr, "ERROR: Tried to stotask(NULL)\n");
        return NULL;
    }

    struct edt_task *res = create_edt_task(0, 0, 0, 0, "");

    size_t time_i = find_matching(str, is_time);
    if (str[time_i] == 0)
    {
        fprintf(stderr, "ERROR: Start time not found\n");
        free_edt_task(res);
        return NULL;
    }

    set_time_from_str(str + time_i, res, 1);

    time_i += 5;

    time_i += find_matching(str + time_i, is_time);
    if (str[time_i] == 0)
    {
        fprintf(stderr, "ERROR: End time not found\n");
        free_edt_task(res);
        return NULL;
    }

    set_time_from_str(str + time_i, res, 2);

    time_i += find_char(str + time_i, '|');

    time_i += 2;
    set_name_from_str(str + time_i, res);

    return res;
}

struct edt_task_list *tasks_from_file(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "ERROR: Couldn't read from file %s", filename);
        return NULL;
    }

    struct edt_task_list *list = create_task_list();
    if (!list)
    {
        fprintf(stderr, "ERROR: Couldn't create the new task_list\n");
        return NULL;
    }

    char *line = NULL;
    size_t read = 0;
    size_t nb_line = 1;
    while (getline(&line, &read, file) != -1)
    {
        struct edt_task *new_task = stotask(line);
        if (!new_task)
        {
            fprintf(stderr, "ERROR: Couldn't stotask() at line %ld", nb_line);
            // free linked-list
            return NULL;
        }

        push_back(list, new_task);

        nb_line++;
    }
    free(line);
    fclose(file);
    return list;
}
