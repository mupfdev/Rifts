// EIKEDWIN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
 
#if !defined(__EIKEDWIN_H__)
#define __EIKEDWIN_H__

#include <s32std.h>
#include <gdi.h>
#include <txtetext.h>
#include <medobsrv.h>
#include <gulutil.h>
#include <fepbase.h>
#include <frmvis.h>
#include <frmtview.h>
#include <uikon.hrh>
#include <eikbctrl.h>
#include <eikedwob.h>
#include <eiksbfrm.h>
#include <eikccpu.h>
#include <eiklay.h>
#include <lafmain.h>

// Deprecated
#define EAutoSelection	EZeroEnumValue 

class CGlobalText;
class CParaFormatLayer;
class CCharFormatLayer;
class MLayDoc;
class CEikEdwinFepSupport;
class CLafEdwinCustomDrawBase;
class CClipboard;

enum TReplaceOption
	{
	ENoReplace,
	EReplaceOnce,
	EReplaceAll,
	EReplaceSkip
	};

struct SEdwinFindModel
	{
	TInt iFlags; // TEdwinFindFlags
	TBuf<EEikEdwinFindStringMaxLen> iText;
	TBuf<EEikEdwinFindStringMaxLen> iReplaceText;
	TReplaceOption iReplaceOption;
	};	

class CEikEdwin : public CEikBorderedControl, public MEikScrollBarObserver, public CTextView::MObserver, public MEditObserver, public MEikCcpuEditor
	{
private:
	class CUndoBuffer;
public:

	enum TFlags
		{ // user flags
		EZeroEnumValue			=0x00000000, 
		EKeepDocument			=0x00000001,
		ESegmentedStorage		=0x00000002,
		EWidthInPixels			=0x00000004,
		ENoAutoSelection		=0x00000008,
		EJustAutoCurEnd			=0x00000010,
		ENoWrap					=0x00000020,
		ELineCursor				=0x00000040, 
		ENoHorizScrolling		=0x00000080, 
		EInclusiveSizeFixed		=0x00000100, 
		EUserSuppliedText		=0x00000200,
		EOwnsWindow				=0x00000400,
		EDisplayOnly			=0x00000800,
		EAlwaysShowSelection	=0x00001000,
		EReadOnly				=0x00002000,
		EAllowPictures			=0x00004000,
		EAllowUndo				=0x00008000,
		ENoLineOrParaBreaks		=0x00010000,
		EOnlyASCIIChars			=0x00020000,
		EResizable				=0x00040000,
		EIgnoreVirtualCursor	=0x00080000,
		ENoCustomDraw			=0x01000000,
		EAvkonEditor			=0x02000000,
		EAvkonDisableCursor		=0x04000000,
		EAvkonNotEditable		=0x08000000, 
		EEdwinAlternativeWrapping = 0x10000000
		};
	enum TClipboardFunc
		{
		ENoClipboard,
		ECut,
		ECopy,
		EPaste
		};
	enum TFindFlags
		{
		EFindDirectionUp	=0x01,
		EFindWholeWord		=0x02,
		EFindCaseSensitive	=0x04,
		EFindAgain			=0x08,
		ENoBusyMessage		=0x10,
		EReadOnlyFile		=0x20 // New for CKon
		};
	enum TSetContent
		{
		EUseText,
		ECopyText
		};
	enum TOwnershipType
		{
		EOwnsText,
		EDoesNotOwnText
		};
	enum TEdwinHotKeys // order of hotkeys defined in resource file.  Not all applicable to plain text editors
		{
		EHotKeyCut,
		EHotKeyCopy,
		EHotKeyPaste,
		EHotKeyUndo,
		EHotKeyFind,
		EHotKeyInsertChar,
		EHotKeyBold,
		EHotKeyItalic,
		EHotKeyUnderline,
		EHotKeyFont,
		EHotKeyInsertObject,
		EHotKeyEditObject,
		EHotKeyFormatObject
		};
public: // construction and destruction
	IMPORT_C ~CEikEdwin();
	IMPORT_C CEikEdwin();
	IMPORT_C CEikEdwin(const TGulBorder& aBorder);
	IMPORT_C void ConstructL(TInt aEdwinFlags=0,TInt aWidthInChars=0,TInt aTextLimit=0,TInt aNumberOfLines=0);
	IMPORT_C void SetEdwinObserver(MEikEdwinObserver* aEdwinObserver);
	IMPORT_C void AddEdwinObserverL(MEikEdwinObserver* aEdwinObserver);
	IMPORT_C void RemoveEdwinObserver(MEikEdwinObserver* aEdwinObserver);
	IMPORT_C void SetContainerWindowL();
	IMPORT_C void SetDocumentContentL(CGlobalText& aText,TSetContent aContent=CEikEdwin::ECopyText);
public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void ActivateL();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C void SetContainerWindowL(const CCoeControl& aParent);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	/**
	* Access to the input capabilities of the edwin
	*
	* @return copy of input capabilities structure
	*/
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	/**
	* This method sets the input capabilities of the edwin. Ownership of the T-class is not
	* transferred; a copy is maintained somewhere within the edwin.
	*
	* @param aInputCapabilities		Reference to an input capabilities object on the heap 
	*/
	IMPORT_C void SetInputCapabilitiesL(const TCoeInputCapabilities& aInputCapabilities); 
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
public: // from MEikScrollBarObserver
	IMPORT_C void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType); // from MEilScrollBarObserver
public: // from CTextView::MObserver
	IMPORT_C void OnReformatL(const CTextView* aTextView);
public:
	IMPORT_C TInt TextLength() const;
	IMPORT_C TInt CursorPos() const;
	IMPORT_C TInt SelectionLength() const;
	IMPORT_C TCursorSelection Selection() const;
	IMPORT_C void ClearSelectionL();
	IMPORT_C void SetSelectionL(TInt aCursorPos,TInt aAnchorPos);
	IMPORT_C void SetCursorPosL(TInt aCursorPos,TBool aSelect);
	IMPORT_C void SelectAllL();
	IMPORT_C void CalculateWidth(TInt aWidthInChars);
	IMPORT_C void GetText(TDes& aDes) const;
	IMPORT_C HBufC* GetTextInHBufL() const;
	IMPORT_C void SetTextL(const TDesC* aDes);
	IMPORT_C void ClipboardL(TClipboardFunc aClipboardFunc);
	IMPORT_C void InsertFieldL(CTextField* aField,TUid aFieldType);
	IMPORT_C void UpdateAllFieldsL();
	IMPORT_C void UpdateCurrentFieldL();
	IMPORT_C TInt CountWords();
	IMPORT_C void InsertFromTextFileL(const TFileName &aFileName,const CPlainText::TTextOrganisation aTextOrganisation=CPlainText::EOrganiseByLine);
	IMPORT_C static TInt IdleL(TAny *aPtr);
	IMPORT_C CPlainText* Text() const;
	IMPORT_C void CancelFepTransaction(); // this is particularly important for when the front-end processor is inline-editing a CEikEdwin
	IMPORT_C void HandleTextChangedL();
	IMPORT_C TInt LayoutWidth() const;
	IMPORT_C void NotifyNewDocumentL();
	IMPORT_C void NotifyNewFormatL();
	IMPORT_C TBool FindL(const TDesC* aFindText,TInt aFindFlags=0);
	IMPORT_C TInt FindTextL(const TDesC* aFindText,TInt aPos,TInt aFindFlags);
	IMPORT_C void ReplaceL(SEdwinFindModel* aFindModel);
	IMPORT_C void ReplaceAllL(SEdwinFindModel* aFindModel);
	IMPORT_C void GetFindText(TDes* aFindText);
	IMPORT_C void UpdateScrollBarsL();
	IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL();
	inline CEikScrollBarFrame* CreatePreAllocatedScrollBarFrameL();
	inline CEikScrollBarFrame* ScrollBarFrame();
	IMPORT_C void SetWordWrapL(TBool aWrapIsOn);
	IMPORT_C virtual TInt LineCursorWidth() const;
	IMPORT_C void SetZoomFactorL(TZoomFactor* aZoomFactor);
	IMPORT_C void SetBackgroundColorL(TRgb aBackground);
	IMPORT_C void SetWysiwygModeOn(TInt aLayoutWidth,MGraphicsDeviceMap* aDevice);
	IMPORT_C void SetWysiwygModeOff();
	IMPORT_C void UpdateLayoutWidth(TInt aLayoutWidth); // for use in wysiwyg mode only
	IMPORT_C void SendDataOverIrL();
	IMPORT_C void ReceiveDataOverIrL();
	IMPORT_C void SetAmountToFormatL(TBool aIsNewDoc=EFalse);
	IMPORT_C void SetPasteFromIrStore(TBool aPasteFromIrStore);
	IMPORT_C void PasteFromStoreL(CStreamStore& aStore, CStreamDictionary& aDict);
	IMPORT_C void CopyToStoreL(CStreamStore& aStore, CStreamDictionary& aDict);
	IMPORT_C void SetBorderViewMargins(TMargins8 aMargins);
	IMPORT_C void ForceScrollBarUpdateL();
	IMPORT_C void SetDocumentOwnership(TOwnershipType aOwner);
	IMPORT_C void SetTextLimit(TInt aLimit);
	IMPORT_C void RunCharMapDialogL();
	IMPORT_C TMargins8 Margins() const;
	IMPORT_C TInt UpperFullFormattingLength() const;
	IMPORT_C TInt LowerPartialFormattingLength() const;
	IMPORT_C void SetReadOnly(TBool aReadOnly);
	IMPORT_C TBool IsReadOnly() const;
	IMPORT_C void CheckNotReadOnlyL();
	IMPORT_C void SetAllowPictures(TBool aAllow);
	IMPORT_C void CheckRemovePictures(TInt aStartPos,TInt aLength);
	IMPORT_C void SetRightWrapGutter(TInt aGap);
	IMPORT_C void UndoL();
	IMPORT_C void ClearUndo();
	IMPORT_C void SetAllowUndo(TBool aAllow);
	IMPORT_C TBool SupportsUndo() const;
	IMPORT_C TBool CanUndo() const;
	IMPORT_C void SetWordDelimiters(TBool aPicture,TBool aPunctuation);
	IMPORT_C void GetWordInfo(TInt aCurrentPos,TInt& aStartPos,TInt& aLength) const;
	IMPORT_C void MoveCursorL(TCursorPosition::TMovementType aMovement,TBool aSelect);
	IMPORT_C void MoveDisplayL(TCursorPosition::TMovementType aMovement);
	IMPORT_C void CheckValidityOfChars(TInt aStartPos,TInt aLength);
	IMPORT_C void SetOnlyASCIIChars(TBool aASCIIOnly);
	IMPORT_C TBool OnlyASCIIChars() const;
	inline TInt AvgLinesInViewRect() const;
	inline TInt AvgCharsPerLine() const;
	inline void SetAvgLinesInViewRect(TInt aAvgLines);
	inline void SetAvgCharsPerLine(TInt aAvgChars);
	IMPORT_C void SetEdwinSizeObserver(MEikEdwinSizeObserver* aEdwinSizeObserver);
	IMPORT_C TInt MinimumHeight() const;
/*	
Please do not use the following method for deciding heights if you are using edwins with Maximum Heights 
in forms.  Use MaximumHeightInLines instead. JIn
*/
	IMPORT_C TInt MaximumHeight() const;

	IMPORT_C void SetMinimumHeight(TInt aHeight);
/*	
Please do not use the following method for setting maximum heights if you are using edwins with 
Maximum Heights in forms.  Use MaximumHeightInLines instead. JIn
*/
	IMPORT_C void SetMaximumHeight(TInt aHeight);
public: // new utility methods
	IMPORT_C void InsertDeleteCharsL(TInt aInsertPos,const TDesC& aText,const TCursorSelection& aDelete);
	IMPORT_C void SetNonPrintingCharsVisibility(TNonPrintingCharVisibility aVisibility);
	IMPORT_C TNonPrintingCharVisibility NonPrintingCharsVisibility() const;
public: // new Avkon wrap interface
	IMPORT_C void SetAvkonWrap(TBool aAvkonWrapIsOn);
public:	// Avkon editor extensions
	IMPORT_C void SetAknEditorCase(TInt aCase);
	IMPORT_C void SetAknEditorPermittedCaseModes(TInt aPermittedCaseModes);
	IMPORT_C void SetAknEditorNumericKeymap(TAknEditorNumericKeymap aNumericKeymap);
	IMPORT_C void SetAknEditorInputMode(TInt aInputMode);
	IMPORT_C void SetAknEditorAllowedInputModes(TInt aInputModes);
	IMPORT_C void SetAknEditorSpecialCharacterTable(TInt aSCTResId);
	IMPORT_C void SetAknEditorFlags(TInt aFlags);
	IMPORT_C void EnableCcpuSupportL(TBool aSupport);
	IMPORT_C void SetAknEditorCurrentInputMode(TInt aInputMode);
	IMPORT_C void SetAknEditorCurrentCase(TInt aCase);
	IMPORT_C void SetAknEditorLocalLanguage(TLanguage aLanguage);
	IMPORT_C void NotifyEditorStateObserverOfStateChangeL();
public:
// These methods have been added for use with Avkon to set maximum editor heights.
// Second argument has been deprecated, and will be removed from future API.
	IMPORT_C void SetMaximumHeightInLines(TInt aLines, TInt aBaselineSeparation);
	IMPORT_C TInt MaximumHeightInLines() const;
public: // From MEikCcpuEditor
	IMPORT_C TBool CcpuIsFocused() const;
	IMPORT_C TBool CcpuCanCut() const;
	IMPORT_C void CcpuCutL();
	IMPORT_C TBool CcpuCanCopy() const;
	IMPORT_C void CcpuCopyL();
	IMPORT_C TBool CcpuCanPaste() const;
	IMPORT_C void CcpuPasteL();
	IMPORT_C TBool CcpuCanUndo() const;
	IMPORT_C void CcpuUndoL();
	IMPORT_C TInt  AknEdwinFlags() const;
 

public: // Internal to Symbian
	// the following methods are deprecated and will be removed in a future release
	IMPORT_C void CreateTextViewL();
	IMPORT_C CTextView* TextView() const;
	IMPORT_C CTextLayout* TextLayout() const;
	IMPORT_C TBool SetUndoBufferL(const TCursorSelection& aSelection);
	IMPORT_C void SetUndoableText(const TCursorSelection& aSelection);

	inline void SetMaxLength(TInt aLength );
	inline TInt MaxLength() const;
public:
	// added to get access to user flags without a get/set for every different flag.
	IMPORT_C void AddFlagToUserFlags(TUint32 aFlag);
	IMPORT_C void RemoveFlagFromUserFlags(TUint32 aFlag);
	IMPORT_C TUint32 UserFlags() const ;

public:
	IMPORT_C void SetCharFormatLayer(CCharFormatLayer* aCharFormatLayer);
	IMPORT_C void SetParaFormatLayer(CParaFormatLayer* aParaFormatLayer);

protected:
	enum TEnd
		{
		EStart,
		EEnd   
		};
	enum TChunkSize
		{
		EChunkWord,
		EChunkPara
		};
	enum TEikEdwinFlags
		{ // internal flags
		ERichText           =0x00000001,
		EDragDouble			=0x00000002,
		ELeftDownInViewRect =0x00000004,
		ENumericCharacters	=0x00000008, // only used to calculate initial width
		EHasOneLineOnly     =0x00000010  // when edwin has one line and is not resizable
		};
protected: // from MEditObserver
	IMPORT_C void EditObserver(TInt aStartEdit,TInt aEditLength);
protected:
	IMPORT_C void TrappedDraw(const TRect& aRect) const;
	IMPORT_C void DrawContents();
	IMPORT_C void BaseConstructL();
	IMPORT_C void FormatTextL();
	IMPORT_C TInt DeleteHighlightL(TBool& aChanged,TBool aIsBackSpace=EFalse,TBool aPromptConfirmation=ETrue);
	IMPORT_C TBool OkToDeleteSelectionL();
	IMPORT_C void DeleteL(TBool& aChanged,const TCursorSelection& aSelection,TBool aIsBackSpace=EFalse,TBool aAllowUndo=ETrue);
	IMPORT_C void TrappedSizeChanged();
	IMPORT_C void HandleSizeChangedL();
	IMPORT_C void CancelSelectionL(TEnd aEndOfSelectionToLeaveCursor);
	IMPORT_C void MoveCursorToChunkStartL(TBool aSelect,TChunkSize aChunkSize,TEnd aEndScanningTowards);
	IMPORT_C void CancelInsertCharFormat();
	IMPORT_C void PlaceDataOnClipboardL();
	IMPORT_C void ReportEdwinEventL(MEikEdwinObserver::TEdwinEvent aEventType);
	IMPORT_C void SetLineCursorDetailsL();
	IMPORT_C virtual void CopyDocumentContentL(CGlobalText& aInText,CGlobalText& aOutText);
	IMPORT_C void DisplayFindTextNotFound(TDes& aFindText);
	IMPORT_C virtual void HandleTextPastedL(TInt aStartPos,TInt& aLength);
	IMPORT_C virtual CLafEdwinCustomDrawBase* CreateCustomDrawL();
	// Avkon editor extensions
	IMPORT_C void ReadAknResourceL(TResourceReader& aReader);
protected: // Internal to Symbian
	IMPORT_C void CreateLayoutL(MLayDoc* aLayDoc);
	IMPORT_C void CreateTextAndLayoutL(CParaFormatLayer* aParaFormatLayer,CCharFormatLayer* aCharFormatLayer);

private:
	enum
		{ // internal flags
		EWysiwygOn						=0x00000010,
		EUnderOneScreenFormattedText	=0x00000020,
		EPictureDelimits				=0x00000040,
		EPunctuationDelimits			=0x00000080,
		EPasteFromIrStore				=0x00000100,
		ELockScrollBarState				=0x00000200,
		EOnReformatting					=0x00000400
		};

private: // from CCoeControl
	IMPORT_C void SizeChanged();
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void Reserved_2();
private:
	IMPORT_C virtual void Reserved_3();
	IMPORT_C virtual void NotifyInvalidOperationOnReadOnlyL();
	IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc);
	void SetVirtualCursorStateL(TBool aIsFocused) const;
	void SetHeightForNumOfLinesL();
	void ApplyAutoSelectionL();
	void SetScrollBarsL();
	void SetVertScrollBarModelByCharactersL(TEikScrollBarModel& aVertModel) const;
	void RetrieveDataFromClipboardL();
	void SetCursorVisibilityL(TBool aEmphasis);
	TBool OwnsScrollBars() const;
	void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
	void UpdateHorizScrollBarThumb();
	void UpdateVertScrollBarThumbL();
	void DoSetUndoBufferL(const TCursorSelection& aSelection);
	void DoPasteFromStoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
	void DoReplaceAllL(SEdwinFindModel* aModel,TBool& aTextFound,TBool& aReplaced);
	void DeleteExtraParasL(TInt aStartPos,TInt aLength);
	TInt LocateChar(TChar aChar,TInt aStartPos,TInt aLength);
	TBool IsValidChar(TInt aChar) const;
	TInt CalcMinimumHeightFromNumOfLinesL() const;
	void CheckEdwinHeight();
	TBool IsNewHeightWithinMinimumAndMaximum(TInt aNewHeight) const;
	void SetEdwinHeight(TInt aHeight);
	void DoCreateCustomDrawL();
	void SetCursorSizeAndType();
	TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void DoCcpuCanPasteL() const;
	void DoReportEventL(MCoeControlObserver::TCoeEvent aEvent);
	void CheckIfEdwinIsResizable();
	void SetKeyboardRepeatRate(TTimeIntervalMicroSeconds32 aKeyRepeatRate) const;
	HBufC* GetAllowedCharsLC() const;
	TInt CheckAllowedCharsL(const TDesC& aChars, CClipboard& aClipboard, TBool aRichText) const;

	TInt CursorWidth() const;
	TFontSpec CursorFontSpec() const;

	void BuildEdwinFepSupport();
	inline void CheckEdwinExtensionL();
	void MakeCharFormatLayerMatchL(CCharFormatLayer* aCharFormatLayer);
	void MakeParaFormatLayerMatchL(CParaFormatLayer* aParaFormatLayer);
private:
	void CEikEdwin::DrawFirstLineTextL() const;

protected:
	TUint32 iEdwinUserFlags;
	TUint32 iEdwinInternalFlags;
	CPlainText* iText;
protected: // Internal to Symbian
	CTextView* iTextView;
	CTextLayout* iLayout;
protected:
	TInt iTextLimit;
	TInt iNumberOfLines;
	MGraphicsDeviceMap* iZoomFactor;
	TInt iLastPointerDocPos;
	TMargins8 iMargins;
private:
	friend class CEikEdwinFepSupport;
	// added this class to allow additional data members without breaking BC
	class CEikEdwinExtension : public CBase
		{
	public:
		inline void SetScrollBarSetter(CIdle* aScrollBarSetter);
		inline CIdle* ScrollBarSetter();
		inline const TAvkonEditorCustomWrap& TextWrapper();
	private:
		CIdle* iSetScrollBar;
		TAvkonEditorCustomWrap iTextWrapper;
		};
	CEikEdwinExtension* iEdwinExtension; // replaced iSetScrollBar
	CEikScrollBarFrame* iSBFrame;
	MEikEdwinObserver* iEdwinObserver;
	CArrayPtr<MEikEdwinObserver>* iObserverArray;
	CEikEdwinFepSupport* iEdwinFepSupport;
	CUndoBuffer* iUndoStore;
	TInt iAvgLinesInViewRect;
	TInt iAvgCharsPerLine;
	TInt iRightWrapGutter;
	TInt iLayoutWidth;
	MEikEdwinSizeObserver* iEdwinSizeObserver;
	TInt iMinimumHeight;
	TInt iMaximumHeight;
/* 
iMaximumHeightInLines
---------------------
This is simply a holder for the number, used to simplify some Avkon LAF requirements.
The viewable region of an edwin is actually measured in pixels, However, if certain LAF
requirements are enforced (that the view region has to be smaller than the number of 
lines viewable * the baseline separation (in pixels)) some undesired scrolling effects
occur.


That is to say, by simply setting iMaximumHeightInLines, this will not affect
the actual maximum height of the edwin.  To do this, you must set the iMaximumHeight

One of the use cases of this member variable is for AknLayoutUtils::LayoutEdwin. 
That method uses iMaximumHeightInLines along with the baseline separation, to set 
the iMaximumHeight.

The general formula is very simple, to remove unneeded scrolling.
iMaximumHeight=baselineSeparation*iMaximumNumberOfLines

If you cannot allocate sufficient space to the edwin, to permit so much viewable region
then the method AlterViewRect can be called on the TextView() component.  This will introduce
a clipping rectangle, which allows blank space required by the edwin layout component
to not be shown.
*/
	TInt iMaximumHeightInLines; 
	CLafEdwinCustomDrawBase* iCustomDrawer;
	TInt iLastPointerAnchorPos;
	CAknCcpuSupport* iCcpuSupport;
	CCharFormatLayer* iCharFormatLayer;
	CParaFormatLayer* iParaFormatLayer;
	TInt iSpare_1;
	TInt iSpare_2;
	};

class CAvkonEdwinCustomDraw : public CLafEdwinCustomDrawBase
	{
public:
	static CAvkonEdwinCustomDraw* NewL(const MLafEnv& aEnv,const CCoeControl& aControl);
public: // from MFormCustomDraw
	void DrawText(const TParam& aParam,const TLineInfo& aLineInfo,const TCharFormat& aFormat,
								   const TDesC& aText,const TPoint& aTextOrigin,TInt aExtraPixels) const;
private:
	CAvkonEdwinCustomDraw(const MLafEnv& aEnv,const CCoeControl& aControl);
	};

inline CEikScrollBarFrame* CEikEdwin::CreatePreAllocatedScrollBarFrameL()
	{ return CreateScrollBarFrameL(ETrue);}
inline CEikScrollBarFrame* CEikEdwin::ScrollBarFrame()
	{ return ((CEikScrollBarFrame* const)iSBFrame); }
inline TInt CEikEdwin::AvgLinesInViewRect() const
	{ return iAvgLinesInViewRect; }
inline TInt CEikEdwin::AvgCharsPerLine() const
	{ return iAvgCharsPerLine;}
inline void CEikEdwin::SetAvgLinesInViewRect(TInt aAvgLines)
	{ iAvgLinesInViewRect=aAvgLines; }
inline void CEikEdwin::SetAvgCharsPerLine(TInt aAvgChars)
	{ iAvgCharsPerLine=aAvgChars; }

inline void CEikEdwin::SetMaxLength(TInt aLength ) 
	{ SetTextLimit(aLength); }
inline TInt CEikEdwin::MaxLength() const 
	{ return iTextLimit; }

inline void CEikEdwin::CEikEdwinExtension::SetScrollBarSetter(CIdle* aScrollBarSetter)
	{ iSetScrollBar=aScrollBarSetter; }
inline CIdle* CEikEdwin::CEikEdwinExtension::ScrollBarSetter()
	{ return iSetScrollBar; }
inline const TAvkonEditorCustomWrap& CEikEdwin::CEikEdwinExtension::TextWrapper()
	{ return iTextWrapper; }

inline void CEikEdwin::CheckEdwinExtensionL()
	{
	if (!iEdwinExtension)
		iEdwinExtension=new (ELeave) CEikEdwinExtension;
	}

#endif
