#ifndef EDT_APPEND_H
#define EDT_APPEND_H

#include "edt_task.h"

int append(struct edt_task *task);
int append_backup(struct edt_task *task, char *filename);

#endif /* ! EDT_APPEND_H */
