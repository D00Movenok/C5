#include "log.h"

#include <stdio.h>  /* snprintf, sprintf, vprintf */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcpy, strcat, strlen */
#include <time.h>   /* time_t, struct tm, strftime, time, localtime */

#define MAX_FMT_TIME 25

const struct LogLevel LOG_TRACE = {.color = "\x1b[94m", .name = "TRACE"},
                      LOG_DEBUG = {.color = "\x1b[36m", .name = "DEBUG"},
                      LOG_INFO = {.color = "\x1b[32m", .name = "INFO"},
                      LOG_WARN = {.color = "\x1b[33m", .name = "WARN"},
                      LOG_ERROR = {.color = "\x1b[31m", .name = "ERROR"},
                      LOG_FATAL = {.color = "\x1b[35m", .name = "FATAL"};

void log_log(struct LogLevel level, const uint8_t* file, size_t line,
             const uint8_t* fmt, ...) {
  /* create RFC3339 formatted time */
  time_t gt = time(NULL);
  struct tm* lt = localtime(&gt);
  uint8_t fmt_time[MAX_FMT_TIME] = {0};
  strftime(fmt_time, sizeof(fmt_time), "%FT%T%z", lt);

  /* fill prefix */
  uint8_t* prefix = "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ";
  size_t filled_prefix_len =
      snprintf(NULL, 0, prefix, fmt_time, level.color, level.name, file, line);
  uint8_t* filled_prefix = malloc(filled_prefix_len + 1);
  sprintf(filled_prefix, prefix, fmt_time, level.color, level.name, file, line);

  /* prefix fmt with filled prefix */
  uint8_t* prefixed_fmt =
      (uint8_t*)malloc(strlen(filled_prefix) + strlen(fmt) + 1);
  strcpy(prefixed_fmt, filled_prefix);
  free(filled_prefix);
  strcat(prefixed_fmt, fmt);
  strcat(prefixed_fmt, "\n");

  /* print log */
  va_list fmt_args;
  va_start(fmt_args, fmt);
  vprintf(prefixed_fmt, fmt_args);
  va_end(fmt_args);

  free(prefixed_fmt);
}
