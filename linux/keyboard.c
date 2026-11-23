#include "input_headers.h"
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int find_keyboards(glob_t *g) {
  int glob_result;

  // TODO: change to read all events and get those that are inputs
  glob_result = glob("/dev/input/event*", 0, NULL, g);

  if (glob_result == GLOB_NOMATCH) {
    fprintf(stderr, "No keyboards found.\n"); // falls under the retryable error
    return 1;
  } else if (glob_result != 0) {
    fprintf(stderr, "No input devices found.\n");
    return 1;
  }

  return 0; // zero on success
}

Keyboards open_keyboards(glob_t *g) {
  int kbd_fd;
  int i = 0;
  Keyboards kbds;

  kbds.slots = malloc(g->gl_pathc * sizeof(int)); // memory allocation 2
  kbds.size = g->gl_pathc;

  if (kbds.slots == NULL) {
    perror("Unable to allocate memory");
    globfree(g); // free memory 1
    exit(EXIT_FAILURE);
  }

  while (g->gl_pathv[i]) {
    kbd_fd = open(g->gl_pathv[i], O_RDONLY);

    if (kbd_fd == -1) {
      if (errno == EACCES) {
        fprintf(stderr,
                "Unable to read keyboard, run sudo usermod -aG input $USER\n");
      } else {
        fprintf(stderr, "Unable to open file %s: %s\n", g->gl_pathv[i],
                strerror(errno));
      }
    }

    kbds.slots[i] = kbd_fd;
    ++i;
  }

  globfree(g); // free memory 1
  return kbds;
}

ssize_t read_event(int key_fd, struct input_event *ev) {

  ssize_t count = read(key_fd, ev, sizeof(*ev));

  if (ev->type != EV_KEY || ev->value == 2) { // skip non-key or long presses
    return -1;
  }

  return count;
}
