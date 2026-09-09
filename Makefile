CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Iinclude
BUILD_DIR := build

.PHONY: all test sanitize clean

all: $(BUILD_DIR)/log_processor

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/log_processor: src/main.c src/log_processor.c include/log_processor.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) src/main.c src/log_processor.c -o $@

$(BUILD_DIR)/test_log_processor: tests/test_log_processor.c src/log_processor.c include/log_processor.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) tests/test_log_processor.c src/log_processor.c -o $@

test: $(BUILD_DIR)/test_log_processor
	$(BUILD_DIR)/test_log_processor

sanitize: CFLAGS += -fsanitize=address,undefined -fno-omit-frame-pointer
sanitize: clean $(BUILD_DIR)/test_log_processor

clean:
	rm -rf $(BUILD_DIR)
