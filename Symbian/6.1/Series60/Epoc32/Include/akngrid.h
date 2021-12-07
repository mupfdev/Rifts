/*
* ============================================================================
*  Name     : AknGrid.h
*  Part of  : Avkon
*
*  Description:
*     This is a concrete class for the handling of a grid. The class handles a
*     rectangular grid arrangement of items held in any linear ordering i.e 
*     cells ordered top to bottom and left, left to right and down etc.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

// AKNGRID.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// Grid

#if !defined(__AKNGRID_H__)
#define __AKNGRID_H__


#include <eiktxlbx.h>
#include <eiklbv.h>

#include <eikfrlbd.h>
#include <eikfrlb.h>

#include <AknGridM.h>
#include <AknGridView.h>

#include "Aknappui.h"

class CAknGrid : public CEikListBox
	{
private:// enums
	enum TIndicatorEvent
		{
		EMove,
		EChangeNumOfItems,
		EResize
		};
public:
	// construction
	IMPORT_C CAknGrid();
	IMPORT_C virtual ~CAknGrid();
	IMPORT_C void SetModel(CAknGridM* aModel);
	IMPORT_C void ConstructL(const CCoeControl* aParent, TInt aFlags = 0);

 	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

	// grid initialisation
	IMPORT_C void SetLayoutL(TBool aVerticalOrientation,
							 TBool aLeftToRight,
							 TBool aTopToBottom,
							 TInt aNumOfItemsInPrimaryOrient,
							 TInt aNumOfItemsInSecondaryOrient,
							 TSize aSizeOfItems,
							 TInt aWidthOfSpaceBetweenItems=0,
							 TInt aHeightOfSpaceBetweenItems=0);
	IMPORT_C void SetLayoutFromResourceL(TResourceReader& aReader);

	// scrolling
	IMPORT_C void SetPrimaryScrollingType(CAknGridView::TScrollingType aScrollingType);
	IMPORT_C void SetSecondaryScrollingType(CAknGridView::TScrollingType aSecondaryScrolling);

	// start index
	IMPORT_C void SetStartPositionL(TPoint aGridStartPosition);

	// the current data item
	IMPORT_C TInt CurrentDataIndex() const;
	IMPORT_C void SetCurrentDataIndex(TInt aDataIndex);

	// data index <-> grid position functions
	IMPORT_C TInt IndexOfPosition(TPoint aGridPosition) const;
	IMPORT_C TPoint PositionAtIndex(TInt aItemIndex) const;

	// drawer
    IMPORT_C CFormattedCellListBoxItemDrawer* ItemDrawer() const;

	// empty grid text
    IMPORT_C void SetEmptyGridTextL(const TDesC& aText);
	inline const TDesC* EmptyGridText() const;

public: // 
    IMPORT_C virtual CListBoxView* MakeViewClassInstanceL();

	IMPORT_C void SetColumnWidth(TInt aColumnWidth);
   	IMPORT_C TInt ColumnWidth() const;

public: //from CEikListBox
	IMPORT_C virtual void UpdateScrollBarsL();
	IMPORT_C void HandleItemAdditionL();
	IMPORT_C void HandleItemRemovalL();
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void SetItemHeightL(TInt aHeight);
	IMPORT_C void SizeChanged();
	IMPORT_C CTextListBoxModel* Model() const;
	IMPORT_C void SetRect(const TRect& aRect);
	IMPORT_C virtual void HandleViewRectSizeChangeL();
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex) const;

protected: // from CEikListBox
	IMPORT_C virtual TInt HorizontalNudgeValue() const;
	IMPORT_C virtual TInt HorizScrollGranularityInPixels() const;
	IMPORT_C virtual void AdjustTopItemIndex() const;
	IMPORT_C virtual void HandleDragEventL(TPoint aPointerPos);
	IMPORT_C virtual void RestoreClientRectFromViewRect(TRect& aClientRect) const;
	IMPORT_C virtual TInt AdjustRectHeightToWholeNumberOfItems(TRect& aRect) const;
	IMPORT_C virtual void UpdateScrollBarThumbs() const;
	IMPORT_C virtual TInt CountComponentControls() const;

protected:
	IMPORT_C void MoveToNextOrPreviousItemL(TPoint aPoint);
	IMPORT_C virtual void CalcGridSizeL();
    IMPORT_C virtual void CreateItemDrawerL();

private:
	__DECLARE_TEST;

	// grid model helper
	inline CAknGridM* GridModel() const;

	// grid view helper
	inline CAknGridView* GridView() const;
private: // from MListBoxModel
	IMPORT_C virtual TAny* MListBoxModel_Reserved();
private: // listbox use only
	IMPORT_C virtual void CEikListBox_Reserved(); 
private:
	TInt  iMinColWidth;
	TBool iCurrentIsValid;
	TInt  iNumOfColsInView;
	TInt  iNumOfRowsInView;
	TSize iSpaceBetweenItems;
	TSize iSizeOfItems;
	TInt iNumOfItemsInPrimaryOrient;
	TBool iIsGridVertical;
	TInt iSpare;
	};

/**
 * Return Model
 */
inline CAknGridM* CAknGrid::GridModel() const
	{
	return STATIC_CAST(CAknGridM*,iModel);
	}

/**
 * Return View 
 */
inline CAknGridView* CAknGrid::GridView() const
	{
	return STATIC_CAST(CAknGridView*,iView);
	}

/**
 * Return text currently in the empty grid text
 */
inline const TDesC* CAknGrid::EmptyGridText() const
	{
	return STATIC_CAST(CAknGridView*,iView)->EmptyListText();
	}

#endif

