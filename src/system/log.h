#ifndef LOG_H
#define LOG_H

// LOG_FAIL
// macro that receives a condition and, if not true, exits process with a error message
#define LOG_FAIL(CONDITION) (void)((CONDITION) || (__log_fail( __FILE__, __LINE__, __func__, #CONDITION), 0))

// __log_fail
// prints error message to stderr and exists process when called
void __log_fail(const char *file, int line, const char *function, const char *message);

#endif // LOG_H
