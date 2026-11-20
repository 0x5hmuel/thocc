#include "input_headers.h"
#include <stdlib.h>
#include <sys/epoll.h>

int create_epoll_instance(void) {
  int epfd = epoll_create1(0);

  if (epfd == -1) {
    perror("Unable to create epoll instance");
    return (-1);
  }

  printf("epoll instance created, waiting for events %d\n", EPOLLIN);

  return epfd;
}

int register_keyboard_epoll_inevents(int *key, int size,
                                     struct epoll_event ev) {
  int epoll = 0;
  int fd, i = 0;

  epoll = create_epoll_instance();
  if (epoll == -1)
    return -1;

  ev.events = EPOLLIN; // monitor read events

  while (i < size) {
    ev.data.fd = key[i];
    fd = epoll_ctl(epoll, EPOLL_CTL_ADD, key[i], &ev);
    if (fd == -1) {
      perror("Unable to open");
      return -1;
    }
    ++i;
  }

  return epoll;
}

int read_epoll_events(int epfd, struct epoll_event ev[]) {
  int event_count = 0;

  event_count = epoll_wait(epfd, ev, MAX_EVENTS, -1);

  if (event_count == -1) {
    perror("Unable to get event");
    exit(EXIT_FAILURE);
  }

  if (event_count == 0) {
    perror("");
    exit(EXIT_FAILURE);
  }

  printf("%d\n", event_count);
  return event_count;
}
