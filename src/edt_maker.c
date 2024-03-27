#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edt_append.h"
#include "edt_cmds.h"
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
        return start_command(argv);
    }

    else if (strcmp(argv[1], "append") == 0)
    {
        // usage: ./edt_maker append hour1 min1 hour2 min2 name
        //              0       1     2    3     4    5    6
        return append_command(argv);
    }

    else if (strcmp(argv[1], "backup") == 0)
    {
        // usage: ./edt_maker backup
        return backup_command();
    }

    return 0;
}
