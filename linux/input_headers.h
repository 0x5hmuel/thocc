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
Keyboards open_keyboards(glob_t *g);
int register_keyboard_epoll_inevents(Keyboards *, struct epoll_event *);
int find_keyboards(glob_t *g);
int read_epoll_events(int, struct epoll_event[]);
ssize_t read_event(int, struct input_event *);

#endif // INPUT_HEADERS_H
