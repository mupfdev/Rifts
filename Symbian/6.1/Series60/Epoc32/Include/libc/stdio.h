/* STDIO.H
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
 *	@(#)stdio.h	5.3 (Berkeley) 3/15/86
 */

/*
 * NB: to fit things in six character monocase externals, the
 * stdio code uses the prefix `__s' for stdio objects, typically
 * followed by a three-character attempt at a mnemonic.
 */

#ifndef _STDIO_H_
#define	_STDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"

#define	_FSTDIO			/* ``function stdio'' */

#define __need_size_t
#include <stddef.h>

#include <stdarg_e.h>		/* defines __e32_va_list */

#include <sys/stdio_t.h>	/* Definition of _fpos_t and struct __sFILE */

typedef _fpos_t fpos_t;
typedef struct __sFILE FILE;

#define	__SLBF	0x0001		/* line buffered */
#define	__SNBF	0x0002		/* unbuffered */
#define	__SRD	0x0004		/* OK to read */
#define	__SWR	0x0008		/* OK to write */
	/* RD and WR are never simultaneously asserted */
#define	__SRW	0x0010		/* open for reading & writing */
#define	__SEOF	0x0020		/* found EOF */
#define	__SERR	0x0040		/* found error */
#define	__SMBF	0x0080		/* _buf is from malloc */
#define	__SAPP	0x0100		/* fdopen()ed in append mode - so must  write to end */
#define	__SSTR	0x0200		/* this is an sprintf/snprintf string */
#define	__SOPT	0x0400		/* do fseek() optimisation */
#define	__SNPT	0x0800		/* do not do fseek() optimisation */
#define	__SOFF	0x1000		/* set iff _offset is in fact correct */
#define	__SMOD	0x2000		/* true => fgetline modified _p text */

/*
 * The following three definitions are for ANSI C, which took them
 * from System V, which stupidly took internal interface macros and
 * made them official arguments to setvbuf(), without renaming them.
 * Hence, these ugly _IOxxx names are *supposed* to appear in user code.
 *
 * Although these happen to match their counterparts above, the
 * implementation does not rely on that (so these could be renumbered).
 */
#define	_IOFBF	0		/* setvbuf should set fully buffered */
#define	_IOLBF	1		/* setvbuf should set line buffered */
#define	_IONBF	2		/* setvbuf should set unbuffered */

#ifndef NULL
#define	NULL	0L
#endif

#define	BUFSIZ	1024
#define	EOF	(-1)

#define	FOPEN_MAX	20	/* must be <= OPEN_MAX <sys/syslimits.h> */
#define	FILENAME_MAX	256	/* must be <= PATH_MAX <sys/syslimits.h> */
#define P_tmpdir        "/System/temp/"
#define WIDEP_tmpdir   L"/System/temp/"
#define	L_tmpnam	34	/* ?:/System/temp/t%x.%x */

#ifndef SEEK_SET
#define	SEEK_SET	0	/* set file offset to offset */
#endif
#ifndef SEEK_CUR
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#endif
#ifndef SEEK_END
#define	SEEK_END	2	/* set file offset to EOF plus offset */
#endif

#define	TMP_MAX		26

/* Function interface to the "constants" stdin, stdout and stderr.
 * These functions guarantee to return a fixed value, so that it
 * will be possible to use expressions such as
 *
 *   if (fp != stdout) 
 *		fclose(fp);
 * 
 * with complete confidence. Unfortunately it will rule out initialising
 * global variables with stdin/stdout/stderr, as in the common idiom:
 *
 *   static FILE *log = stderr;
 *
 * This isn't currently possible with EPOC32.
 */

IMPORT_C FILE *__stdin  (void);
IMPORT_C FILE *__stdout (void);
IMPORT_C FILE *__stderr (void);

#define	stdin	(__stdin())
#define	stdout	(__stdout())
#define	stderr	(__stderr())

/*
 * Functions defined in ANSI C standard.
 */

IMPORT_C FILE *	tmpfile		(void);
IMPORT_C char *	tmpnam		(char *);
IMPORT_C wchar_t *	wtmpnam		(wchar_t *);
IMPORT_C int	fclose		(FILE *);
IMPORT_C int	fflush		(FILE *);
IMPORT_C FILE *	freopen		(const char *, const char *, FILE *);
IMPORT_C FILE *	wfreopen		(const wchar_t *, const wchar_t *, FILE *);
IMPORT_C void	setbuf		(FILE *, char *);
IMPORT_C int	setvbuf		(FILE *, char *, int, size_t);
IMPORT_C int	fprintf		(FILE *, const char *, ...);
IMPORT_C int	fscanf		(FILE *, const char *, ...);
IMPORT_C int	printf		(const char *, ...);
IMPORT_C int	scanf		(const char *, ...);
IMPORT_C int	sscanf		(const char *, const char *, ...);
IMPORT_C int	vfprintf	(FILE *, const char *, __e32_va_list);
IMPORT_C int	vprintf		(const char *, __e32_va_list);
IMPORT_C int	vsprintf	(char *, const char *, __e32_va_list);
IMPORT_C int	fgetc		(FILE *);
IMPORT_C char *  fgets		(char *, int, FILE *);
IMPORT_C int	fputc		(int, FILE *);
IMPORT_C int	fputs		(const char *, FILE *);
IMPORT_C int	getc		(FILE *);
IMPORT_C int	getchar		(void);
IMPORT_C char *  gets		(char *);
IMPORT_C int	putc		(int, FILE *);
IMPORT_C int	putchar		(int);
IMPORT_C int	puts		(const char *);
IMPORT_C int	ungetc		(int, FILE *);
IMPORT_C size_t	fread		(void*, size_t _size, size_t _n, FILE *);
IMPORT_C size_t	fwrite		(const void* , size_t _size, size_t _n, FILE *);
IMPORT_C int	fgetpos		(FILE *, fpos_t *);
IMPORT_C int	fseek		(FILE *, long, int);
IMPORT_C int	fsetpos		(FILE *, const fpos_t *);
IMPORT_C long	ftell		(FILE *);
IMPORT_C void	rewind		(FILE *);
IMPORT_C void	clearerr	(FILE *);
IMPORT_C int	feof		(FILE *);
IMPORT_C int	ferror		(FILE *);
IMPORT_C void    perror		(const char *);
#ifndef _REENT_ONLY
IMPORT_C FILE *	fopen		(const char *_name, const char *_type);
IMPORT_C FILE *	wfopen		(const wchar_t *_name, const wchar_t *_type);
IMPORT_C int	sprintf		(char *, const char *, ...);
#endif

/*
 * Routines in POSIX 1003.1.
 */

IMPORT_C int	fileno		(FILE *);

#ifndef _REENT_ONLY
IMPORT_C FILE *	fdopen		(int, const char *);
IMPORT_C FILE *	wfdopen		(int, const wchar_t *);
#endif

/* The name _cleanup is rather well-known... */
IMPORT_C void	_cleanup	(void);

/* 
 * EPOC32 support for multiple processes
 */

IMPORT_C int	popen3	(const char *cmd, const char *mode, char** envp, int fids[3]);
IMPORT_C int	wpopen3	(const wchar_t *cmd, const wchar_t *mode, wchar_t** envp, int fids[3]);


#ifndef _STRICT_ANSI

int	getw		(FILE *);
int	putw		(int, FILE *);
void    setbuffer	(FILE *, char *, int);
int	setlinebuf	(FILE *);

/*
 * Stdio function-access interface.
 */
FILE	*funopen (const void* _cookie,
			int	(*readfn) (void* _cookie, char *_buf, int _n),
			int	(*writefn)(void* _cookie, const char *_buf, int _n),
			fpos_t	(*seekfn) (void* _cookie, fpos_t _off, int _whence),
			int	(*closefn)(void* _cookie));

#define	fropen(cookie, fn) funopen(cookie, fn, (int (*)())0, (fpos_t (*)())0, (int (*)())0)
#define	fwopen(cookie, fn) funopen(cookie, (int (*)())0, fn, (fpos_t (*)())0, (int (*)())0)

#define	getchar()	getc(stdin)
#define	putchar(x)	putc(x, stdout)

#define	L_cuserid	9		/* posix says it goes in stdio.h :( */

#endif /* _STRICT_ANSI */

#ifdef __cplusplus
}
#endif
#endif /* _STDIO_H_ */
