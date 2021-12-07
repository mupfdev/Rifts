// TXTETEXT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTETEXT_H__
#define __TXTETEXT_H__

#include <e32std.h>
#include <e32base.h>
#include <fldset.h>
#include <s32std.h>


// Forward references
class CParaFormatLayer;
class CCharFormatLayer;
class MTextFieldFactory;
class CTextFieldSet;
class CTextField;
class TFindFieldInfo;
class CInlineEditData;
class MFepInlineTextFormatRetriever;
class TCharFormat;
class CEditableTextOptionalData;
class RFs;


// UIDs
const TUid KPlainTextFieldDataUid = {268435555};
const TUid KEditableTextUid = {268450334};
const TUid KPlainTextCharacterDataUid = {268450341};
const TUid KClipboardUidTypePlainText = {268450333};


const TInt KMaxFieldBufferSize=0x14;


/*
An abstract base class for editable text.
It contains some data, including optional FEP inline editing information.
*/
class CEditableText : public CBase
	{
public:
	IMPORT_C ~CEditableText();
	IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);

	// virtual persistence functions
	virtual void ExternalizeL(RWriteStream& aStream) const;
	virtual void InternalizeL(RReadStream& aStream);
	virtual void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap) const = 0;
	virtual void RestoreComponentsL(const CStreamStore& aStore) = 0;

	// modifier functions
	virtual void Reset() = 0;
	virtual void InsertL(TInt aInsertPos,const TChar& aChar) = 0;
	virtual void InsertL(TInt aInsertPos,const TDesC& aBuf) = 0;
	virtual TBool DeleteL(TInt aPos,TInt aLength) = 0;

	// interrogation functions
	virtual TPtrC Read(TInt aStartPos) const = 0;
	virtual TPtrC Read(TInt aStartPos,TInt aLength) const = 0;
	virtual void Extract(TDes& aBuf,TInt aPos=0) const = 0;
	virtual void Extract(TDes& aBuf,TInt aPos,TInt aLength) const = 0;

	// copy and paste
	virtual void CopyToStoreL(CStreamStore& aStore,CStreamDictionary& aDictionary,TInt aPos,TInt aLength) const = 0;
	virtual TInt PasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDictionary,TInt aPos) = 0;

	// utility functions
	virtual TInt WordCount() const = 0;
	virtual TInt ParagraphCount() const = 0;
	virtual TInt DocumentLength() const = 0;
	virtual TInt ToParagraphStart(TInt& aPos) const = 0;
	inline TBool HasChanged() const;
	virtual void GetWordInfo(TInt aCurrentPos,TInt& aStartPos,TInt& aLength,
							 TBool aPictureIsDelimiter,TBool aPunctuationIsDelimiter) const = 0;
	IMPORT_C virtual TInt ScanWords(TInt& aPos,TUint& aScanMask) const;
	IMPORT_C virtual TInt ScanParas(TInt& aPos,TUint& aScanMask) const;
	IMPORT_C virtual void SetHasChanged(TBool aHasChanged);

	// Internal to Symbian - support for front-end-processor inline editing
	IMPORT_C void StartFepInlineEditL(TBool& aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt& aNumberOfCharactersSuccessfullyDeleted,TInt& aNumberOfCharactersSuccessfullyInserted,TInt& aPositionOfInsertionPointInDocument,TInt aNewPositionOfInsertionPointInDocument,const TDesC& aInitialInlineText,TInt aPositionOfInlineTextInDocument,TInt aNumberOfCharactersToHide,MFepInlineTextFormatRetriever& aInlineTextFormatRetriever);
	IMPORT_C void UpdateFepInlineTextL(TBool& aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt& aNumberOfCharactersSuccessfullyDeleted,TInt& aNumberOfCharactersSuccessfullyInserted,TInt& aPositionOfInsertionPointInDocument,TInt aNewPositionOfInsertionPointInDocument,const TDesC& aNewInlineText);
	IMPORT_C void CommitFepInlineEditL(TBool& aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt& aNumberOfCharactersSuccessfullyDeleted,TInt& aNumberOfCharactersSuccessfullyInserted,TInt& aPositionOfInsertionPointInDocument,TInt aNewPositionOfInsertionPointInDocument);
	IMPORT_C void CancelFepInlineEdit(TBool& aParagraphContainingStartPositionOfInlineTextHasChangedFormat,TInt& aNumberOfCharactersSuccessfullyDeleted,TInt& aNumberOfCharactersSuccessfullyInserted,TInt& aPositionOfInsertionPointInDocument,TInt aNewPositionOfInsertionPointInDocument);

	IMPORT_C virtual void Reserved_1();

	enum TDocumentStorage
		{
		EFlatStorage,
		ESegmentedStorage
		};
	
	enum 
		{
		EDefaultTextGranularity = 256
		};

	/*
	Useful Unicode character definitions.
	ETEXT uses standard Unicode to store its text. In particular 0x2029 and 0x2028 are used
	as paragraph separator and forced line break respectively.
	*/
	enum
		{								// Unicode name, etc.
		ETabCharacter = 0x0009,			// horizontal tabulation
		EPageBreak = 0x000C,			// form feed
		ESpace = 0x0020,				// space
		EApostrophe = 0x0027,			// apostrophe
		EHyphenMinus = 0x002D,			// hyphen-minus; generally used for hyphen, but see 0x2010
		ENonBreakingSpace = 0x00A0,		// no-break space
		EPotentialHyphen = 0x00AD,		// soft hyphen
		EHyphen = 0x2010,				// hyphen; intended as an unambiguous hyphen codepoint
		ENonBreakingHyphen = 0x2011,	// non-breaking hyphen
		ELeftSingleQuote = 0x2018,		// left single quotation mark
		ERightSingleQuote = 0x2019,		// right single quotation mark
		ELeftDoubleQuote = 0x201C,		// left double quotation mark
		ERightDoubleQuote = 0x201D,		// right double quotation mark
		EBullet = 0x2022,				// bullet
		EEllipsis = 0x2026,				// horizontal ellipsis
		ELineBreak = 0x2028,			// line separator
		EParagraphDelimiter = 0x2029,	// paragraph separator
		EPictureCharacter = 0xFFFC,		// object replacement character
		EZeroWidthNoBreakSpace = 0xFEFF,// zero-width no-break space
		EByteOrderMark = 0xFEFF,		// byte order mark; SAME AS zero-width no-break space
		EReversedByteOrderMark = 0xFFFE	// not a character; evidence of endianness opposite to that of platform
		};

protected:
	// support for front-end-processor inline-editing
	IMPORT_C void OverrideFormatOfInlineTextIfApplicable(TPtrC& aView,TCharFormat& aFormat,TInt aStartPos) const;

	TBool iHasChanged;

private:
	void SetAndTransferOwnershipOfInlineEditDataL(CInlineEditData* aInlineEditData);
	CInlineEditData* InlineEditData() const;
	void DeleteInlineEditDataAndSetToNull();

	CEditableTextOptionalData* iOptionalData;
	};


// Information relating to the number of components owned by an editable text instance.
class TEtextComponentInfo
	{
public:
	IMPORT_C TEtextComponentInfo();
	IMPORT_C TEtextComponentInfo(TInt aFieldCount,TInt aPictureCount,TInt aStyleCount);
public:
	TInt iFieldCount;
	TInt iPictureCount;
	TInt iStyleCount;
	};

typedef CArrayFix<TInt> TPageTable;
	
/**
CPlainText stores unformatted Unicode text, and provides the following services among others:
externalization and internalization; import from, and export to, arbitrary streams, optionally
translating between Unicode and other encodings; reading and writing of field data; extraction
of Unicode text; finding word and paragraph boundaries.
*/
class CPlainText: public CEditableText
	{
public:
	enum TTextOrganisation
		{
		EOrganiseByParagraph,
		EOrganiseByLine
		};

	enum
		{
		EScanBackwards = 0x01,
		EScanStayIfBoundary = 0x02,
		EScanToUnitStart = 0x04,
		EScanToUnitEnd = 0x08,
		EScanJoinDelimiters = 0x10,
		EScanPictureIsDelimiter = 0x20,
		EScanPunctuationIsDelimiter = 0x40
		};

	enum TScanDataEnd
		{
		EScanEndOfData = -1
		};

	class TImportExportParam
		{
		public:
		TImportExportParam():
			iOrganisation(EOrganiseByParagraph),
			iMaxOutputChars(KMaxTInt),
			iMaxInputChars(KMaxTInt),
			iMaxLineLength(KMaxTInt),
			iOutputInternal(FALSE),
			iInputInternal(FALSE),
			iForeignEncoding(0),
			iGuessForeignEncoding(FALSE),
			iFileSession(NULL),
			iReserved(0)
			{
			}

		TTextOrganisation iOrganisation;
		TInt iMaxOutputChars;
		TInt iMaxInputChars;
		TInt iMaxLineLength;				// maximum line length when exporting text
		TBool iOutputInternal;				// output is in internal format, so write according to native endianness
		TBool iInputInternal;				// input is in internal format, so read according to native endianness
		TUint iForeignEncoding;				// if non-zero, UID of non-Unicode encoding to convert to or from
		TBool iGuessForeignEncoding;		// if true, guess the foreign encoding when importing; use
											// the guessed encoding if the confidence level is 50% or above
											// otherwise leave with KErrNotSupported
		RFs* iFileSession;					// if non-null, file session used by CHARCONV to load conversion data
		TUint iReserved;
		};

	class TImportExportResult
		{
		public:
		TImportExportResult():
			iOutputChars(0),
			iInputChars(0),
			iForeignEncoding(0),
			iReserved(0)
			{
			}

		TInt iOutputChars;
		TInt iInputChars;
		TUint iForeignEncoding;				// foreign encoding actually used; useful if the encoding was guessed
		TUint iReserved;		
		};
			   
	IMPORT_C static CPlainText* NewL(TDocumentStorage aStorage = ESegmentedStorage,
									 TInt aDefaultTextGranularity = EDefaultTextGranularity);
	IMPORT_C static CPlainText* NewL(const CStreamStore& aStore,TStreamId aStreamId,
									 MTextFieldFactory* aFieldFactory = NULL,
									 TDocumentStorage aStorage = ESegmentedStorage);
	IMPORT_C virtual ~CPlainText();

	// primary persistence functions
	IMPORT_C virtual void StoreComponentsL(CStreamStore& aStore,CStoreMap& aMap) const;
	IMPORT_C virtual void RestoreComponentsL(const CStreamStore& aStore);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);

	// secondary persistence functions
	IMPORT_C void ExternalizePlainTextL(RWriteStream& aStream) const;
	IMPORT_C void InternalizePlainTextL(RReadStream& aStream);
	IMPORT_C void ExternalizePlainTextNoLengthCountL(RWriteStream& aStream) const; // Deprecated
	IMPORT_C void InternalizePlainTextL(RReadStream& aStream,TInt aLength); // Deprecated

	// import and export text
	IMPORT_C void ImportTextL(TInt aPos,RReadStream& aInput,TTextOrganisation aTextOrganisation,
							  TInt aMaxOutputChars = KMaxTInt,TInt aMaxInputChars = KMaxTInt,
							  TInt* aOutputChars = NULL,TInt* aInputChars = NULL);
	IMPORT_C void ExportTextL(TInt aPos,RWriteStream& aOutput,TTextOrganisation aTextOrganisation,
							  TInt aMaxOutputChars = KMaxTInt,TInt aMaxInputChars = KMaxTInt,
							  TInt aMaxLineLength = KMaxTInt,
							  TInt* aOutputChars = NULL,TInt* aInputChars = NULL) const;
	IMPORT_C virtual TInt ImportTextFileL(TInt aPos,const TDes& aFileName,TTextOrganisation aTextOrganisation);
	IMPORT_C virtual void ExportAsTextL(const TDes& aFileName,TTextOrganisation aTextOrganisation,
										TInt aMaxLineLength) const;

	// import and export text AND optionally translate from or to a non-Unicode encoding
	IMPORT_C void ImportTextL(TInt aPos,RReadStream& aInput,
							  const TImportExportParam& aParam,TImportExportResult& aResult);
	IMPORT_C void ExportTextL(TInt aPos,RWriteStream& aOutput,
							  const TImportExportParam& aParam,TImportExportResult& aResult) const;

	// read and write field data
	IMPORT_C void StoreFieldComponentsL(CStreamStore& aStore,CStoreMap& aMap) const;
	IMPORT_C void RestoreFieldComponentsL(const CStreamStore& aStore);
	IMPORT_C void ExternalizeFieldDataL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeFieldDataL(RReadStream& aStream);

	// modifier functions
	IMPORT_C virtual void Reset();
	IMPORT_C virtual void InsertL(TInt aPos,const TChar& aChar);
	IMPORT_C virtual void InsertL(TInt aPos,const TDesC& aBuf);
	IMPORT_C virtual TBool DeleteL(TInt aPos,TInt aLength);

	// interrogation functions
	IMPORT_C virtual TPtrC Read(TInt aStartPos) const;
	IMPORT_C virtual TPtrC Read(TInt aStartPos,TInt aLength) const;
	IMPORT_C virtual void Extract(TDes& aBuf,TInt aPos=0) const;
	IMPORT_C virtual void Extract(TDes& aBuf,TInt aPos,TInt aLength) const;

	// Flags for ExtractSelectively
	enum
		{
		EExtractAll = 0,	// extract all characters
		EExtractVisible = 1	// discard control characters and soft hyphens; change par and line separators to spaces
		};
	IMPORT_C void ExtractSelectively(TDes& aBuf,TInt aPos,TInt aLength,TUint aFlags);

	// copy and paste
	IMPORT_C virtual void CopyToStoreL(CStreamStore& aStore,CStreamDictionary& aDictionary,TInt aPos,TInt aLength) const;
	IMPORT_C virtual TInt PasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDictionary,TInt aPos);

	// utility functions
	IMPORT_C void SetPageTable(TPageTable* aPageTable);
	IMPORT_C TInt PageContainingPos(TInt aPos) const;
	IMPORT_C virtual TInt DocumentLength() const;
 	IMPORT_C virtual TInt WordCount() const;
	IMPORT_C virtual TInt ParagraphCount() const;
	IMPORT_C virtual TInt ToParagraphStart(TInt& aPos) const;
	IMPORT_C virtual TInt CharPosOfParagraph(TInt& aLength,TInt aParaOffset) const;
	IMPORT_C virtual TInt ParagraphNumberForPos(TInt& aPos) const;
	IMPORT_C virtual void GetWordInfo(TInt aCurrentPos,TInt& aStartPos,TInt& aLength,
						TBool aPictureIsDelimiter,TBool aPunctuationIsDelimiter) const;
	IMPORT_C virtual TInt ScanWords(TInt& aPos,TUint& aScanMask) const;
	IMPORT_C virtual TInt ScanParas(TInt& aPos,TUint& aScanMask) const;
	IMPORT_C virtual TEtextComponentInfo ComponentInfo() const;
	//
	// Field functions
	IMPORT_C void SetFieldFactory(MTextFieldFactory* aFactory);
	inline const MTextFieldFactory* FieldFactory() const;
	IMPORT_C CTextField* NewTextFieldL(TUid aFieldType) const;
	IMPORT_C void InsertFieldL(TInt aPos,CTextField* aField,TUid aFieldType); 
	IMPORT_C virtual void UpdateFieldL(TInt aPos); 
	IMPORT_C void UpdateAllFieldsL(); 
	IMPORT_C TInt FieldCount() const;
	IMPORT_C const CTextField* TextField(TInt aPos) const;
	IMPORT_C TBool FindFields(TInt aPos) const; 
	IMPORT_C TBool FindFields(TFindFieldInfo& aInfo,TInt aPos,TInt aRange=0) const;
	IMPORT_C TBool RemoveField(TInt aPos);  
	IMPORT_C TBool ConvertFieldToText(TInt aPos); 
	IMPORT_C void ConvertAllFieldsToText();

protected:
	IMPORT_C CPlainText();
	IMPORT_C void ConstructL(TDocumentStorage aStorage = ESegmentedStorage,
							 TInt aDefaultTextGranularity = EDefaultTextGranularity);
	IMPORT_C void ConstructL(const CStreamStore& aStore,TStreamId aStreamId,MTextFieldFactory* aFieldFactory,
							 TDocumentStorage aStorage = ESegmentedStorage);
	IMPORT_C void DoConstructL(TDocumentStorage aStorage,TInt aDefaultTextGranularity,
							   MTextFieldFactory* aFieldFactory = NULL);
	void DoExtract(TDes& aBuf,TInt aPos,TInt aLength,TUint aFlags = 0) const;
	IMPORT_C void PtInsertL(TInt aInsertPos,const TDesC& aBuf);
	IMPORT_C void DoPtInsertL(TInt aPos,const TDesC& aBuf);
	IMPORT_C TBool DoPtDelete(TInt aPos,TInt aLength);
	void InsertL(TInt aPos,const CPlainText* aText);
	TBool Delete(TInt aPos,TInt aLength);

	// streaming
	IMPORT_C void DoExternalizeFieldDataL(RWriteStream& aStream) const;
	IMPORT_C void DoInternalizeFieldDataL(RReadStream& aStream);
	IMPORT_C void DoExternalizePlainTextL(RWriteStream& aStream) const;
	IMPORT_C void DoInternalizePlainTextL(RReadStream& aStream);
	TStreamId DoCopyToStoreL(CStreamStore& aStore,CStreamDictionary& aDictionary,TInt aPos,TInt aLength) const;
	TInt DoPasteFromStoreL(const CStreamStore& aStore,TStreamId aStreamId,TInt aPos);
	void CopyComponentsL(CStreamStore& aStore,CStoreMap& aMap,TInt aPos,TInt aLength) const;
	void PasteComponentsL(const CStreamStore& aStore,TInt aPos);
	void CopyToStreamL(RWriteStream& aStream,TInt aPos,TInt aLength) const;

	// utility functions
	inline static void ConsumeAdornmentL(RReadStream& aStream);
	inline static TUid UidFromStreamL(RReadStream& aStream);
protected:
	enum
		{
		EImportBufSize = 512,
		EBiggestCharacterPaste=0x100000
		};

	enum TUnitOfText
		{
		EUnitIsWord,
		EUnitIsParagraph
		};

	struct SScanData
		{
		TInt pos;			// current character position
		TInt oldPos;		// old character position
		TText* buf;			// address of data (Unicode-aware)
		TInt currentSegLen; // number of characters left in segment
		TInt totalBufLen;	// number of unread characters
		TInt delta;			// specifies current scan direction
		TUint32 scanMask;	// bitmask containing the scan settings
		enum
			{
			EInsideUnit = 0x10000000,
			EStopEnd = 0x20000000,
			EStopBegin = 0x40000000,
			EIsDelimiter = 0x80000000
			};
		};

private:
	CPlainText(const CPlainText& aPlainTextDoc);
	CPlainText& operator=(const CPlainText& aPlainTextDoc);
	TInt PasteFromStreamL(RReadStream& aStream,TInt aPos);
	void InsertEodL();
	void InitScanControl(TInt& aPos,TUint& aScanMask,TUnitOfText aContext,SScanData& aScanData) const;
	void InitScanData(TInt aPos,SScanData& aScanData) const;
	void KillFieldSet();
	TInt CountUnits(TUnitOfText aContext) const;
	TInt ScanUnit(TInt& aPos,TUnitOfText aContext,SScanData& aScanData) const;
	TBool TestForDelimiter(TUnitOfText aContext,SScanData& aScanData) const;
	TBool GetChar(SScanData& aScanData,TChar& aChar) const;
	void UpdatePageTable(TInt aPos,TInt aLength);
	inline TBool FieldSetPresent() const;
	void CreateFieldSetL(TInt aDocumentLength);

	IMPORT_C void Reserved_1();			// from CEditableText
	IMPORT_C virtual void Reserved_2();	// new

	void* iReserved_1;

protected:
	CBufBase* iByteStore;				// handle to document storage class.
	TSwizzle<CTextFieldSet> iFieldSet;  // handle to field storage class
	TPageTable* iPageTable;				// may be NULL
	MTextFieldFactory* iFieldFactory;  // temporary handle to field factory during restoration

	__DECLARE_TEST;
	};


#include <txtetext.inl>

#endif // __TXTETEXT_H__
