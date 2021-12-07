// TXTFMSTM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// PRIVATE HEADER FILE CONTAINING IMPLEMENTATION SPECIFIC CLASSES

#ifndef __TXTFMSTM_H__
#define __TXTFMSTM_H__

#include <e32std.h>
#include <txtfrmat.h>

// forward declarations
class RReadStream;
class RWriteStream;
class TCharFormatX;
class TCharFormatXMask;

// stores format attributes as bytecode
class RFormatStream
	{
public:
	RFormatStream::RFormatStream();
	void CopyL(const RFormatStream& aSource);
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	void Reset();
	const TUint8* Ptr(TInt& aSize) const;
	void SetParaFormatL(const CParaFormat* aDesiredFormat,const TParaFormatMask& aDesiredMask,const CParaFormat* aCurrentFormat);
	void SenseParaFormatL(CParaFormat* aParaFormat,TParaFormatMask& aMask,CParaFormat::TParaFormatGetMode aMode)const;
	void SetCharFormatL(const TCharFormatX& aCharFormat,const TCharFormatXMask& aMask);
	void SenseCharFormat(TCharFormatX& aCharFormat,TCharFormatXMask& aMask)const;

private:
	void AllocL(TInt aSize);
	TInt Length(TUint8*& aPtr,TTextFormatAttribute aType)const;
	TInt DoCalcSizeParaFormat(const CParaFormat* aDesiredFormat,TParaFormatMask aMask,const CParaFormat* aCurrentFormat);
	void DoSetParaFormat(const CParaFormat* aDesiredFormat,TParaFormatMask aMask,const CParaFormat* aCurrentFormat);
	void RemoveRedundantCharFormat(TCharFormatMask& aMask,const TCharFormatX& aFormat,const TCharFormatX& aEffectiveFormat);
	TInt DoCalcSizeCharFormat(const TCharFormatX& aCharFormat,const TCharFormatXMask& aMask);
	void DoStoreCharFormat(const TCharFormatX& aCharFormat,TCharFormatXMask aMask);
	TUint8* StoreBullet(TUint8* aPtr,const TBullet& aSource);
	TUint8* StoreBorder(TUint8* aPtr,TTextFormatAttribute aType,const TParaBorder& aSource);
	TUint8* StoreTab(TUint8* aPtr,const TTabStop& aSource);
	TInt StoreTabs(TUint8*& aPtr,const CParaFormat* aDesiredFormat,const CParaFormat* aCurrentFormat,TBool aStoreData);
	TInt MergeTabLists(TUint8*& aPtr,const CParaFormat* aDesiredFormat,TInt aDesiredTabCount,
					   const CParaFormat* aCurrentFormat,TInt aCurrentTabCount,TBool aStoreData);
	void StoreAllTabs(TUint8*& aPtr,const CParaFormat* aSource);
	TUint8* Store(TUint8* aPtr,const TRgb& aRgb);
	TUint8* Store(TUint8* aPtr,const TTypeface& aTypeface);
	TUint8* ReadValue(TUint8* aPtr,TRgb& aRgb)const;
	TUint8* ReadValue(TUint8* aPtr,TTypeface& aTypeface)const;
	TUint8* ReadValue(TUint8* aPtr,TParaBorder& aBorder)const;
	TUint8* ReadValue(TUint8* aPtr,TBullet& aBullet)const;
	TUint8* ReadTabL(TUint8* aPtr,CParaFormat* aTarget)const;

	TUint8* iBase;	// start of stored bytecode
	TUint8* iEnd;	// end of stored bytecode
	__DECLARE_TEST;
	};

#endif
