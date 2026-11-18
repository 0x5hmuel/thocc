#include "input_headers.h"
#include <stdio.h>

int read_input(void) {
  int *keyboard_fd = open_keyboard();
  struct input_event ev;

  if (keyboard_fd == -1) {
    fprintf(stderr, "Unable to open keyboard\n");
    return EXIT_FAILURE;
  }

  while (1) {
    ssize_t n = read(keyboard_fd, &ev,
                     sizeof(ev)); // using read for raw unformatted data
                                  // void * means "a pointer to any raw
                                  // memory address, with no type rules."
    if (n == (ssize_t)-1) {
      if (errno == EINTR) {
        return EXIT_SUCCESS;
      }
      perror("Unable to read");
      return EXIT_FAILURE;
    } else if (n != sizeof(ev)) {
      fprintf(stderr, "Unexpected short read (%zd bytes)\n", n);
      return EXIT_FAILURE;
    }
    printf("This is after the conditional\n");
    printf("%d\n", ev.value);

    if (ev.type != EV_KEY || ev.value == 2) { // 2 is for long press. ignore it
      continue;
    }
    printf("%d %d\n", ev.value, ev.code);
    // play the relevant audio file
  }

  close(keyboard_fd);
  return EXIT_SUCCESS;
}
