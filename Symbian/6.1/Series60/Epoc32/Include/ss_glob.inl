// SS_GLOB.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __SS_GLOB_INL__
#define __SS_GLOB_INL__

inline void SockManGlobals::Set(TSockManData * aGlobals)
	{ Dll::SetTls(aGlobals); }

inline TSockManData* SockManGlobals::Get()
	{ TSockManData * d=(TSockManData *)Dll::Tls(); return d; }

#endif
