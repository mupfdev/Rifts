/* STDARG.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/*
 *
 * This is all somewhat tortured because ANSI C says that stdio.h is not supposed 
 * to define va_list. stdarg_e.h defines something suitable for stdio.h, and
 * this file sorts out va_list.
 */

#ifndef _STDARG_H
#define _STDARG_H

#include <stdarg_e.h>

#define va_list __e32_va_list

#endif
