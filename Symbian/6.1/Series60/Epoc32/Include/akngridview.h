/*
* ============================================================================
*  Name     : AknGridView.h
*  Part of  : Avkon
*
*  Description:
*     CAknGridView handles the drawing, the mapping
*     of the grid data index to the underlying listbox index (and
*     visa versa) as well as the movement around the grid.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AKNGRIDVIEW.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// grid view

#if !defined(__AKNGRIDVIEW_H__)
#define __AKNGRIDVIEW_H__

#include <eiklbv.h>
#include <AknGridM.h>
#include <eiklabel.h>

/**
 * Differentiation is needed between a data index and the list box
 * index since the inherited list box code handles the top,bottom and
 * current indexes as though everything is order topdown and left to
 * right. This is no good for grid that maybe order in 8 different
 * ways so need conversion between list box index and actual data
 * index.
 * <p><ul>
 * <li>List box index = the index for the data item according to the
 *                  snaking list box format of numbering data items.</li>
 * <li>Data index     = the actual index in the grid according to the
 *                  ordering applied to the data by the user.</li>
 *</ul>
 * <p>Note: the logical position is the intermediate form used to map
 * from a list box index to a data index or vi sa versa. It is
 * essentialy the position of the item in relation to the top left
 * corner of the grid. I.e. the top left position has logical
 * position 0,0.
 */
class CAknGridView : public CListBoxView 
	{
public:
	enum TGridFlags
		{
		EPrimaryIsVertical	= 0x0001,
		ETopToBottom		= 0x0002,
		ELeftToRight		= 0x0004
		};

	enum TScrollingType
		{
		EScrollFollowsItemsAndStops,
		EScrollFollowsItemsAndLoops,
		EScrollFollowsGrid,
		EScrollStops,
		EScrollIncrementLineAndStops,
		EScrollIncrementLineAndLoops
		};

	struct SGrid
		{
		TSize iGridDimensions;// current size of entire grid
		TInt iGridFlags;// flags
		TInt iPageSize;// iColsInView * iRowsInView
		TInt iColsInView;// number of columns in the viewable area
		TInt iRowsInView;// number of rows in the viewable area
		TSize iSizeBetweenItems;// the size of gap between items (height and width)
		TSize iSizeOfItems;// the size of an item
		};

protected:
	enum TPageIndex 
		{
		EPreviousPage,
		ENextPage,
		EHome,
		EEnd
		};

	enum TPositionCurrentIndex
		{
		EPage,
		EColumn,
		EOppositeCorner
		};

public:
	IMPORT_C CAknGridView();
	IMPORT_C virtual ~CAknGridView();

	// actual <-> listbox index conversion routines
	IMPORT_C TInt ActualDataIndex(TInt aListBoxIndex) const;
	IMPORT_C TInt ListBoxIndex(TInt aDataIndex) const;

	// the current data item
	IMPORT_C TInt CurrentDataIndex() const;
	IMPORT_C void SetCurrentDataIndex(TInt aDataIndex);

	// scrolling
	IMPORT_C void SetPrimaryScrollingType(TScrollingType aScrollingType);
	IMPORT_C void SetSecondaryScrollingType(TScrollingType aSecondaryScrolling);

	// grid size details
	IMPORT_C void SetGridCellDimensions(TSize aGridDimensions);
	IMPORT_C TSize GridCellDimensions() const;
	IMPORT_C void SetSpacesBetweenItems(TSize aSizeOfSpaceBetweenItems);
	IMPORT_C TBool IsPrimaryVertical() const;

	// logical position routines - the intermediate step for
	// converting between list box index <-> data index
	IMPORT_C void DataIndexFromLogicalPos(
		TInt& aItemIndex,
		TInt aRowIndex,
		TInt aColIndex) const;
	IMPORT_C void LogicalPosFromDataIndex(
		TInt aItemIndex,
		TInt& aRowIndex,
		TInt& aColIndex) const;
	IMPORT_C void ListBoxIndexFromLogicalPos(
		TInt& aItemIndex,
		TInt aRowIndex,
		TInt aColIndex) const;
	IMPORT_C void LogicalPosFromListBoxIndex(
		TInt aItemIndex,
		TInt& aRowIndex,
		TInt& aColIndex) const;

	// empty grid text
	IMPORT_C virtual void DrawEmptyList() const;

	IMPORT_C void SetGridDetails(SGrid aGridDetails);

	IMPORT_C void MoveToItemIndexL(TInt aItemIndex, TSelectionMode aSelectionMode);

	IMPORT_C TInt NumberOfColsInView() const;
	IMPORT_C TInt NumberOfRowsInView() const;

public: // from CListBoxView 
	IMPORT_C virtual void DrawMatcherCursor();
	IMPORT_C TInt CurrentItemIndex() const;

protected:
	IMPORT_C TBool ItemExists(TInt aListBoxIndex) const;

public: // code moved from CSnakingListBoxView

	IMPORT_C void SetColumnWidth(TInt aColumnWidth);
	IMPORT_C virtual void MoveCursorL(
		TCursorMovement aCursorMovement,
		TSelectionMode aSelectionMode);

	IMPORT_C virtual void Draw(const TRect* aClipRect = NULL) const;
	IMPORT_C virtual void DrawItem(TInt aItemIndex) const;

	IMPORT_C virtual TPoint ItemPos(TInt aItemIndex) const;
	IMPORT_C virtual void CalcBottomItemIndex();
	IMPORT_C virtual TInt CalcNewTopItemIndexSoItemIsVisible(TInt aItemIndex) const;
	IMPORT_C virtual void DrawItemRange(TInt aStartItemIndex, TInt aEndItemIndex) const;

	inline TInt ColumnWidth() const;
	IMPORT_C virtual void SetTopItemIndex(TInt aItemIndex);
	IMPORT_C virtual void SetItemHeight(TInt aItemHeight);
	IMPORT_C virtual TBool XYPosToItemIndex(TPoint aPosition, TInt& aItemIndex) const;
	IMPORT_C virtual void CalcDataWidth();
	IMPORT_C virtual TInt VisibleWidth(const TRect& aRect) const;
	IMPORT_C virtual TBool ScrollToMakeItemVisible(TInt aItemIndex);
	IMPORT_C virtual TInt CalculateHScrollOffsetSoItemIsVisible(TInt aItemIndex);
	IMPORT_C virtual TSize ItemSize(TInt aItemIndex=0) const;
	IMPORT_C void CalcRowAndColIndexesFromItemIndex(TInt aItemIndex, TInt& aRowIndex, TInt& aColIndex) const;
	IMPORT_C void CalcItemIndexFromRowAndColIndexes(TInt& aItemIndex, TInt aRowIndex, TInt aColIndex) const;

protected: // code moved from CSnakingListBoxView
	IMPORT_C void DrawColumnRange(TInt aStartColIndex, TInt aEndColIndex) const;
	IMPORT_C void ClearUnusedItemSpace(TInt aStartItemIndex, TInt aEndItemIndex) const;
	IMPORT_C void UpdateHScrollOffsetBasedOnTopItemIndex();
protected:
	// grid model helper
	inline CAknGridM* GridModel() const;

	// movement handling routines
	IMPORT_C void DoMoveL(TCursorMovement aCursorMovement, TSelectionMode aSelectionMode);

private:
	// movement handling routines

	IMPORT_C TInt SearchByLines(TInt aX, TInt aY, TCursorMovement aCursorMovement, TBool aBeginSearchOnIndex = EFalse);
	IMPORT_C TInt FindNextItem(TInt aItemIndex, TBool aLookDown, TBool aLookRight, TBool aFirstLookHorizontal, TBool aBeginSearchOnIndex = EFalse);
	TBool IsEdgePassed(TInt aItemIndex, TBool aLookDown, TBool aLookRight, TBool aFirstLookHorizontal, TBool aBeginSearchOnIndex, TInt& aNewIndex);

	TBool IsMoveRight(TCursorMovement aCursorMovement);
	TBool IsMoveDown(TCursorMovement aCursorMovement);
private: // overridden from CListBoxView
	IMPORT_C virtual TAny* Reserved_1();
private:
	TScrollingType iScrollingType;
	TScrollingType iScrollInSecondaryDimension;

	SGrid iGridDetails;
	TInt iSpare;
	};

inline CAknGridM* CAknGridView::GridModel() const
	{
	return STATIC_CAST(CAknGridM*,iModel);
	}

inline TInt CAknGridView::ColumnWidth() const
	{ return iGridDetails.iSizeOfItems.iWidth; }

#endif
