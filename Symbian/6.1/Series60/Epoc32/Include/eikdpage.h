// EIKDPAGE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDPAGE_H__)
#define __EIKDPAGE_H__

#include <coeccntx.h>
#include <eiksbfrm.h>
#include <coecobs.h>
#include <eikedwob.h>
#include <aknpopupfieldtext.h>

//
// Forward declarations.
//

class CEikCapCArray;
class CEikCaptionedControl;
class CEikDialogPageContainer;
class CEikEdwin;
class CEikLabel;
class MEikDialogPageObserver;
struct SEikControlInfo;

//class CAknNavigationDecorator ;

const TInt KXOffsetForDataPaneInEditMode=1;
const TInt KYOffsetForDataPaneInEditMode=7;


class CEikDlgToolTipMgr ;
/**
 * The CEikDialogPage class implements a scrollable dialog page control.
 *
 * @internal
 * @since ER5U
 */
class CEikDialogPage : 
	public CCoeControl, 
	public MCoeControlObserver, 
	public MEikScrollBarObserver, 
	public MEikEdwinSizeObserver,
	public MAknPopupFieldObserver,
	public MEikEdwinObserver
	{
public:
	enum TFocusNavigationMode
		{
		ECyclic,
		ENonCyclic
		};
	enum TAScrollBarBreadthAllocationMode
		{
		ENone									=0x0000,
		EScrollBarBreadthPreAllocated			=0x1000
		};
	/**
	* Enumeration to express what layout is currently being used. Note that the use of 
	* bitmaps on the left is controlled by D
	*
	*/
	enum TFormLayoutSelection
		{
		ESingle,
		EDouble
		};

public:
	~CEikDialogPage();
	static CEikDialogPage* NewL(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver);
	static CEikDialogPage* NewLC(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver);
	static CEikDialogPage* NewL(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver,TResourceReader& aReader);
	static CEikDialogPage* NewLC(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,const CEikDialogPageContainer& aParent,MEikDialogPageObserver* aPageObserver,TResourceReader& aReader);
	void SetDataPosition(TInt aPosition);
	TSize PreferredSize() const;
	void SetActiveL();
	void SetActiveAndFocusL();
	void SetInactiveL();
	TInt PageId() const;
	TInt LineId(const CCoeControl& aControl) const;
	TBool SetInitialFocus();
	CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aLineId,TInt aControlType,TAny* aReturnValue);
	void SetControlCaptionL(TInt aLineId,const TDesC& aText);
	void SetControlCaptionL(TInt aLineId,TInt aResourceId);
	CCoeControl* Control(TInt aLineId) const;
	CCoeControl* ControlOrNull(TInt aLineId) const;
	TInt ControlHeight(TInt aLineIndex) const;
	CEikCaptionedControl* Line(TInt aLineId) const;
	CEikCaptionedControl* LineOrNull(TInt aLineId) const;
	CEikCaptionedControl* CurrentLine() const;
	void SetDensePacking(TBool aDensePacking);
	void InsertLineL(TInt aPosition,TInt aResourceId);
	void DeleteLine(TInt aLineId,TBool aRedrawNow);
	void AdjustAllIds(TInt aControlIdDelta);
	TInt FocusLineL(TInt aLineId);
	TInt FocusedLineId() const;
	void GetAutoValues();
	TKeyResponse OfferUpDownKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,TFocusNavigationMode aFocusNavigationMode);
	TBool OwnsLine(TInt aLineId) const;
	void ResetLineMinimumSizes();
	TInt FindLineIndex(const CCoeControl* aControl) const;
	TBool RotateFocusByL(TInt aDelta);
	TKeyResponse OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TBool TakesEnterKey();
	TInt LineIndex(TInt aLineId);
	void ReportPageChangedL();
	void SetFlag(TInt aFlag);
	TInt GetFormFlags() const;
	void ConstructFormFromResourceL( TResourceReader& aReader ) ;
	void SetEditableL( TBool aEditable, TBool aActivePage ) ;
	void SetTipManager( CEikDlgToolTipMgr* aTipManager ) ;
	TBool IsEditable() const;
	TBool IsForm() const;
public:
	void UpdateScrollBarL();


public: // from CCoeControl
	TSize MinimumSize();
	virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	virtual void HandleResourceChange(TInt aType);
	virtual void PrepareForFocusLossL();
	virtual void SetDimmed(TBool aDimmed);
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
public: // from MCoeControlObserver
	virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
public: // from MEikEdwinSizeObserver
	virtual TBool HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize);
public: // from MEikEdwinObserver
	virtual void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType);

public: // from MAknPopupFieldObserver
	virtual void HandlePopupFieldEventL(CAknPopupField* aPopupField, TAknPopupFieldEvent aEventType, TInt aHint);
public: 
	void SetPageContainer(const CEikDialogPageContainer* aPageContainer);
	const CEikDialogPageContainer* PageContainer() const;
	void RedrawNecessaryDataNow(const TRect& aRect) const;
protected: // from CCoeControl
	void WriteInternalStateL(RWriteStream& aWriteStream) const;
	void SizeChanged();
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	void FocusChanged(TDrawNow aDrawNow);
	void Draw(const TRect& aRect) const;
public:
	// added to allow Form format to be set by API
	IMPORT_C void SetFormLayout(TFormLayoutSelection aLayout);
	IMPORT_C TFormLayoutSelection FormLayout() const;
public:
	CEikCaptionedControl* FindNextControlOnPageWithHeight(TBool aUpwards,const CEikCaptionedControl* aLineYouAreOn) const;
public:
	TBool IsAtOrOffTopOfPage(const CCoeControl* aControl) const;
	TBool IsAtOrOffBottomOfPage(const CCoeControl* aControl) const ;
public:
	TBool VisibleSizeOnPage(TInt& aHeightOfControlVisibleOnPage, const CCoeControl* aControl) const;

protected: // from MEikScrollBarObserver
	virtual void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType);

private: // from CCoeControl
	void Reserved_2();
private:
	enum TFlag
		{
		EWindowsSizedForScrollBar=0x0001
		};
private: // new functions
	void AfterAddingNewLinesL(TInt aNewLineAdded);
	void CallDrawNowOnMinimumNoComponents(TRect aRect) const;

	CEikDialogPage(TInt aId,RWindow& aViewWin,CEikScrollBarFrame& aSBFrame,MEikDialogPageObserver* aPageObserver);
	void ConstructL();
	void ConstructFromResourceL(TResourceReader& aReader, TBool aFormControl = EFalse );
	void ConstructByTypeL(TInt aControlType,CEikCaptionedControl* aLine,CCoeControl* aContainer);
	void ShowFocus(TBool aFocus, TBool aRedraw=ETrue);
    SEikControlInfo CreateCustomControlL(TInt aControlType);
	void ChangeFocusTo(TInt aLineIndex);
	void PrepareForFocusTransitionL();
	TInt IdOfFocusControl() const;
	void UpdateScrollBar();
	void ChangeFocusToAndExposeL(TInt aLine,TBool aShowWholeControl=EFalse);
	TInt TopFocusableLine() const;
	TInt BottomFocusableLine() const;
	TBool LineIsFocusable(TInt aLine) const;
	TBool ResizeEdwinToFitTextL(CEikEdwin* aEdwin, TDrawNow aDrawNow, TSize aDesirableEdwinSize);
	TSize SizeDeltaOfEdwinBorderPlusMargins(CEikEdwin* aEdwin) const;
	TInt YPosToLine(TInt& aYPos) const;
	TInt LineToYPos(TInt& aLine) const;
	void ExposeLine(TInt aLine, TBool aShowWholeLine=EFalse);
	void SetDataWinSize();
	void PassOnEventL(CCoeControl* aControl,MCoeControlObserver::TCoeEvent aEvent);
	CEikCaptionedControl* ConstructLineL(TInt aResourceId);
	CEikCaptionedControl* ConstructLineL(TResourceReader& aReader);
	void ConstructLineL(TResourceReader& aReader,CEikCaptionedControl* aLine);
	TKeyResponse HandleCyclicFocusNavigationKeyL(const TKeyEvent& aKeyEvent);
	TKeyResponse HandleNonCyclicFocusNavigationKeyL(const TKeyEvent& aKeyEvent);
	void MakeEdwinScrollbarsVisibleL(TBool aVisible);
	TBool Flag(TFlag aFlag) const;
	void SetFlag(TFlag aFlag);
	void ClearFlag(TFlag aFlag);
	void LineChangedL(TInt aControlId);

	void UpdateToolTipL() ;
	void UpdateScrollBarThumb();

	TInt CalculateEdwinCursorPosition( CEikEdwin* aEdwin , TInt& aLineNumber ) const ;
	TInt GetPositionOfEdwinCursorInDataWin(CEikEdwin* aEdwin) const;
	void ReconsiderPageSize();

	enum TScrollDirection
		{
		ESingleLineScrollUp ,
		ESingleLineScrollDown
		} ;
	void RegisterComponent(TInt aControlType, CCoeControl* aControl, CEikCaptionedControl* aLine);
	static void CommonConstructCodeBetweenNewL(CEikDialogPage& aDialogPage, const CEikDialogPageContainer& aParent);

public: 
	TBool AnythingToDisplay() const;
	void DrawVerticalLine() const;
	CEikCaptionedControl* LineOnPageOrNull(TInt aLine) const;
	TSize RealDataSize() const;
	TInt NumberOfLines() const;
	CEikCaptionedControl* LineByIndex(TInt aIndex) const;
private:
	RWindow& iViewWin;
	CEikScrollBarFrame& iSBFrame;
	CEikCapCArray* iLines;
	MEikDialogPageObserver* iPageObserver;
	TInt iPageId;
	TInt iCurrentLine;
	TPoint iViewWinPos;
	TSize iViewWinSize;
	TPoint iDataWinPos;
	TSize iDataWinSize;
	TInt iFlags;
	TInt16 iFormFlags ;
	TBool iIsEditable;

	TBool iFormControl ;
	CEikDlgToolTipMgr* iTipManager ;

	TInt iLastExposedLine;
	TInt iLastExposedLineViewWinYPosition;
	const CEikDialogPageContainer* iPageContainer;
	TFormLayoutSelection iFormLayout;
public:
mutable	CEikEdwin* iIgnoreFurtherEdwinResizeEvents;
private:
	TInt iSpare;
	};


/**
 * The CEikDialogPageContainer class contains one or more dialog pages and provides an interface to the active
 * page.
 *
 * @internal
 * @since ER5U
 */
class CEikDialogPageContainer : public CCoeControl, public MCoeControlContext
	{
public:
	~CEikDialogPageContainer();
	static CEikDialogPageContainer* NewL(const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver);
	static CEikDialogPageContainer* NewLC(const CCoeControl& aParent,MEikDialogPageObserver* aPageObserver);
	TSize PreferredSize(const TSize& aMaxSize) const;
	void SetActivePageByIdL(TInt aPageId);
	void SetActivePageByIndexL(TInt aPageIndex);
	TInt ActivateFirstPageL();
	void AddPageL(TInt aPageId);
	void AddPageL(TInt aPageId,TResourceReader& aReader);
	TBool SetInitialFocus();
	CEikCaptionedControl* Line(TInt aLineId) const;
	CEikCaptionedControl* LineOrNull(TInt aLineId) const;
	CEikCaptionedControl* CurrentLine() const;
	void SetPageDensePacked(TInt aPageId,TBool aDensePacked);
	void SetAllPagesDensePacked(TBool aDensePacked);
	void SetPageDimmed(TInt aPageId,TBool aDimmed,TDrawNow aDrawNow);
	TBool IsActivePageDimmed() const;
	TInt LineId(const CCoeControl& aControl) const;
	void InsertLineL(TInt aPosition,TInt aPageId,TInt aResourceId);
	void DeleteLine(TInt aLineId, TBool aRedrawNow);
	void AdjustAllIds(TInt aPageId,TInt aControlIdDelta);
	CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aLineId,TInt aControlType,TAny* aReturnValue);
	CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aLineId,TInt aControlType,TAny* aReturnValue);
	TInt FocusLineL(TInt aLineId);
	TInt FocusedLineId() const;
	void GetAutoValues();
	TKeyResponse OfferUpDownKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType,CEikDialogPage::TFocusNavigationMode aFocusNavigationMode);
	TInt ActivePageId() const;
	TInt ActivePageIndex() const;
	void ResetLineMinimumSizes();
	TInt FindLineIndex(const CCoeControl& aControl) const;
	TBool RotateFocusByL(TInt aDelta);
	TInt NumPages() const;
	TKeyResponse OfferHotKeysKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	TBool TakesEnterKey();
	TInt FindPageIndexForLineId(TInt aLineId);
	void SetPageFlag(TInt aPageId, TInt aFlag);

	CEikDialogPage* Page( TInt aPageID ) ;
	void SetEditableL( TBool aEditable ) ;
	void SetTipManager( CEikDlgToolTipMgr* aTipManager ) ;

public: // from CCoeControl
	virtual void Draw(const TRect& aRect) const;
	virtual TSize MinimumSize();
	virtual void PrepareForFocusLossL();
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	virtual void HandleResourceChange(TInt aType);
public: // from MCoeControlContext
	virtual void PrepareContext(CWindowGc& aGc) const;
public:
	void SetPageFormSized();
protected:	// from CCoeControl
	virtual void SizeChanged();
	virtual TInt CountComponentControls() const;
	virtual CCoeControl* ComponentControl(TInt aIndex) const;
	virtual void ActivateL();
	virtual void FocusChanged(TDrawNow aDrawNow);
	virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;
	virtual void Reserved_2();
public: 
	void SetPageSelector(const CEikDialogPageSelector* aPageSelector);
	const CEikDialogPageSelector* PageSelector() const; 
	void DrawBackgroundNow(const TRect& aRect) const;
private:
	void DrawBackground(const TRect& aRect) const;
private:
	CEikDialogPageContainer(MEikDialogPageObserver* aPageObserver);
	void ConstructL(const CCoeControl& aParent);
	void ConstructFromResourceL(TResourceReader& aReader,const CCoeControl& aParent);
	void CommonConstructL(const CCoeControl& aParent);
	void CreatePageArrayL();
	void CreateScrollBarL(const CCoeControl& aParent);
	void CreateViewWinL(const CCoeControl& aParent);
	TInt PageIndex(TInt aPageId) const;
	TInt PageId(TInt aIndex) const;
	TInt PageIdFromLineId(TInt aLineId) const;
	void SetToolTips() ;
private:
	CEikScrollBarFrame* iSBFrame;
	CArrayPtr<CEikDialogPage>* iPageArray;
	MEikDialogPageObserver* iPageObserver;
	TInt iActivePage;
	CEikDlgToolTipMgr* iTipManager ;
	const CEikDialogPageSelector* iPageSelector;
	TBool iForm;
	TBool iIsEditable;
	};

#endif
