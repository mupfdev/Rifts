// VJDECOMP.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__VJDECOMP_INL_)
#define __VJDECOMP_INL_

inline void CVJDeCompressor::SetFlag(const TUint aFlag)
	{
	iFlags |= aFlag;
	return;
	}
	
inline void CVJDeCompressor::ClearFlag(const TUint aFlag)
	{
	iFlags &= ~aFlag;
	return;
	}

inline TBool CVJDeCompressor::TestFlag(const TUint aFlag)
	{
	return (iFlags & aFlag);
	}

#endif // __VJDECOMP_INL_
