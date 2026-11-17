#include "input_headers.h"

int open_keyboard(void) {
  glob_t g;
  int fd;

  if (glob("/dev/input/by-path/*-event-kbd", 0, NULL, &g) != 0) {
    fprintf(stderr, "No input devices found.\n");
    return -1;
  }

  printf("Opening...\n");
  fd = open(g.gl_pathv[0], O_RDONLY); // open the first file

  if (fd == -1) {
    if (errno == EACCES) {
      fprintf(stderr,
              "Unable to read keyboard, run sudo usermod -aG input $USER\n");
    } else
      fprintf(stderr, "Unable to open file %s: %s\n", g.gl_pathv[0],
              strerror(errno));
  }

  globfree(&g);
  return fd;
}
