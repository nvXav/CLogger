#include <stdarg.h>

#define CLOGPRINT(x, ...) log_print(__FILE__, __LINE__, x, ##__VA_ARGS__);
#define CLOGWARN(x, ...) log_warning(__FILE__, __LINE__, x, ##__VA_ARGS__);
#define CLOGERROR(x, ...) log_error(__FILE__, __LINE__, x, ##__VA_ARGS__);

char *buffer;

void save_log();
void cancel_save_log();
void log_print(char *file_name, int lnnb, const char *fmt, ...);
void log_warning(char *file_name, int lnnb, char *fmt, ...);
void log_error(char *file_name, int lnnb, char *fmt, ...);
