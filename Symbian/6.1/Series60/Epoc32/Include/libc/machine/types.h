/* TYPES.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef	_MACHTYPES_H_
#define	_MACHTYPES_H_

#define	_CLOCK_T_   signed int	/* clock() - EPOC32 TInt */
#define	_TIME_T_    signed int	/* time()  - EPOC32 TInt */

#define CLOCKS_PER_SEC 1		/* machine dependent */
#define CLK_TCK CLOCKS_PER_SEC

#endif	/* _MACHTYPES_H_ */


