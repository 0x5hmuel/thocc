#include "linux/input_headers.h"
#include <unistd.h>

/**
 *
 *
 */
int main(void) {
  struct epoll_event ev, events[MAX_EVENTS];

  printf("Welcome to THocc!\n");

  glob_t g = find_keyboards();
  Keyboards keyboard_fd = open_keyboards(g);
  int i = 0;

  int epoll_fd =
      register_keyboard_epoll_inevents(keyboard_fd.slots, keyboard_fd.size, ev);

  if (epoll_fd != -1) {
    while (1) {
      int e = read_epoll_events(epoll_fd, events);
      printf("Epoll events: %d\n", e);
    }
  }

  while (i < keyboard_fd.size) {
    close(keyboard_fd.slots[i]);
    ++i;
  }
  free(keyboard_fd.slots);

  return 0;
}
