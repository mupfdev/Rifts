/* STDLIB.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/*
 * Definitions for common types, variables, and functions.
 */


#ifndef _STDLIB_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _STDLIB_H_

#include "_ansi.h"

#define __need_size_t
#define __need_wchar_t
#include <stddef.h>

#include <sys/reent.h>

typedef struct 
{
  int quot; /* quotient */
  int rem; /* remainder */
} div_t;

#define	labs abs
#define	ldiv div
#define ldiv_t div_t

#ifndef NULL
#define NULL 0L
#endif

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define RAND_MAX 0x7fffffff

#define MB_CUR_MAX 3

/* Workaround a built-in prototype in MSVC 5.0 */
#define atexit	_epoc32_atexit
IMPORT_C int	_epoc32_atexit	(void (*_func)(void));

IMPORT_C void	abort	(void);
IMPORT_C int	abs		(int);
IMPORT_C double	atof	(const char *_nptr);
IMPORT_C int	atoi	(const char *_nptr);
#define atol	atoi
IMPORT_C void*	bsearch	(const void * _key,
		       const void * _base,
		       size_t _nmemb,
		       size_t _size,
		       int (*_compar)(const void *, const void *));
IMPORT_C void*	calloc	(size_t _nmemb, size_t _size);
IMPORT_C div_t	div	(int _numer, int _denom);
IMPORT_C void	exit	(int _status) _ATTRIBUTE((noreturn));
IMPORT_C void	free	(void *);
IMPORT_C char*  getenv	(const char *_string);
IMPORT_C wchar_t*  wgetenv	(const wchar_t *_string);
IMPORT_C void*	malloc	(size_t _size);

IMPORT_C int	mbtowc	 (wchar_t *pwc, const char *s, size_t n);
IMPORT_C int	wctomb	 (char *s, wchar_t wc);
IMPORT_C int	mbstowcs (wchar_t *pwc, const char *s, size_t n);
IMPORT_C int	wcstombs (char *s, const wchar_t *pwc, size_t n);
IMPORT_C int    mblen    (const char * string, size_t size);

IMPORT_C void	qsort	(void * _base, size_t _nmemb, size_t _size, int(*_compar)(const void *, const void *));
IMPORT_C int	rand	(void);
IMPORT_C void*	realloc	(void * _r, size_t _size);
IMPORT_C void	srand	(unsigned _seed);
IMPORT_C double	strtod	(const char *_n, char **_end_PTR);
IMPORT_C long	strtol	(const char *_n, char **_end_PTR, int _base);
IMPORT_C unsigned long strtoul		(const char *_n_PTR, char **_end_PTR, int _base);
IMPORT_C int	system	(const char *_string);
IMPORT_C int	wsystem	(const wchar_t *_string);

/* not STRICT ANSI, but available anyway... */

IMPORT_C int	setenv	(const char *_string, const char *_value, int _overwrite);
IMPORT_C void	unsetenv (const char *_name);
IMPORT_C int	wsetenv	(const wchar_t *_string, const wchar_t *_value, int _overwrite);
IMPORT_C void	wunsetenv (const wchar_t *_name);

#ifndef _STRICT_ANSI
float	strtodf	(const char *_n, char **_end_PTR);
float	atoff	(const char *_nptr);

void	cfree	(void *, void *);
int	putenv	(const char *_string);

char *	gcvt	(double,int,char *);
char *	gcvtf	(float,int,char *);
char *	fcvt	(double,int,int *,int *);
char *	fcvtf	(float, int,int *,int *);
char *	ecvt	(double, int,int *,int *);
char *	ecvtbuf	(double, int, int*, int*, char *);
char *	fcvtbuf	(double, int, int*, int*, char *);
char *	ecvtf	(float, int,int *,int *);
char *	dtoa	(double, int, int, int *, int*, char**);
#endif /* ! _STRICT_ANSI */

/* FIXME: 4.10.7: Multibyte character functions are missing.  */

#ifdef __cplusplus
}
#endif
#endif /* _STDLIB_H_ */
