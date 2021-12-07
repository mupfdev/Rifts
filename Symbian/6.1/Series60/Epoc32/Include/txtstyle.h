// TXTSTYLE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTSTYLE_H__
#define __TXTSTYLE_H__

#include <e32std.h>
#include <e32base.h>
#include "txtfmlyr.h"


// Classes declared in this file:
class CParagraphStyle;
class CStyleTable;
//
// Classes referenced in this file:
class RReadStream;
class RWriteStream;

const TInt KMaxParagraphStyleName=0x20;
typedef TBuf<KMaxParagraphStyleName> TParagraphStyleName;

const TUid KUserDefinedParagraphStyleUid={268435535};


//
// Defines a paragraph style, and the paragraph style to use next.

class RParagraphStyleInfo
	{
public:
	inline RParagraphStyleInfo();
	inline RParagraphStyleInfo(CParagraphStyle* aStyle,CParagraphStyle* aStyleForNextPara=NULL);
	inline void Discard();
public:
	CParagraphStyle* iStyle;  // owned
	CParagraphStyle* iStyleForNextPara;  // referenced, may be NULL
	};


//
// Defines a paragraph style as a named para format with richer attributes.

class CParagraphStyle : public CParaFormatLayer
	{
public:
	friend class CStyleList;
	friend class CRichTextIndex;
	enum TStylePasteMode
		{
		EAddNewStyles,
		EConvertNewStyles,
		EIgnoreNewStyles
		};
	enum TApplyParaStyleMode
		{
		ERetainAllSpecificFormats,
		ERetainNoSpecificFormats,
		ERetainSpecificParaFormat,
		ERetainSpecificCharFormat
		};
public:
	// Creates style & bases it on the speicfied global layers - the 'Normal' style.
	IMPORT_C static CParagraphStyle* NewL(const CParaFormatLayer& aGlobalParaFormatLayer,const CCharFormatLayer& aGlobalCharFormatLayer);
	IMPORT_C ~CParagraphStyle();
	//
	// Getters/Setters
	inline CCharFormatLayer* CharFormatLayer()const;
	inline TInt OutlineLevel()const;
	inline void SetOutlineLevel(TInt aOutlineLevel);
	//
	// Utilities
	IMPORT_C virtual TUid Type()const;
	inline void SetType(TUid aType);
	inline CParagraphStyle* CloneL()const;
private:
	CParagraphStyle();	
	void ConstructL(const CParaFormatLayer& aGlobalParaFormatLayer,
							 const CCharFormatLayer& aGlobalCharFormatLayer);
	IMPORT_C virtual CFormatLayer* DoCloneL()const;
	//
	// Save/Load
	static CParagraphStyle* NewL(RReadStream& aStream,const CParaFormatLayer& aGlobalParaFormatLayer,const CCharFormatLayer& aGlobalCharFormatLayer);
	virtual void InternalizeL(RReadStream& aStream,const CFormatLayer* aParaLayerBase,const CFormatLayer* aCharLayerBase);
	virtual void ExternalizeL(RWriteStream& aStream)const;
private:
	TUid iType;
	TInt iOutlineLevel;
	CCharFormatLayer* iCharFormatLayer;  // should never be NULL
public:
	TParagraphStyleName iName;
	};


const TInt KMaxStyleListGranularity=0x04;
class CStyleList : public CBase
	{
public:
	IMPORT_C static CStyleList* NewL(TInt aCapacity=KMaxStyleListGranularity);
	IMPORT_C static CStyleList* NewL(RReadStream& aStream,
									const CParaFormatLayer* aGlobalParaFormatLayer,
									const CCharFormatLayer* aGlobalCharFormatLayer);
	IMPORT_C ~CStyleList();
	//
	inline const RParagraphStyleInfo& operator[](TInt aIndex)const;
	inline RParagraphStyleInfo& operator[](TInt aIndex);
	IMPORT_C const RParagraphStyleInfo& At(TInt aIndex)const;
	IMPORT_C RParagraphStyleInfo& At(TInt aIndex);
	//
	// Persistence
	IMPORT_C TStreamId StoreL(CStreamStore& aStore)const;
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream,
								const CParaFormatLayer* aGlobalParaFormatLayer,
								const CCharFormatLayer* aGlobalCharFormatLayer);
	//
	// Table maintenance
	IMPORT_C void Reset();  // Delete all styles from the style list.
	IMPORT_C TInt AppendL(RParagraphStyleInfo* aStyleSet);
	IMPORT_C void Remove(CParagraphStyle* aStyle);
	IMPORT_C TInt SetStyleToFollow(const RParagraphStyleInfo& aStyleSet);  // returns KErrNone or KErrNotFound
	IMPORT_C CStyleList* DeepCloneL()const;
	//
	// Getters
	IMPORT_C RParagraphStyleInfo* PtrByName(const TParagraphStyleName& aName)const;
	IMPORT_C RParagraphStyleInfo* PtrByType(const TUid aType)const;
	IMPORT_C TInt IndexByPtr(const CParaFormatLayer* aPtr)const;
	// Returns KErrNotFound if the specified style is not located in the style list.
	//
	IMPORT_C TInt IndexByName(const TDesC& aName)const;
	// Returns KErrNotFound if the specified style name is not located in the style list.
	//
	// General
	inline TInt Count()const;
protected:
	IMPORT_C CStyleList();
	IMPORT_C void ConstructL(TInt aGranularity);
private:
	void KillStyleList();
private:
	CArrayFixFlat<RParagraphStyleInfo>* iList;
	__DECLARE_TEST;
	};


#include <txtstyle.inl>

#endif