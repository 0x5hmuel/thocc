#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

#define LOG_DEBUG 10
#define LOG_INFO 20
#define LOG_WARN 30
#define LOG_ERROR 40

#define LOG_LEVEL 20

void log_msg(int level, const char *msg, ...);

#endif
