/* STRING.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/*
 * Definitions for memory and string functions.
 */

#ifndef _STRING_H_
#define	_STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"

#ifndef __GCC32__
#define memcpy	_e32memcpy	// GCC has memcpy as an intrinsic
#endif

#define __need_size_t
#include <stddef.h>

#ifndef NULL
#define NULL 0L
#endif

IMPORT_C void*	memchr		(const void*, int, size_t);
IMPORT_C int 	memcmp		(const void*, const void*, size_t);
IMPORT_C void*	memcpy		(void* dst, const void* src, size_t);
IMPORT_C void*	memmove		(void*, const void*, size_t);
IMPORT_C void*	memset		(void*, int, size_t);
IMPORT_C char*	strcat		(char *, const char *);
IMPORT_C wchar_t* wcscat	(wchar_t *, const wchar_t *);
IMPORT_C char*	strchr		(const char *, int);
IMPORT_C int	strcmp		(const char *, const char *);
IMPORT_C int	wcscmp		(const wchar_t *, const wchar_t *);
IMPORT_C int	strcoll		(const char *, const char *);
IMPORT_C char*	strcpy		(char *, const char *);
IMPORT_C wchar_t* wcscpy	(wchar_t *, const wchar_t *);
IMPORT_C size_t	strcspn		(const char *, const char *);
IMPORT_C char*	strerror	(int);
IMPORT_C size_t	strlen		(const char *);
IMPORT_C size_t	wcslen		(const wchar_t *);
IMPORT_C char*	strncat		(char *, const char *, size_t);
IMPORT_C int	strncmp		(const char *, const char *, size_t);
IMPORT_C char*	strncpy		(char *, const char *, size_t);
IMPORT_C char*	strpbrk		(const char *, const char *);
IMPORT_C char*	strrchr		(const char *, int);
IMPORT_C size_t	strspn		(const char *, const char *);
IMPORT_C char*	strstr		(const char *, const char *);
IMPORT_C size_t	strxfrm		(char *, const char *, size_t);

#ifndef _REENT_ONLY
IMPORT_C char*	strtok		(char *, const char *);
#endif

IMPORT_C char*	strtok_r	(char *, const char *, char **);

/* EPOC32 bonus functions - _STRICT_ANSI */

IMPORT_C int	strcasecmp	(const char *, const char *);
IMPORT_C char*	strdup		(const char *);
IMPORT_C wchar_t*	wcsdup		(const wchar_t *);
IMPORT_C int	strncasecmp	(const char *, const char *, size_t);
IMPORT_C char 	*rindex		(const char *, int);
IMPORT_C char 	*index		(const char *, int);

#ifndef _STRICT_ANSI
int	 bcmp		(const char *, const char *, size_t);
void	 bcopy		(const char *src, char *dst, size_t);
void	 bzero		(char *, size_t);
int	 ffs		(int);
void	*memccpy	(void*, const void*, int, size_t);
char 	*strsep		(char **, const char *);
void	 swab		(const char *, char *, size_t);
#endif /* ! _STRICT_ANSI */

#ifdef __cplusplus
}
#endif
#endif /* _STRING_H_ */
