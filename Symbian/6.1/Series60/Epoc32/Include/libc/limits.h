/* LIMITS.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef	_LIMITS_H_
#define	_LIMITS_H_
/* Number of bits in a `char'.	*/
#define	CHAR_BIT	8

/* Maximum length of any multibyte character in any locale.
   Locale-writers should change this as necessary.  */
#define	MB_LEN_MAX	2

/* Minimum and maximum values a `signed char' can hold.  */
#define	SCHAR_MIN	(-128)
#define	SCHAR_MAX	127

/* Maximum value an `unsigned char' can hold.  (Minimum is 0.)  */
#define	UCHAR_MAX	255U

/* Minimum and maximum values a `char' can hold.  
 * The sign of "char" is probably dictated by a command-line switch to
 * your compiler. 
 * MSVC will define _CHAR_UNSIGNED if the /J option is used.
 * GCC uses --unsigned-char (and friends) to override the default for
 * the target processor and defines a symbol __CHAR_UNSIGNED__
 * if appropriate.
 */
#if defined(__CHAR_UNSIGNED__) || defined(_CHAR_UNSIGNED)
#define	CHAR_MIN	0
#define	CHAR_MAX	UCHAR_MAX
#else
#define	CHAR_MIN	SCHAR_MIN
#define	CHAR_MAX	SCHAR_MAX
#endif

/* Minimum and maximum values a `signed short int' can hold.  */
#define	SHRT_MIN	(-32768)
#define	SHRT_MAX	32767

/* Maximum value an `unsigned short int' can hold.  (Minimum is 0.)  */
#define	USHRT_MAX	65535

/* Minimum and maximum values a `signed int' can hold.  */
#define	INT_MIN	(- INT_MAX - 1)
#define	INT_MAX	2147483647

/* Maximum value an `unsigned int' can hold.  (Minimum is 0.)  */
#define	UINT_MAX	4294967295U

/* Minimum and maximum values a `signed long int' can hold.  */
#define	LONG_MIN	INT_MIN
#define	LONG_MAX	INT_MAX

/* Maximum value an `unsigned long int' can hold.  (Minimum is 0.)  */
#define	ULONG_MAX	UINT_MAX

#endif	/* limits.h  */
