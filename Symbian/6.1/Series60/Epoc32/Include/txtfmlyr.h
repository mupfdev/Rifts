// TXTFMLYR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTFMLYR_H__
#define __TXTFMLYR_H__

#include <e32std.h>
#include <e32base.h>
#include <txtfmstm.h>
#include <txtfrmat.h>

// forward declarations
class CFormatStream;  
class RReadStream;
class RWriteStream;
class TCharFormatX;

const TUid KNormalParagraphStyleUid={268435531};

//
// Implements layering of formats, and services to re/store sets of format layers.

class CFormatLayer : public CBase
	{
public:
	//
	// Based-on link utilities
	IMPORT_C void Reset();  // Remove all contents of this layer in a leave safe manner.
	IMPORT_C void SetBase(const CFormatLayer* aBaseFormatLayer);  // Set this layer to be based on the specified layer.
	IMPORT_C const CFormatLayer* SenseBase()const;
	IMPORT_C TInt ChainCount()const;  // Returns the number of format layers in the chain, inclusive of itself.
	//
	// Persistence
	virtual void InternalizeL(RReadStream& aStream,const CFormatLayer* aBase=NULL)=0;
	virtual void ExternalizeL(RWriteStream& aStream)const=0;
	//
	//	Restore a format chain where the end of the chain is based on aBase (where aBase may be null).
	IMPORT_C void InternalizeChainL(RReadStream& aStream,const CFormatLayer* aBase=NULL);
	//	Stores a format layer chain of length length-aExcludeCount (or by default the whole chain).
	IMPORT_C void ExternalizeChainL(RWriteStream& aStream,TInt aExcludeCount=0)const;
	//
	// Equality
	virtual TBool IsIdentical(CFormatLayer* aLayer,TBool aCheckBasedOnLink=ETrue)const=0;
	IMPORT_C TBool IsEmpty()const;
private:
	CFormatLayer(const CFormatLayer& aFormatLayer);
	CFormatLayer& operator=(const CFormatLayer& aFormatLayer);
	virtual CFormatLayer* DoCloneL()const=0;
protected:
	CFormatLayer();
	~CFormatLayer();
	virtual CFormatLayer* RestoreNewL(RReadStream& aStream)=0;
	void ExternalizeLayersRecurseL(RWriteStream& aStream,TInt aDescendantCount)const;
	TBool IsIdentical(const TUint8* aPtr,TInt aSize)const;
	const TUint8* Ptr(TInt& aSize)const;
	void CloneLayerL(CFormatLayer* aClone)const;
protected:
	RFormatStream iStore;
	const CFormatLayer* iBasedOn;  // If non-null used to inherit format attributes from the lower layer.
	__DECLARE_TEST;
	};

//
// Implements paragraph format layers.
// Has explicit knowledge of paragraph formats.

class CParaFormatLayer : public CFormatLayer
	{
public:
	IMPORT_C static CParaFormatLayer* NewL();
	IMPORT_C static CParaFormatLayer* NewL(const CParaFormat* aParaFormat,const TParaFormatMask& aMask);
	IMPORT_C static CParaFormatLayer* NewL(RReadStream& aStream);
	static CParaFormatLayer* NewL(const CParaFormatLayer* aLayer);
	static CParaFormatLayer* NewCopyBaseL(const CParaFormatLayer* aLayer);
	// Create a new instance, restoring it from the specified stream.
	// The based on link is NULL. Restores only one layer.
	//
	// Persistence
	IMPORT_C virtual void InternalizeL(RReadStream& aStream,const CFormatLayer* aBase=NULL);	
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream)const;
	//
	// Core methods
	IMPORT_C void SetL(const CParaFormat* aDesiredEffectiveFormat,const TParaFormatMask& aMask);
	IMPORT_C void SenseEffectiveL(CParaFormat* aParaFormat,CParaFormat::TParaFormatGetMode aMode=CParaFormat::EAllAttributes)const;
	IMPORT_C void SenseL(CParaFormat* aParaFormat,TParaFormatMask& aMask,CParaFormat::TParaFormatGetMode aMode=CParaFormat::EAllAttributes)const;
	//
	// Utilities
	inline CParaFormatLayer* CloneL()const;
	IMPORT_C TBool IsIdenticalL(const CParaFormat* aParaFormat,const TParaFormatMask& aMask)const;
	IMPORT_C virtual TBool IsIdentical(CFormatLayer* aLayer,TBool aCheckBasedOnLink=ETrue)const;
	IMPORT_C virtual TUid Type()const;
	IMPORT_C const TUint8* Ptr(TInt& aSize)const;
private:
	//
	// No implementation provided
	CParaFormatLayer(const CParaFormatLayer& aParaFormatLayer);
	CParaFormatLayer& operator=(const CParaFormatLayer& aParaFormatLayer);
	IMPORT_C virtual CFormatLayer* DoCloneL()const;
	void FillParaFormatL(CParaFormat* aParaFormat,TParaFormatMask& aMask,CParaFormat::TParaFormatGetMode aMode)const;
	void CleanupEffectiveFormat(CParaFormat* aParaFormat,TParaFormatMask aMask)const;
	void CleanupBorders(CParaFormat* aParaFormat)const;
protected:
	CParaFormatLayer();
	virtual CFormatLayer* RestoreNewL(RReadStream& aStream);
	};

//
// Implements character format layers.
// Has explicit knowledge of character formats.

class CCharFormatLayer : public CFormatLayer
	{
public:
	IMPORT_C static CCharFormatLayer* NewL();
	IMPORT_C static CCharFormatLayer* NewL(const TCharFormat& aFormat,const TCharFormatMask& aMask);
	IMPORT_C static CCharFormatLayer* NewL(RReadStream& aStream);
	IMPORT_C virtual void InternalizeL(RReadStream& aStream,const CFormatLayer* aBase=NULL);	
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void SetL(const TCharFormat& aCharFormat,const TCharFormatMask& aMask);
	IMPORT_C void SenseEffective(TCharFormat& aCharFormat)const;
	IMPORT_C void Sense(TCharFormat& aCharFormat,TCharFormatMask& aMask)const;
	inline CCharFormatLayer* CloneL()const;
	IMPORT_C virtual TBool IsIdentical(CFormatLayer* aLayer,TBool aCheckBasedOnLink=ETrue)const;
	IMPORT_C TBool IsIdentical(const TCharFormat& aCharFormat,const TCharFormatMask& aMask)const;
	IMPORT_C const TUint8* Ptr(TInt& aSize)const;

	// non-exported public functions
	static CCharFormatLayer* NewL(const CCharFormatLayer* aLayer);
	static CCharFormatLayer* NewCopyBaseL(const CCharFormatLayer* aLayer);
	static CCharFormatLayer* NewL(const TCharFormatX& aFormat,const TCharFormatXMask& aMask);
	void SetL(const TCharFormatX& aCharFormat,const TCharFormatXMask& aMask);
	void SenseEffective(TCharFormatX& aCharFormat)const;
	void Sense(TCharFormatX& aCharFormat,TCharFormatXMask& aMask) const;
	
private:
	CCharFormatLayer();
	virtual CFormatLayer* RestoreNewL(RReadStream& aStream);
	virtual void FillCharFormat(TCharFormatX& aCharFormat,TCharFormatXMask& aMask)const;
	IMPORT_C virtual CFormatLayer* DoCloneL()const;

	CCharFormatLayer(const CCharFormatLayer& aCharFormatLayer); // deliberately unimplemented
	CCharFormatLayer& operator=(const CCharFormatLayer& aCharFormatLayer); // deliberately unimplemented
	};


#include <txtfmlyr.inl>


#endif
