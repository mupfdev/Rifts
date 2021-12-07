/* NETDB_R.H
 * 
 * Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
 */

/*
 * Sundry networking-related functions which uses static data areas or other bits of
 * nastiness.
 */

#ifndef _NETDB_R_H_
#define _NETDB_R_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <netdb.h>
#include <reent.h>
#include <sys/socket.h>
#include <netinet/in.h>

IMPORT_C char*	_inet_ntoa_r (struct _reent*, struct in_addr);
IMPORT_C struct hostent* _gethostbyaddr_r (struct _reent* rp, const char* addr, int length, int format);
IMPORT_C struct hostent* _gethostbyname_r (struct _reent* rp, const char* name);

#ifdef __cplusplus
}
#endif

#endif /* !_NETDB_R_H_ */
