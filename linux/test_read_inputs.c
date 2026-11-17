#include "input_headers.h"
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/types.h>

int read_keyboard(void) {
  glob_t g;
  int fd, i, device;
  ssize_t n;
  struct input_event ev;

  fd = glob("/dev/input/event*", 0, NULL, &g);

  if (fd != 0) {
    fprintf(stderr, "Unable to find input files\n");
    return (1);
  };

  i = 0;

  // epoll_data(g.gl_pathv)

  while (g.gl_pathv[i]) {
    device = open(g.gl_pathv[i], O_RDONLY);

    if (fd == -1) {
      perror("Unable to open file");
      return (1);
    }

    ++i;

    n = read(fd, &ev, sizeof(ev));

    if (n == (ssize_t)-1) {
      perror("Unable to read file");
      continue;
    } else if (n != sizeof(ev)) {
      fprintf(stderr, "Unexpected short read");
      continue;
    }

    if (ev.type != EV_KEY) {
      continue;
    }
  };

  globfree(&g);
  return (0);
}
