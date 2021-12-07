// ETEL.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TVersion RTelServer::Version() const
//
//	Get current ETel version
//
	{
	return(TVersion(KEtelMajorVersionNumber,
					KEtelMinorVersionNumber,
					KEtelBuildVersionNumber));
	}

//
// RTelSubSessionBase
//
inline RSessionBase& RTelSubSessionBase::SessionHandle() const
	{ 
	return *iTelSession;
	}

inline void RTelSubSessionBase::SetSessionHandle(RSessionBase& aTelSession)
	{ 
	iTelSession=&aTelSession;
	}

inline TInt RTelSubSessionBase::SubSessionHandle()
	{
	return(RSubSessionBase::SubSessionHandle());
	}
