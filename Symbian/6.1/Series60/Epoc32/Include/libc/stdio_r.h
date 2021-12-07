/* STDIO_R.H
 * 
 * Portions copyright (c) 1990-1999 Symbian Ltd.  All rights reserved.
 */

/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Based on @(#)stdio.h	5.3 (Berkeley) 3/15/86
 */

#ifndef _STDIO_R_H_
#define	_STDIO_R_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <sys/reent.h>

#define _stdin_r(x)	(&((x)->_sf[0]))
#define _stdout_r(x)	(&((x)->_sf[1]))
#define _stderr_r(x)	(&((x)->_sf[2]))

/*
 * Reentrant versions of the <stdio.h> functions
 */

IMPORT_C void	_cleanup_r	(struct _reent *);
IMPORT_C FILE *	_fdopen_r	(struct _reent *, int, const char *);
IMPORT_C FILE *	_wfdopen_r	(struct _reent *, int, const wchar_t *);
IMPORT_C FILE *	_fopen_r	(struct _reent *, const char *, const char *);
IMPORT_C FILE *	_wfopen_r	(struct _reent *, const wchar_t *, const wchar_t *);
IMPORT_C int	_getchar_r	(struct _reent *);
IMPORT_C char *	_gets_r		(struct _reent *, char *);
IMPORT_C int	_iprintf_r	(struct _reent *, const char *, ...);
IMPORT_C int	_mkstemp_r	(struct _reent *, char *);
IMPORT_C char *	_mktemp_r	(struct _reent *, char *);
IMPORT_C void	_perror_r	(struct _reent *, const char *);
IMPORT_C int	_printf_r	(struct _reent *, const char *, ...);
IMPORT_C int	_putchar_r	(struct _reent *, int);
IMPORT_C int	_puts_r		(struct _reent *, const char *);
IMPORT_C int	_scanf_r	(struct _reent *, const char *, ...);
IMPORT_C int	_sprintf_r	(struct _reent *, char *, const char *, ...);
IMPORT_C char *	_tempnam_r	(struct _reent *, char *, char *);
IMPORT_C FILE *	_tmpfile_r	(struct _reent *);
IMPORT_C char *	_tmpnam_r	(struct _reent *, char *);
IMPORT_C wchar_t *	_wtmpnam_r	(struct _reent *, wchar_t *);
IMPORT_C int	_vfprintf_r	(struct _reent *, FILE *, const char *, __e32_va_list);

IMPORT_C int	_popen3_r	(struct _reent *, const char *cmd, const char *mode, char** envp, int fids[3]);
IMPORT_C int	_wpopen3_r	(struct _reent *, const wchar_t *cmd, const wchar_t *mode, wchar_t** envp, int fids[3]);

#ifdef __cplusplus
}
#endif
#endif /* _STDIO_H_ */
