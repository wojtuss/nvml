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
 * replica.h -- internal definitions for replica processing functions
 *
 * For definitions of the terms used see doc/glossary.md
 */

#include "libpmemlot.h"

enum del_parts_mode {
	DELETE_NONE,	/* do not delete part files */
	DELETE_CREATED,	/* delete only newly created part files */
	DELETE_ALL	/* force delete all part files */
};

struct replica {
	int nparts;
	struct part parts[];
	size_t size;		/* size of the replica's lot */
	size_t poolsize;	/* current size of a pool stored in the lot */
	int is_pmem;		/* true if all the parts are in PMEM */
	struct remote_replica *remote;
	int health;		/* flags indicating health status */
};

/* get the (p)th part */
#define PART(rep, p) ((rep)->part[p])

int replica_close(struct replica *rep, enum del_parts_mode del);
int replica_close_local(struct replica *rep, enum del_parts_mode del);
int replica_close_remote(struct replica *rep, enum del_parts_mode del);
// z util_replica_close
int replica_close_lot(struct replica *rep);


//-----------

ssize_t replica_get_size(struct replica *rep);
ssize_t replica_get_poolsize(struct replica *rep);
int replica_is_healthy(struct replica *rep);
int replica_is_broken(struct replica *rep);

int replica_open(struct replica *rep);

