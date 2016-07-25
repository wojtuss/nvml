cmake_minimum_required (VERSION 3.2)
project (pmem VERSION 1.0.0 LANGUAGES C)

set(sources
	libpmem.c
	cpu.c
	pmem.c
	pmem_linux.c
	)

add_library(pmem SHARED
	${sources}
	$<TARGET_OBJECTS:pmemcommon_no_libpthread>)

add_library(pmemStatic STATIC
	${sources}
	$<TARGET_OBJECTS:pmemcommon_no_libpthread>)

target_include_directories(pmem PRIVATE ${COMMON})
target_include_directories(pmemStatic PRIVATE ${COMMON})

set_target_properties(pmem PROPERTIES SOVERSION 1)
target_compile_options(pmem PRIVATE -fPIC)
target_compile_definitions(pmem PRIVATE NO_LIBPTHREAD)

set_target_properties(pmemStatic PROPERTIES OUTPUT_NAME pmem)
target_compile_options(pmemStatic PRIVATE -fPIC)
target_compile_definitions(pmemStatic PRIVATE NO_LIBPTHREAD)

install(TARGETS pmem pmemStatic
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)  # This is for Windows
