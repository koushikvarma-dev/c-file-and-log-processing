cmake_minimum_required(VERSION 3.16)
project(c_file_and_log_processing C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(log_processor src/log_processor.c)
target_include_directories(log_processor PUBLIC include)
target_compile_options(log_processor PRIVATE -Wall -Wextra -Wpedantic)

add_executable(log_processor_cli src/main.c)
target_link_libraries(log_processor_cli PRIVATE log_processor)

enable_testing()
add_executable(test_log_processor tests/test_log_processor.c)
target_link_libraries(test_log_processor PRIVATE log_processor)
target_compile_options(test_log_processor PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME log_processor_tests COMMAND test_log_processor)
