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
 * libpmemlot.c -- entry points for libpmemlot
 */

#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/param.h>

#include "pmemcommon.h"
#include "libpmemlot.h"
#include "pmemlot.h"
#include "pool.h"
#include "check.h"

#ifdef USE_RPMEM
#include "rpmem_common.h"
#include "rpmem_util.h"
#endif

/*
 * libpmemlot_init -- load-time initialization for libpmemlot
 *
 * Called automatically by the run-time loader.
 */
__attribute__((constructor))
static void
libpmemlot_init(void)
{
	common_init(PMEMLOT_LOG_PREFIX, PMEMLOT_LOG_LEVEL_VAR,
		PMEMLOT_LOG_FILE_VAR, PMEMLOT_MAJOR_VERSION,
		PMEMLOT_MINOR_VERSION);
	LOG(3, NULL);
#ifdef USE_RPMEM
	util_remote_init();
	rpmem_util_cmds_init();
#endif
}

/*
 * libpmemlot_fini -- libpmemlot cleanup routine
 *
 * Called automatically when the process terminates.
 */
__attribute__((destructor))
static void
libpmemlot_fini(void)
{
	LOG(3, NULL);
#ifdef USE_RPMEM
	util_remote_fini();
	rpmem_util_cmds_fini();
#endif
	common_fini();
}

/*
 * pmemlot_check_version -- see if library meets application version
 *	requirements
 */
const char *
pmemlot_check_version(unsigned major_required, unsigned minor_required)
{
	LOG(3, "major_required %u minor_required %u",
			major_required, minor_required);

	if (major_required != PMEMLOT_MAJOR_VERSION) {
		ERR("libpmemlot major version mismatch (need %u, found %u)",
			major_required, PMEMLOT_MAJOR_VERSION);
		return out_get_errormsg();
	}

	if (minor_required > PMEMLOT_MINOR_VERSION) {
		ERR("libpmemlot minor version mismatch (need %u, found %u)",
			minor_required, PMEMLOT_MINOR_VERSION);
		return out_get_errormsg();
	}

	return NULL;
}

/*
 * pmemlot_errormsg -- return last error message
 */
const char *
pmemlot_errormsg(void)
{
	return out_get_errormsg();
}

