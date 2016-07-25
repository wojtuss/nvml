cmake_minimum_required (VERSION 3.2)
project (pmemblk VERSION 1.0.0 LANGUAGES C)

add_library(pmemblk SHARED
       libpmemblk.c
       blk.c
       blk.h
       btt.c
       btt.h
       btt_layout.h
       $<TARGET_OBJECTS:common>)
add_library(pmemblkStatic STATIC
       libpmemblk.c
       blk.c
       blk.h
       btt.c
       btt.h
       btt_layout.h
       $<TARGET_OBJECTS:common>)
target_include_directories(pmemblk PRIVATE ../common)
target_include_directories(pmemblkStatic PRIVATE ../common)

find_package (Threads REQUIRED)
target_link_libraries(pmemblk pmem ${CMAKE_THREAD_LIBS_INIT})

set(compile_flags "-fPIC")
set_target_properties(pmemblk PROPERTIES SOVERSION 1 COMPILE_FLAGS ${compile_flags})
set_target_properties(pmemblkStatic PROPERTIES COMPILE_FLAGS ${compile_flags})
set_target_properties(pmemblkStatic PROPERTIES OUTPUT_NAME pmemblk)

install(TARGETS pmemblk pmemblkStatic
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)  # This is for Windows

