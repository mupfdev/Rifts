// EIKCAPC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCAPC_H__)
#define __EIKCAPC_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__FEPBASE_H__)
#include <fepbase.h>
#endif

#if !defined(__EIKLABEL_H__)
#include <eiklabel.h>
#endif

#include <eikdialg.h>
#include <eikdpage.h>



//Temporary Akn constants!  (These should really be read in from Avkon.rss)
const TInt KAknVerticalBar = 50 -1;  // -1 because the whole control is offset by one pixel
const TInt KShadowWidth = 1 ;


class CEikImage ;
class CEikDialogPage;
// Forward declaration of types used in layout routines.
class CAknPopupField;
class CAknSlider;
class CEikEdwin;
class CEikMfne; 
class CEikSecretEditor;

class CEikCaptionedControl : public CCoeControl, public MCoeCaptionRetrieverForFep
	{
public:
	enum TSpaceSharingFlags
		{
		EIfTooSmallCtlGetsWidthLast			=0x0,
		EIfTooSmallCtlGetsWidthFirst		=0x1,
		EIfTooSmallCtlGetsEqualShareOfWidth	=0x2,
		EIfTooBigCtlStaysMinHeight			=0x4,
		EIfTooBigCtlStaysMinWidth			=0x8,
		EIfTooBigCtlStaysMinSize			=0xc
		};
	enum TCaptionExpandingState
		{
		EInitial = 0,
		EExtended =1,
		ERetracted =2
		};

public:
	IMPORT_C CEikCaptionedControl();
	IMPORT_C ~CEikCaptionedControl();
public: // new functions
	IMPORT_C void SetUsesEars();
	IMPORT_C void SetSpaceSharingFlags(TInt aFlags);
	IMPORT_C void SetExtraAscent();
	IMPORT_C void SetCaptionL(const TDesC& aText);
	IMPORT_C void SetTrailerL(const TDesC& aText);
	IMPORT_C void SetCurrent(TBool aSelected);
	IMPORT_C void CheckDimmedDisplayState();
	IMPORT_C void ResetMinimumSizes();
	IMPORT_C TBool IsLatent() const;
	IMPORT_C void SetLatent(TBool aLatent);
	IMPORT_C TBool LatentGroupLineFollows() const;
	IMPORT_C void SetLatentGroupLineFollows(TBool aLglf);
	IMPORT_C TBool DividerAfter() const;
	IMPORT_C void SetDividerAfter(TBool aDividerAfter);
	IMPORT_C TBool TakesEnterKey() const;
	IMPORT_C void SetTakesEnterKey(TBool aTakesEnter);
	IMPORT_C TBool OfferHotKeys() const;
	IMPORT_C void SetOfferHotKeys(TBool aOffer);
public:
	TInt MaximumNumberOfControlLinesOnVisiblePage() const;
public:
	TBool ControlIsAnEdwin(TInt aControlType) const;
	TBool ControlIsAMfne(TInt aControlType) const;
	TBool ControlIsAPopfield(TInt aControlType) const;
	TBool ControlIsASecretEditor(TInt aControlType) const;
	TBool ControlIsASlider(TInt aControlType) const;

public: // from CCoeControl
	IMPORT_C TSize MinimumSize();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;
	IMPORT_C void SetDimmed(TBool aDimmed);
public:
	void RegisterPageWithCaptionControl(const CEikDialogPage* aPage);

private: // from CCoeControl
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void SizeChanged();
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
protected: // from CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
	// from MCoeCaptionRetrieverForFep
	IMPORT_C virtual void GetCaptionForFep(TDes& aCaption) const;
	IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_1();
	IMPORT_C virtual void MCoeCaptionRetrieverForFep_Reserved_2();
public:
	IMPORT_C void SetToolTipTextL( const TDesC& aText ) ;
	IMPORT_C const TDesC* ToolTipText() const ;
	IMPORT_C void SetBitmapFromFileL( const TDesC& aFilename,TInt aMainId,TInt aMaskId =-1 ) ;
//	void ExchangeControlsL(TBool aEditable); // added to allow hidden and viewable controls... usually called by seteditable
	IMPORT_C void SetEditableL( TBool aEditable, TBool aShowEmptyFields = ETrue ) ;
	TPoint LowestExtremity() const ;
	
	void SetFormFlags( TInt aFlags ) ;
	void GetAknLayoutValuesL() ;  // Visible within DLL only.
	TBool HasSeparator() const;
	IMPORT_C const TPtrC GetFullCaptionText() const;
	TBool	IsDisplayable() const;
	void ClearCaptionControlNow() const; // used to clear graphics area before deletion.
protected:
	TRect ViewRect() const;
	TRect EditRect() const;

private:
	enum TWhichEars
		{
		ENoEar=0x00,
		ELeftEar=0x01,
		ERightEar=0x02,
		EBothEars=0x03
		};
private: // new functions
	TInt WidthForEars(TInt aWidthRemaining) const;
	void DrawEarsNow(TWhichEars aEar) const;
	void DrawEars(TWhichEars aEar) const;
	void DrawSingleEar(TWhichEars aEar,TBool aPressed) const;
	TRect EarRect(TWhichEars aEar) const;
	void FireEarL(TWhichEars aEar,TInt aEarRepeat);
	TInt SquashComponentWidth(TInt& aTotalWidth,const TInt aComponentWidthHint);
	void StretchComponents();
	void SetVertEdgeSpacing( TInt aVertEdgeSpacing );
	void SetHorzEdgeSpacing( TInt aHorzEdgeSpacing );
	void SquashComponents();
	void CalculateNumberOfLinesForControl( TInt aLines ) ;
	void SizeDialogComponents() ;
	void PositionDialogComponents() ;
public:
	void PositionFormComponents() ;
public:
	void DrawClosingLine() const;
private:
	TSize EditorControlSize() const ;
	void SetElementBrushColorsL( TRgb aColor ) ;

	TBool ShowBitmap() const;
	void  LayoutBitmap(const TRect& aRect);
	void  LayoutCaption(const TRect& aRect);
	void DoFormCaptionSettingsL(const TDesC& aText);
private:
	static void FormLayoutControlBitmap(CEikImage* aBitmap, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines);
	static void FormLayoutControlEdwin(CEikEdwin* aEdwin, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent);
	static void FormLayoutControlLabel(CEikLabel* aSlider, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aLayoutWithBitmap);
	static void FormLayoutControlMfne(CEikMfne* aMfne,  const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent);
	static void FormLayoutControlPopfield(CAknPopupField* aPopfield, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent);
	static void FormLayoutControlSecretEditor(CEikSecretEditor* aSecretEd, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent);
	static void FormLayoutControlSlider(CAknSlider* aSlider, const TRect& aParent, TBool aIsEditable, TBool aSingleLayout, TInt aNumberOfLines, TBool aBitmapPresent);
	static void ConvertViewRectToEditRect(TRect& aRect);
	static void ConvertEditRectToViewRect(TRect& aRect);

	/**
	*
	* Access method for use in a CAknForm context. 
	*
	* @return	Enumeration for layout for the CAknForm
	*/
	CEikDialogPage::TFormLayoutSelection FormLayout() const;

	/**
	* Draws the separator between (at the top of current ) caption control(s)
	*
	* @param	gc	Current graphics contect
	*/
	void DrawFormSeparator( CWindowGc& gc ) const;

public:
	CCoeControl* iControl;
	CEikLabel* iCaption;
	HBufC* iCaptionText;

	CEikLabel* iTrailer;
	TInt iId;
	TInt iControlType;
	TAny* iReturnValue;
	TBool iIsFormControl ;
	CEikImage* iBitmap ;
	TBool iIsEditable ;

private:
	TBool iHasAppendedEditIndicator;
	TSize iMinSize;
	TInt  iCapCFlags;
	TInt  iCaptionWidth;
	TInt  iFullWidth;
	TSize iNormalSize ;
	HBufC*iToolTipText ;
	TBool iDoNotDisplay ;

	TInt iVertEdgeSpacing ;
	TInt iHorzEdgeSpacing ;
	TInt iOriginalHeight ;

	TSize iEditorControlSize ;
	TInt iNumberOfLines ;

	friend class CEikCapCArray;

	enum { ENotSupplied = -1 } ;
	TInt iFlags ;

	TBool iRefresh ;

	TInt iCaptionFontId ;
	TInt iEditorFontId ;
	TInt iVerticalLineXPosition; //iAknTopSpacing ;			
	CCoeControl* iHighlightControl;
	TInt iSpare; 
	TInt iAknFormControlHeight ;
	TInt iAknFormControlWidth ;
	TInt iPenColor ;
	TInt iShadowColor ;
	TBool iIsCurrentLine;
	const CEikDialogPage* iDialogPage;
	};



#endif
