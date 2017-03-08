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
 * poolset.h -- internal definitions for poolset processing functions
 *
 * For definitions of the terms used see doc/glossary.md
 */

#include "libpmemlot.h"

struct poolset {
	uuid_t uuid;
	int nreplicas;
	struct replica *replicas[];
	int rdonly;
	int zeroed;
	size_t size;		/* total capacity of the poolset */
				/* equals the smallest replica size */
	size_t poolsize;	/* current size of the poolt */
	int remote;
	int health;
};

ssize_t poolset_get_size(struct poolset *set);
ssize_t poolset_get_poolsize(struct poolset *set);
int poolset_find_healthy_replica(struct poolset *set);
int poolset_is_healthy(struct poolset *set);

int poolset_open(struct poolset *set);
int poolset_close(struct poolset *set);
int poolset_sync(struct poolset *set);
int poolset_transform(struct poolset *set);
int poolset_check(struct poolset *set);
