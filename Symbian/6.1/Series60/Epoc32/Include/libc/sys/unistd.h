/* UNISTD.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _SYS_UNISTD_H
#define _SYS_UNISTD_H
#ifdef __cplusplus
extern "C" {
#endif
#include <_ansi.h>
#include <sys/types.h>
#define __need_size_t
#include <stddef.h>

IMPORT_C int	access		(const char *_path, int _amode );
IMPORT_C int	waccess		(const wchar_t *_path, int _amode );
IMPORT_C int    chdir		(const char *_path );
IMPORT_C int    wchdir		(const wchar_t *_path );
IMPORT_C int    chmod		(const char *_path, mode_t _mode );
IMPORT_C int    wchmod		(const wchar_t *_path, mode_t _mode );
IMPORT_C int    close		(int _fildes );
IMPORT_C int    dup		(int _fildes );
IMPORT_C int    dup2		(int _fildes, int _fildes2 );
IMPORT_C int    fsync		(int _fildes );
IMPORT_C char*	getcwd		(char *_buf, size_t _size );
IMPORT_C wchar_t*	wgetcwd		(wchar_t *_buf, size_t _size );
IMPORT_C int	gethostname	(char *_buf, size_t _size );
IMPORT_C int    isatty		(int _fildes );
IMPORT_C off_t  lseek		(int _fildes, off_t _offset, int _whence );
IMPORT_C int	open		(const char *, int, ...);
IMPORT_C int	wopen		(const wchar_t *, int, ...);
IMPORT_C int    read		(int _fildes, char *_buf, size_t _nbyte );
IMPORT_C int	rename		(const char *, const char *);
IMPORT_C int	wrename		(const wchar_t *, const wchar_t *);
IMPORT_C int    rmdir		(const char *_path );
IMPORT_C int    wrmdir		(const wchar_t *_path );
IMPORT_C int    unlink		(const char *_path );
IMPORT_C int    wunlink		(const wchar_t *_path );
IMPORT_C int    write		(int _fildes, const char *_buf, size_t _nbyte );
IMPORT_C void	_exit		(int _status ) _ATTRIBUTE((noreturn));

/* NB. open is also declared in fcntl.h */

IMPORT_C pid_t   getpid		(void );
IMPORT_C unsigned sleep		(unsigned int _seconds );

#define remove(x)       unlink(x)
#define wremove(x)       wunlink(x)

unsigned  alarm		(unsigned _secs );
int     chown		(const char *_path, uid_t _owner, gid_t _group );
char    *ctermid	(char *_s );
char    *cuserid	(char *_s );
int     execl		(const char *_path, const char *, ... );
int     execle		(const char *_path, const char *, ... );
int     execlp		(const char *_file, const char *, ... );
int     execv		(const char *_path, char * const _argv[] );
int     execve		(const char *_path, char * const _argv[], char * const _envp[] );
int     execvp		(const char *_file, char * const _argv[] );
pid_t   fork		(void );
long    fpathconf	(int _fd, int _name );
gid_t   getegid		(void );
uid_t   geteuid		(void );
gid_t   getgid		(void );
int     getgroups	(int _gidsetsize, gid_t _grouplist[] );
char    *getlogin	(void );
size_t  getpagesize	(void);
pid_t   getpgrp		(void );
pid_t   getppid		(void );
uid_t   getuid		(void );
int     link		(const char *_path1, const char *_path2 );
long    pathconf	(char *_path, int _name );
int     pause		(void );
int     pipe		(int _fildes[2] );
void *  sbrk		(size_t incr);
int     setgid		(gid_t _gid );
int     setpgid		(pid_t _pid, pid_t _pgid );
pid_t   setsid		(void );
int     setuid		(uid_t _uid );
long    sysconf		(int _name );
pid_t   tcgetpgrp	(int _fildes );
int     tcsetpgrp	(int _fildes, pid_t _pgrp_id );
char    *ttyname	(int _fildes );

long	sysconf		(int _name);

# define	_SC_ARG_MAX	0
# define	_SC_CHILD_MAX	1
# define	_SC_CLK_TCK	2
# define	_SC_NGROUPS_MAX	3
# define	_SC_OPEN_MAX	4
/* no _SC_STREAM_MAX */
# define	_SC_JOB_CONTROL	5
# define	_SC_SAVED_IDS	6
# define	_SC_VERSION	7
# define        _SC_PAGESIZE    8
# define	_PC_LINK_MAX	0
# define	_PC_MAX_CANON	1
# define	_PC_MAX_INPUT	2
# define	_PC_NAME_MAX	3
# define	_PC_PATH_MAX	4
# define	_PC_PIPE_BUF	5
# define	_PC_CHOWN_RESTRICTED	6
# define	_PC_NO_TRUNC	7
# define	_PC_VDISABLE	8


# define	F_OK	0
# define	R_OK	4
# define	W_OK	2
# define	X_OK	1

# define	SEEK_SET	0
# define	SEEK_CUR	1
# define	SEEK_END	2

#ifdef __svr4__
# define _POSIX_JOB_CONTROL	1
# define _POSIX_SAVED_IDS	1
# define _POSIX_VERSION	199009L
#endif

#define STDIN_FILENO    0       /* standard input file descriptor */
#define STDOUT_FILENO   1       /* standard output file descriptor */
#define STDERR_FILENO   2       /* standard error file descriptor */

# ifndef	_POSIX_SOURCE
#  define	MAXNAMLEN	256	/* E32STD.H: KMaxName */	
# endif		/* _POSIX_SOURCE */

# define	MAXPATHLEN	256	/* E32STD.H: KMaxFullName */

#ifdef __cplusplus
}
#endif
#endif
