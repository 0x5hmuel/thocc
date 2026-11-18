#include "input_headers.h"

int read_input(void) {
  // struct input_event ev, events;

  // while (1) {
  //   ssize_t n = read(keyboard_fd, &ev,
  //                    sizeof(ev)); // using read for raw unformatted data
  //                                 // void * means "a pointer to any raw
  //                                 // memory address, with no type rules."
  //   if (n == (ssize_t)-1) {
  //     if (errno == EINTR) {
  //       return EXIT_SUCCESS;
  //     }
  //     perror("Unable to read");
  //     return EXIT_FAILURE;
  //   } else if (n != sizeof(ev)) {
  //     fprintf(stderr, "Unexpected short read (%zd bytes)\n", n);
  //     return EXIT_FAILURE;
  //   }
  //   printf("This is after the conditional\n");
  //   printf("%d\n", ev.value);
  //
  //   if (ev.type != EV_KEY || ev.value == 2) { // 2 is for long press. ignore
  //   it
  //     continue;
  //   }
  //   printf("%d %d\n", ev.value, ev.code);
  //   // play the relevant audio file
  // }

  while (keyboard_fd[i]) {
    close(keyboard_fd[i]);
    ++i;
  }

  free(keyboard_fd);
  return EXIT_SUCCESS;
}
