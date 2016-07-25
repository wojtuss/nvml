cmake_minimum_required (VERSION 3.2)
project (pmemcommon C)

set(source 
	file.c
	file_linux.c
	mmap.c
	mmap_linux.c
	out.c
	pool_hdr.c
	pool_hdr_linux.c
	set.c
	util.c
	uuid.c
	uuid_linux.c
	)

add_library(pmemcommon OBJECT ${source})
target_include_directories(pmemcommon PRIVATE ${INCLUDE})
target_compile_options(pmemcommon PRIVATE -fPIC)

add_library(pmemcommon_no_libpthread OBJECT ${source})
target_include_directories(pmemcommon_no_libpthread PRIVATE ${INCLUDE})
target_compile_options(pmemcommon_no_libpthread PRIVATE -fPIC)
target_compile_definitions(pmemcommon_no_libpthread PRIVATE NO_LIBPTHREAD)

