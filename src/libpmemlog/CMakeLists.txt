cmake_minimum_required (VERSION 3.2)
project (pmemlog VERSION 1.0.0 LANGUAGES C)

add_library(pmemlog SHARED
       libpmemlog.c
       log.c
       log.h
       $<TARGET_OBJECTS:common>)
add_library(pmemlogStatic STATIC
       libpmemlog.c
       log.c
       log.h
       $<TARGET_OBJECTS:common>)
target_include_directories(pmemlog PRIVATE ../common)
target_include_directories(pmemlogStatic PRIVATE ../common)

find_package (Threads REQUIRED)
target_link_libraries(pmemlog pmem ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(pmemlog PROPERTIES SOVERSION 1 COMPILE_FLAGS "-fPIC")
set_target_properties(pmemlogStatic PROPERTIES OUTPUT_NAME pmemlog)

install(TARGETS pmemlog pmemlogStatic
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)  # This is for Windows
