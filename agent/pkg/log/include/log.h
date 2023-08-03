#pragma once

#include <stdarg.h> /* va_list, va_start, va_end, __VA_ARGS__ */
#include <stddef.h> /* size_t */
#include <stdint.h> /* uint8_t */

struct LogLevel {
  const uint8_t* color;
  const uint8_t* name;
};

const struct LogLevel LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR,
    LOG_FATAL;

#if defined(LOGLEVEL_INFO) || defined(LOGLEVEL_DEBUG) || defined(LOGLEVEL_TRACE)
#  define log_info(...) log_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#  define log_warn(...) log_log(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#  define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#  define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
#  if defined(LOGLEVEL_DEBUG) || defined(LOGLEVEL_TRACE)
#    define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#  else
#    define log_debug(...)
#  endif
#  if defined(LOGLEVEL_TRACE)
#    define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#  else
#    define log_trace(...)
#  endif
#else
#  define log_trace(...)
#  define log_debug(...)
#  define log_info(...)
#  define log_warn(...)
#  define log_error(...)
#  define log_fatal(...)
#endif

void log_log(struct LogLevel level, const uint8_t* file, size_t line,
             const uint8_t* fmt, ...);
