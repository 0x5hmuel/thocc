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
    fprintf(stderr, "Failed to find input devices\n");
    return 1;
  }

  Keyboards keyboards = open_keyboards(&g);

  int epoll_fd = register_keyboard_epoll_inevents(&keyboards, &ev);

  if (epoll_fd != -1) {
    while (1) {
      int e = read_epoll_events(epoll_fd, events);

      if (e == -1) {
        if (errno == EINTR)
          continue;
        else {
          perror("Unable to get event");
          exit(EXIT_FAILURE);
        }
      }

      for (int n = 0; n < e; n++) { // loop up to the number of fd ready for I/O
        int fd = events[n].data.fd;
        ssize_t count = read_event(fd, &input_ev);
        int error = errno;

        if (count == (ssize_t)-1) {
          if (errno == ENODEV) {
            fprintf(stderr, "Error: %s\n", strerror(error));
            perror("Device disconnected");
            if (deregister_epoll_event(fd, &ev, epoll_fd) == -1) {
              fprintf(stderr, "Error: %s\n", strerror(error));
              perror("Unable to disconnect device");
            } else
              printf("Successfully disconnected");
            continue;
          }
        } else
          printf("Keypress: %d\n ", input_ev.code);
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
