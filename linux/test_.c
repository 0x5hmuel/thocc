#include <fcntl.h>
#include <glob.h>
#include <linux/input.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void test_input(void) {
  int fd, glob_status;
  glob_t g;
  struct input_event ev;

  glob_status = glob("/dev/input/event*", 0, NULL, &g);

  if (glob_status != 0) {
    fprintf(stderr, "unable to read files in directory\n");
    return;
  }

  if (fd == -1) {
    perror("Unable to open file");
    return;
  }

  ssize_t n = read(fd, &ev, sizeof(ev));
  if (n == (ssize_t)-1) {
    perror("Unable to read file");
    close(fd);
  } else if (n != sizeof(ev)) {
    perror("Short read.");
    close(fd);
  }
}
