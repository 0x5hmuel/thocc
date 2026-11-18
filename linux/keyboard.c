#include "input_headers.h"

glob_t find_keyboards() {
  glob_t g;

  int glob_result = -1;

  glob_result = glob("/dev/input/by-path/*-event-kbd", 0, NULL, &g);

  if (glob_result == GLOB_NOMATCH) {
    perror("No keyboards found");
    exit(EXIT_FAILURE);
  } else if (glob_result != 0) {
    fprintf(stderr, "No input devices found.\n");
    exit(EXIT_FAILURE);
  }

  return g;
};

Keyboards open_keyboards(glob_t g) {
  int kbd_fd;
  int i = 0;

  Keyboards kbds;

  kbds.slots = malloc(g.gl_pathc * sizeof(int));
  kbds.size = g.gl_pathc;

  if (kbds.slots == NULL) {
    perror("Unable to allocate memory");
    globfree(&g);
    exit(EXIT_FAILURE);
  }

  while (g.gl_pathv[i]) {
    kbd_fd = open(g.gl_pathv[i], O_RDONLY);

    if (kbd_fd == -1) {
      if (errno == EACCES) {
        fprintf(stderr,
                "Unable to read kbd, run sudo usermod -aG input $USER\n");
      } else {
        fprintf(stderr, "Unable to open file %s: %s\n", g.gl_pathv[i],
                strerror(errno));
      }
    }

    kbds.slots[i] = kbd_fd;
    ++i;
  }

  globfree(&g);
  return kbds;
}
