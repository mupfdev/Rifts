/* CTYPE.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _CTYPE_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _CTYPE_H_

#include "_ansi.h"

IMPORT_C int isalnum(int c);
IMPORT_C int isalpha(int c);
IMPORT_C int iscntrl(int c);
IMPORT_C int isdigit(int c);
IMPORT_C int isgraph(int c);
IMPORT_C int islower(int c);
IMPORT_C int isprint(int c);
IMPORT_C int ispunct(int c);
IMPORT_C int isspace(int c);
IMPORT_C int isupper(int c);
IMPORT_C int isxdigit(int c);
IMPORT_C int tolower(int c);
IMPORT_C int toupper(int c);

/* not strict ansi, but popular nevertheless */

#define isascii(c)	((unsigned)(c)<=0177)
#define toascii(c)	((c)&0177)

#ifndef _STRICT_ANSI
#define _tolower(c)	tolower(c)
#define _toupper(c)	toupper(c)
#endif

#ifdef __cplusplus
}
#endif
#endif /* _CTYPE_H_ */
