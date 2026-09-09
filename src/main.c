#include "log_processor.h"

#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <log-file>\n", argv[0]);
        return 2;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Unable to open log file");
        return 1;
    }

    LogStats stats;
    int success = process_log_file(input, &stats);
    fclose(input);

    if (!success) {
        fprintf(stderr, "Error while reading log file\n");
        return 1;
    }

    print_stats(&stats, stdout);
    return 0;
}
