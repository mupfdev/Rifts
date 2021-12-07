// ET_PHONE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline void CPhoneFactoryBase::Inc()
	{
	CObject::Inc();
	}

inline TVersion CPhoneFactoryBase::TsyVersionNumber() const
	{
	return iVersion;
	}

inline void CSubSessionExtBase::Inc()
	{
	CObject::Inc();
	}

inline TBool CBuffer::OverFlow() const
	{
	return iOverFlow;
	}

inline TBool CBuffer::BufferFull() const
	{
	return iBufferFull;
	}

