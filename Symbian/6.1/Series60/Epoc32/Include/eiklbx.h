// EIKLBX.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
   
#if !defined(__EIKLBX_H__)
#define __EIKLBX_H__

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__EIKLBO_H__)
#include <eiklbo.h>
#endif

#if !defined(__EIKSBFRM_H__)
#include <eiksbfrm.h>
#endif

#if !defined(__EIKLBM_H__)
#include <eiklbm.h>
#endif

#if !defined(__EIKLBV_H__)
#include <eiklbv.h>
#endif

#if !defined(__GULBORDR_H__)
#include <gulbordr.h>
#endif

#if !defined(__EIKLBED_H__)
#include <eiklbed.h>
#endif

#if !defined(__GULUTIL_H__)
#include <gulutil.h>
#endif

#if !defined(__LAFPUBLC_H__)
#include <lafpublc.h>
#endif



enum TKeyCode;
class RIncrMatcherBase;
class CListItemDrawer;
class CEikScrollBarFrame;
class CEikButtonBase;
class CMatchBuffer;
class CListBoxExt;

class CEikListBox : public CEikBorderedControl, public MEikScrollBarObserver
	{
public:
	friend class CListBoxExt;
public:
	enum TFlags
		{
		EMultipleSelection			= SLafListBox::EMultipleSelection,
		ENoExtendedSelection		= SLafListBox::ENoExtendedSelection,
		EIncrementalMatching		= SLafListBox::EIncrementalMatching,
		EPopout						= SLafListBox::EPopout,
		ELeftDownInViewRect			= SLafListBox::ELeftDownInViewRect,
		EItemDoubleClicked			= SLafListBox::EItemDoubleClicked,
		EKeepModel					= SLafListBox::EKeepModel,
		EScrollBarSizeExcluded		= SLafListBox::EScrollBarSizeExcluded,
		EStateChanged				= SLafListBox::EStateChanged,
		ECreateOwnWindow			= SLafListBox::ECreateOwnWindow,
        ENoFirstLetterMatching      = SLafListBox::ENoFirstLetterMatching,
 		EPaintedSelection			= SLafListBox::EPaintedSelection ,
		ELoopScrolling = 0x1000,
		EEnterMarks = 0x2000,		// Avkon multiselection list
		EShiftEnterMarks = 0x4000,	// Avkon markable list
		EViewerFlag = 0x8000,		// combined the two flags to fit to WORD.
		EPageAtOnceScrolling = 0x8000, // Avkon viewers
		EDisableHighlight = 0x8000  // Avkon viewers
		};
	enum {KEikMaxMatchingBufferLength = 2};
	enum TScrollBarOwnerShip
	    {
	    ENotOwnedExternally=0x0000,
	    EOwnedExternally   =0x0001
		};
protected:
	enum TReasonForFocusLost
		{ EFocusLostToExternalControl, EFocusLostToInternalEditor };
public:
	// construction/initialization
	IMPORT_C ~CEikListBox();
	IMPORT_C CEikListBox();
	IMPORT_C void ConstructL(MListBoxModel* aListBoxModel,CListItemDrawer* aListItemDrawer,const CCoeControl* aParent,TInt aFlags = 0);
	IMPORT_C void ConstructL(MListBoxModel* aListBoxModel,CListItemDrawer* aListItemDrawer,const CCoeControl* aParent, TGulBorder aBorder, TInt aFlags = 0);

	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C virtual void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aContainer);
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual void SetDimmed(TBool aDimmed);

	IMPORT_C virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType);

	// model/view access functions 
	IMPORT_C MListBoxModel* Model() const;
	IMPORT_C CListBoxView* View() const;

	// functions for accessing top/current/bottom item index
	IMPORT_C TInt TopItemIndex() const;	 
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;
	IMPORT_C TInt BottomItemIndex() const;
	IMPORT_C TInt CurrentItemIndex() const;	  
	IMPORT_C void SetCurrentItemIndex(TInt aItemIndex) const;
	IMPORT_C void SetCurrentItemIndexAndDraw(TInt aItemIndex) const;

	// functions for dealing with the selection state
	IMPORT_C const CListBoxView::CSelectionIndexArray* SelectionIndexes() const;
	IMPORT_C void SetSelectionIndexesL(CListBoxView::CSelectionIndexArray* aArrayOfSelectionIndexes);
	IMPORT_C void ClearSelection();	

	// functions for updating a listbox's internal state after its model has been updated
	IMPORT_C void HandleItemAdditionL();
	IMPORT_C void HandleItemRemovalL();
	IMPORT_C void HandleItemAdditionL(CArrayFix<TInt> &aArrayOfNewIndexesAfterAddition);
	IMPORT_C void HandleItemRemovalL(CArrayFix<TInt> &aArrayOfOldIndexesBeforeRemoval);
	IMPORT_C void Reset();

	// functions for accessing the item height
	IMPORT_C virtual void SetItemHeightL(TInt aHeight);
	IMPORT_C TInt ItemHeight() const;

	// functions for scrollbars
	IMPORT_C CEikScrollBarFrame* CreateScrollBarFrameL(TBool aPreAlloc=EFalse);

	IMPORT_C void SetScrollBarFrame(CEikScrollBarFrame* aScrollBarFrame, TScrollBarOwnerShip aOwnerShip);
	IMPORT_C TBool IsScrollBarFrameOwnedExternally() const;

	IMPORT_C CEikScrollBarFrame* const ScrollBarFrame();
	IMPORT_C virtual void UpdateScrollBarsL();

	// construction support functions
	IMPORT_C void CalculatePopoutRect(TInt aTargetItemIndex, TInt aTargetYPos, TRect& aListBoxRect, TInt aMinHeightInNumOfItems = 1);
	IMPORT_C TSize CalcSizeInPixels(TInt aWidthAsNumOfChars, TInt aHeightAsNumOfItems) const;
	IMPORT_C TInt CalcWidthBasedOnNumOfChars(TInt aNumOfChars) const;
	IMPORT_C TInt CalcHeightBasedOnNumOfItems(TInt aNumOfItems) const;
	IMPORT_C TInt CalcWidthBasedOnRequiredItemWidth(TInt aTextWidthInPixels) const;

	// drawing/scrolling functions
	IMPORT_C void DrawItem(TInt aItemIndex) const;
	IMPORT_C void ScrollToMakeItemVisible(TInt aItemIndex) const;

	// observer support
	IMPORT_C void SetListBoxObserver(MEikListBoxObserver* aObserver);

	IMPORT_C TInt VerticalInterItemGap() const;

	// popouts only
	IMPORT_C void SetLaunchingButton(CEikButtonBase* aButton);

    // Editing support
    IMPORT_C void SetItemEditor(MEikListBoxEditor* aEditor);
    IMPORT_C void ResetItemEditor();
    IMPORT_C MEikListBoxEditor* ItemEditor();
    IMPORT_C virtual void EditItemL(TInt aMaxLength);
    IMPORT_C void StopEditingL(TBool aUpdateModel);

	// functions needed for Avkon shortcuts, 
	// passing information from one list to another
	IMPORT_C virtual TInt ShortcutValueForNextList();
	IMPORT_C virtual void SetShortcutValueFromPrevList(TInt aValue);

public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
	IMPORT_C virtual void ActivateL();
	IMPORT_C TCoeInputCapabilities InputCapabilities() const;

protected:
	// Shortcuts need access to Incremental matching
	// The shortcuts will be used inside OfferkeyEventL().
	friend class AknListBoxShortCutsImplementation;
	// Avkon layout uses SetVerticalMargin, which is protected.
	friend class AknListBoxLayouts;

	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void HandleViewRectSizeChangeL();
	IMPORT_C virtual TInt CountComponentControls() const;
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

	// functions that implement first letter and incremental matching
	IMPORT_C void CreateMatchBufferL();  // utility function called from RestoreL() of subclasses such as CEikStandardListBox
	IMPORT_C void ClearMatchBuffer() const;
	IMPORT_C void MatchTypedCharL(TUint aCode);
	IMPORT_C void UndoLastChar();
	IMPORT_C TBool LastCharMatched() const;

	// functions needed for supporting scrollbars
	IMPORT_C virtual void UpdateScrollBarThumbs() const;
	IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;
	IMPORT_C virtual TInt HorizontalNudgeValue() const;
	IMPORT_C virtual void AdjustTopItemIndex() const;

	// navigation support functions
	IMPORT_C void SimulateArrowKeyEventL(TKeyCode aKeyCode);
	IMPORT_C virtual void HandleLeftArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);
	IMPORT_C virtual void HandleRightArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);

	// construction support functions
	IMPORT_C void RestoreCommonListBoxPropertiesL(TResourceReader& aReader); // utility function called from RestoreL() of subclasses such as CEikStandardListBox
	IMPORT_C virtual void ConstructL(const CCoeControl* aParent,TInt aFlags = 0);
	IMPORT_C virtual void CreateViewL();
	IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
	IMPORT_C void SetViewRectFromClientRect(const TRect& aClientRect);
	IMPORT_C virtual void RestoreClientRectFromViewRect(TRect& aClientRect) const;
	IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;

	// accessor for Laf members
	IMPORT_C TMargins8 ListBoxMargins() const;

	// various accessors for private data members
	IMPORT_C TInt HorizontalMargin() const;
	IMPORT_C TInt VerticalMargin() const;
	IMPORT_C void SetHorizontalMargin(TInt aMargin);
	IMPORT_C void SetVerticalMargin(TInt aMargin);
	IMPORT_C RIncrMatcherBase* MatchBuffer() const;
	IMPORT_C TInt ViewRectHeightAdjustment() const;
	IMPORT_C TRgb BackColor() const;
	IMPORT_C void SetViewRectHeightAdjustment(TInt aAdjustment);

	// misc functions
	IMPORT_C virtual void ReportListBoxEventL(MEikListBoxObserver::TListBoxEvent aEvent);
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	IMPORT_C void ClearMargins() const;
	IMPORT_C virtual void UpdateCurrentItem(TInt aItemIndex) const;
	IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);
	IMPORT_C TBool ItemExists(TInt aItemIndex) const;
	IMPORT_C void DrawMatcherCursor() const;

	IMPORT_C static TInt InterItemGap();

	IMPORT_C void UpdateViewColors();
	IMPORT_C void UpdateItemDrawerColors();

protected:	// functions which deal with extension

	IMPORT_C void SetReasonForFocusLostL(TReasonForFocusLost aReasonForFocusLost);
	IMPORT_C TReasonForFocusLost ReasonForFocusLostL();
	IMPORT_C TBool IsMatchBuffer() const;
	void CheckCreateExtensionL();
	TBool CheckCreateExtension();
	void CheckCreateBufferL();
	CMatchBuffer* Buffer() const;
protected:
	IMPORT_C void CreateScrollBarFrameLayout(TEikScrollBarFrameLayout& aLayout) const;
private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private:
	IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
	void HorizontalScroll(TInt aScrollAmountInPixels);
	void DrawItemInView(TInt aItemIndex) const;
	void ClearMargins(CWindowGc& aGc) const;
	TKeyResponse DoOfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void UpdateScrollBarColors(CEikScrollBar* aScrollBar);
	void UpdateScrollBarsColors();

	void HandleItemRemovalWithoutSelectionsL();
protected:
	TInt iListBoxFlags;
	CListBoxView* iView;
	CListItemDrawer* iItemDrawer;
	MListBoxModel* iModel;
	TInt iItemHeight; 	
	CEikScrollBarFrame* iSBFrame;
	TScrollBarOwnerShip iSBFrameOwned;
	TInt iRequiredHeightInNumOfItems;
	CEikButtonBase* iLaunchingButton; // only used by popouts
	MEikListBoxObserver* iListBoxObserver;
private:
	TRgb iBackColor;
//	TInt iHorizontalMargin;
//	TInt iVerticalMargin;
	TMargins8 iMargins ;
	CListBoxExt* iListBoxExt;
	TInt iViewRectHeightAdjustment;
    MEikListBoxEditor* iItemEditor;
	TBool* iLbxDestroyed;
	TBool iLastCharMatched;
	TInt iSpare;
	};


class CEikSnakingListBox : public CEikListBox  
	{
public:
	IMPORT_C CEikSnakingListBox();
	IMPORT_C ~CEikSnakingListBox();
	IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;
   	IMPORT_C TInt ColumnWidth() const;
	IMPORT_C void SetColumnWidth(TInt aColumnWidth);
protected:
	IMPORT_C virtual void HandleViewRectSizeChangeL();
	IMPORT_C virtual void HandleLeftArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);
	IMPORT_C virtual void HandleRightArrowKeyL(CListBoxView::TSelectionMode aSelectionMode);
	IMPORT_C virtual TInt HorizontalNudgeValue() const;
	IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;
	IMPORT_C virtual void AdjustTopItemIndex() const;
	IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);
	IMPORT_C virtual void RestoreClientRectFromViewRect(TRect& aClientRect) const;
	IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;
	IMPORT_C void MoveToNextOrPreviousItemL(TPoint aPoint);
protected: //from CCoeControl
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u
	IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u
private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private:
	IMPORT_C virtual void CEikListBox_Reserved(); // listbox use only
	};

#endif
