#include "log_processor.h"

#include <assert.h>
#include <string.h>

static void test_levels(void) {
    assert(parse_log_level("INFO") == LOG_INFO);
    assert(parse_log_level("WARN") == LOG_WARN);
    assert(parse_log_level("ERROR") == LOG_ERROR);
    assert(parse_log_level("DEBUG") == LOG_INVALID);
}

static void test_parser(void) {
    LogRecord record;
    assert(parse_log_line("2026-09-09 10:15:21 [ERROR] request failed\n", &record));
    assert(strcmp(record.timestamp, "2026-09-09 10:15:21") == 0);
    assert(record.level == LOG_ERROR);
    assert(strcmp(record.message, "request failed") == 0);
    assert(!parse_log_line("not a valid record\n", &record));
}

static void test_processing(void) {
    const char *text =
        "2026-09-09 10:00:00 [INFO] started\n"
        "2026-09-09 10:01:00 [WARN] retry\n"
        "broken line\n"
        "2026-09-09 10:02:00 [ERROR] failed\n";
    FILE *input = tmpfile();
    assert(input != NULL);
    fputs(text, input);
    rewind(input);

    LogStats stats;
    assert(process_log_file(input, &stats));
    assert(stats.total == 3);
    assert(stats.info == 1);
    assert(stats.warn == 1);
    assert(stats.error == 1);
    assert(stats.malformed == 1);
    fclose(input);
}

int main(void) {
    test_levels();
    test_parser();
    test_processing();
    puts("All tests passed.");
    return 0;
}
