#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#define CLOGPRINT(x, ...) log_print(__FILE__, __LINE__, x, ##__VA_ARGS__);
#define CLOGWARN(x, ...)  log_warning(__FILE__, __LINE__, x, ##__VA_ARGS__);
#define CLOGERROR(x, ...) log_error(__FILE__, __LINE__, x, ##__VA_ARGS__);


char *g_path;
char *g_name;
bool  save;
FILE *g_fp;

bool save_log(char *clog);
bool set_save_log(char *path, char *name);
void log_print(char *file_name, int lnnb, const char *fmt, ...);
void log_warning(char *file_name, int lnnb, char *fmt, ...);
void log_error(char *file_name, int lnnb, char *fmt, ...);
