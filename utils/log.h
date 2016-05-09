/*
 * Copyright 2003 James Bursa <bursa@users.sourceforge.net>
 * Copyright 2004 John Tytgat <joty@netsurf-browser.org>
 *
 * This file is part of NetSurf, http://www.netsurf-browser.org/
 *
 * NetSurf is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * NetSurf is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NETSURF_LOG_H_
#define _NETSURF_LOG_H_

#include <stdio.h>
#include <stdbool.h>

#include "utils/errors.h"

extern bool verbose_log;

/**
 * Ensures the FILE handle is available to write logging to.
 *
 * This is provided by the frontends if required
 */
typedef bool(nslog_ensure_t)(FILE *fptr);

/**
 * Initialise the logging system.
 *
 * Sets up everything required for logging. Processes the argv passed
 * to remove the -v switch for verbose logging. If necessary ensures
 * the output file handle is available.
 */
extern nserror nslog_init(nslog_ensure_t *ensure, int *pargc, char **argv);

#ifdef NDEBUG
#  define LOG(format, ...) ((void) 0)
#else

extern void nslog_log(const char *file, const char *func, int ln, const char *format, ...) __attribute__ ((format (printf, 4, 5)));

#  ifdef __GNUC__
#    define LOG_FN __PRETTY_FUNCTION__
#    define LOG_LN __LINE__
#  elif defined(__CC_NORCROFT)
#    define LOG_FN __func__
#    define LOG_LN __LINE__
#  else
#    define LOG_FN ""
#    define LOG_LN __LINE__
#  endif

#define LOG(format, args...)						\
	do {								\
		if (verbose_log) {					\
			nslog_log(__FILE__, LOG_FN, LOG_LN, format , ##args); \
		}							\
	} while(0)

#endif

#endif
