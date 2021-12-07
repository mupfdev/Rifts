/* IOCTL.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef _SYS_IOCTL_H_
#define _SYS_IOCTL_H_

#include <sys/serial.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ioctls under EPOC32 are only loosely related to ioctls in other systems
 * The _IOR(), _IOW() and _IOWR() macros are provided for documentation purposes,
 * to indicate the appropriate form of the third parameter
 */

#define _IOW(n,T)	(n)	/* passes in a T value via the supplied T* ptr */
#define _IOR(n,T)	(n)	/* returns a T value via the supplied T* ptr */ 
#define _IOWR(n,T)	(n)	/* both of the above */

IMPORT_C int ioctl (int, int, void*);

/* number of bytes available to be read - cf BSD FIONREAD 
 */
#define E32IONREAD	_IOR( 1,int)	

/* ioctl-based form of select with infinite timeout - specify a mask of selectable
 * states and receive back the mask of triggering states
 */
#define E32IOSELECT	_IOWR(2,int)	
#   define E32SELECT_READ	0x01
#   define E32SELECT_WRITE	0x02
#   define E32SELECT_EXCEPT	0x04



//ioctls for serial port			values may change
#define COMMIOCTL_SETSIGNALS		1
#define	COMMIOCTL_GETSIGNALS		2
#define COMMIOCTL_SETCONFIG			3
#define	COMMIOCTL_GETCONFIG			4
#define	COMMIOCTL_BREAK				5
#define	COMMIOCTL_SETREADTIMEOUT	6
#define	COMMIOCTL_GETREADTIMEOUT	7
#define	COMMIOCTL_SETREADTHRESHOLD	8
#define	COMMIOCTL_GETREADTHRESHOLD	9
#define	COMMIOCTL_SETBUFFERLENGTH	10
#define	COMMIOCTL_GETBUFFERLENGTH	11
#define	COMMIOCTL_NOTIFYSUPPORTED	12
#define	COMMIOCTL_NOTIFY			0x400d

#define	REAL_COMMIOCTL_NOTIFY		13		// = COMMIOCTL_NOTIFY-0x4000


#ifdef __cplusplus
}
#endif
#endif
