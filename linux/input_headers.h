#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <glob.h>
#include <linux/input.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int read_input(void);
int open_keyboard(void);
