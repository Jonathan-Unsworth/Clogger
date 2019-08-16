#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

#define NO_OF_WRITERS 5

struct logger_t {
    FILE *log;
    format_t format;
};

// Private functions
void write_log_txt(logger_t, level_t, const char *);
void write_log_csv(logger_t, level_t, const char *);
void write_log_tsv(logger_t, level_t, const char *);
void write_log_xml(logger_t, level_t, const char *);
void write_log_json(logger_t, level_t, const char *);

// Jump table
void (*log_writers[NO_OF_WRITERS])(logger_t, level_t, const char *) = {
    write_log_txt,
    write_log_csv,
    write_log_tsv,
    write_log_xml,
    write_log_json
};

char levels[5][256] = {
    "[INFO]",
    "[WARNING]",
    "[ERROR]",
    "[FATAL]",
    "[SYSTEM DOWN]"
};

logger_t open_logger(const char *path, format_t format) {
    logger_t logger = (logger_t) malloc(sizeof * logger);

    if(logger) {
        if(logger->log = fopen(path, "a+")) {
            logger->format = format;
        } else {
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
        log_writers[logger->format](logger, level, message);
    }
}

void write_log_txt(logger_t logger, level_t level, const char *message) {
    fprintf(logger->log, "%s %s %s\n", __TIME__, levels[level], message);
}

void write_log_csv(logger_t logger, level_t level, const char *message) {
    fprintf(logger->log, "%s,%s,%s\n", __TIME__, levels[level], message);
}

void write_log_tsv(logger_t logger, level_t level, const char *message) {
    fprintf(logger->log, "%s\t%s\t%s\n", __TIME__, levels[level], message);
}

void write_log_xml(logger_t logger, level_t level, const char *message) {
    fprintf(logger->log, "<log>\n");
    fprintf(logger->log, "\t<time>%s</time>\n", __TIME__);
    fprintf(logger->log, "\t<level>%s</level>\n", levels[level]);
    fprintf(logger->log, "\t<message>%s</message>\n", message);
    fprintf(logger->log, "</log>");
}

void write_log_json(logger_t logger, level_t level, const char *message) {
    
}