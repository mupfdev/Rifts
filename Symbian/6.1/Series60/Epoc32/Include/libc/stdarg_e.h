/* STDARG_E.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/*
 *
 * This is all somewhat tortured because ANSI C says that stdio.h is not supposed 
 * to define va_list: it needs to have access to that data type, but must not use that name.
 * Instead stdio.h should use an __ name, which is safe because it is reserved for 
 * the implementation.  Hence __e32_va_list.
 */

#ifndef _STDARG_E_H
#define _STDARG_E_H

/* EPOC32 definitions, extracted from E32DEFS.H
 */

typedef char* __e32_va_list;
#define va_start(ap,pn) (ap=(__e32_va_list)&pn+((sizeof(pn)+sizeof(int)-1)&~(sizeof(int)-1)),(void)0)
#define va_arg(ap,type) (ap+=((sizeof(type)+sizeof(int)-1)&~(sizeof(int)-1)),(*(type *)(ap-((sizeof(type)+sizeof(int)-1)&~(sizeof(int)-1)))))
#define va_end(ap) (ap=0,(void)0)

#endif
