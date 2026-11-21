#include "linux/input_headers.h"
#include <linux/input.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * main - entry point to the program
 * Returns: 0 on success exit
 */

int main(void) {
  glob_t g;
  struct epoll_event ev, events[MAX_EVENTS];
  struct input_event input_ev;
  int kbds;
  int i = 0;

  printf("Welcome to THocc!\n");

  kbds = find_keyboards(&g);

  if (kbds != 0) {
    fprintf(stderr, "Failed to find input devices");
    return 1;
  }

  Keyboards keyboards = open_keyboards(&g);

  int epoll_fd = register_keyboard_epoll_inevents(&keyboards, &ev);

  if (epoll_fd != -1) {
    while (1) {
      int e = read_epoll_events(epoll_fd, events);
      for (int n = 0; n < e; n++) {
        int fd = events[n].data.fd;
        ssize_t count = read_event(fd, &input_ev);
        if (count == (ssize_t)-1) {
          continue;
        }
        printf("%d %d %d\n", input_ev.value, input_ev.code, input_ev.type);
      }
    }
  }

  while (i < keyboards.size) {
    close(keyboards.slots[i]);
    ++i;
  }
  free(keyboards.slots);

  return 0;
}
