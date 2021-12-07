/* STDLIB_R.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/*
 * Extension of <stdlib.h> with reentrant functions.
 */


#ifndef _STDLIB_R_H_
#define _STDLIB_R_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <sys/reent.h>

/* EPOC32 malloc uses the thread heap, so it is already thread-safe
 * and no _malloc_r variants are needed.
 */
#define _malloc_r(x,n)		malloc(n)
#define _calloc_r(x,n,m)	calloc(n,m)
#define _realloc_r(x,p,n)	realloc(p,n)
#define _free_r(x,p)		free(p)

IMPORT_C char*	_dtoa_r		(struct _reent *, double, int, int, int *, int*, char**);
IMPORT_C void	_mstats_r	(struct _reent *, char *);
IMPORT_C int	_system_r	(struct _reent *, const char *);
IMPORT_C int	_wsystem_r	(struct _reent *, const wchar_t *);
IMPORT_C int	_rand_r		(struct _reent *);
IMPORT_C void	_srand_r	(struct _reent *, unsigned);
IMPORT_C int	_setenv_r	(struct _reent *, const char *, const char *, int);
IMPORT_C void	_unsetenv_r	(struct _reent *, const char *);
IMPORT_C char*	_getenv_r	(struct _reent *, const char *);
IMPORT_C int	_wsetenv_r	(struct _reent *, const wchar_t *, const wchar_t *, int);
IMPORT_C void	_wunsetenv_r	(struct _reent *, const wchar_t *);
IMPORT_C wchar_t*	_wgetenv_r	(struct _reent *, const wchar_t *);
IMPORT_C unsigned long _strtoul_r(struct _reent *,const char *, char **, int);

/* It's possible to override exit() by supplying abort(), exit() and _exit()
 * The generic exit() and abort() routines look like
 *
 *   void exit(int code) _ATTRIBUTE((noreturn))
 *	{
 *	_atexit_processing_r(_REENT);
 *	_exit(code);
 *	}
 *   void abort(void) _ATTRIBUTE((noreturn))
 *	{
 *	_exit(1);
 *	}
 *
 * which then allows your _exit() to capture all exits from ESTLIB, 
 * except for __assert() which calls abort().
 */

IMPORT_C void _atexit_processing_r (struct _reent *);

#ifdef __cplusplus
}
#endif
#endif /* _STDLIB_R_H_ */
