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
 * libpmemlot.h -- definitions of libpmemlot entry points
 *
 * See libpmemlot(3) for details.
 */

#ifndef LIBPMEMLOT_H
#define LIBPMEMLOT_H 1

#ifdef _WIN32
#include <pmemcompat.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <limits.h>


/* COMMON FLAGS */

/*
 * do not apply changes, only check if operation is viable
 */
#define PMEMLOT_DRY_RUN (1 << 1)

/*
 * LIBPMEMLOT SYNC & TRANSFORM
 */

/*
 * Synchronize data between replicas within a poolset.
 */
int pmemlot_sync(const char *poolset_file, unsigned flags);

/*
 * Modify internal structure of a poolset.
 */
int pmemlot_transform(const char *poolset_file_src,
		const char *poolset_file_dst, unsigned flags);


/* PMEMLOT RM */

#define PMEMLOT_RM_FORCE		(1 << 0) /* ignore any errors */
#define PMEMLOT_RM_POOLSET_LOCAL	(1 << 1) /* remove local poolsets */
#define PMEMLOT_RM_POOLSET_REMOTE	(1 << 2) /* remove remote poolsets */
int pmemlot_rm(const char *path, int flags);

/*
 * PMEMLOT_MAJOR_VERSION and PMEMLOT_MINOR_VERSION provide the current version
 * of the libpmemlot API as provided by this header file.  Applications can
 * verify that the version available at run-time is compatible with the version
 * used at compile-time by passing these defines to pmemlot_check_version().
 */
#define PMEMLOT_MAJOR_VERSION 1
#define PMEMLOT_MINOR_VERSION 1
const char *pmemlot_check_version(unsigned major_required,
	unsigned minor_required);

/*
 * get the last error message
 */
const char *pmemlot_errormsg(void);

#ifdef __cplusplus
}
#endif
#endif	/* libpmemlot.h */
