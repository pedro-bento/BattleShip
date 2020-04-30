#ifndef LOG_H
#define LOG_H

#define LOG_FAIL(CONDITION) (void)((CONDITION) || (__log_fail( __FILE__, __LINE__, __func__, #CONDITION), 0))

void __log_fail(const char *file, int line, const char *function, const char *message);

#endif // LOG_H
