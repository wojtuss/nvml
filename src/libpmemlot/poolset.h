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
 * repset.h -- internal definitions for repset processing functions
 *
 * For definitions of the terms used see doc/glossary.md
 */

#include "libpmemlot.h"

struct repset {
	uuid_t uuid;
	int nreplicas;
	struct replica *replicas[];
	int rdonly;
	int zeroed;
	size_t size;		/* size of the lot exposed by the repset */
				/* equals the smallest replica size */
	size_t poolsize;	/* current size of the pool stored in the lot */
	int remote;
	int health;
};

/* get the (r)th replica */
#define REP(set, r) ((set)->replica[r])

// z util_poolset_parse i util_poolset_read
int repset_parse(struct repset **setp, struct fileh *file);
// z util_poolset_create_set
int repset_create(struct repset **setp, struct fileh *file,
		size_t poolsize, size_t, minsize);

int repset_open(struct repset *set, int flags);
int repset_close(struct repset *set, enum del_parts_mode del);
void repset_free(struct repset *set);
int repset_chmod(struct repset *set, mode_t mode);
// sprawdź czy potrzebne w headerze
int repset_fdclose(struct repset *set);
int repset_is_repset_file(struct fileh *file);

ssize_t repset_get_size(struct repset *set);
ssize_t repset_get_poolsize(struct repset *set);

//-----------


int repset_find_healthy_replica(struct repset *set);
int repset_is_healthy(struct repset *set);

int repset_sync(struct repset *set);
int repset_transform(struct repset *set);
int repset_check(struct repset *set);
