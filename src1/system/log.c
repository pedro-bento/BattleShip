#include <stdio.h>
#include <stdlib.h>

#include "log.h"

void __log_fail(const char *file, int line, const char *function, const char *message)
{
  fprintf(stderr, "%s:%d: %s: Assertion [%s] failed\n", file, line, function, message);
  exit(EXIT_FAILURE);
}
