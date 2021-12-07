// TXTRICH.H
//
// Copyright (C) 1997-1999 Symbian Ltd. All rights reserved.
//

#ifndef __TXTRICH_H__
#define __TXTRICH_H__

#include <e32std.h>
#include <e32base.h>
#include <txtglobl.h>
#include <txtstyle.h>
#include <mparser.h>
#include <medobsrv.h>


// forward references
class CRichTextIndex;
class CStreamStore;
class CStoreMap;
class MPictureFactory;
class MRichTextStoreResolver;
class TCharFormatX;
class TCharFormatXMask;
class CParserData;


// UIDs
const TUid KRichTextStyleDataUid = { 268450335 };
const TUid KClipboardUidTypeRichText = { 268450336 };
const TUid KClipboardUidTypeRichTextWithStyles = { 268450337 };
const TUid KRichTextMarkupDataUid = { 268435558 };


/*
The rich text component where each paragraph can have a different paragraph format, and
each character can have a different character format..
*/
class CRichText : public CGlobalText
	{
public:
	enum TParaType {ESinglePara, EMultiPara};
public:
	// Create new rich text component whose sole content is an end-of-document character.	
	IMPORT_C static CRichText* NewL(const CParaFormatLayer* aGlobalParaLayer, const CCharFormatLayer* aGlobalCharLayer,
									TDocumentStorage aStorage = ESegmentedStorage,
									TInt aDefaultTextGranularity = EDefaultTextGranularity,
									TParaType aParaType = EMultiPara);
	// Create new rich text component, supporting STYLES, whose sole content is an end-of-document character.
	IMPORT_C static CRichText* NewL(const CParaFormatLayer* aGlobalParaLayer, const CCharFormatLayer* aGlobalCharLayer,
									const CStyleList& aStyleList,
									TDocumentStorage aStorage = ESegmentedStorage,
									TInt aDefaultTextGranularity = EDefaultTextGranularity,
									TParaType aParaType = EMultiPara);
	// Restore into new rich text, using the specified global layers.
	IMPORT_C static CRichText* NewL(const CStreamStore& aStore, TStreamId aStreamId,
									const CParaFormatLayer* aGlobalParaLayer, const CCharFormatLayer* aGlobalCharLayer,
									MTextFieldFactory* aFieldFactory = NULL,
									TDocumentStorage aStorage = ESegmentedStorage);
	// Restore into new rich text, using the specified layers, store & picture factory.
	IMPORT_C static CRichText* NewL(const CStreamStore& aStore, TStreamId aStreamId,
									const CParaFormatLayer* aGlobalParaLayer, const CCharFormatLayer * aGlobalCharLayer,
									MPictureFactory* aPictureFactory, MRichTextStoreResolver* aStoreResolver,
									MTextFieldFactory* aFieldFactory = NULL,
									TDocumentStorage aStorage = ESegmentedStorage);
	IMPORT_C virtual ~CRichText();
	//
	// Default persist functions - Deferred loading of pictures
	IMPORT_C void RestoreWithStyleListL(const CStreamStore& aStore, TStreamId aStreamId, const CStyleList& aExternalStyleList);
	//
	IMPORT_C virtual void StoreComponentsL(CStreamStore& aStore, CStoreMap& aMap) const;
	IMPORT_C virtual void RestoreComponentsL(const CStreamStore& aStore);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	//
	// Custom persist functions
	IMPORT_C void ExternalizeStyleDataL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeStyleDataL(RReadStream& aStream);
	//
	IMPORT_C void StoreMarkupComponentsL(CStreamStore& aStore, CStoreMap& aMap) const;
	IMPORT_C void ExternalizeMarkupDataL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeMarkupDataL(RReadStream& aStream);
	//
	// Utility persist functions
	IMPORT_C void SetPictureFactory(MPictureFactory* aPictureFactory, MRichTextStoreResolver* aStoreResolver);
	inline MPictureFactory* PictureFactory() const;
	inline MRichTextStoreResolver* StoreResolver() const;
	IMPORT_C TPictureHeader PictureHeader(TInt aPos) const;
	IMPORT_C void DropPictureOwnership(TInt aPos);		// delete picture character. Forget but don't delete picture.
	IMPORT_C void DetachFromStoreL(CPicture::TDetach aDegree);
	IMPORT_C void DetachFromStoreL(CPicture::TDetach aDegree, TInt aPos, TInt aLength);
	IMPORT_C TBool HasMarkupData() const;
	//
	// Copy/Paste
	IMPORT_C virtual void CopyToStoreL(CStreamStore& aStore, CStreamDictionary& aDictionary, TInt aPos, TInt aLength) const;
	IMPORT_C virtual TInt PasteFromStoreL(const CStreamStore& aStore, const CStreamDictionary& aDictionary, TInt aPos);
	IMPORT_C TInt PasteFromStoreL(const CStreamStore& aStore, const CStreamDictionary& aDictionary, TInt aPos, CParagraphStyle::TStylePasteMode aStylePasteMode);
	//
	// Content modifier functions
	IMPORT_C virtual void Reset();
	IMPORT_C virtual void InsertL(TInt aPos, const TChar& aChar);  // Insert a single character.
	IMPORT_C virtual void InsertL(TInt aPos, const TDesC& aBuf);
	IMPORT_C void InsertL(TInt aPos, const TPictureHeader& aHeader);  // Insert a picture header.
	//
	// aPos is the position of the character being deleted, *not* the current cursor position!
	IMPORT_C virtual TBool DeleteL(TInt aPos, TInt aLength);  // Call this for a delete-forward.
	//
	// Leave-safe delete for removing content from *within* a single paragraph only
	IMPORT_C void DeleteFromParagraph(TInt aPos, TInt aLength);
	//
	// Leave-safe delete for removing *entire* paragraphs
	IMPORT_C void DeleteParagraph(TInt aPos, TInt aLength);
	//
	// Special behaviour format modifier functions.
	// Call this when applying a character format to a zero length selection, eg, turning bold on.
	IMPORT_C void SetInsertCharFormatL(const TCharFormat& aFormat, const TCharFormatMask& aMask, TInt aPos);
	//
	// Call this on every cursor movement, page up/down etc...
	IMPORT_C void CancelInsertCharFormat();
	//
	// Delete content, but preserve phrase format if aPos is at a phrase boundary.
	// aPos is the position of the character being deleted, *not* the current cursor position!
	IMPORT_C TBool DelSetInsertCharFormatL(TInt aPos, TInt aLength);
	//
	// MLaydoc implementation
	IMPORT_C virtual void GetParagraphFormatL(CParaFormat* aFormat, TInt aPos) const;
	IMPORT_C virtual void GetChars(TPtrC& aView, TCharFormat& aFormat, TInt aPos) const;
	IMPORT_C virtual TInt GetPictureSizeInTwips(TSize& aSize, TInt aPos) const;
	IMPORT_C virtual CPicture* PictureHandleL(TInt aPos, MLayDoc::TForcePictureLoad aForceLoad = MLayDoc::EForceLoadTrue) const;
	//
	// MFormatText implementation
	// Used only by dialog writers, since they are not interested in the text, but require knowledge
	// of attributes whose values change across the specified range.
	IMPORT_C virtual void GetParaFormatL(CParaFormat* aFormat, TParaFormatMask& aVaries, TInt aPos, TInt aLength,
										CParaFormat::TParaFormatGetMode aMode = CParaFormat::EAllAttributes) const;
	IMPORT_C virtual void ApplyParaFormatL(const CParaFormat* aFormat, const TParaFormatMask& aMask, TInt aPos, TInt aLength);
	IMPORT_C virtual void GetCharFormat(TCharFormat& aFormat, TCharFormatMask& aVaries, TInt aPos, TInt aLength) const;
	IMPORT_C virtual void ApplyCharFormatL(const TCharFormat& aFormat, const TCharFormatMask& aMask, TInt aPos, TInt aLength);
	//
	//
	IMPORT_C void GetSpecificCharFormat(TCharFormat& aFormat, TCharFormatMask& aMask, TInt aPos) const;
	IMPORT_C void GetSpecificCharFormatRight(TCharFormat& aFormat, TCharFormatMask& aMask, TInt aPos) const;
	IMPORT_C void GetSpecificParagraphFormatL(CParaFormat* aFormat, TParaFormatMask& aMask, TInt aPos) const;
	//
	// Paragraph style implementation
	IMPORT_C void ApplyParagraphStyleL(const CParagraphStyle& aStyle, TInt aPos, TInt aLength, CParagraphStyle::TApplyParaStyleMode aMode);
	inline void NotifyStyleDeletedL(const CParagraphStyle* aStyle);
	IMPORT_C void NotifyStyleChangedL(const CParagraphStyle* aTo, const CParagraphStyle* aFrom);
	IMPORT_C const CParaFormatLayer* ParagraphStyle(TBool& aStyleChangesOverRange, TInt aPos, TInt aLength) const;
	//
	// StyleList implementation
	inline TBool StyleListPresent() const;
	inline CStyleList* StyleList() const;
	inline TInt StyleCount() const;
	inline void SetStyleListExternallyOwned(TBool aExternallyOwned);
	IMPORT_C void SetStyleListExternallyOwned(const CStyleList& aStyleList);
	inline TBool StyleListExternallyOwned() const;
	//
	// Utility functions
	IMPORT_C void RemoveSpecificParaFormatL(TInt aPos, TInt aLength);  
	IMPORT_C void RemoveSpecificCharFormatL(TInt aPos, TInt aLength);
	IMPORT_C TInt PictureCount() const;
	IMPORT_C virtual TInt ParagraphCount() const;
	IMPORT_C virtual TInt CharPosOfParagraph(TInt& aLength, TInt aParaOffset) const;
	IMPORT_C virtual TInt ParagraphNumberForPos(TInt& aPos) const;
	IMPORT_C virtual TEtextComponentInfo ComponentInfo() const;
	//
	// Text field implementation
	IMPORT_C virtual void UpdateFieldL(TInt aPos);  // updates the field at aPos
	// finds number of fields in range. Includes the field containing aPos, if applicable
	// aInfo is set to the first field in the range (if any are found)
	//
	// Speciality functions
	IMPORT_C void AppendTakingSolePictureOwnershipL(const CRichText& aSource);
	IMPORT_C void AppendParagraphL(TInt aReplicas = 1);
	IMPORT_C virtual void SetHasChanged(TBool aHasChanged);

	// non-exported public functions
	void ApplyExtendedCharFormatL(const TCharFormatX& aFormat, const TCharFormatXMask& aMask, TInt aPos, TInt aLength);
	void GetExtendedCharFormat(TCharFormatX& aFormat, TCharFormatXMask& aVaries, TInt aPos, TInt aLength) const;
	void GetTextAndExtendedFormat(TPtrC& aText, TCharFormatX& aFormat, TInt aPos) const;

private:
	CRichText(const CRichText& aRichText);
	CRichText& operator=(const CRichText& aRichText);
	void KillStyleList();
	void KillIndex();
	TBool CreateEmptyMarkupComponentL();
	void CreateAndGenerateMarkupComponentL();
	void GenerateMarkupL();
	void CompletePastePlainTextL(TInt aPos,TInt aCharacterCount);
	TInt DoPasteRtFromStoreL(const CStreamStore& aStore, const CStreamDictionary& aDictionary, TInt aPos, CParagraphStyle::TStylePasteMode aStylePasteMode);
	TBool IndexPresent() const;
	inline void SetParaTypeIsSingle(TBool aBool);
	inline TBool ParaTypeIsSingle() const;
	void SetExtendedInsertCharFormatL(const TCharFormatX& aFormat, const TCharFormatXMask& aMask, TInt aPos);
	void GetSpecificCharFormatLeftRight(TCharFormat& aFormat,
		TCharFormatMask& aMask, TInt aPos, TBool aLeft) const;

protected:
	IMPORT_C CRichText(const CParaFormatLayer* aGlobalParaLayer, const CCharFormatLayer* aGlobalCharLayer,
					   CStyleList* aStyleList = NULL);
	// New constructL's - to be merged post 057
	IMPORT_C void ConstructL(TDocumentStorage aStorage, TInt aDefaultTextGranularity, TParaType aParaType);
	IMPORT_C void ConstructL(const CStreamStore& aStore, TStreamId aStreamId, MPictureFactory* aFactory, MRichTextStoreResolver* aStoreResolver,
							 MTextFieldFactory* aFieldFactory=NULL,
							 TDocumentStorage aStorage = ESegmentedStorage);
	//
	void InternalizeL(RReadStream& aStream, const CStyleList* aExternalStyleList);
	IMPORT_C void DoExternalizeStyleDataL(RWriteStream& aStream) const;
	IMPORT_C void DoInternalizeStyleDataL(RReadStream& aStream);
	void DoInternalizeStyleDataL(RReadStream& aStream, const CStyleList* aExternalStyleList);
	IMPORT_C void DoExternalizeMarkupDataL(RWriteStream& aStream) const;
	IMPORT_C void DoInternalizeMarkupDataL(RReadStream& aStream);
	void StoreStylesL(CStreamStore& aStore,CStoreMap& aMap) const;
	void RestoreStylesL(const CStreamStore& aStore, TStreamId aId, const CParaFormatLayer* aParaFormatLayer, const CCharFormatLayer* aCharFormatLayer);
	void StoreMarkupL(CStreamStore& aStore,CStoreMap& aMap)const;
	//
	IMPORT_C void RtInsertL(TInt aPos,const TDesC& aBuf);
	//
	TStreamId DoCopyToStoreL(CStreamStore& aStore, TInt aPos, TInt aLength, TStreamId aGlobalTextId, TBool aCopyStyles) const;
	IMPORT_C void CopyComponentsL(CStreamStore& aStore, CStoreMap& aMap, TInt aPos,TInt aLength, TStreamId aGlobalTextId) const;
	IMPORT_C void CopyToStreamL(RWriteStream& aStream, TInt aPos, TInt aLength, TStreamId aGlobalTextId) const;
	IMPORT_C void CopyToStreamL(RWriteStream& aStream, TInt aPos, TInt aLength) const;
	void CopyToStreamL(RWriteStream& aStream, TInt aPos, TInt aLength, TStreamId aGlobalTextId, TBool aCopyStyles) const;
	TInt PasteRichTextFromStoreL(const CStreamStore& aStore, const CStreamDictionary& aDictionary, TStreamId& anId, TInt aPos, CParagraphStyle::TStylePasteMode aStylePasteMode);
	void CompletePasteRichTextFromStoreL(const CStreamStore& aStore, TStreamId& aRichTextStreamId, TInt aPos, CParagraphStyle::TStylePasteMode aStylePasteMode);
	TInt PastePlainTextFromStoreL(const CStreamStore& aStore, TStreamId& anId, TInt aPos);
	//
	// Append
	void PrepareAppendMarkupL(const CRichText& aSource);
	void DoAppendTakingSolePictureOwnershipL(const CRichText& aSource);
public:
	IMPORT_C static void ActivateParserL(MParser* aParser);		// Switch on a particular parser
	IMPORT_C static void DeactivateParser(MParser* aParser);	// Switch off a particular parser
	IMPORT_C static void ActivateDefaultParserL(MParser* aParser);	// Switch on a default parser
	IMPORT_C static void DeactivateParserDefaults();				// Switch off default set (if any)
																// and delete EText TLS

	IMPORT_C void SetEditObserver(MEditObserver* aEditObserver);
	IMPORT_C TBool ParseText(TInt& aStartOfTags, TInt& aLength, TBool aForceScanAllText);
	IMPORT_C TBool CursorOverTag(TInt aPos, MParser*& aParser, TInt& aTagStart, TInt& aLength) const;
	// Next tag (forwards), any or specific parser
	IMPORT_C TInt PositionOfNextTag(TInt aPos) const;
	IMPORT_C TInt PositionOfNextTag(TInt aPos, const MParser* aParser) const;
	// Prev tag (backwards), any or specific parser
	IMPORT_C TInt PositionOfPrevTag(TInt aPos) const;
	IMPORT_C TInt PositionOfPrevTag(TInt aPos, const MParser* aParser) const;

private:
	static void CreateParserETextTLSL();
	TBool DoCursorOverTag(TInt aPos, MParser*& aParser, TInt& aTagStart, TInt& aLength) const;
	void OverrideFormatForParsersIfApplicable(TPtrC& aText, TCharFormatX& aFormat, TInt aStartPos) const;
	void CallEditObserver(TInt aStart, TInt aExtent) const;

protected:
	enum {EDelimiterCharacterLength = 1};
private:
	TSwizzle<CStyleList> iStyleList;
	TSwizzle<CRichTextIndex> iIndex;
	TUint32 iFlags;
	MPictureFactory* iPictureFactory;
	MRichTextStoreResolver* iStoreResolver;

	CParserData* iParserData;

	void* iReserved_3;

	__DECLARE_TEST;  // Index consistency check with document length.
	};


#include <txtrich.inl>


#endif



