#include "log_processor.h"

#include <string.h>

LogLevel parse_log_level(const char *text) {
    if (text == NULL) return LOG_INVALID;
    if (strcmp(text, "INFO") == 0) return LOG_INFO;
    if (strcmp(text, "WARN") == 0) return LOG_WARN;
    if (strcmp(text, "ERROR") == 0) return LOG_ERROR;
    return LOG_INVALID;
}

const char *log_level_name(LogLevel level) {
    switch (level) {
        case LOG_INFO: return "INFO";
        case LOG_WARN: return "WARN";
        case LOG_ERROR: return "ERROR";
        default: return "INVALID";
    }
}

int parse_log_line(const char *line, LogRecord *record) {
    if (line == NULL || record == NULL) return 0;
    memset(record, 0, sizeof(*record));

    const char *open = strchr(line, '[');
    const char *close = open != NULL ? strchr(open, ']') : NULL;
    if (open == NULL || close == NULL || close <= open + 1) return 0;

    size_t timestamp_len = (size_t)(open - line);
    if (timestamp_len == 0 || timestamp_len >= sizeof(record->timestamp)) return 0;
    memcpy(record->timestamp, line, timestamp_len);
    if (record->timestamp[timestamp_len - 1] == ' ') record->timestamp[timestamp_len - 1] = '\0';
    else record->timestamp[timestamp_len] = '\0';

    size_t level_len = (size_t)(close - open - 1);
    if (level_len >= 16) return 0;
    char level[16];
    memcpy(level, open + 1, level_len);
    level[level_len] = '\0';
    record->level = parse_log_level(level);
    if (record->level == LOG_INVALID) return 0;

    const char *message = close + 1;
    while (*message == ' ') message++;
    size_t message_len = strlen(message);
    while (message_len > 0 && (message[message_len - 1] == '\n' || message[message_len - 1] == '\r')) message_len--;
    if (message_len >= sizeof(record->message)) message_len = sizeof(record->message) - 1;
    memcpy(record->message, message, message_len);
    record->message[message_len] = '\0';
    return 1;
}

int process_log_file(FILE *input, LogStats *stats) {
    if (input == NULL || stats == NULL) return 0;
    memset(stats, 0, sizeof(*stats));

    char line[1024];
    while (fgets(line, sizeof(line), input) != NULL) {
        LogRecord record;
        if (!parse_log_line(line, &record)) {
            stats->malformed++;
            continue;
        }
        stats->total++;
        switch (record.level) {
            case LOG_INFO: stats->info++; break;
            case LOG_WARN: stats->warn++; break;
            case LOG_ERROR: stats->error++; break;
            default: stats->malformed++; stats->total--; break;
        }
    }
    return ferror(input) == 0;
}

void print_stats(const LogStats *stats, FILE *output) {
    if (stats == NULL || output == NULL) return;
    fprintf(output, "Total valid records : %zu\n", stats->total);
    fprintf(output, "INFO                : %zu\n", stats->info);
    fprintf(output, "WARN                : %zu\n", stats->warn);
    fprintf(output, "ERROR               : %zu\n", stats->error);
    fprintf(output, "Malformed records   : %zu\n", stats->malformed);
}
