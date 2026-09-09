#ifndef LOG_PROCESSOR_H
#define LOG_PROCESSOR_H

#include <stddef.h>
#include <stdio.h>

#define LOG_MESSAGE_MAX 512

typedef enum {
    LOG_INFO = 0,
    LOG_WARN = 1,
    LOG_ERROR = 2,
    LOG_INVALID = -1
} LogLevel;

typedef struct {
    char timestamp[20];
    LogLevel level;
    char message[LOG_MESSAGE_MAX];
} LogRecord;

typedef struct {
    size_t total;
    size_t info;
    size_t warn;
    size_t error;
    size_t malformed;
} LogStats;

LogLevel parse_log_level(const char *text);
int parse_log_line(const char *line, LogRecord *record);
int process_log_file(FILE *input, LogStats *stats);
void print_stats(const LogStats *stats, FILE *output);
const char *log_level_name(LogLevel level);

#endif
