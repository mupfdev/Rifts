// btsdp.inl
//
// Copyright (c) 2000-2001 Symbian Ltd.  All rights reserved.
//

inline TBool TAttrRange::IsInRange(TSdpAttributeID aAttrId) const
	{
	return aAttrId >= iStart && aAttrId <= iEnd;
	}

inline TBool TAttrRange::IsContiguousWith(TSdpAttributeID aAttrId) const 
	{
	return (aAttrId >= iStart - 1) && (aAttrId <= iEnd + 1);
	}

inline TBool TAttrRange::IsContiguousWith(TAttrRange aRange) const
	{
	return IsContiguousWith(aRange.iStart) || IsContiguousWith(aRange.iEnd);
	}

inline TBool CSdpAttrIdMatchList::InMatchList(TSdpAttributeID aAttrId) const
	{
	TInt pos;
	return InMatchList(aAttrId, pos);
	}

inline TInt CSdpAttrIdMatchList::Count() const
	{
	return iList->Count();
	}

inline void CElementParser::SetBuilder(MSdpElementBuilder* aBuilder)
	{
	iBuilder = aBuilder;
	}

inline MSdpElementBuilder* CElementParser::Builder()
	{
	return iBuilder;
	}

// Template class TSdpIntBuf
template <class T>
inline TSdpIntBuf<T>::TSdpIntBuf(const T &aRef)
	{
	DoSetLength(sizeof(T));
	SdpUtil::PutUint(iBuf, TInt64(aRef), sizeof(T));
	}

inline TSdpIntBuf<TUint32>::TSdpIntBuf(const TUint32 &aRef)
: TSdpIntBuf<TUint>(aRef)
	{
	}

inline TSdpIntBuf<TUint16>::TSdpIntBuf(const TUint16 &aRef)
: TSdpIntBuf<TUint>(0)
	{
	DoSetLength(sizeof(TUint16));
	TUint16 num(aRef);
	iBuf[1] = TUint8(num & 0xff);
	num >>= 8;
	iBuf[0] = TUint8(num & 0xff);
	}

