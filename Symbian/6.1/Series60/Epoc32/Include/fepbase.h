// FEPBASE.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__FEPBASE_H__)
#define __FEPBASE_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__E32BASE_H__)
#include <E32BASE.H>
#endif

#if !defined(__F32FILE_H__)
#include <F32FILE.H>
#endif

#if !defined(__W32STD_H__)
#include <W32STD.H>
#endif

#if !defined(__COEDEF_H__)
#include <COEDEF.H>
#endif

#if !defined(__COEMAIN_H__)
#include <COEMAIN.H>
#endif

// macros to be called by keyboard-based FEPs in their CCoeControl::OfferKeyEventL-overriding function

#define FEP_START_KEY_EVENT_HANDLER_L(aFep, aKeyEvent, aEventCode)\
	{\
	if ((aFep).IsSimulatingKeyEvent())\
		{\
		return EKeyWasNotConsumed;\
		}\
	(aFep).OnStartingHandlingKeyEvent_WithDownUpFilterLC();\
	if (((aEventCode)!=EEventKey) || (aFep).IsTurnedOnByL(aKeyEvent) || (aFep).IsTurnedOffByL(aKeyEvent))\
		{\
		return (aFep).OnFinishingHandlingKeyEvent_WithDownUpFilterL((aEventCode), (aKeyEvent), EKeyWasConsumed);\
		}\
	if (!(aFep).IsOn())\
		{\
		return (aFep).OnFinishingHandlingKeyEvent_WithDownUpFilterL((aEventCode), (aKeyEvent), EKeyWasNotConsumed);\
		}\
	}

#define FEP_END_KEY_EVENT_HANDLER_L(aFep, aKeyEvent, aKeyResponse)\
	{\
	return (aFep).OnFinishingHandlingKeyEvent_WithDownUpFilterL(EEventKey, (aKeyEvent), (aKeyResponse));\
	}

#define FEP_START_KEY_EVENT_HANDLER_NO_DOWN_UP_FILTER_L(aFep, aKeyEvent, aEventCode)\
	{\
	if ((aFep).IsSimulatingKeyEvent())\
		{\
		return EKeyWasNotConsumed;\
		}\
	(aFep).OnStartingHandlingKeyEvent_NoDownUpFilterLC();\
	if ((aEventCode)==EEventKey)\
		{\
		if ((aFep).IsTurnedOnByL(aKeyEvent) || (aFep).IsTurnedOffByL(aKeyEvent))\
			{\
			return (aFep).OnFinishingHandlingKeyEvent_NoDownUpFilterL((aEventCode), (aKeyEvent), EKeyWasConsumed);\
			}\
		if (!(aFep).IsOn())\
			{\
			return (aFep).OnFinishingHandlingKeyEvent_NoDownUpFilterL((aEventCode), (aKeyEvent), EKeyWasNotConsumed);\
			}\
		}\
	}

#define FEP_END_KEY_EVENT_HANDLER_NO_DOWN_UP_FILTER_L(aFep, aKeyEvent, aEventCode, aKeyResponse)\
	{\
	return (aFep).OnFinishingHandlingKeyEvent_NoDownUpFilterL((aEventCode), (aKeyEvent), (aKeyResponse));\
	}

class TFepOnOrOffKeyData
	{
public:
	inline TFepOnOrOffKeyData(TUint aCharacterCodeForFoldedMatch, TUint aModifierMask, TUint aModifierValues) :iCharacterCodeForFoldedMatch(aCharacterCodeForFoldedMatch), iModifierMask(aModifierMask), iModifierValues(aModifierValues) {}
	inline TUint CharacterCodeForFoldedMatch() const {return iCharacterCodeForFoldedMatch;}
	inline TUint ModifierMask() const {return iModifierMask;}
	inline TUint ModifierValues() const {return iModifierValues;}
private:
	TUint iCharacterCodeForFoldedMatch;
	TUint iModifierMask;
	TUint iModifierValues;
	};

class CDictionaryStore;
class RWriteStream;
class RReadStream;

class CFepGenericGlobalSettings : public CBase
	{
public:
	IMPORT_C static CFepGenericGlobalSettings* NewL(CCoeEnv& aConeEnvironment, const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	IMPORT_C static CFepGenericGlobalSettings* NewLC(CCoeEnv& aConeEnvironment, const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	IMPORT_C TFepOnOrOffKeyData OnKeyData() const;
	IMPORT_C void SetOnKeyData(const TFepOnOrOffKeyData& aOnKeyData);
	IMPORT_C TFepOnOrOffKeyData OffKeyData() const;
	IMPORT_C void SetOffKeyData(const TFepOnOrOffKeyData& aOffKeyData);
	IMPORT_C TBool IsOn() const;
	IMPORT_C void SetIsOn(TBool aIsOn);
	IMPORT_C void StoreChangesAndBroadcastL();
	IMPORT_C void RefreshL();
	static void ReadOnAndOffKeyDataFromStreamL(TFepOnOrOffKeyData& aOnKeyData, TFepOnOrOffKeyData& aOffKeyData, RReadStream& aStream);
	static void ReadIsOnFromStreamL(TUint& aFlags, TUint aFlagIsOn, RReadStream& aStream);
	static void StoreIsOnAndBroadcastL(CCoeEnv& aConeEnvironment, TBool aIsOn);
private:
	CFepGenericGlobalSettings(CCoeEnv& aConeEnvironment, const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	void ConstructL();
	static void ReadOnOrOffKeyDataFromStreamL(TFepOnOrOffKeyData& aOnOrOffKeyData, RReadStream& aStream);
	static void WriteOnOrOffKeyDataToStreamL(const TFepOnOrOffKeyData& aOnOrOffKeyData, RWriteStream& aStream);
	static void WriteOnAndOffKeyDataAndBroadcastL(CCoeEnv& aConeEnvironment, const TFepOnOrOffKeyData& aOnKeyData, const TFepOnOrOffKeyData& aOffKeyData, CDictionaryStore& dictionaryStore);
	static void WriteIsOnDataAndBroadcastL(CCoeEnv& aConeEnvironment, TBool aIsOn, CDictionaryStore& aDictionaryStore);
private:
	enum
		{
		EFlagDefaultIsOn	=0x00000001,
		EFlagIsOn			=0x00000002
		};
private:
	CCoeEnv& iConeEnvironment;
	TUint iFlags;
	TFepOnOrOffKeyData iDefaultOnKeyData;
	TFepOnOrOffKeyData iDefaultOffKeyData;
	TFepOnOrOffKeyData iOnKeyData;
	TFepOnOrOffKeyData iOffKeyData;
	};

class MCoeFepObserver
	{
public:
	// both of these functions do nothing by default - the reason that they are not pure virtual is that most applications will only want to override one of them
	IMPORT_C virtual void HandleStartOfTransactionL(); // the responsibility of FEPs to call
	IMPORT_C virtual void HandleCompletionOfTransactionL(); // the responsibility of FEPBASE to call - not to be called if the transaction is canceled
private:
	IMPORT_C virtual void MCoeFepObserver_Reserved_1();
	IMPORT_C virtual void MCoeFepObserver_Reserved_2();
	};

IMPORT_C void FepObserverHandleStartOfTransactionL(MCoeFepObserver& aFepObserver);

class CCoeFepParameters : public CBase
	{
public: // Internal to Symbian
	IMPORT_C static CCoeFepParameters* NewL(const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	IMPORT_C static CCoeFepParameters* NewLC(const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
	TFepOnOrOffKeyData DefaultOnKeyData() const;
	TFepOnOrOffKeyData DefaultOffKeyData() const;
	TBool DefaultIsOn() const;
private:
	CCoeFepParameters(const TFepOnOrOffKeyData& aDefaultOnKeyData, const TFepOnOrOffKeyData& aDefaultOffKeyData, TBool aDefaultIsOn);
private:
	TFepOnOrOffKeyData iDefaultOnKeyData;
	TFepOnOrOffKeyData iDefaultOffKeyData;
	TBool iDefaultIsOn;
	};

class MFepAttributeStorer
	{
public:
	IMPORT_C void ReadAllAttributesL(CCoeEnv& aConeEnvironment);
	IMPORT_C void WriteAttributeDataAndBroadcastL(CCoeEnv& aConeEnvironment, TUid aAttributeUid);
	IMPORT_C void WriteAttributeDataAndBroadcastL(CCoeEnv& aConeEnvironment, const TArray<TUid>& aAttributeUids);
	virtual TInt NumberOfAttributes() const=0;
	virtual TUid AttributeAtIndex(TInt aIndex) const=0;
	virtual void WriteAttributeDataToStreamL(TUid aAttributeUid, RWriteStream& aStream) const=0;
	virtual void ReadAttributeDataFromStreamL(TUid aAttributeUid, RReadStream& aStream)=0;
private:
	IMPORT_C virtual void MFepAttributeStorer_Reserved_1();
	IMPORT_C virtual void MFepAttributeStorer_Reserved_2();
	TInt NumberOfOccurrencesOfAttributeUid(TUid aAttributeUid) const;
	};

class CCoeControl;

class CCoeFep : public CBase, protected MFepAttributeStorer, public MCoeForegroundObserver, public MCoeFocusObserver, private MCoeMessageObserver
	{
public:
	enum TEventResponse
		{
		EEventWasNotConsumed,
		EEventWasConsumed
		};
	class MDeferredFunctionCall
		{
	public:
		virtual void ExecuteFunctionL()=0;
	private:
		IMPORT_C virtual void MDeferredFunctionCall_Reserved_1();
		IMPORT_C virtual void MDeferredFunctionCall_Reserved_2();
		};
	class MKeyEventQueue // Internal to Symbian
		{
	public:
		virtual void AppendKeyEventL(const TKeyEvent& aKeyEvent)=0;
	private:
		IMPORT_C virtual void MKeyEventQueue_Reserved_1();
		IMPORT_C virtual void MKeyEventQueue_Reserved_2();
		};
	class MModifiedCharacter
		{
	public:
		virtual TUint CharacterCode() const=0;
		virtual TUint ModifierMask() const=0;
		virtual TUint ModifierValues() const=0;
	private:
		IMPORT_C virtual void MModifiedCharacter_Reserved_1();
		IMPORT_C virtual void MModifiedCharacter_Reserved_2();
		};
public:
	IMPORT_C virtual ~CCoeFep();
	IMPORT_C TBool IsSimulatingKeyEvent() const;
	IMPORT_C TBool IsTurnedOnByL(const TKeyEvent& aKeyEvent) const;
	IMPORT_C TBool IsTurnedOffByL(const TKeyEvent& aKeyEvent) const;
	// new public virtual functions
	virtual void CancelTransaction()=0;
public: // Internal to Symbian
	// the following functions (and also those of MCoeForegroundObserver) are to be called by applications that do not always have an active-scheduler running, (e.g. OPLR)
	IMPORT_C TEventResponse OfferKeyEvent(TInt& aError, MKeyEventQueue& aKeyEventQueue, const TKeyEvent& aKeyEvent, TEventCode aEventCode);
	IMPORT_C TEventResponse OfferPointerEvent(TInt& aError, MKeyEventQueue& aKeyEventQueue, const TPointerEvent& aPointerEvent, const CCoeControl* aWindowOwningControl);
	IMPORT_C TEventResponse OfferPointerBufferReadyEvent(TInt& aError, MKeyEventQueue& aKeyEventQueue, const CCoeControl* aWindowOwningControl);
	IMPORT_C static TEventResponse OfferEventToActiveScheduler(CCoeFep* aFep, TInt& aError, MKeyEventQueue& aKeyEventQueue, TInt aMinimumPriority); // aFep may be NULL
public: // *** Do not use! API liable to change ***
	IMPORT_C void OnStartingHandlingKeyEvent_WithDownUpFilterLC();
	IMPORT_C void OnStartingHandlingKeyEvent_NoDownUpFilterLC();
	IMPORT_C TKeyResponse OnFinishingHandlingKeyEvent_WithDownUpFilterL(TEventCode aEventCode, const TKeyEvent& aKeyEvent, TKeyResponse aKeyResponse);
	IMPORT_C TKeyResponse OnFinishingHandlingKeyEvent_NoDownUpFilterL(TEventCode aEventCode, const TKeyEvent& aKeyEvent, TKeyResponse aKeyResponse);
protected:
	IMPORT_C CCoeFep(CCoeEnv& aConeEnvironment);
	IMPORT_C void BaseConstructL(const CCoeFepParameters& aFepParameters);
	IMPORT_C void ReadAllAttributesL();
	IMPORT_C void MakeDeferredFunctionCall(MDeferredFunctionCall& aDeferredFunctionCall);
	IMPORT_C void SimulateKeyEventsL(const TArray<TUint>& aArrayOfCharacters);
	IMPORT_C void SimulateKeyEventsL(const TArray<MModifiedCharacter>& aArrayOfModifiedCharacters);
	IMPORT_C void WriteAttributeDataAndBroadcastL(TUid aAttributeUid);
	IMPORT_C void WriteAttributeDataAndBroadcastL(const TArray<TUid>& aAttributeUids);
	IMPORT_C TBool IsOn() const;
private:
	enum {EUndefinedEventResponse=100};
	enum
		{
		EFlagDefaultIsOn		=0x00000001,
		EFlagIsOn				=0x00000002,
		EFlagIsHandlingKeyEvent	=0x00000004,
		EFlagNoDownUpFilter		=0x00000008
		};
	struct SKeyEvent
		{
		TEventCode iEventCode;
		TKeyEvent iKeyEvent;
		TKeyResponse iKeyResponse;
		};
	class CHighPriorityActive;
	class CLowPriorityActive;
private:
	void DoOnStartingHandlingKeyEventLC(TUint aFlagNoDownUpFilter);
	TKeyResponse DoOnFinishingHandlingKeyEventL(TEventCode aEventCode, const TKeyEvent& aKeyEvent, TKeyResponse aKeyResponse);
	static TBool KeyEventMatchesOnOrOffKeyData(const TKeyEvent& aKeyEvent, const TFepOnOrOffKeyData& aOnOrOffKeyData);
	static void TurnOffKeyEventHandlingFlags(TAny* aFlags);
	// from MFepAttributeStorer
	IMPORT_C virtual void MFepAttributeStorer_Reserved_1();
	IMPORT_C virtual void MFepAttributeStorer_Reserved_2();
	// from MCoeForegroundObserver
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_1();
	IMPORT_C virtual void MCoeForegroundObserver_Reserved_2();
	// from MCoeFocusObserver
	IMPORT_C virtual void MCoeFocusObserver_Reserved_1();
	IMPORT_C virtual void MCoeFocusObserver_Reserved_2();
	// from MCoeMessageObserver
	IMPORT_C virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
	IMPORT_C virtual void MCoeMessageObserver_Reserved_1();
	IMPORT_C virtual void MCoeMessageObserver_Reserved_2();
	// new private virtual functions
	virtual void IsOnHasChangedState()=0;
	virtual void OfferKeyEventL(TEventResponse& aEventResponse, const TKeyEvent& aKeyEvent, TEventCode aEventCode)=0;
	virtual void OfferPointerEventL(TEventResponse& aEventResponse, const TPointerEvent& aPointerEvent, const CCoeControl* aWindowOwningControl)=0;
	virtual void OfferPointerBufferReadyEventL(TEventResponse& aEventResponse, const CCoeControl* aWindowOwningControl)=0;
	IMPORT_C virtual void CCoeFep_Reserved_1();
	IMPORT_C virtual void CCoeFep_Reserved_2();
private:
	CCoeEnv& iConeEnvironment;
	TUint iFlags;
	TFepOnOrOffKeyData iDefaultOnKeyData;
	TFepOnOrOffKeyData iDefaultOffKeyData;
	TFepOnOrOffKeyData iOnKeyData;
	TFepOnOrOffKeyData iOffKeyData;
	CHighPriorityActive* iHighPriorityActive;
	CLowPriorityActive* iLowPriorityActive;
	MKeyEventQueue* iKeyEventQueue; // this pointer does not own anything
	SKeyEvent* iLastKeyEvent;
	};

class CFepFastFileAccessor : public CBase, private MCoeMessageObserver // Internal to Symbian
	{
public: // *** Do not use! API liable to change ***
	class MFileObserver
		{
	public:
		virtual void FileHasChangedL(const TDesC& aFullFileName, const TUint8* aData, TInt aDataLength, TBool aIsRom)=0;
	private:
		IMPORT_C virtual void MFileObserver_Reserved_1();
		IMPORT_C virtual void MFileObserver_Reserved_2();
		};
public: // Internal to Symbian
	inline static CFepFastFileAccessor* NewL(CCoeEnv& aConeEnvironment) {return NewL(aConeEnvironment, NULL);}
	inline static CFepFastFileAccessor* NewL(CCoeEnv& aConeEnvironment, MFileObserver& aFileObserver) {return NewL(aConeEnvironment, &aFileObserver);}
	inline static CFepFastFileAccessor* NewLC(CCoeEnv& aConeEnvironment) {return NewLC(aConeEnvironment, NULL);}
	inline static CFepFastFileAccessor* NewLC(CCoeEnv& aConeEnvironment, MFileObserver& aFileObserver) {return NewLC(aConeEnvironment, &aFileObserver);}
	IMPORT_C virtual ~CFepFastFileAccessor();
	IMPORT_C void AddFileL(const TDesC& aFullFileName);
	IMPORT_C void RemoveFile(const TDesC& aFullFileName);
	inline void GetData(const TDesC& aFullFileName, const TUint8*& aData, TInt& aDataLength) const {GetData(aFullFileName, aData, aDataLength, NULL);}
	inline void GetData(const TDesC& aFullFileName, const TUint8*& aData, TInt& aDataLength, TBool& aIsRom) const {GetData(aFullFileName, aData, aDataLength, &aIsRom);}
	IMPORT_C void FileHasChangedL(const TDesC& aFullFileName);
private:
	enum {EGranularity=5};
	enum {EBroadcastUid=0x1000162a};
	struct SFile
		{
		HBufC* iFullName;
		TBool iIsRom;
		TUint8* iData;
		TInt iDataLength;
		};
private:
	IMPORT_C static CFepFastFileAccessor* NewL(CCoeEnv& aConeEnvironment, MFileObserver* aFileObserver);
	IMPORT_C static CFepFastFileAccessor* NewLC(CCoeEnv& aConeEnvironment, MFileObserver* aFileObserver);
	CFepFastFileAccessor(CCoeEnv& aConeEnvironment, MFileObserver* aFileObserver);
	void ConstructL();
	IMPORT_C void GetData(const TDesC& aFullFileName, const TUint8*& aData, TInt& aDataLength, TBool* aIsRom) const; // exported as it is used by public inline functions
	void LoadNonRomFileL(SFile& aFile);
	void CloseArrayIfEmpty();
	static void CloseFile(SFile& aFile);
	static TBool IsFullFileName(const TDesC& aFileName);
	// from MCoeMessageObserver
	virtual TMessageResponse HandleMessageL(TUint32 aClientHandleOfTargetWindowGroup, TUid aMessageUid, const TDesC8& aMessageParameters);
private:
	CCoeEnv& iConeEnvironment;
	TInt iArrayLength;
	SFile* iArrayOfFiles;
	MFileObserver* iFileObserver;
	};

class CFepGlobalDynamicFrequencyTable : public CBase // Internal to Symbian
	{
public: // Internal to Symbian
	typedef TInt (*TCharacterCompareFunction)(TUint aCharacter1, TUint aCharacter2); // returns a negative number if aCharacter1 "comes before" aCharacter2, a positive number if aCharacter2 "comes before" aCharacter1 or zero if they are equivalent
	enum TSortType
		{
		ESortByFrequencyThenByUserDefinedCompareFunction,
		ESortByUserDefinedCompareFunctionThenByFrequency
		};
	class MCharacterArray
		{
	public:
		virtual TInt NumberOfCharacters() const=0;
		virtual TUint CharacterAtIndex(TInt aIndex) const=0;
		virtual void SetCharacterAtIndex(TInt aIndex, TUint aCharacter)=0;
	private:
		IMPORT_C virtual void MCharacterArray_Reserved_1();
		IMPORT_C virtual void MCharacterArray_Reserved_2();
		};
public: // Internal to Symbian
	IMPORT_C static CFepGlobalDynamicFrequencyTable* NewL(TInt aMaximumNumberOfCharacters);
	IMPORT_C static CFepGlobalDynamicFrequencyTable* NewLC(TInt aMaximumNumberOfCharacters);
	IMPORT_C virtual ~CFepGlobalDynamicFrequencyTable();
	IMPORT_C void IncrementFrequencyOfCharacter(TUint aCharacter);
	IMPORT_C void SortL(MCharacterArray& aCharacterArray, TCharacterCompareFunction aUserDefinedCharacterCompareFunction, TSortType aSortType);
	IMPORT_C void Reset();
private:
	struct SFrequencyCountedCharacter
		{
		TUint iCharacter;
		TInt iFrequencyCount;
		};
	struct SGlobalData
		{
		struct SArrayOfCharactersOrderedByAge
			{
			TInt iMaximumCount;
			TInt iCount;
			TInt iIndexOfOldest;
			TInt iOffsetToArray; // offset from the address of the SGlobalData object
			};
		struct SArrayOfFrequencyCountedCharactersOrderedByCharacterEncoding
			{
			TInt iCount;
			TInt iOffsetToArray; // offset from the address of the SGlobalData object
			};
		SArrayOfCharactersOrderedByAge iArrayOfCharactersOrderedByAge;
		SArrayOfFrequencyCountedCharactersOrderedByCharacterEncoding iArrayOfFrequencyCountedCharactersOrderedByCharacterEncoding;
		};
	struct SSortItem
		{
		SFrequencyCountedCharacter iFrequencyCountedCharacter;
		TInt iOriginalIndex;
		};
	typedef TBool (*TFirstParameterComesBeforeSecondFunction)(const SSortItem& aSortItem1, const SSortItem& aSortItem2, TCharacterCompareFunction aUserDefinedCharacterCompareFunction); // returns a non-zero if aSortItem1 "comes before" aSortItem2
private:
	CFepGlobalDynamicFrequencyTable();
	void ConstructL(TInt aMaximumNumberOfCharacters);
	void HeapSort(TInt aNumberOfSortItems, SSortItem* aArrayOfSortItems, TFirstParameterComesBeforeSecondFunction aFirstParameterComesBeforeSecondFunction, TCharacterCompareFunction aUserDefinedCharacterCompareFunction);
	TInt IndexInArrayOfFrequencyCountedCharactersOrderedByCharacterEncoding(TUint aCharacter, TBool& aExists);
	static TBool FirstParameterComesBeforeSecondWhenSortedByFrequencyThenByUserDefinedCompareFunction(const SSortItem& aSortItem1, const SSortItem& aSortItem2, TCharacterCompareFunction aUserDefinedCharacterCompareFunction);
	static TBool FirstParameterComesBeforeSecondWhenSortedByUserDefinedCompareFunctionThenByFrequency(const SSortItem& aSortItem1, const SSortItem& aSortItem2, TCharacterCompareFunction aUserDefinedCharacterCompareFunction);
private:
	RMutex iMutex;
	RChunk iChunk;
	SGlobalData* iGlobalData; // this pointer does not own anything
	TAny* iSpareForFutureUse;
	};

class MFepPointerEventHandlerDuringInlineEdit // to be overridden by inline-editing front-end processors
	{
public:
	virtual void HandlePointerEventInInlineTextL(TPointerEvent::TType aType, TUint aModifiers, TInt aPositionInInlineText)=0;
private:
	IMPORT_C virtual void MFepPointerEventHandlerDuringInlineEdit_Reserved_1();
	IMPORT_C virtual void MFepPointerEventHandlerDuringInlineEdit_Reserved_2();
	};

class TCharFormat;
class TCursorSelection;
class MFormCustomDraw;
class MFepInlineTextFormatRetriever;
class MCoeFepAwareTextEditor_Extension1;

class MCoeFepAwareTextEditor // to be overridden by text-editors
	{
public:
	virtual void StartFepInlineEditL(const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility, const MFormCustomDraw* aCustomDraw, MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit)=0;
	virtual void UpdateFepInlineTextL(const TDesC& aNewInlineText, TInt aPositionOfInsertionPointInInlineText)=0;
	virtual void SetInlineEditingCursorVisibilityL(TBool aCursorVisibility)=0;
	IMPORT_C void CommitFepInlineEditL(CCoeEnv& aConeEnvironment);
	virtual void CancelFepInlineEdit()=0;
	// with regard to the behaviour of the following functions (except GetScreenCoordinatesForFepL), note that when inline editing, the contents of the editor will be such that the text constituting the selection immediately prior to inline editing will be replaced by the inline text (CancelFepInlineEdit reinstates the previous selection)
	virtual TInt DocumentLengthForFep() const=0;
	virtual TInt DocumentMaximumLengthForFep() const=0;
	virtual void SetCursorSelectionForFepL(const TCursorSelection& aCursorSelection)=0;
	virtual void GetCursorSelectionForFep(TCursorSelection& aCursorSelection) const=0;
	virtual void GetEditorContentForFep(TDes& aEditorContent, TInt aDocumentPosition, TInt aLengthToRetrieve) const=0;
	virtual void GetFormatForFep(TCharFormat& aFormat, TInt aDocumentPosition) const=0;
	virtual void GetScreenCoordinatesForFepL(TPoint& aLeftSideOfBaseLine, TInt& aHeight, TInt& aAscent, TInt aDocumentPosition) const=0;
	IMPORT_C MCoeFepAwareTextEditor_Extension1* Extension1();
private:
	virtual void DoCommitFepInlineEditL()=0;
	IMPORT_C virtual MCoeFepAwareTextEditor_Extension1* Extension1(TBool& aSetToTrue);
	IMPORT_C virtual void MCoeFepAwareTextEditor_Reserved_2();
	};

class MCoeFepAwareTextEditor_Extension1 // to be overridden by text-editors
	{
public:
	class CState : public CBase
		{
	protected:
		IMPORT_C CState();
		IMPORT_C void BaseConstructL();
	public:
		IMPORT_C virtual ~CState();
	private:
		IMPORT_C virtual void CState_Reserved_1();
		IMPORT_C virtual void CState_Reserved_2();
		IMPORT_C virtual void CState_Reserved_3();
		IMPORT_C virtual void CState_Reserved_4();
	private:
		TAny* iSpareForFutureUse;
		};
public:
	virtual void SetStateTransferingOwnershipL(CState* aState, TUid aTypeSafetyUid)=0; // this function must only transfer ownership after it has successfully done everything that can leave
	virtual CState* State(TUid aTypeSafetyUid)=0; // this function does *not* transfer ownership
public:
	IMPORT_C virtual void StartFepInlineEditL(TBool& aSetToTrue, const TCursorSelection& aCursorSelection, const TDesC& aInitialInlineText, TInt aPositionOfInsertionPointInInlineText, TBool aCursorVisibility, const MFormCustomDraw* aCustomDraw, MFepInlineTextFormatRetriever& aInlineTextFormatRetriever, MFepPointerEventHandlerDuringInlineEdit& aPointerEventHandlerDuringInlineEdit);
	IMPORT_C virtual void SetCursorType(TBool& aSetToTrue, const TTextCursor& aTextCursor);
private:
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_3();
	IMPORT_C virtual void MCoeFepAwareTextEditor_Extension1_Reserved_4();
	};

class MCoeCaptionRetrieverForFep // to be overridden by captioned-controls
	{
public:
	virtual void GetCaptionForFep(TDes& aCaption) const=0; // gets as much as will fit in aCaption
private:
	IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_1();
	IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_2();
	};

#endif

