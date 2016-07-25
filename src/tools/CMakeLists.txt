cmake_minimum_required (VERSION 3.2)
project (test_tools VERSION 1.0.0 LANGUAGES C)

add_executable(pmemdetect pmemdetect/pmemdetect.c)
target_link_libraries(pmemdetect PRIVATE pmem)
target_include_directories(pmemdetect PRIVATE common_SOURCE_DIR)

