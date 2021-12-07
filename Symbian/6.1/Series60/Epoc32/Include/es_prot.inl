// ES_PROT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline void CServProviderBase::SetNotify(MSocketNotify * aSocket)
	{ iSocket=aSocket; }

inline TInt CProtocolBase::RefCount() const
	{ return iRefCount; }

inline void CResolverProvdBase::SetNotify(MResolverNotify * aNotifier)
	{ iNotify=aNotifier; }


