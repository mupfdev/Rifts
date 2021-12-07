// GRDSTD.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// CGridLay

inline void CGridLay::SetGridTable(const MGridTable* aGridTable)
	{ iGridTable = aGridTable; }

inline TRangeRef CGridLay::VisibleRange() const
	{ return iVisibleRange; }

inline TRangeRef CGridLay::TitleRange() const
	{ return iTitleRange; }

inline TRangeRef CGridLay::GridRange() const
	{ return iGridRange; }

inline TBool CGridLay::IsSideLabels() const
	{ return (iFlags&EIsSideLabels); }

inline TBool CGridLay::IsTopLabels() const
	{ return (iFlags&EIsTopLabels); }

inline TBool CGridLay::IsVerticalGridLines() const
	{ return (iFlags&EIsVerticalGridLines); }

inline TBool CGridLay::IsHorizontalGridLines() const
	{ return (iFlags&EIsHorizontalGridLines); }

inline TBool CGridLay::IsGridLabelSeparators() const
	{ return (iFlags&EIsGridLabelSeparators); }

inline TBool CGridLay::IsColumnBursting() const
	{ return (iFlags&EIsColumnBursting); }

inline TBool CGridLay::IsCursorVisible() const
	{ return (iFlags&EIsCursorVisible); }

inline TBool CGridLay::IsHighlightVisible() const
	{ return (iFlags&EIsHighlightVisible); }

inline TBool CGridLay::IsRowPermanentlySelected() const
	{ return (iFlags&EIsRowPermanentlySelected); }

inline TBool CGridLay::IsTitleLines() const
	{ return (iFlags&(EIsHorizontalTitleLine|EIsVerticalTitleLine)); }

inline TBool CGridLay::IsHorizontalTitleLine() const
	{ return (iFlags&EIsHorizontalTitleLine); }

inline TBool CGridLay::IsVerticalTitleLine() const
	{ return (iFlags&EIsVerticalTitleLine); }

inline TBool CGridLay::IsIndefiniteRowBoundaries() const
	{ return (iFlags&EIsIndefiniteRowBoundaries); }

inline TBool CGridLay::IsUniformRowHeight() const
	{ return (iFlags&EIsUniformRowHeight); }

inline TBool CGridLay::IsUniformColumnWidth() const
	{ return (iFlags&EIsUniformColumnWidth); }

inline TBool CGridLay::IsTopLabelDragDisabled() const
	{ return (iFlags&EIsTopLabelDragDisabled); }

inline TBool CGridLay::IsSideLabelDragDisabled() const
	{ return (iFlags&EIsSideLabelDragDisabled); }

inline TBool CGridLay::IsPrintedLabels() const
	{ return (iFlags&EIsPrintedLabels); }

inline TBool CGridLay::IsPrintedGridLines() const
	{ return (iFlags&EIsPrintedGridLines); }

inline TBool CGridLay::IsVisibleToRowFullyVisible() const
	{ return (iFlags&EIsVisibleToRowFullyVisible); }

inline TBool CGridLay::IsVisibleToColumnFullyVisible() const
	{ return (iFlags&EIsVisibleToColumnFullyVisible); }

inline TBool CGridLay::IsEncroachingCellBorders() const
	{ return (iFlags&EIsEncroachingCellBorders); }

inline TBool CGridLay::IsRowSelectionDisabled() const
	{ return (iFlags&EIsRowSelectionDisabled); }

inline TBool CGridLay::IsColumnSelectionDisabled() const
	{ return (iFlags&EIsColumnSelectionDisabled); }

inline TBool CGridLay::IsAutoClearGridCells() const
	{ return (iFlags&EIsAutoClearGridCells); }

inline TBool CGridLay::IsPageBreakLinesHidden() const
	{ return (iFlags&EIsPageBreakLinesHidden); }

inline TBool CGridLay::HasChanged() const
	{ return iHasChanged; }

inline void CGridLay::SetHasChanged(TBool aHasChanged)
	{ iHasChanged=aHasChanged; }

inline void CGridLay::SetGridEdgeColor(TRgb aColor)
	{ iGridEdgeColor=aColor; }

inline TBool CGridLay::IsPaginated() const
	{ return (iFlags&EIsPaginated); }

inline void CGridLay::SetPrintRange(const TRangeRef& aPrintRange) 
	{ iVisibleRange=aPrintRange; }

inline TSize CGridLay::PageSizeInTwips() const
	{ return iPageSizeInTwips; }

inline TBool CGridLay::IsAutoPagination() const
	{ return (iFlags&EIsAutoPagination); }

// CGridLabelImg

inline void CGridLabelImg::SetGraphicsDeviceMap(MGraphicsDeviceMap* aGraphicsDeviceMap)
	{
	iGraphicsDeviceMap=aGraphicsDeviceMap;
	}

inline TFontSpec CGridLabelImg::FontSpec() const
	{
	return iFontSpec;
	}

inline void CGridLabelImg::SetGridColors(const TGridColors& aGridColors)
	{
	iGridColors = aGridColors;
	}

// CGridCellImg

inline TInt CGridCellImg::BurstColOffset() const
	{ return iBurstColOffset; }

inline TInt CGridCellImg::BurstLeft() const
	{ return iBurstLeft; }

inline TInt CGridCellImg::BurstRight() const
	{ return iBurstRight; }

inline TBool CGridCellImg::IsHorizontalGridLines() const
	{ return iGridLineFlags&EIsHorizontalGridLines; }

inline TBool CGridCellImg::IsVerticalGridLines() const
	{ return iGridLineFlags&EIsVerticalGridLines; }

inline void CGridCellImg::SetGridColors(const TGridColors& aGridColors)
	{
	iGridColors = aGridColors;
	}

// CGridImg

inline void CGridImg::SetGridLay(CGridLay* aGridLay)
	{ iGridLay = aGridLay; }

inline void CGridImg::SetWindow(RWindow *aWin)
	{ iWin = aWin; }

////////////////////////->
//inline void CGridImg::SetGridLabelImg(CGridLabelImg *aGridLabelImg)
//	{ iGridLabelImg =  aGridLabelImg; }
////////////////////////->

inline void CGridImg::SetCursorMoveCallBack(MGridCursorMoveCallBack *aCursorMoveCallBack)
	{ iCursorMoveCallBack = aCursorMoveCallBack; }

inline const CGridCellRegion* CGridImg::Selected() const
	{ return iSelected; }

inline const CGridLabelImg* CGridImg::GridLabelImg() const
	{ return iGridLabelImg; }

inline TCellRef CGridImg::CursorPos() const
	{ return iCursorPos; }

inline TCellRef CGridImg::AnchorPos() const
	{ return iAnchorPos; }

inline TCellRef CGridImg::NewCursorPos() const
	{ return iNewCursorPos; }

inline TRect CGridImg::GridRect() const
	{ return iGridRect; }

inline TPoint CGridImg::TitlePoint() const
// Returns the point of the top left cell in the grid;
	{ return iTitlePoint; }

inline TPoint CGridImg::MainPoint() const
// Returns the most commonly used point in the grid (usually same as TitlePoint()).
	{ return iMainPoint; }

inline TRect CGridImg::MainRect() const
	{ return TRect(iMainPoint,iGridRect.iBr); }


