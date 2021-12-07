/* ASSERT.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"

#undef assert

#ifdef NDEBUG           /* required by ANSI standard */
#define assert(p)  	((void)0)
#else
#define assert(e)       ((e) ? (void)0 : __assert(__FILE__, __LINE__, #e))
#endif /* NDEBUG */

IMPORT_C void __assert(const char *, int, const char *);

#ifdef __cplusplus
}
#endif
