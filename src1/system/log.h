#ifndef LOG_H
#define LOG_H

#define LOG_FAIL(CONDITION) (void)((CONDITION) || fprintf(stderr, "%s:%d: %s: Assertion [%s] failed\n", __FILE__, __LINE__, __func__, #CONDITION))

#endif // LOG_H
