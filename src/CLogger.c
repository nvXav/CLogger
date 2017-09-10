#include <alloca.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CLogger.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define MAX_BUFLEN 512


static char *get_time_string()
{
    /* Get current time */
    time_t raw_time;
    char *c_time_string;

    time(&raw_time);
    c_time_string = ctime(&raw_time);
    char *ctime = c_time_string + 4;

    for (int i = 0; i < strlen(ctime); ++i)
    {
        if (ctime[i] == '\n')
        {
            ctime[i] = '\0';
        }
    }

    static char bufferTime[32];
    snprintf(bufferTime, 32, "[%s] ", ctime);

    return bufferTime;
}

static char *get_file_info(char *file_name, int line_num)
{
    static char file_info[MAX_BUFLEN];
    char filename[strlen(file_name)];
    strcpy(filename, file_name);

    char *pch = strrchr(filename, '/');

    snprintf(file_info, MAX_BUFLEN, "Line %d [%s]", line_num, pch + 1);
    return file_info;
}

static char* allocate_input(char *file_name, int lnnb, const char *fmt, const va_list  args)
{
    /* Initialise the output string */
    char buffer[MAX_BUFLEN];
    buffer[0] = 0;

    /* Analyse the input */
    char tmpChar[MAX_BUFLEN];
    char *tmpString;
    int tmpInt;
    double tmpDbl;

    for (int i = 0; i < strlen(fmt); ++i)
    {
        if (fmt[i] != '%')
        {
            snprintf(tmpChar, 4, "%c", fmt[i]);
            strcat(buffer, tmpChar);
        }
        else
        {
            switch (fmt[++i])
            {
            case 's':
                tmpString = va_arg(args, char *);
                snprintf(tmpChar, MAX_BUFLEN, "%s", tmpString);
                strcat(buffer, tmpString);

                break;
            case 'd':
                tmpInt= va_arg(args, int);
                snprintf(tmpChar, MAX_BUFLEN, "%d", tmpInt);
                strcat(buffer, tmpChar);

                break;
            case 'f':
                tmpDbl= va_arg(args, double);
                snprintf(tmpChar, MAX_BUFLEN, "%f", tmpDbl);
                strcat(buffer, tmpChar);

                break;
            case '%':
                snprintf(tmpChar, MAX_BUFLEN, "%c", fmt[i]);
                strcat(buffer, tmpChar);

                break;
            default:
                break;
            }
        }
    }

    buffer[strlen(buffer)] = 0;

    /* Get file infotmation */
    char *file_info = get_file_info(file_name, lnnb);

    /* Get time string */
    char *time = get_time_string();

    /* Get output string */
    static char output[2 * MAX_BUFLEN];
    output[0] = 0;
    snprintf(output, 2 * MAX_BUFLEN, "%s%s%s%s", file_info, time, buffer, "\n");

    return output;
}

void log_print(char *file_name, int lnnb, const char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    char *input;
    input = allocate_input(file_name, lnnb, fmt, args);
    char info[MAX_BUFLEN];
    snprintf(info, MAX_BUFLEN, "%s%s", "Info: ", input);
    va_end(args);
    printf(GREEN "%s" COLOR_RESET, info);

    if (save)
    {
        save_log(info);
    }
}

void log_warning(char *file_name, int lnnb, char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    char *input;
    input = allocate_input(file_name, lnnb, fmt, args);
    char info[MAX_BUFLEN];
    snprintf(info, MAX_BUFLEN, "%s%s", "Warning: ", input);
    va_end(args);
    printf(YELLOW "Warning: %s" COLOR_RESET, input);

    if (save)
    {
        save_log(info);
    }
}

void log_error(char *file_name, int lnnb, char *fmt, ...)
{
    va_list args;
    va_start (args, fmt);
    char *input;
    input = allocate_input(file_name, lnnb, fmt, args);
    char info[MAX_BUFLEN];
    snprintf(info, MAX_BUFLEN, "%s%s", "Error: ", input);
    va_end(args);
    printf(RED "ERROR: %s" COLOR_RESET, input);

    if (save)
    {
        save_log(info);
    }
}

bool set_save_log(char *path, char *name)
{
    save = true;

    if (strcmp(name, "") == 0)
    {
        g_name = "save_log.txt";
    }
    else
    {
        g_name = name;
    }
    g_path = path;

}

bool save_log(char *clog)
{
    /* Analyse file address*/
    char file_path[MAX_BUFLEN];
    if (strcmp(g_path, "") == 0)
    {
        snprintf(file_path, MAX_BUFLEN, "%s", g_name);
    }
    else
    {
        if (g_path[0] != '/')
        {
            if (g_path[0] != '~')
            {
                printf(RED "ERROR: Inaccurate address format of file: %s" COLOR_RESET "\n", g_path);
                return false;
            }
        }
        snprintf(file_path, MAX_BUFLEN, "%s/%s",g_path, g_name);
    }

    /* Save in a file */
    char *cfile_path = file_path;
    g_fp = fopen(cfile_path, "a+r");
    if(!g_fp)
    {
        printf(RED "ERROR: Can not create or open file %s" COLOR_RESET "\n", g_name);
        return false;
    }

    char log[MAX_BUFLEN];
    snprintf(log, MAX_BUFLEN, "%s", "\n");
    fwrite(clog, strlen(clog) + sizeof(char), 1, g_fp);

    fclose(g_fp);
}
