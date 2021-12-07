/* STDIO_T.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _SYS_STDIO_T_H_
#define _SYS_STDIO_T_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <_ansi.h>

/*
 * Stdio buffers.
 */

struct __sbuf {
	unsigned char *	_base;
	int				_size;
};

/*
 * We need fpos_t for the following, but it doesn't have a leading "_",
 * so we use _fpos_t instead.
 */

typedef long _fpos_t;		/* XXX must match off_t in <sys/types.h> */
							/* (and must be `long' for now) */

/*
 * Stdio state variables.
 *
 * The following always hold:
 *
 *	if (_flags&(__SLBF|__SWR)) == (__SLBF|__SWR),
 *		_lbfsize is -_bf._size, else _lbfsize is 0
 *	if _flags&__SRD, _w is 0
 *	if _flags&__SWR, _r is 0
 *
 * This ensures that the getc and putc macros (or inline functions) never
 * try to write or read from a file that is in `read' or `write' mode.
 * (Moreover, they can, and do, automatically switch from read mode to
 * write mode, and back, on "r+" and "w+" files.)
 *
 * _lbfsize is used only to make the inline line-buffered output stream
 * code as compact as possible.
 *
 * _ub, _up, and _ur are used when ungetc() pushes back more characters
 * than fit in the current _bf, or when ungetc() pushes back a character
 * that does not match the previous one in _bf.  When this happens,
 * _ub._base becomes non-nil (i.e., a stream has ungetc() data iff
 * _ub._base!=NULL) and _up and _ur save the current values of _p and _r.
 */

struct __sFILE {
  unsigned char *_p;			/* current position in (some) buffer */
  int			 _r;			/* read space left for getc() */
  int			 _w;			/* write space left for putc() */
  short			 _flags;		/* flags, below; this FILE is free if 0 */
  short			 _file;			/* fileno, if Unix descriptor, else -1 */
  struct __sbuf	 _bf;			/* the buffer (at least 1 byte, if !NULL) */
  int			 _lbfsize;		/* 0 or -_bf._size, for inline putc */

  /* operations */
  void *		 _cookie;		/* cookie passed to io functions */

  int		(*_read) (void * _cookie, char *_buf, int _n);
  int		(*_write)(void * _cookie, const char *_buf, int _n);
  _fpos_t	(*_seek) (void * _cookie, _fpos_t _offset, int _whence);
  int		(*_close)(void * _cookie);

  /* separate buffer for long sequences of ungetc() */
  struct __sbuf		_ub;		/* ungetc buffer */
  unsigned char *	_up;		/* saved _p when _p is doing ungetc data */
  int				_ur;		/* saved _r when _r is counting ungetc data */

  /* tricks to meet minimum requirements even when malloc() fails */
  unsigned char		_ubuf[3];	/* guarantee an ungetc() buffer */
  unsigned char		_nbuf[1];	/* guarantee a getc() buffer */

  /* separate buffer for fgetline() when line crosses buffer boundary */
  struct __sbuf		_lb;		/* buffer for fgetline() */

  /* Unix stdio files get aligned to block boundaries on fseek() */
  int				_blksize;	/* stat.st_blksize (may be != _bf._size) */
  int				_offset;	/* current lseek offset */

  struct _reent *	_data;		/* pointer back to re-entrancy context block */
};


#ifdef __cplusplus
}
#endif
#endif /* _SYS_STDIO_T_H_ */
