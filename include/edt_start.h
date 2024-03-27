#ifndef EDT_START_H
#define EDT_START_H

#include "edt_task.h"

int start(struct edt_task *task);
int start_backup(struct edt_task *task, char *filename);

#endif /* ! EDT_START_H */
