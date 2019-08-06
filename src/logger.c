#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

struct logger_t {
    FILE *log;
};

char levels[5][256] = {
    "[INFO]",
    "[WARNING]",
    "[ERROR]",
    "[FATAL]",
    "[SYSTEM DOWN]"
};

logger_t open_logger(const char *path) {
    logger_t logger = (logger_t) malloc(sizeof * logger);

    if(logger) {
        if(!(logger->log = fopen(path, "a+"))) {
            free(logger);
            logger = NULL;
        }
    }

    return logger;
}

void close_logger(logger_t logger) {
    if(logger) {
        fclose(logger->log);
        free(logger);
        logger = NULL;
    }
}

void write_log(logger_t logger, level_t level, const char *message) {
    if(logger) {
        level = (level >= INFO && level <= SYSTEM_DOWN) ? level : INFO;
        fprintf(logger->log, "%s %s %s\n", __TIME__, levels[level], message);
    }
}