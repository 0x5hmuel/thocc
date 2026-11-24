#include "log.h"
#include <stdio.h>

static const char *level_to_str(int level) {
  switch (level) {
  case LOG_DEBUG:
    return "DEBUG";
  case LOG_INFO:
    return "INFO";
  case LOG_WARN:
    return "WARN";
  case LOG_ERROR:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

void log_msg(int level, const char *msg, ...) {
  if (level < LOG_LEVEL)
    return;

  va_list args;

  va_start(args, msg);

  fprintf(stderr, "[%s] ", level_to_str(level));

  vfprintf(stderr, msg, args); // automatically calls va_arg

  fputc('\n', stderr);
  va_end(args);
}
