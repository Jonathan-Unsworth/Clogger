#ifndef __LOGGER_H__
#define __LOGGER_H__

// Opaque pointer to hide implementation details
typedef struct logger_t * logger_t;

// Supported output formats
typedef enum {
    TXT,
    CSV,
    TSV,
    XML,
    JSON
} format_t;

// Log levels
typedef enum {
    INFO,
    WARNING,
    ERROR,
    FATAL,
    SYSTEM_DOWN
} level_t;

// Lifetime functions
logger_t open_logger(const char *, format_t);
void close_logger(logger_t);

// Log functions
void write_log(logger_t, level_t, const char *);

#endif