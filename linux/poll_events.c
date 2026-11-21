#include "input_headers.h"

int create_epoll_instance(void) {
  int epfd = epoll_create1(0);

  if (epfd == -1) {
    perror("Unable to create epoll instance");
    return (-1);
  }

  printf("epoll instance created, waiting for events %d\n", EPOLLIN);

  return epfd;
}

int register_keyboard_epoll_inevents(Keyboards *key, struct epoll_event *ev) {
  int epoll = 0;
  int ctrl_int, i = 0;

  epoll = create_epoll_instance();
  if (epoll == -1)
    return -1;

  ev->events = EPOLLIN; // monitor read events

  while (i < key->size) {
    ev->data.fd = key->slots[i];

    ctrl_int = epoll_ctl(epoll, EPOLL_CTL_ADD, key->slots[i], ev);

    if (ctrl_int == -1) {
      fprintf(stderr, "Unable to add input device.\n");
      continue; // skip if the keyboard cannot be registered. IMO this is to be
                // logged into the systemd log
    }
    ++i;
  }

  return epoll;
}

int read_epoll_events(int epfd, struct epoll_event *ev) {
  int event_count = 0;

  event_count = epoll_wait(epfd, ev, MAX_EVENTS, -1);

  if (event_count == -1) {
    perror("Unable to get event");
    exit(EXIT_FAILURE);
  }

  return event_count;
}
