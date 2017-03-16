/*
 * Copyright 2017, Intel Corporation
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
 * part.h -- internal definitions for part processing functions
 *
 * For definitions of the terms used see doc/glossary.md
 */

#include "libpmemlot.h"

struct part {
	struct fileh *file;
	size_t size;		/* aligned to page size */
	int created;		/* indicates newly created (zeroed) file */
	void *remote_hdr;	/* allocated header for remote replica */
	void *hdr;		/* base address of header */
	size_t hdrsize;		/* size of the header mapping */
	void *addr;		/* base address of the mapping */
	size_t mapsize;		/* size of the mapping - page aligned */
	int rdonly;		/* is set based on compat features, affects */
				/* the whole poolset */
	uuid_t uuid;
	int health;
};

/* get a pointer to the header of the (p)th part */
#define HDR(rep, p) ((struct pool_hdr *)(PART(rep, p).hdr))

ssize_t part_get_size(struct part *part);
int part_is_broken(struct part *part);

int part_open(struct part *part);
int part_close(struct part *part);
int part_remove(struct part *part);

