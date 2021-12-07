// EIKDIALG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKDIALG_H__
#define __EIKDIALG_H__

#ifndef __COECOBS_H__
#include <coecobs.h>
#endif

#ifndef __COECCNTX_H__
#include <coeccntx.h>
#endif

#ifndef __EIKBCTRL_H__
#include <eikbctrl.h>
#endif

#ifndef __EIKDPOBS_H__
#include <eikdpobs.h>
#endif

#ifndef __BADESCA_H__
#include <badesca.h>
#endif 

#ifndef __GULFTFLG_HRH__
#include <gulftflg.hrh>
#endif



//
// Header files needed by deprecated interfaces.
//

#ifndef __EIKBUTB_H__
#include <eikbutb.h>
#endif

#ifndef __EIKBTGPC_H__
#include <eikbtgpc.h>
#endif

#include <aknpopupfader.h>

//
// Forward declarations.
//

class CEikMover;
class CEikCaptionedControl;
class CEikCapCArray;
class CEikDialogPageSelector;
class CEikButtonGroupContainer;
class CEikDialogButtonCommandObserver;
class MEikCommandObserver;

struct SEikControlInfo;

//
// Forward declarations needed by deprecated interfaces.
//

class CEikLabel;
class CGlobalText;
struct SEikRange;
struct SEikDegreesMinutesDirection;


/**
 * The CEikDialog class provides an instantiable base class for dialogs. Controls can be added directly
 * to this class but it is normal to create a subclass to handle the controls appearing on the dialog
 * dynamically.
 */
class CEikDialog : public CEikBorderedControl,public MCoeControlObserver,public MEikDialogPageObserver,public MCoeControlContext, public MAknFadedComponent
	{ 
public:
	IMPORT_C CEikDialog(); 
	IMPORT_C ~CEikDialog(); 
	IMPORT_C virtual TInt ExecuteLD(TInt aResourceId);
	IMPORT_C virtual void PrepareLC(TInt aResourceId);
	IMPORT_C virtual TInt RunLD();
	IMPORT_C void SetTitleL(const TDesC& aText);
	IMPORT_C void SetTitleL(TInt aResourceId);
	IMPORT_C void SetPageDimmedNow(TInt aPageId,TBool aDimmed);
	IMPORT_C void SetLineNonFocusing(TInt aControlId);
	IMPORT_C void SetLineDimmedNow(TInt aControlId,TBool aDimmed);
	IMPORT_C void MakeLineVisible(TInt aControlId,TBool aVisible);
	IMPORT_C void MakeWholeLineVisible(TInt aControlId,TBool aVisible);
	IMPORT_C void DeleteLine(TInt aControlId, TBool aRedraw=ETrue);
	IMPORT_C void InsertLineL(TInt aIndex,TInt aResourceId,TInt aPageId=0);
	IMPORT_C void MakePanelButtonVisible(TInt aButtonId,TBool aVisible);
	IMPORT_C void TryChangeFocusToL(TInt aControlId);
	IMPORT_C void SwitchLineLatency(TInt aBecomesLatent,TInt aNoLongerLatent);
	IMPORT_C void SetPageDensePacking(TInt aPageId,TBool aDensePacking);
	IMPORT_C void ConstructAutoDialogLC(TInt aFlags,TInt aButtonsId);
	IMPORT_C void DeclareItemAuto(TInt aControlId,TInt aControlType,TAny* aReturnValue);
	IMPORT_C void Layout();
	IMPORT_C TSize PreferredSize(const TSize& aMaxSize) const;
	IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aControlId,TInt aControlType,TAny* aReturnValue);
	IMPORT_C CCoeControl* CreateLineByTypeL(const TDesC& aCaption,TInt aPageId,TInt aControlId,TInt aControlType,TAny* aReturnValue);
	IMPORT_C void SetControlCaptionL(TInt aControlId,const TDesC& aText);
	IMPORT_C void SetControlCaptionL(TInt aControlId,TInt aResourceId);
	IMPORT_C CEikLabel* ControlCaption(TInt aControlId) const;
	IMPORT_C CCoeControl* Control(TInt aControlId) const;
	IMPORT_C CCoeControl* ControlOrNull(TInt aControlId) const;
	IMPORT_C CEikButtonGroupContainer& ButtonGroupContainer() const;
	IMPORT_C CEikMover& Title() const;
	IMPORT_C TInt ActivePageId() const;
	IMPORT_C void ActivateFirstPageL() const;


// To Support Edit/View state switch for forms (Sapphire DFRD)
// This breaks Binary Compatibility
	IMPORT_C void SetEditableL( TBool aEditable ) ;
	IMPORT_C TBool IsEditable() const ;


public: // from CCoeControl
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C void MakeVisible(TBool aVisible);
protected: // from MEikDialogPageObserver
	IMPORT_C virtual void PrepareForFocusTransitionL();
	IMPORT_C virtual void PageChangedL(TInt aPageId);
	IMPORT_C virtual void LineChangedL(TInt aControlId);
public: // from MEikDialogPageObserver
	IMPORT_C virtual SEikControlInfo CreateCustomControlL(TInt aControlType);
	IMPORT_C MEikDialogPageObserver::TFormControlTypes ConvertCustomControlTypeToBaseControlType(TInt aControlType) const;
	IMPORT_C virtual void GetCustomAutoValue(TAny* aReturnValue,TInt aControlType,const CCoeControl* aControl);
protected: // from MCoeControlContext
	IMPORT_C void PrepareContext(CWindowGc& aGc) const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
protected:
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
protected:
	IMPORT_C TInt GetNumberOfLinesOnPage(TInt aPageIndex) const;
	IMPORT_C TInt GetNumberOfPages() const;
	IMPORT_C CEikCaptionedControl* GetLineByLineAndPageIndex(TInt aLineIndex, TInt aPageIndex) const;
private:
	IMPORT_C void SizeChanged();
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void Reserved_2();
protected: // from MCoeControlObserver
	IMPORT_C void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
protected: // new functions
	IMPORT_C void TryExitL(TInt aButtonId);
	IMPORT_C void AdjustAllIdsOnPage(TInt aPageId,TInt aControlIdDelta);
	IMPORT_C void ConstructSleepingDialogL(TInt aResourceId);
	IMPORT_C void ConstructSleepingAlertDialogL(TInt aResourceId);
	IMPORT_C TInt RouseSleepingDialog();
	IMPORT_C void ExitSleepingDialog();
	IMPORT_C TInt IdOfFocusControl() const;
	IMPORT_C TInt FindLineIndex(const CCoeControl& aControl) const;
	IMPORT_C CEikCaptionedControl* Line(TInt aControlId) const;
	IMPORT_C CEikCaptionedControl* CurrentLine() const;
	IMPORT_C TBool RotateFocusByL(TInt aDelta);
	IMPORT_C TInt ActivePageIndex() const;
	IMPORT_C void ResetLineMinimumSizes();
	IMPORT_C CEikButtonGroupContainer* SwapButtonGroupContainer(CEikButtonGroupContainer* aContainer);
	IMPORT_C MEikCommandObserver* ButtonCommandObserver() const;
protected: // new functions
	IMPORT_C virtual TBool OkToExitL(TInt aButtonId);
	IMPORT_C virtual void PreLayoutDynInitL();
	IMPORT_C virtual void PostLayoutDynInitL();
	IMPORT_C virtual void SetInitialCurrentLine();
	IMPORT_C virtual void HandleControlStateChangeL(TInt aControlId);
	IMPORT_C virtual void HandleInteractionRefused(TInt aControlId);
	IMPORT_C virtual void SetSizeAndPosition(const TSize& aSize);
	IMPORT_C virtual TInt BorderStyle();
	// Added for Avkon


/**
 *  Routine to map the button id ( Avkon softkey command id) to CEikBidCancel if it is a 
 *  "cancel" type command type. 
 *
 * The following cases are mapped to a give an ExecuteLD return value of 0:
 *
 *		EAknSoftkeyCancel:
 *		EAknSoftkeyBack:
 *		EAknSoftkeyNo:
 *
 * Other cases left unchanged
 * 
 * This operation is performed at the last minute and does not affect other processing in CEik/AknDialog. 
 *
 * It is a framework method; It can be overridded to obtain customized behaviour
 *
 * @param	aButtonId	input id to map 
 * @return				0 for re-mapped negative command ids; other values are returned as their 
 *						original command id values
 *		 
 * @since Avkon
 */
	IMPORT_C virtual TInt MappedCommandId( TInt aButtonId );
	IMPORT_C TInt FormFlagsFromActivePage();
/* The following two methods are deprecated
	GetFirstLineOnFirstPageOrNull
	ControlsOnPage

instead the functionality can be achieved by
	TInt GetNumberOfLinesOnPage(TInt aPageIndex) const;
	TInt GetNumberOfPages() const;
	CEikCaptionedControl* GetLineByLineAndPageIndex(TInt aLineIndex, TInt aPageIndex) const;
*/

	IMPORT_C virtual CEikCaptionedControl* GetFirstLineOnFirstPageOrNull();
	IMPORT_C void    ControlsOnPage(RArray<CEikCaptionedControl*>& aControls, TInt aPageId) const;

protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private: // new functions
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();
private: // internal functions
	void BaseConstructL();
	void StaticConstructL(TInt aResourceId);
	void DynamicConstructL();
	void CreateTitleBarL();
	void CreateButtonGroupContainerL(TInt aResourceId);
	void CreatePageSelectorL();
	void CreatePageSelectorL(TInt aResourceId);
	TInt WaitAsRequired();
	void StopWaitingAsRequired();
	TKeyResponse TryAnimateButtonAndExitL(TInt aKeycode);
	void GetAutoValues();
	void CommonConstructSleepingDialog(TInt aResourceId);
	void SetBorderStyle();
	void FadeBehindPopup(TBool aFade);
	void DoFadeBehindPopup(TBool aFade);
	// From MAknFadedComponent
	IMPORT_C virtual TInt CountFadedComponents();
	IMPORT_C virtual CCoeControl* FadedComponent(TInt aIndex);
private:
	CEikMover* iTitleBar;
	CEikDialogPageSelector* iPageSelector;
	CEikButtonGroupContainer* iButtonGroupContainer;
	CEikDialogButtonCommandObserver* iButtonCommandObserver;
	TInt iDialogFlags;
	TInt* iExitConfirmed;

	TBool iIsEditable ;
	TAknPopupFader iPopupFader;
	CActiveSchedulerWait iWait;		// owned, safe to use as direct member data.

	// Extra spare
	TInt iSpareExtra;

private:
	friend class CEikDialogButtonCommandObserver;

public: // added JIn to allow access to dialog flags.
	IMPORT_C TInt DialogFlags();

protected: 
	void RegisterDialgWithPageSelector();

//
// Deprecated interfaces.
// Defined in EIKDLGUT.CPP.
//
public: // Declare auto interfaces.
	IMPORT_C void DeclareAutoTextEditorL(TInt aId,TDes* aText);
	IMPORT_C void DeclareAutoNumberEditor(TInt aId,TInt* aNumber);
	IMPORT_C void DeclareAutoRangeEditor(TInt aId,SEikRange* aRange);
	IMPORT_C void DeclareAutoTimeEditor(TInt aId,TTime* aTime);
	IMPORT_C void DeclareAutoDateEditor(TInt aId,TTime* aDate);
	IMPORT_C void DeclareAutoTimeAndDateEditor(TInt aId,TTime* aTimeAndDate);
	IMPORT_C void DeclareAutoDurationEditor(TInt aId,TTimeIntervalSeconds* aDuration);
	IMPORT_C void DeclareAutoTimeOffsetEditor(TInt aId,TTimeIntervalSeconds* aTimeOffset);
//	IMPORT_C void DeclareAutoLatitudeEditor(TInt aId,SEikDegreesMinutesDirection* aLatitude);
//	IMPORT_C void DeclareAutoLongitudeEditor(TInt aId,SEikDegreesMinutesDirection* aLongitude);
	IMPORT_C void DeclareAutoFixedPointEditor(TInt aId,TInt* aValue);
	IMPORT_C void DeclareAutoSecretEditor(TInt aId,TDes* aText);

public: // Add auto interfaces.
	IMPORT_C void AddAutoTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TDes* aReturn);
	IMPORT_C void AddAutoGlobalTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);
	IMPORT_C void AddAutoRichTextEditorL(const TDesC& aPrompt,TInt aId,TInt aFlags,TInt aWidthInChars,TInt aNoOfLines,TInt aTextLimit,CGlobalText* aReturn,TInt aFontControlFlags=EGulFontControlAll,TInt aFontNameFlags=EGulNoSymbolFonts);
	IMPORT_C void AddAutoNumberEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aReturn);
	IMPORT_C void AddAutoRangeEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,HBufC* aSeparatorText,SEikRange* aReturn);
	IMPORT_C void AddAutoTimeEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TTime* aReturn);
	IMPORT_C void AddAutoDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax, TBool aNoPopout,TTime* aReturn);
	IMPORT_C void AddAutoTimeAndDateEditorL(const TDesC& aPrompt,TInt aId,const TTime& aMin,const TTime& aMax,TBool aNoSeconds,TBool aNoPopout,HBufC* aInterveningText,TTime* aReturn);
	IMPORT_C void AddAutoDurationEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn);
	IMPORT_C void AddAutoTimeOffsetEditorL(const TDesC& aPrompt,TInt aId,const TTimeIntervalSeconds& aMin,const TTimeIntervalSeconds& aMax,TBool aNoSeconds,TTimeIntervalSeconds* aReturn);
//	IMPORT_C void AddAutoLatitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,HBufC* aSecondSign,HBufC* aTextForNorth,TChar aKeyToMatchForNorth,HBufC* aTextForSouth,TChar aKeyToMatchForSouth,SEikDegreesMinutesDirection* aReturn,TInt aFlags=0);
//	IMPORT_C void AddAutoLongitudeEditorL(const TDesC& aPrompt,TInt aId,HBufC* aDegreeSign,HBufC* aMinuteSign,HBufC* aSecondSign,HBufC* aTextForEast,TChar aKeyToMatchForEast,HBufC* aTextForWest,TChar aKeyToMatchForWest,SEikDegreesMinutesDirection* aReturn,TInt aFlags=0);
	IMPORT_C void AddAutoFloatEditorL(const TDesC& aPrompt,TInt aId,const TReal& aMin,const TReal& aMax,TReal* aReturn);
	IMPORT_C void AddAutoFixedPointEditorL(const TDesC& aPrompt,TInt aId,TInt aMin,TInt aMax,TInt* aRetValue,TInt aDecimalPlaces);
	IMPORT_C void AddAutoSecretEditorL(const TDesC& aPrompt,TInt aId,TDes* aReturn);
protected: // Set state interfaces.
	IMPORT_C void SetLabelL(TInt aControlId, const TDesC& aDes);
	IMPORT_C void SetLabelL(TInt aControlId, TInt aResourceId);
	IMPORT_C void SetLabelReserveLengthL(TInt aControlId, TInt aLength);
	IMPORT_C void SetEdwinTextL(TInt aControlId, const TDesC* aDes);
	IMPORT_C void SetTextEditorTextL(TInt aControlId,const CGlobalText* aGlobalText);
	IMPORT_C void ResetSecretEditor(TInt aControlId);
	IMPORT_C void SetFloatingPointEditorValueL(TInt aControlId, const TReal* aValue);
	IMPORT_C void SetFixedPointEditorValueL(TInt aControlId,TInt aValue);
	IMPORT_C void SetFixedPointEditorDecimal(TInt aControlId, TInt aDecimal);
	IMPORT_C void SetNumberEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial min and max are permitted
	IMPORT_C void SetNumberEditorValue(TInt aControlId, TInt aNumber);
	IMPORT_C void SetFloatEditorMinAndMax(TInt aControlId,TInt aMin,TInt aMax);
	IMPORT_C void SetFloatEditorValueL(TInt aControlId,TReal aFloat);
	IMPORT_C void SetRangeEditorMinAndMax(TInt aControlId, TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial min and max are permitted
	IMPORT_C void SetRangeEditorValue(TInt aControlId, const SEikRange& aRange);
	IMPORT_C void SetTTimeEditorMinAndMax(TInt aControlId, const TTime& aMinimumTime, const TTime& aMaximumTime); // only values inside the initial min and max are permitted
	IMPORT_C void SetTTimeEditorValue(TInt aControlId, const TTime& aTime);
	IMPORT_C void SetDurationEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); // only values inside the initial min and max are permi
	IMPORT_C void SetDurationEditorValue(TInt aControlId, const TTimeIntervalSeconds& aDuration);
	IMPORT_C void SetTimeOffsetEditorMinAndMax(TInt aControlId, const TTimeIntervalSeconds& aMinimumTimeOffset, const TTimeIntervalSeconds& aMaximumTimeOffset); // only values inside the initial min and max are
	IMPORT_C void SetTimeOffsetEditorValue(TInt aControlId, const TTimeIntervalSeconds& aTimeOffset);
//	IMPORT_C void SetLatitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLatitude);
//	IMPORT_C void SetLongitudeEditorValue(TInt aControlId, const SEikDegreesMinutesDirection& aLongitude);
	IMPORT_C void SetListBoxCurrentItem(TInt aControlId, TInt aItem);
	IMPORT_C void SetFileNameL(TInt aControlId, const TDesC* aFileName);
protected: // Get state interfaces.
	IMPORT_C void GetLabelText(TDes& aDes,TInt aControlId) const;
	IMPORT_C void GetEdwinText(TDes& aDes,TInt aControlId) const;
	IMPORT_C void GetTextEditorText(CGlobalText*& aGlobalText,TInt aControlId);
	IMPORT_C void GetSecretEditorText(TDes& aDes,TInt aControlId) const;
	IMPORT_C TReal FloatingPointEditorValue(TInt aControlId) const;
	IMPORT_C TInt FixedPointEditorValue(TInt aControlId) const;
	IMPORT_C TInt FixedPointEditorDecimal(TInt aControlId) const;
	IMPORT_C TReal FloatEditorValue(TInt aControlId) const;
	IMPORT_C TInt NumberEditorValue(TInt aControlId) const;
	IMPORT_C SEikRange RangeEditorValue(TInt aControlId) const;
	IMPORT_C TTime TTimeEditorValue(TInt aControlId) const;
	IMPORT_C TTimeIntervalSeconds DurationEditorValue(TInt aControlId) const;
	IMPORT_C TTimeIntervalSeconds TimeOffsetEditorValue(TInt aControlId) const;
//	IMPORT_C SEikDegreesMinutesDirection LatitudeEditorValue(TInt aControlId) const;
//	IMPORT_C SEikDegreesMinutesDirection LongitudeEditorValue(TInt aControlId) const;
	IMPORT_C void GetAutoValuesFromPage(CEikCapCArray* aLines);
	IMPORT_C TInt ListBoxCurrentItem(TInt aControlId) const;
	IMPORT_C void GetFileName(TFileName* aFileName,TInt aControlId) const;
/**
UpdatePageL

Only has effect on Forms, call this after adding or deleting lines.
@ param - whether to redraw the page.  Usually expect this to be ETrue
*/
	IMPORT_C void UpdatePageL(TBool aRedraw);
	};

 
/**
 * AKNLAF - The following structures, classes and static functions 
 * provide LAF for Dialogs and Forms
 * Extensions can be provided as necessary.
 * There are no changes to public API at this stage.
 * There is currently no external configuration
 *
 * SDlgLaf: This class defines a structure for dialog drawing constants.
 * A static function fills a structure.
 */

struct SDlgLaf 
	{
	TInt iTopMargin ;
	TInt iLeftMargin ;
	TInt iColumnSpacing ;
	TInt iRowSpacing ;
	} ;

class LafDialog 
	{
	public:
		static void GetDialogConstants( SDlgLaf& aDlgLaf ) ;  
		static void GetRowSpacing( TInt& aTopMargin, TInt& aRowSpacing ) ;

	} ;

/**
 * SFormLaf: This class defines a structure for Form drawing constants.
 * A static function returns a fills a structure.
 */

struct SFormLaf 
	{
	TInt iTopSpacing ;
	TInt iEditorLineHeight ;
	TInt iEditorWidth ;
	TInt iFormControlHeight ;
	TInt iFormControlWidth ;
	TInt iLeftMargin ;
	TInt iBitmapTop ;
	TInt iBitmapWidth ;
	TInt iBitmapHeight ;
	TInt iCaptionMarginWithBitmap ;
	TInt iCaptionTop ;
	TInt iCaptionWidthWithBitmap ;
	TInt iCaptionWidthNoBitmap ;
	TInt iCaptionHeight ;
	TInt iEditorLeft ;
	TInt iEditorTop ;
	TInt iVerticalBar ;
	TInt iMaxEditorLines ;
	} ;



class LafForm 
	{
	public:
		static void GetFormConstants( SFormLaf& aFormLaf ) ;  
		static void GetRowSpacing( TInt& aTopMargin, TInt& aRowSpacing ) ;
		static void GetVerticalBar( TInt& aVerticalBar ) ;

	} ;


#endif
