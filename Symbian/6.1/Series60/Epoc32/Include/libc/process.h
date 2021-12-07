/* PROCESS.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef __PROCESS_H_
#define __PROCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int execl(const char *path, const char *argv0, ...);
extern int execle(const char *path, const char *argv0, ... /*, char * const *envp */);
extern int execlp(const char *path, const char *argv0, ...);
extern int execlpe(const char *path, const char *argv0, ... /*, char * const *envp */);

extern int execv(const char *path, char * const *argv);
extern int execve(const char *path, char * const *argv, char * const *envp);
extern int execvp(const char *path, char * const *argv);
extern int execvpe(const char *path, char * const *argv, char * const *envp);


#ifdef __cplusplus
}
#endif

#endif


