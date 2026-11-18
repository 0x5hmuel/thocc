#include "input_headers.h"
#include <fcntl.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

int create_epoll_instance() {
  int epfd = epoll_create1(0);
  if (epfd == -1) {
    perror("Unable to create epoll instance");
    exit(EXIT_FAILURE);
  }

  printf("epoll instance created, waiting for events %d\n", EPOLLIN);

  return epfd;
}

int register_keyboard_epoll_inevents(int *key) {
  int epoll = 0;
  int fd, i = 0;
  struct epoll_event ev;

  epoll = create_epoll_instance();
  if (epoll == -1)
    return -1;

  ev.events = EPOLLIN; // monitor read events

  while (key[i]) {
    fd = epoll_ctl(key[i], EPOLLIN, key[i], &ev);
    if (fd == -1) {
      perror("Unable to open");
      return -1;
    }
    ev.data.fd = fd;
    ++i;
  }

  return epoll;
}

int read_epoll_events(int epfd, struct epoll_event ev) {
  struct epoll_event events[MAX_EVENTS];
  int event_count = 0;

  while (1) {
    event_count = epoll_wait(epfd, &ev, MAX_EVENTS, -1);

    if (event_count == -1) {
      perror("Unable to get event");
      exit(EXIT_FAILURE);
    }

    return event_count;
  }
}
