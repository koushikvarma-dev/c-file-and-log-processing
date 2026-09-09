# C File and Log Processing

A portfolio project demonstrating robust C file I/O, line-oriented log parsing, filtering, statistics, and defensive error handling.

> Portfolio project — created to demonstrate C programming and systems-level engineering skills.

## Features

- Read text files safely using buffered I/O
- Parse structured log lines
- Filter records by log level
- Count INFO, WARN, and ERROR events
- Calculate processing statistics
- Export a compact report
- Handle missing files and malformed records gracefully
- Automated tests

## Project structure

```text
.
├── include/
│   └── log_processor.h
├── src/
│   └── log_processor.c
├── tests/
│   └── test_log_processor.c
├── examples/
│   └── application.log
├── CMakeLists.txt
├── Makefile
├── .gitignore
└── README.md
```

## Build

```bash
make
```

Run the processor:

```bash
./build/log_processor examples/application.log
```

Run tests:

```bash
make test
```

CMake:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Example log format

```text
2026-09-09 10:15:21 [INFO] service started
2026-09-09 10:16:02 [WARN] connection retry
2026-09-09 10:16:18 [ERROR] request failed
```

## Engineering focus

The implementation emphasizes bounded parsing, explicit return-status handling, resource cleanup, predictable memory ownership, and separation between parsing, aggregation, and reporting.

## Technologies

- C11
- Standard C library
- GCC/Clang
- Make
- CMake
