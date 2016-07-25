cmake_minimum_required (VERSION 3.2)
project (test VERSION 1.0.0 LANGUAGES C)

add_subdirectory(tools)

add_library(unittest STATIC
	unittest/ut.c
	unittest/ut_alloc.c
	unittest/ut_file.c
	unittest/ut_pthread.c
	unittest/ut_signal.c
	unittest/ut_backtrace.c
	unittest/unittest.h)

find_package (Threads REQUIRED)
target_link_libraries(unittest PRIVATE ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(unittest PUBLIC ../include)


add_executable(pmem_is_pmem		pmem_is_pmem/pmem_is_pmem.c)
add_executable(pmem_is_pmem_proc 	pmem_is_pmem_proc/pmem_is_pmem_proc.c)
add_executable(pmem_map			pmem_map/pmem_map.c)
add_executable(pmem_memcpy		pmem_memcpy/pmem_memcpy.c)
add_executable(pmem_memmove		pmem_memmove/pmem_memmove.c)
add_executable(pmem_memset		pmem_memset/pmem_memset.c)
add_executable(pmem_movnt		pmem_movnt/pmem_movnt.c)
add_executable(pmem_movnt_align		pmem_movnt_align/pmem_movnt_align.c)
add_executable(pmem_valgr_simple	pmem_valgr_simple/pmem_valgr_simple.c)


target_include_directories(pmem_is_pmem PRIVATE unittest)
target_link_libraries(pmem_is_pmem PRIVATE unittest pmem)
add_test(pmem_is_pmem_test pmem_is_pmem)

target_include_directories(pmem_is_pmem_proc PRIVATE unittest)
target_link_libraries(pmem_is_pmem_proc PRIVATE unittest pmem dl)

target_include_directories(pmem_map PRIVATE unittest)
target_link_libraries(pmem_map PRIVATE unittest pmem dl)

target_include_directories(pmem_memcpy PRIVATE unittest)
target_link_libraries(pmem_memcpy PRIVATE unittest pmem)

target_include_directories(pmem_memmove PRIVATE unittest)
target_link_libraries(pmem_memmove PRIVATE unittest pmem)

target_include_directories(pmem_memset PRIVATE unittest)
target_link_libraries(pmem_memset PRIVATE unittest pmem)

target_include_directories(pmem_movnt PRIVATE unittest)
target_link_libraries(pmem_movnt PRIVATE unittest pmem)

target_include_directories(pmem_movnt_align PRIVATE unittest)
target_link_libraries(pmem_movnt_align PRIVATE unittest pmem)

target_include_directories(pmem_valgr_simple PRIVATE unittest)
target_link_libraries(pmem_valgr_simple PRIVATE unittest pmem)

add_custom_target(check
	COMMAND "./RUNTESTS pmem_is_pmem"
	DEPENDS pmem_is_pmem)
