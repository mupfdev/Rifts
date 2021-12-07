/* REENT.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/* The reentrant system calls here serve two purposes:

   1) Provide reentrant versions of the system calls the ANSI C library
      requires.
   2) Provide these system calls in a namespace clean way.

   It is intended that *all* system calls that the ANSI C library needs
   be declared here.  It documents them all in one place.  All library access
   to the system is via some form of these functions.

   There are three ways a target may provide the needed syscalls.

   1) Define the reentrant versions of the syscalls directly.
      (eg: _open_r, _close_r, etc.).  Please keep the namespace clean.
      When you do this, set "syscall_dir" to "syscalls" in configure.in,
      and add -DREENTRANT_SYSCALLS_PROVIDED to target_cflags in configure.in.

   2) Define namespace clean versions of the system calls by prefixing
      them with '_' (eg: _open, _close, etc.).  Technically, there won't be
      true reentrancy at the syscall level, but the library will be namespace
      clean.
      When you do this, set "syscall_dir" to "syscalls" in configure.in.

   3) Define or otherwise provide the regular versions of the syscalls
      (eg: open, close, etc.).  The library won't be reentrant nor namespace
      clean, but at least it will work.
      When you do this, add -DMISSING_SYSCALL_NAMES to target_cflags in
      configure.in.

   Stubs of the reentrant versions of the syscalls exist in the libc/reent
   source directory and are used if REENTRANT_SYSCALLS_PROVIDED isn't defined.
   They use the native system calls: _open, _close, etc. if they're available
   (MISSING_SYSCALL_NAMES is *not* defined), otherwise open, close, etc.
   (MISSING_SYSCALL_NAMES *is* defined).
 */

/* WARNING: All identifiers here must begin with an underscore.  This file is
   included by stdio.h and others and we therefore must only use identifiers
   in the namespace allotted to us.  */

#ifndef _REENT_H_
#define _REENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define __need_size_t
#include <stddef.h>

#include <sys/reent.h>
#include <sys/_types.h>
#include <sys/types.h>

/* FIXME: not namespace clean */
struct stat;
struct sockaddr;

/* Reentrant versions of system calls.  
 * Most of these are thread-safe in EPOC32 anyway
 */

IMPORT_C int	_chdir_r	(struct _reent *, const char *);
IMPORT_C int	_wchdir_r	(struct _reent *, const wchar_t *);
IMPORT_C int	_chmod_r	(struct _reent *, const char *, mode_t);
IMPORT_C int	_wchmod_r	(struct _reent *, const wchar_t *, mode_t);
IMPORT_C int	_close_r	(struct _reent *, int);
IMPORT_C int	_dup_r		(struct _reent *, int);
IMPORT_C int	_dup2_r		(struct _reent *, int, int);
IMPORT_C int	_fcntl_r	(struct _reent *, int, int, int);
IMPORT_C int	_fork_r		(struct _reent *);
IMPORT_C int	_fstat_r	(struct _reent *, int, struct stat *);
IMPORT_C int	_fsync_r	(struct _reent *, int);
IMPORT_C char*	_getcwd_r	(struct _reent *, char *, size_t);
IMPORT_C wchar_t*	_wgetcwd_r	(struct _reent *, wchar_t *, size_t);
IMPORT_C int	_ioctl_r	(struct _reent *, int, int, void *);
IMPORT_C int	_kill_r		(struct _reent *, int, int);
IMPORT_C int	_link_r		(struct _reent *, const char *, const char *);
IMPORT_C off_t	_lseek_r	(struct _reent *, int, _off_t, int);
IMPORT_C int	_mkdir_r	(struct _reent *, const char *, mode_t);
IMPORT_C int	_wmkdir_r	(struct _reent *, const wchar_t *, mode_t);
IMPORT_C int	_open_r		(struct _reent *, const char *, int, int);
IMPORT_C int	_wopen_r		(struct _reent *, const wchar_t *, int, int);
IMPORT_C int	_read_r		(struct _reent *, int, char *, size_t);
IMPORT_C char *	_realpath_r	(struct _reent *, const char *, char *);
IMPORT_C wchar_t *	_wrealpath_r	(struct _reent *, const wchar_t *, wchar_t *);
IMPORT_C int	_rename_r	(struct _reent *, const char *_old, const char *_new);
IMPORT_C int	_wrename_r	(struct _reent *, const wchar_t *_old, const wchar_t *_new);
IMPORT_C int	_rmdir_r	(struct _reent *, const char *);
IMPORT_C int	_wrmdir_r	(struct _reent *, const wchar_t *);
IMPORT_C int	_stat_r		(struct _reent *, const char *, struct stat *);
IMPORT_C int	_wstat_r		(struct _reent *, const wchar_t *, struct stat *);
IMPORT_C int	_unlink_r	(struct _reent *, const char *);
IMPORT_C int	_wunlink_r	(struct _reent *, const wchar_t *);
IMPORT_C int	_wait_r		(struct _reent *, int *);
IMPORT_C int	_waitpid_r	(struct _reent *, int, int *, int);
IMPORT_C int	_write_r	(struct _reent *, int, const char *, size_t);

IMPORT_C int	_accept_r	(struct _reent*, int, struct sockaddr *, size_t *);
IMPORT_C int	_bind_r		(struct _reent*, int, struct sockaddr *, size_t);
IMPORT_C int	_connect_r	(struct _reent*, int, struct sockaddr *, size_t);
IMPORT_C int	_getpeername_r	(struct _reent*, int, struct sockaddr *, size_t *);
IMPORT_C int	_getsockname_r	(struct _reent*, int, struct sockaddr *, size_t *);
IMPORT_C int	_getsockopt_r	(struct _reent*, int, int, int, void *, size_t *);
IMPORT_C int	_listen_r	(struct _reent*, int, int);
IMPORT_C int	_recv_r		(struct _reent*, int, char *, size_t, int);
IMPORT_C int	_recvfrom_r	(struct _reent*, int, char *, size_t, int, struct sockaddr *, size_t *);
IMPORT_C int	_send_r		(struct _reent*, int, const char *, size_t, int);
IMPORT_C int	_sendto_r	(struct _reent*, int, const char *, size_t, int, struct sockaddr *, size_t);
IMPORT_C int	_setsockopt_r	(struct _reent*, int, int, int, void *, size_t);
IMPORT_C int	_socket_r	(struct _reent*, int, int, int);
IMPORT_C int	_shutdown_r	(struct _reent*, int, int);

#define _remove_r(r,x)	_unlink_r(r,x)
#define _wremove_r(r,x)	_wunlink_r(r,x)

#ifdef __cplusplus
}
#endif
#endif /* _REENT_H_ */
