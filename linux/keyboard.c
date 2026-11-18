#include "input_headers.h"
#include <stdlib.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

int *open_keyboard(void) {
  glob_t g;
  int kbd_fd;
  int i = 0;
  int *keyboard_fds; // could

  int glob_result = -1;

  glob_result = glob("/dev/input/by-path/*-event-kbd", 0, NULL, &g);

  if (glob_result == GLOB_NOMATCH) {
    perror("No keyboards found");
    return NULL;
  } else if (glob_result != 0) {
    fprintf(stderr, "No input devices found.\n");
    return NULL;
  }

  keyboard_fds = malloc(g.gl_pathc * sizeof(int));

  if (keyboard_fds == NULL) {
    perror("Unable to allocate memory");
    globfree(&g);
    return NULL;
  }

  while (g.gl_pathv[i]) {
    kbd_fd = open(g.gl_pathv[i], O_RDONLY);

    if (kbd_fd == -1) {
      if (errno == EACCES) {
        fprintf(stderr,
                "Unable to read kbd, run sudo usermod -aG input $USER\n");
        exit(EXIT_FAILURE);
      } else {
        fprintf(stderr, "Unable to open file %s: %s\n", g.gl_pathv[i],
                strerror(errno));
        exit(EXIT_FAILURE);
      }
    }

    keyboard_fds[i] = kbd_fd;
    ++i;
  }
  keyboard_fds[i] = '\0';

  globfree(&g);
  return keyboard_fds;
}
