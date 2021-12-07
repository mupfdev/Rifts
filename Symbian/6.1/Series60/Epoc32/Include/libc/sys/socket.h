/* SOCKET.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

#ifndef	_SYS_SOCKET_H
#define	_SYS_SOCKET_H

#include "_ansi.h"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Types - may be extended by individual protocols
 */
#define	SOCK_STREAM	1		/* stream socket */
#define	SOCK_DGRAM	2		/* datagram socket */
#define	SOCK_SEQPACKET	3		/* sequenced packet stream */
#define	SOCK_RAW	4		/* raw-protocol interface */

/*
 * Options for use with [gs]etsockopt at the socket level.
 * NB. EPOC32 setsockopt ignores the options with values <= 0
 */
#define	SOL_SOCKET	1		/* options for socket level */

#define	SO_DEBUG	1		/* turn on debugging info recording */
#define	SO_RCVBUF	2		/* receive buffer size */
#define	SO_SNDBUF	3		/* send buffer size */
#define	SO_ERROR	9		/* get error status and clear */
#define	SO_REUSEADDR	0x406		/* reuse local addresses */
#define	SO_BROADCAST	-1		/* permit sending of broadcast msgs */
#define	SO_USELOOPBACK	-2		/* bypass hardware when possible - always true in EPOC32 */
#define	SO_LINGER	-3		/* linger on close if data present */
#define	SO_OOBINLINE	-4		/* leave received OOB data in line */

/*
 * Address families - for EPOC32 these are based on the protocol IDs.
 */
#define	AF_UNSPEC	0		/* unspecified */
#define	AF_LOCAL	0x666		/* local to host (pipes) */
#define	AF_INET		0x0800		/* internetwork: UDP, TCP, etc. */
#define	AF_IRDA		0x0100		/* IrDA */
#define AF_PLP		273		/* Psion link protocol */

/*
 * Protocol families, same as address families
 */
#define	PF_UNSPEC	AF_UNSPEC
#define	PF_LOCAL	AF_LOCAL
#define	PF_INET		AF_INET
#define	PF_IRDA		AF_IRDA
#define PF_PLP		AF_PLP

/*
 * Structure used by EPOC32 to store most addresses.
 * NB. EPOC32 uses 32-bit family and port numbers internally, but they have been
 * left as shorts here for compatibility with code that uses htons()/ntohs() explicitly.
 */
struct sockaddr {
	u_short	sa_family;		/* address family */
	u_short sa_port;		/* port number - a common feature of most protocols */
	char	sa_data[24];		/* up to 24 bytes of direct address */
};

/*
 * Maximum queue length specifiable by listen.
 */
#define	SOMAXCONN	5

#define	MSG_PEEK	1		/* peek at incoming message */
#define	MSG_OOB		1		/* write out-of-band data */

IMPORT_C int accept(int, struct sockaddr *, size_t *);
IMPORT_C int bind(int, struct sockaddr *, size_t);
IMPORT_C int connect(int, struct sockaddr *, size_t);
IMPORT_C int getpeername(int, struct sockaddr *, size_t *);
IMPORT_C int getsockname(int, struct sockaddr *, size_t *);
IMPORT_C int getsockopt(int, int, int, void *, size_t *);
IMPORT_C int listen(int, int);
IMPORT_C int recv(int, char *, size_t, int);
IMPORT_C int recvfrom(int, char *, size_t, int, struct sockaddr *, size_t *);
IMPORT_C int send(int, const char *, size_t, int);
IMPORT_C int sendto(int, const char *, size_t, int, struct sockaddr *, size_t);
IMPORT_C int setsockopt(int, int, int, void *, size_t);
IMPORT_C int socket(int, int, int);
IMPORT_C int shutdown(int, int);

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SOCKET_H */
