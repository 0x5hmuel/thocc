#include "input_headers.h"
#include <asm-generic/errno-base.h>
#include <linux/input.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <sys/types.h>
#define BUF_SIZE 4096

int scan_input_dirs(void) {
  int notify_q, notify_watch;
  const uint32_t masks =
      IN_CREATE | IN_DELETE | IN_CLOSE_NOWRITE | IN_CLOSE_WRITE;

  notify_q = inotify_init1(IN_NONBLOCK); // blocking for now

  if (notify_q == -1) {
    perror("Error initialising event queue");
    return -1;
  }

  notify_watch = inotify_add_watch(notify_q, "/dev/input/", masks);

  if (notify_watch == -1) {
    if (errno == EACCES) {
      perror("No read access for specified directory.");
    } else
      perror("Unable to watch directory.\n");
    return -1;
  }

  return notify_q;
}

// TODO: find a proper name for this function
int random_function(void) {
  int notify_q = scan_input_dirs();

  if (notify_q == -1) {
    exit(EXIT_FAILURE);
  }

  char buf[BUF_SIZE];
  ssize_t size;

  const struct inotify_event *event;

  while (1) {
    size = read(notify_q, buf, sizeof(buf));

    if (size == -1) {
      if (errno != EAGAIN)
        perror("Unable to read notification event");
      if (errno == EAGAIN)
        perror("Nothing here right now, try again later");
      else
        exit(EXIT_FAILURE);
    }

    if (size <= 0)
      break;

    for (char *ptr = buf; ptr < buf + size;
         ptr += sizeof(struct inotify_event) + event->len) {
      event = (const struct inotify_event *)ptr;

      if (event->mask == IN_CREATE) {
        printf("Input device added");
      }
      if (event->mask == IN_DELETE) {
        printf("Input device removed");
      }

      // scan input devices and register only the keyboards
    }
  }
  return 1;
}
