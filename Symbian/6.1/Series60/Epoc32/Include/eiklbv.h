// EIKLBV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__EIKLBV_H__)
#define __EIKLBV_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__GDI_H__)
#include <gdi.h>
#endif

class CListItemDrawer;
class MListBoxModel;
class CWindowGc;
class RWindowGroup;
class CWsScreenDevice;
class CWindowGc;
class RWindow;

//
// class MListVisibiltyObserver
//

class MListVisibilityObserver 
	{
public:
	virtual TBool IsVisible() const = 0;
	};

//
// class CListBoxView
//

class CListBoxView : public CBase
	{
public:
	enum TCursorMovement 
		{
		ECursorNextItem,  	
		ECursorPreviousItem,
		ECursorNextColumn,  
		ECursorPreviousColumn,  
		ECursorPreviousPage, 
		ECursorNextPage,
		ECursorFirstItem,
		ECursorLastItem,
		ECursorNextScreen,
		ECursorPrevScreen
		};  
	enum TFlags
		{
		EAnchorExists		= 0x0001,
		EEmphasized			= 0x0002,
		EDimmed				= 0x0004,
		EHasMatcherCursor	= 0x0008,
		EDisableRedraw		= 0x0010,
		EPaintedSelection     = 0x0020,
		EMarkSelection         = 0x0040,
		EUnmarkSelection       = 0x0080,
		EItemCountModified     = 0x0100
		};
	enum TSelectionMode {ENoSelection, ESingleSelection, EContiguousSelection, EDisjointSelection, EDisjointMarkSelection};
	typedef CArrayFix<TInt> CSelectionIndexArray;
public:
	IMPORT_C ~CListBoxView();
	IMPORT_C CListBoxView();

	// constructors
	IMPORT_C virtual void ConstructL(MListBoxModel* aListBoxModel, CListItemDrawer* aItemDrawer, CWsScreenDevice* aScreen, RWindowGroup* aGroupWin, RWindow* aWsWindow, const TRect& aDisplayArea, TInt aItemHeight);

	// functions for accessing the view rect (the area of the host window in which the items are drawn)
	IMPORT_C TRect ViewRect() const;
	IMPORT_C void SetViewRect(const TRect& aRect);  // the area within the list window in which the view can draw itself

	// misc. access functions for the main attributes 
	IMPORT_C virtual TInt CurrentItemIndex() const;	
	IMPORT_C void SetCurrentItemIndex(TInt aItemIndex); 
	IMPORT_C TInt TopItemIndex() const;		
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);
	IMPORT_C TInt BottomItemIndex() const;
	IMPORT_C virtual void CalcBottomItemIndex();
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);

	// functions that support incremental matching 
	IMPORT_C void SetMatcherCursorColor(TRgb aColor);
	IMPORT_C void SetMatcherCursorPos(TInt aPosWithinCurrentItem);
	IMPORT_C TInt MatcherCursorPos() const;
	IMPORT_C virtual void DrawMatcherCursor();
	IMPORT_C void HideMatcherCursor();

	// functions for getting/setting flags
	IMPORT_C void SetMatcherCursor(TBool aMatcherCursor);
	IMPORT_C void SetEmphasized(TBool aEmphasized);
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C void SetDisableRedraw(TBool aDisableRedraw);
	IMPORT_C TBool RedrawDisabled() const;
	IMPORT_C void SetPaintedSelection( TBool aPaintedSelection );

	// functions that support selection
	IMPORT_C const CSelectionIndexArray* SelectionIndexes() const;
	IMPORT_C void GetSelectionIndexesL(CSelectionIndexArray* aSelectionArray) const;
	IMPORT_C void SetSelectionIndexesL(const CSelectionIndexArray* aSelectionIndexes);
	IMPORT_C void ClearSelection();	 // resets the selection state so that there is nothing selected  		
	IMPORT_C virtual void UpdateSelectionL(TSelectionMode aSelectionMode);  // select/highlight items without moving the cursor
	IMPORT_C void ToggleItemL(TInt aItemIndex);
	IMPORT_C void SelectItemL(TInt aItemIndex);
	IMPORT_C void DeselectItem(TInt aItemIndex);
	IMPORT_C void SetAnchor(TInt aItemIndex);
	IMPORT_C void ClearSelectionAnchorAndActiveIndex();

	// functions that support scrolling
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
	IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex);
	IMPORT_C virtual void VScrollTo(TInt aNewTopItemIndex, TRect& aMinRedrawRect);
	IMPORT_C virtual void HScroll(TInt aHScrollAmount);
	IMPORT_C TInt HScrollOffset() const;
	IMPORT_C void SetHScrollOffset(TInt aHorizontalOffset);
	IMPORT_C TInt DataWidth() const;
	IMPORT_C virtual void CalcDataWidth();
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;
	IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;

	// functions that support drawing
	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual void DrawItem(TInt aItemIndex) const;

	IMPORT_C void SetListEmptyTextL(const TDesC& aText);
	inline const TDesC* EmptyListText() const;

	// functions for accessing an item's position/size, selection status, and visibility status
	IMPORT_C TBool ItemIsSelected(TInt aItemIndex) const; 
	IMPORT_C TBool ItemIsVisible(TInt aItemIndex) const;
	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;

	IMPORT_C void SetTextColor(TRgb aColor);
	IMPORT_C void SetBackColor(TRgb aColor);
	IMPORT_C TRgb TextColor() const;
	IMPORT_C TRgb BackColor() const;

	IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);
	IMPORT_C virtual void VerticalMoveToItemL(TInt aTargetItemIndex, TSelectionMode aSelectionMode);
	IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;   // returns false if no item 															//Keyword to test this
	IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;

	void SetVisibilityObserver(MListVisibilityObserver* aObserver);
	IMPORT_C TBool IsVisible() const;

	inline CListItemDrawer* ItemDrawer() const;

	IMPORT_C virtual void DrawEmptyList(const TRect &aClientRect) const;
private: // defined here.
	IMPORT_C virtual TAny* Reserved_1();
protected:
	// functions for accessing the flags
	inline TInt Flags() const;
	inline void SetFlags(TInt aMask);
	inline void ClearFlags(TInt aMask);

    friend class CEikListBox; // to access SetFlags()/ClearFlags()

	// misc. functions
	IMPORT_C void SelectRangeL(TInt aItemIndex1, TInt aItemIndex2);

protected:
	TInt iFlags;   	
	CListItemDrawer* iItemDrawer;
	MListBoxModel* iModel;
	TInt iDataWidth;			// width (in pixels) of the longest item in the model
	TInt iTopItemIndex;
	TInt iBottomItemIndex;
	TInt iHScrollOffset;		// pixel offset (from the left margin) of the visible portion of the data 
	TInt iCurrentItemIndex;
	TInt iItemHeight;
	RWindow* iWin;
	RWindowGroup* iGroupWin;
	CWindowGc* iGc;
	TRect iViewRect;

	HBufC *iListEmptyText;
private:
	TInt iMatcherCursorPos;
	TRgb iMatcherCursorColor; 
	TRgb iBackColor;
	TRgb iTextColor;
	TInt iAnchorIndex;  
	TInt iActiveEndIndex;
	CSelectionIndexArray* iSelectionIndexes;
	MListVisibilityObserver* iVisibilityObserver;
	TInt iSpare;
	};

/**
 * Return text currently in the empty list text
 */
inline const TDesC* CListBoxView::EmptyListText() const
	{ return(iListEmptyText); }


class CSnakingListBoxView : public CListBoxView
	{
public:
	IMPORT_C ~CSnakingListBoxView();
	IMPORT_C CSnakingListBoxView();
	inline TInt ColumnWidth() const;
	IMPORT_C void SetColumnWidth(TInt aColumnWidth);
	IMPORT_C virtual void MoveCursorL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);
	IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;
	IMPORT_C virtual TInt NumberOfItemsThatFitInRect(const TRect& aRect) const;
	IMPORT_C virtual void HScroll(TInt aHScrollAmount);
	IMPORT_C virtual void CalcDataWidth();
	IMPORT_C virtual void CalcBottomItemIndex();
	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
	IMPORT_C virtual TInt CalculateHScrollOffsetSoItemIsVisible(TInt aItemIndex);
	IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;
	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;
	IMPORT_C void CalcRowAndColIndexesFromItemIndex(TInt aItemIndex, TInt& aRowIndex, TInt& aColIndex) const;
	IMPORT_C void CalcItemIndexFromRowAndColIndexes(TInt& aItemIndex, TInt aRowIndex, TInt aColIndex) const;
	IMPORT_C virtual TInt NumberOfItemsPerColumn() const;
protected:
	IMPORT_C virtual void DrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex) const;
	IMPORT_C void DrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const;
	IMPORT_C void MoveToPreviousColumnL(TSelectionMode aSelectionMode);
	IMPORT_C void MoveToNextColumnL(TSelectionMode aSelectionMode);
	IMPORT_C void ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const;
	IMPORT_C void UpdateHScrollOffsetBasedOnTopItemIndex();
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
protected:
	TInt iColumnWidth;
	};



inline TInt CListBoxView::Flags() const
	{ return iFlags; }

inline void CListBoxView::SetFlags(TInt aMask)
	{ iFlags|=aMask; }
 
inline void CListBoxView::ClearFlags(TInt aMask)
	{ iFlags&=(~aMask); }

inline CListItemDrawer* CListBoxView::ItemDrawer() const
	{ return iItemDrawer; }

inline TInt CSnakingListBoxView::ColumnWidth() const
	{ return iColumnWidth; }


#endif
