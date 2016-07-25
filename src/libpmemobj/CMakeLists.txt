cmake_minimum_required (VERSION 3.2)
project (pmemobj VERSION 1.0.0 LANGUAGES C)

add_library(pmemobj SHARED
	libpmemobj.c
	obj.c
	obj.h
	redo.c
	redo.h
	pmalloc.c
	pmalloc.h
	lane.c
	lane.h
	list.c
	list.h
	ctree.c
	ctree.h
	bucket.c
	bucket.h
	heap.c
	heap.h
	cuckoo.c
	cuckoo.h
	sync.c
	sync.h
	tx.c
	tx.h
	memops.c
	memops.h
	memblock.c
	memblock.h
	pvector.c
	pvector.h
	heap_layout.h
	$<TARGET_OBJECTS:common>)
add_library(pmemobjStatic STATIC
	libpmemobj.c
	obj.c
	obj.h
	redo.c
	redo.h
	pmalloc.c
	pmalloc.h
	lane.c
	lane.h
	list.c
	list.h
	ctree.c
	ctree.h
	bucket.c
	bucket.h
	heap.c
	heap.h
	cuckoo.c
	cuckoo.h
	sync.c
	sync.h
	tx.c
	tx.h
	memops.c
	memops.h
	memblock.c
	memblock.h
	pvector.c
	pvector.h
	heap_layout.h
	$<TARGET_OBJECTS:common>)
target_include_directories(pmemobj PRIVATE ../common)
target_include_directories(pmemobjStatic PRIVATE ../common)

find_package (Threads REQUIRED)
target_link_libraries(pmemobj pmem ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(pmemobj PROPERTIES SOVERSION 1 COMPILE_FLAGS "-fPIC")
set_target_properties(pmemobjStatic PROPERTIES OUTPUT_NAME pmemobj)

install(TARGETS pmemobj pmemobjStatic
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin)  # This is for Windows
