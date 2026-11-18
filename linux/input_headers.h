#ifndef INPUT_HEADERS_H
#define INPUT_HEADERS_H

#define MAX_EVENTS 10

#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <glob.h>
#include <linux/input.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
  int size;
  int *slots;
} Keyboards;

int read_input(void);
Keyboards open_keyboards(glob_t g);
int register_keyboard_epoll_inevents(int *, int, struct epoll_event);
glob_t find_keyboards(void);
int read_epoll_events(int, struct epoll_event[]);

#endif // INPUT_HEADERS_H
