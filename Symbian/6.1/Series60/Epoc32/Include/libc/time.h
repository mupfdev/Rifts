/* TIME.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/*
 * Struct and function declarations for dealing with time.
 */

#ifndef _TIME_H_
#define _TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"

#ifndef NULL
#define	NULL	0L
#endif

#include <machine/types.h>	/* Get _CLOCK_T_ and _TIME_T_.  */

#define __need_size_t
#include <stddef.h>


#ifndef __clock_t_defined
typedef _CLOCK_T_ clock_t;
#define __clock_t_defined
#endif

#ifndef __time_t_defined
typedef _TIME_T_ time_t;
#define __time_t_defined
#endif

struct tm
{
  int	tm_sec;		/* seconds (0-59) */
  int	tm_min;		/* minutes (0-59) */
  int	tm_hour;	/* hours since midnight (0-23) */
  int	tm_mday;	/* day of month (1-31) */
  int	tm_mon;		/* month (0-11, January = 0) */
  int	tm_year;	/* years since 1900 */
  int	tm_wday;	/* day of week (0-6, Sunday = 0) */
  int	tm_yday;	/* day of year (0-365, Jan 1st = 0) */
  int	tm_isdst;	/* negative means dst status unknown */
};

IMPORT_C clock_t	clock		(void);
IMPORT_C double		difftime	(time_t _time2, time_t _time1);
IMPORT_C time_t		mktime		(struct tm *_timeptr);
IMPORT_C time_t		time		(time_t *_timer);
IMPORT_C size_t		strftime	(char *_s, size_t _maxsize, const char *_fmt, const struct tm *_t);
#ifndef _REENT_ONLY
IMPORT_C char*		asctime		(const struct tm *_tblock);
IMPORT_C char*		ctime		(const time_t *_time);
IMPORT_C struct tm*	gmtime		(const time_t *_timer);
IMPORT_C struct tm*	localtime	(const time_t *_timer);
#endif

/* Re-entrant versions of the functions that return pointers to
 * a statically allocated buffer. These are internal to the STDLIB
 * implementation and not standard ANSI functions
 */
IMPORT_C char*		asctime_r	(const struct tm *, char *);
IMPORT_C char*		ctime_r		(const time_t *, char *);
IMPORT_C struct tm*	gmtime_r	(const time_t *, struct tm *);
IMPORT_C struct tm*	localtime_r	(const time_t *, struct tm *);

#ifdef __cplusplus
}
#endif
#endif /* _TIME_H_ */
