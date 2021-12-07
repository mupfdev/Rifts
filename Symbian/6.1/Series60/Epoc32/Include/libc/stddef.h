/* STDDEF.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _STDDEF_H_
#define _STDDEF_H_

/* There seems to be a lot of nonsense about _need_wchar_t etc., but for
 * STDLIB we have cut the Gordian knot and done the simple thing.
 */

typedef unsigned short int wchar_t;
typedef long		ptrdiff_t;
typedef unsigned int	size_t;

/* Offset of member MEMBER in a struct of type TYPE.  */
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#endif /* _STDDEF_H_ */
