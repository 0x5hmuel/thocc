#include "linux/input_headers.h"

/**
 *
 *
 */
int main(int argc, char *argv[]) {
  // TODO: this needs to be removed once I understand how to make use of epoll
  // or a better alternative
  if (argc < 2) {
    fprintf(stderr, "%s: error: keyboard path missing\n", argv[0]);
    fprintf(stderr, "Usage: %s <keyboard_path>\n", argv[0]);
    return 1;
  }

  char *keyboard_path = argv[1];
  printf("Welcome to THocc!\n");
  read_input();

  return 0;
}
