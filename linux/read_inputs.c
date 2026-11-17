#include "input_headers.h"
#include <stdio.h>

int read_input(void) {
  int keyboard_fd = open_keyboard();
  printf("kbd -> %d\n", keyboard_fd);
  struct input_event ev;

  printf("Keyboard fd: %d\n", keyboard_fd);
  if (keyboard_fd == -1) {
    fprintf(stderr, "Unable to open keyboard\n");
    return EXIT_FAILURE;
  }

  while (1) {
    puts("In the loop....");

    ssize_t n = read(keyboard_fd, &ev,
                     sizeof(ev)); // using read for raw unformatted data
                                  // void * means "a pointer to any raw
                                  // memory address, with no type rules."
    printf("%ld bytes read\n", n);
    if (n == (ssize_t)-1) {
      if (errno == EINTR) {
        printf("Interrupted\n");
        return EXIT_SUCCESS;
      }
      perror("Unable to read");
      return EXIT_FAILURE;
    } else if (n != sizeof(ev)) {
      fprintf(stderr, "Unexpected short read (%zd bytes)\n", n);
      return EXIT_FAILURE;
    }
    printf("This is after the conditional\n");

    if (ev.type != EV_KEY || ev.value == 2) // 2 is for long press. ignore it
      continue;
    printf("LOagin...");
    printf("%d %d\n", ev.value, ev.code);
    // play the relevant audio file
  }

  close(keyboard_fd);
  return EXIT_SUCCESS;
}
