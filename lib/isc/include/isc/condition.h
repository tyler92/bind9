/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, you can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * See the COPYRIGHT file distributed with this work for additional
 * information regarding copyright ownership.
 */

#pragma once

/*! \file */

#include <errno.h>

#include <isc/error.h>
#include <isc/lang.h>
#include <isc/mutex.h>
#include <isc/result.h>
#include <isc/string.h>
#include <isc/types.h>
#include <isc/util.h>

typedef pthread_cond_t isc_condition_t;

#define isc_condition_init(cond)                          \
	{                                                 \
		int _ret = pthread_cond_init(cond, NULL); \
		ERRNO_CHECK(pthread_cond_init, _ret);     \
	}

#ifdef ISC_TRACK_PTHREADS_OBJECTS
#define isc_condition_wait(cp, mp) isc__condition_wait(cp, *mp)
#else /* ISC_TRACK_PTHREADS_OBJECTS */
#define isc_condition_wait(cp, mp) isc__condition_wait(cp, mp)
#endif /* ISC_TRACK_PTHREADS_OBJECTS */

#define isc__condition_wait(cp, mp) \
	RUNTIME_CHECK(pthread_cond_wait((cp), (mp)) == 0)

#define isc_condition_signal(cp) RUNTIME_CHECK(pthread_cond_signal((cp)) == 0)

#define isc_condition_broadcast(cp) \
	RUNTIME_CHECK(pthread_cond_broadcast((cp)) == 0)

#define isc_condition_destroy(cp) RUNTIME_CHECK(pthread_cond_destroy((cp)) == 0)

ISC_LANG_BEGINDECLS

isc_result_t
isc_condition_waituntil(isc_condition_t *, isc_mutex_t *, isc_time_t *);

ISC_LANG_ENDDECLS
