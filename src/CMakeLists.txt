cmake_minimum_required (VERSION 3.2)
project (src VERSION 1.0.0 LANGUAGES C)

execute_process(COMMAND bash -c "git describe 2>/dev/null || cat .version 2>/dev/null || git log -1 --format=%h 2>/devnull" OUTPUT_VARIABLE SRCVERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
add_definitions(-DSRCVERSION="${SRCVERSION}")

set(INCLUDE ${CMAKE_SOURCE_DIR}/src/include)
set(COMMON ${CMAKE_SOURCE_DIR}/src/common)
add_subdirectory(common)
add_subdirectory(libpmem)
#add_subdirectory(libpmemblk)
#add_subdirectory(libpmemlog)
#add_subdirectory(libpmemobj)
#add_subdirectory(test)

