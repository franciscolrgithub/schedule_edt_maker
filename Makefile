CC = gcc
CPPFLAGS = -Iinclude/
CFLAGS = -Wall -Werror -Wextra -Wvla -pedantic -std=c99 -g -fsanitize=address
LDLIBS = -fsanitize=address

SRC = src/edt_maker.c src/edt_start.c src/edt_task.c src/edt_format.c \
	  src/edt_append.c src/edt_task_list.c src/edt_file.c src/edt_cmds.c
OBJ = ${SRC:.c=.o}

edt_maker: $(OBJ)
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

clean:
	$(RM) edt_maker $(OBJ)
