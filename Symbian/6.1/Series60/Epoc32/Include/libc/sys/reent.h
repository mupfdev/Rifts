/* REENT.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/* WARNING: All identifiers here must begin with an underscore.  This file is
   included by stdio.h and others and we therefore must only use identifiers
   in the namespace allotted to us.
 */

#ifndef _SYS_REENT_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _SYS_REENT_H_

#include <_ansi.h>
#include <sys/stdio_t.h>	/* _sFILE type */
#include <time.h>		/* for struct tm */

struct _glue 
{
  struct _glue *_next;
  int _niobs;
  struct __sFILE *_iobs;
};

/*
 * atexit() support
 */

#define	_ATEXIT_SIZE 32	/* must be at least 32 to guarantee ANSI conformance */

struct _atexit {
	struct	_atexit *_next;			/* next in list */
	int	_ind;				/* next index in this table */
	void	(*_fns[_ATEXIT_SIZE])(void);	/* the table itself */
};


/*
 * struct _reent
 *
 * This structure contains *all* globals needed by the library.
 * It's raison d'etre is to facilitate threads by making all library routines
 * reentrant.  IE: All state information is contained here.
 */

#define _ASCTIME_SIZE	(26+8)	/* 26 min, plus caution factor! */
#define _MINNARROWBUFSIZE	100
struct _reent
{
  /* local copy of errno */
  int _errno;
  struct __sFILE _sf[3];		/* first three file descriptors: stdin, stdout, stderr */

  char *_scanpoint;		/* used by strtok */
  char _asctime[_ASCTIME_SIZE];	/* used by asctime */
  struct tm _struct_tm;		/* used by gmtime */
  long _next[2];		/* used by rand/srand (64-bit seed for EPOC32) */
  int  _inc;			/* used by tmpnam */
  char _tmpnam[37];		/* used by tmpnam & inet_ntoa */
  wchar_t _wtmpnam[37];		/* used by tmpnam & inet_ntoa */
  void *_netdb;			/* used by gethostbyaddr and similar netdb functions */
 
  int _current_category;	/* used by setlocale */
  const char *_current_locale;

  int __sdidinit;		/* 1 means stdio has been init'd */

  void (*__cleanup)(struct _reent *);

  /* atexit stuff */
  struct _atexit *_atexit;	/* points to head of LIFO stack */
  struct _atexit _atexit0;	/* one guaranteed table, required by ANSI */

  /* signal info */
  void (**(_sig_func))();

  struct _glue __sglue;		/* root of glue chain for additional sFILE structures */

  char **environ;
  int environ_slots;

  char* _pNarrowEnvBuffer;
  int _NEBSize;

  void *_system;		/* Pointer to a C++ POSIX System object - Hands off! */
};

/* The struct _reent is managed on a per-thread basis by EPOC32, so there
 * is no global variable _impure_pointer and everyone has to use _REENT.
 */
IMPORT_C void		_reclaim_reent	(struct _reent*);
IMPORT_C void		_REENT_INIT	(struct _reent*);
IMPORT_C struct _reent*	ImpurePtr	(void);
IMPORT_C void		_init_reent	(struct _reent*,void*);

/* Support for explicit release of all STDLIB resources belonging to this thread
 */
IMPORT_C void CloseSTDLIB();

#define _REENT (ImpurePtr())
#define __errno_r(ptr) ((ptr)->_errno)

#ifdef __cplusplus
}
#endif

#endif /* _SYS_REENT_H_ */
