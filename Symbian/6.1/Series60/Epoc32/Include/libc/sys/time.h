/* TIME.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <_ansi.h>

struct timeval {
  long tv_sec;
  long tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};

IMPORT_C int gettimeofday (struct timeval *tp, struct timezone *tzp);

#ifdef __cplusplus
}
#endif
#endif
