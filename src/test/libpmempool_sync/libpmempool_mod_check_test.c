/*
 * Copyright 2016, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * libpmempool_repl_sync_mod -- Tool for modifying data in a poolset.
 *
 */

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "unittest.h"

enum oper_mode
{
	READ_POOL,
	WRITE_POOL
};

enum disp_format
{
	STR_FORMAT,
	DEC_FORMAT
};

/*
 * print_usage -- print usage of program
 */
static void
print_usage(char *name)
{
	UT_OUT("Usage: %s <-l <layout>> [-s <data_len>][-o <offset>]"
		"[-w] [-f <dec_format>] [-d <data>] [-r <root_size>]"
		" <pool_path>\n", name);
}

int
main(int argc, char *argv[])
{
	int opt;
	char *pool = NULL;
	char *layout = NULL;
	char *data = NULL;

	off_t offset = 0;
	size_t size = 0;
	size_t root_size = 0;
	enum oper_mode type = READ_POOL;
	enum disp_format format = STR_FORMAT;

	START(argc, argv, "libpmempool_mod_check_test");

	while ((opt = getopt(argc, argv, "wfs:o:l:d:r:")) != -1) {
		switch (opt) {
		case 'w':
			type = WRITE_POOL;
			break;
		case 'f':
			format = DEC_FORMAT;
			break;
		case 'o':
			offset = (unsigned)strtoul(optarg, NULL, 0);
			break;
		case 's':
			size = (unsigned)strtoul(optarg, NULL, 0);
			break;
		case 'l':
			layout = strdup(optarg);
			break;
		case 'd':
			data = strdup(optarg);
			size = strlen(optarg);
			break;
		case 'r':
			root_size = strtoul(optarg, NULL, 0);
			break;
		default:
			print_usage(argv[0]);
			return -1;
		}
	}
	if (optind < argc) {
		pool = argv[optind];
	} else {
		print_usage(argv[0]);
		return -1;
	}

	if (layout == NULL || size == 0) {
		UT_OUT("Layout name and data size are required\n");
		return -1;
	}

	if (type == WRITE_POOL && data == NULL) {
		UT_OUT("Data is required when write option enabled\n");
		return -1;
	}

	PMEMobjpool *pop = pmemobj_open(pool, layout);
	if (pop == NULL) {
		UT_OUT("Pool opening error: %s\n", pool);
		return -1;
	}

	PMEMoid root = pmemobj_root(pop, root_size);
	UT_ASSERT(!OID_IS_NULL(root));

	char *root_data = pmemobj_direct(root);

	if (type == WRITE_POOL) {
		pmemobj_memcpy_persist(pop, root_data + offset, data, size);
	} else {
		char *buff = malloc(size);
		memcpy(buff, root_data + offset, size);

		if (format == STR_FORMAT) {
			buff[size - 1] = '\0';
			UT_OUT("%s", buff);
		} else {
			for (unsigned i = 0; i < (size / 4); ++i) {
				UT_OUT("0x%X\t0x%X\t0x%X\t0x%X",
					buff[i * 4], buff[i * 4 + 1],
					buff[i * 4 + 2], buff[i * 4 + 3]);
			}
		}
	}

	pmemobj_close(pop);
	free(data);
	free(layout);
	data = NULL;
	layout = NULL;
	DONE(NULL);
}
