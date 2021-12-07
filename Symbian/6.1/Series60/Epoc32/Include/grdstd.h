// GRDSTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__GRDSTD_H__)
#define __GRDSTD_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif
#if !defined(__GRDCELLS_H__)
#include <grdcells.h>
#endif
#if !defined(__GRDDEF_H__)
#include <grddef.h>
#endif


class MGridTable
	{
public:
	enum
		{
		EDefaultRowExtent=20,EDefaultColumnExtent=20
		};
public:
	IMPORT_C virtual TBool RequestRow(TInt aRow,TInt& aReturnRow) const;//If used should be derived from
	IMPORT_C virtual TInt RowExtent() const;
	IMPORT_C virtual TInt ColumnExtent() const;
	};


////////////////////////->
class TGridColors
	{
public:
	IMPORT_C TGridColors();
	IMPORT_C TGridColors(TRgb aForeground, TRgb aBackground, TRgb aLines, TRgb aLabelSeparators);
public:
	TRgb iForeground;
	TRgb iBackground;
	TRgb iLines;
	TRgb iLabelSeparators;
//	TRgb iEdge;
	};
////////////////////////->


class RReadStream;
class RWriteStream;
class CStreamStore;
class CGridImg;
class CSparseMap;

class CGridLay : public CBase
	{
	friend class CGridImg;
public:
	enum TPageOrder
		{ ERightThenDown,EDownThenRight};
	enum TFixGridRange
		{ EFixGridRange,EAdjustGridRange};
public:
	IMPORT_C CGridLay(MGraphicsDeviceMap* aGraphicsDeviceMap);
	IMPORT_C void ConstructL(CGridLay* aGridLay,CGridImg* aGridImg);//Constructs Partial Copy
	IMPORT_C void ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,TInt aNoOfRows,TInt aNoOfCols);
	IMPORT_C void ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,TInt aNoOfCols);
	IMPORT_C virtual ~CGridLay();

	IMPORT_C TPoint PageScroll(TMoveDirectionAndAmount aPageScroll);
	IMPORT_C TPoint ExposeCell(const TCellRef &aCell);
	IMPORT_C TPoint ExposeCellToTopLeft(const TCellRef &aCell);

	IMPORT_C void SetGridImgL(CGridImg* aGridImg);
	inline void SetGridTable(const MGridTable* aGridTable);
	inline TRangeRef VisibleRange() const;
	IMPORT_C void SetVisibleRange(const TCellRef& aTopLeftCell);
	inline TRangeRef TitleRange() const;
	inline TRangeRef GridRange() const;
	IMPORT_C void SetGraphicsDeviceMap(MGraphicsDeviceMap* aGraphicsDeviceMap);
	IMPORT_C void SetGridToDefault();

	IMPORT_C TInt ColumnWidthInTwips(TInt aCol) const;
	IMPORT_C void SetColumnWidthInTwipsL(TInt aCol,TInt aWidthInTwips);
	IMPORT_C TInt SetColumnWidthInTwipsL(TInt aStartCol,TInt aEndCol,TInt aWidthInTwips);
	IMPORT_C TInt DefaultColumnWidthInTwips() const;
	IMPORT_C void SetDefaultColumnWidthInTwips(TInt aWidthInTwips);
	IMPORT_C void SetColumnWidthsToDefault();
	IMPORT_C TInt MinColumnWidthInPixels() const;
	IMPORT_C void SetMinColumnWidthInPixels(TInt aWidthInPixels);
	IMPORT_C TInt ColumnWidthOfSelectedInTwips() const;
	IMPORT_C void SetColumnWidthOfSelectedInTwipsL(TInt aWidthInTwips);
	IMPORT_C TInt RowHeightInTwips(TInt aRow) const;
	IMPORT_C void SetRowHeightInTwipsL(TInt aRow,TInt aHeightInTwips);
	IMPORT_C TInt SetRowHeightInTwipsL(TInt aStartRow,TInt aEndRow,TInt aHeightInTwips);
	IMPORT_C TInt DefaultRowHeightInTwips() const;
	IMPORT_C void SetDefaultRowHeightInTwips(TInt aHeightInTwips);
	IMPORT_C void SetRowHeightsToDefault();
	IMPORT_C TInt MinRowHeightInPixels() const;
	IMPORT_C void SetMinRowHeightInPixels(TInt aHeightInPixels);
	IMPORT_C TInt RowHeightOfSelectedInTwips() const;
	IMPORT_C void SetRowHeightOfSelectedInTwipsL(TInt aHeightInTwips);
	IMPORT_C void RecalcPixelSparseMaps();
	IMPORT_C void InsertDeleteColumns(TInt aStartCol,TInt aNoOfCols,
		TFixGridRange aFixGridRange=EFixGridRange);
	IMPORT_C void InsertDeleteRows(TInt aStartRow,TInt aNoOfRows,
		TFixGridRange aFixGridRange=EFixGridRange);

	inline TBool IsSideLabels() const;
	IMPORT_C void SetSideLabels(TBool aState);
	inline TBool IsTopLabels() const;
	IMPORT_C void SetTopLabels(TBool aState);
	inline TBool IsVerticalGridLines() const;
	IMPORT_C void SetVerticalGridLines(TBool aState);
	inline TBool IsHorizontalGridLines() const;
	IMPORT_C void SetHorizontalGridLines(TBool aState);
	inline TBool IsGridLabelSeparators() const;
	IMPORT_C void SetGridLabelSeparators(TBool aState);
	inline TBool IsColumnBursting() const;
	IMPORT_C void SetColumnBursting(TBool aState);
	inline TBool IsCursorVisible() const;
	IMPORT_C void SetCursorVisible(TBool aVisible);
	inline TBool IsHighlightVisible() const;
	IMPORT_C void SetHighlightVisible(TBool aVisible);
	inline TBool IsRowPermanentlySelected() const;
	IMPORT_C void SetRowPermanentlySelectedL(TBool aState);
	inline TBool IsTitleLines() const;
	inline TBool IsHorizontalTitleLine() const;
	inline TBool IsVerticalTitleLine() const;
	IMPORT_C void SetTitleLinesL(TBool aState);
	IMPORT_C void SetTitleLinesL(const TCellRef& aCellRef);
	IMPORT_C void ToggleTitleLinesL();
	inline TBool IsIndefiniteRowBoundaries() const;
	inline TBool IsUniformRowHeight() const;
	IMPORT_C void SetUniformRowHeight(TBool aState);
	inline TBool IsUniformColumnWidth() const;
	IMPORT_C void SetUniformColumnWidth(TBool aState);
	inline TBool IsTopLabelDragDisabled() const;
	IMPORT_C void SetTopLabelDragDisabled(TBool aState);
	inline TBool IsSideLabelDragDisabled() const;
	IMPORT_C void SetSideLabelDragDisabled(TBool aState);
	inline TBool IsPrintedLabels() const;
	IMPORT_C void SetPrintedLabels(TBool aState);
	inline TBool IsPrintedGridLines() const;
	IMPORT_C void SetPrintedGridLines(TBool aState);
	inline TBool IsEncroachingCellBorders() const;
	IMPORT_C void SetEncroachingCellBorders(TBool aState);
	inline TBool IsRowSelectionDisabled() const;
	IMPORT_C void SetRowSelectionDisabled(TBool aState);
	inline TBool IsColumnSelectionDisabled() const;
	IMPORT_C void SetColumnSelectionDisabled(TBool aState);
	inline TBool IsAutoClearGridCells() const;
	IMPORT_C void SetAutoClearGridCells(TBool aState);
	inline TBool IsPageBreakLinesHidden() const;
	IMPORT_C void SetPageBreakLinesHidden(TBool aState);
	inline TBool HasChanged() const;
	inline void SetHasChanged(TBool aHasChanged);
	inline void SetGridEdgeColor(TRgb aColor);

	IMPORT_C TInt MinVisibleFromRow() const;
	IMPORT_C TInt MinVisibleFromColumn() const;
	IMPORT_C void ResetVisibleToRow();
	IMPORT_C void ResetVisibleToColumn();
	IMPORT_C void ResetVisibleToCell();
	IMPORT_C TInt RowExtent() const;
	IMPORT_C TInt ColumnExtent() const;

	IMPORT_C TInt RowToYVal(TInt aRow) const;
	IMPORT_C TInt RowToYVal(TInt aStartRow,TInt aEndRow) const;
	IMPORT_C TInt VisibleRowToYVal(TInt aRow) const;
	IMPORT_C TInt TitleRowToYVal(TInt aTitleRow) const;
	IMPORT_C TInt ColumnToXVal(TInt aCol) const;
	IMPORT_C TInt ColumnToXVal(TInt aStartCol,TInt aEndCol) const;
	IMPORT_C TInt VisibleColumnToXVal(TInt aCol) const;
	IMPORT_C TInt TitleColumnToXVal(TInt aTitleCol) const;
	IMPORT_C TInt YValToRow(TInt aYVal) const;
	IMPORT_C TInt YValToRow(TInt aStartRow,TInt aDisp) const;
	IMPORT_C TInt YValToTitleRow(TInt aYVal) const;
	IMPORT_C TInt XValToColumn(TInt aXVal) const;
	IMPORT_C TInt XValToColumn(TInt aStartCol,TInt aDisp) const;
	IMPORT_C TInt XValToTitleColumn(TInt aXVal) const;
	IMPORT_C TCellRef PointToCell(const TPoint &aPoint) const;
	IMPORT_C TCellRef PointToCell(const TCellRef &aStartCell,const TPoint &aPointDisp) const;
	IMPORT_C TPoint CellToPoint(const TCellRef &aCell) const;
	IMPORT_C TPoint CellToPoint(const TCellRef &aStartCell,const TCellRef &aEndCell) const;
	IMPORT_C TPoint TitleCellToPoint(const TCellRef& aTitleCell) const;
	IMPORT_C TRect CellToRect(const TCellRef& aCell) const;
	IMPORT_C TInt YValToNearestRow(TInt aStartRow,TInt aDisp) const;
	IMPORT_C TInt XValToNearestColumn(TInt aStartCol,TInt aDisp) const;
	IMPORT_C TSize TopLeftTitleRangeSize() const;

	IMPORT_C void PaginateL();
	IMPORT_C void ClearPagination();
	IMPORT_C void NotifyPaginationOutOfDateL();
	inline TBool IsPaginated() const;
	IMPORT_C TRangeRef PageToRange(TInt aPageNo,TPageOrder aPageOrder) const;
	inline void SetPrintRange(const TRangeRef& aPrintRange);
	IMPORT_C TInt NoOfPages() const;
	IMPORT_C void SetPageSizeInTwipsL(const TSize& aPageSize);
	inline TSize PageSizeInTwips() const;
	inline TBool IsAutoPagination() const;
	IMPORT_C void SetAutoPagination(TBool aState);
	IMPORT_C TBool IsHardRowPageBreak(TInt aRow) const;
	IMPORT_C TBool IsHardColumnPageBreak(TInt aCol) const;
	IMPORT_C void SetHardRowPageBreakL(TInt aRow);
	IMPORT_C void ClearHardRowPageBreakL(TInt aRow);
	IMPORT_C void SetHardColumnPageBreakL(TInt aCol);
	IMPORT_C void ClearHardColumnPageBreakL(TInt aCol);
	IMPORT_C void ClearAllHardPageBreaksL();

	IMPORT_C void ExternalizeL(RWriteStream &aStream) const;
	IMPORT_C void InternalizeL(RReadStream &aStream);
	IMPORT_C TStreamId StoreL(CStreamStore& aStore) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,TStreamId aStreamId);
////////////////////////->
//	Setting the grid colors
	IMPORT_C void SetGridColors(TGridColors aColors);
//	Getting the grid colors
	IMPORT_C const TGridColors& GridColors() const;
////////////////////////->
private:
	void SetIndefiniteRowBoundaries(TBool aState);
	inline TBool IsVisibleToRowFullyVisible() const;
	void SetVisibleToRowFullyVisible(TBool aState);
	inline TBool IsVisibleToColumnFullyVisible() const;
	void SetVisibleToColumnFullyVisible(TBool aState);
	TInt ColumnWidthInPixels(TInt aCol) const;
	void SetColumnWidthInPixelsL(TInt aCol,TInt aWidthInPixels);
	void PreCheckColumnWidthChange(TInt aCol,TBool aNonZeroWidth);
	void PostCheckColumnWidthChange(TInt aCol,TBool aNonZeroWidth);
	TInt DefaultColumnWidthInPixels() const;
	void SetDefaultColumnWidthInPixels(TInt aWidthInPixels);
	TInt RowHeightInPixels(TInt aRow) const;
	void SetRowHeightInPixelsL(TInt aRow,TInt aHeightInPixels);
	void PreCheckRowHeightChange(TInt aRow,TBool aNonZeroHeight);
	void PostCheckRowHeightChange(TInt aRow,TBool aNonZeroHeight);
	TInt DefaultRowHeightInPixels() const;
	void SetDefaultRowHeightInPixels(TInt aHeightInPixels);
	TPoint CalcOffsetBetweenCells(const TCellRef& aCell1,const TCellRef& aCell2) const;
	TBool LimitRow(TInt& aRow) const;
	TBool LimitColumn(TInt &aColumn) const;
	void LimitRow(TInt& aRow,TInt aLowerLimit,TInt aUpperLimit) const;
	void LimitColumn(TInt& aCol,TInt aLowerLimit,TInt aUpperLimit) const;
	TBool LimitCell(TCellRef& aCell) const;
	void LimitRowToVisible(TInt& aRow) const;
	void LimitColumnToVisible(TInt& aCol) const;
	void LimitCellToVisible(TCellRef& aCell) const;
	TBool IsCellOutOfVisibleRange(const TCellRef &aCell) const;
	TBool IsCellOutOfGridRange(const TCellRef& aCell) const;
	void StepRowForward(TInt& aRow) const;
	void StepRowBackward(TInt& aRow) const;
	void StepColumnForward(TInt& aCol) const;
	void StepColumnBackward(TInt& aCol) const;
	void CalcVisibleFromRow(TInt aVisibleToRow,TInt& aNewVisibleFromRow) const;
	TBool CalcVisibleToRow(TInt aVisibleFromRow,TInt& aNewVisibleToRow) const;
	void CalcVisibleFromColumn(TInt aVisibleToCol,TInt& aNewVisibleFromCol) const;
	TBool CalcVisibleToColumn(TInt aVisibleFromCol,TInt& aNewVisibleToCol) const;
	TInt CalcVisibleFromRowAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const;
	TInt CalcVisibleFromColumnAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const;
	TCellRef CalcVisibleFromCellAfterPageScroll(TMoveDirectionAndAmount aPageScroll) const;
	TBool FindNextRowPageBreak(TInt aSearchStart,TInt& aFoundRow) const;
	TBool FindNextColumnPageBreak(TInt aSearchStart,TInt& aFoundCol) const;
	void DoMainPaginationLoopL(TInt aPageSpan,CSparseMap* aCellSpanMap,CSparseMap* aPageMap,
		CArrayFix<TInt>* aHardPageBreaks,TInt aStartId);
	TBool RequestRow(TInt aRow,TInt& aReturnRow) const;

	void ConstructL(const MGridTable *aGridTable,CGridImg *aGridImg,const TRangeRef& aGridRange);
//private:
private:
	enum 
		{
		EMaxArrayChanges=256,
		EInitialDefaultRowHeightInTwips = 300,
		EInitialDefaultColumnWidthInTwips = 900
		};
	enum
		{
		EIsTopLabels = 0x1,
		EIsSideLabels = 0x2,
		EIsHorizontalGridLines =  0x4,
		EIsVerticalGridLines = 0x8,
		EIsColumnBursting = 0x10,
		EIsCursorVisible = 0x20,
		EIsRowPermanentlySelected = 0x40,
		EIsHorizontalTitleLine = 0x80,
		EIsVerticalTitleLine = 0x100,
		EIsIndefiniteRowBoundaries = 0x200,
		EIsUniformRowHeight = 0x400,
		EIsUniformColumnWidth = 0x800,
		EIsTopLabelDragDisabled = 0x1000,
		EIsSideLabelDragDisabled = 0x2000,
		EIsPaginated = 0x4000,
		EIsAutoPagination = 0x8000,
		EIsPrintedLabels = 0x10000,
		EIsPrintedGridLines = 0x20000,
		EIsVisibleToRowFullyVisible = 0x40000,
		EIsVisibleToColumnFullyVisible = 0x80000,
		EIsEncroachingCellBorders = 0x100000,
		EIsColumnSelectionDisabled = 0x200000,
		EIsRowSelectionDisabled = 0x400000,
		EIsAutoClearGridCells = 0x800000,
		EIsGridLabelSeparators = 0x1000000,
		EIsHighlightVisible = 0x2000000,
		EIsPageBreakLinesHidden = 0x4000000
		};
private:
	const MGridTable* iGridTable;
	const MGraphicsDeviceMap* iGraphicsDeviceMap;		//*
	CGridImg*   iGridImg;								//*
// persistent
	TRangeRef   iGridRange;								//*
	TRangeRef   iVisibleRange;
	TRangeRef   iTitleRange;
	CSparseMap* iColumnWidthMap;						//*
	CSparseMap* iRowHeightMap;							//*
	CSparseMap* iColumnPageMap;							//*
	CSparseMap* iRowPageMap;							//*
	CArrayFix<TInt>* iHardRowPageBreaks;
	CArrayFix<TInt>* iHardColumnPageBreaks;
	TRgb		iGridEdgeColor;
	TInt        iMinRowHeightInPixels;
	TInt        iMinColumnWidthInPixels;
	TSize       iPageSizeInTwips;						//*
	TUint32		iFlags;									//* Starred items are used in printing
////////////////////////->
	TGridColors iColors;
////////////////////////->
// End of persistent data
	TBool		iHasChanged;
	};



class CGridLabelImg : public CBase
	{
	friend class CGridImg;
public:
	IMPORT_C virtual ~CGridLabelImg();
	IMPORT_C void ConstructL();
	inline void SetGraphicsDeviceMap(MGraphicsDeviceMap* aGraphicsDeviceMap);
	inline TFontSpec FontSpec() const;
	IMPORT_C void ReleaseFont();
	IMPORT_C void NotifyGraphicsDeviceMapChangeL();
	inline void SetGridColors(const TGridColors& aGridColors);
protected:
	IMPORT_C CGridLabelImg(const TFontSpec& aFontSpec,MGraphicsDeviceMap* aGraphicsDeviceMap);
////////////////////////->
	IMPORT_C void DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect, TRgb aColor) const;
////////////////////////->
private:
	virtual void DrawRowLabelL(CGraphicsContext* aGc,TInt aRow,const TRect& aRect) const=0;
	virtual void DrawColLabelL(CGraphicsContext* aGc,TInt aCol,const TRect& aRect) const=0;
	IMPORT_C virtual void DrawTopLeftLabelL(CGraphicsContext* aGc,const TRect& aRect) const;
	IMPORT_C virtual TInt SideLabelWidthInPixels(TInt aStartRow,TInt aEndRow) const;
	IMPORT_C virtual TInt TopLabelHeightInPixels() const;
	IMPORT_C virtual void DrawRowCursorL(CGraphicsContext* aGc,const TRect& aRect) const;
protected:
	enum
		{
		EDefaultSideLabelWidthInTwips=300,
		EDefaultTopLabelHeightInTwips=300
		};
protected:
	CFont* iFont;
	TFontSpec iFontSpec;
	MGraphicsDeviceMap* iGraphicsDeviceMap;
	TGridColors iGridColors;
private:
	TInt iSpare;
	};

class CGridCellImg : public CBase
	{
	friend class CGridImg;
public:
	IMPORT_C virtual ~CGridCellImg();
	inline TInt BurstColOffset() const;
	inline TInt BurstLeft() const;
	inline TInt BurstRight() const;
	inline TBool IsHorizontalGridLines() const;
	inline TBool IsVerticalGridLines() const;
	inline void SetGridColors(const TGridColors& aGridColors);
protected:
	IMPORT_C CGridCellImg();
private:
	virtual void DrawL(CGraphicsContext* aGc,const TCellRef& aCell,const TRect& aDrawRect,
		const TRect& aClipRect) const=0;
	IMPORT_C virtual TInt DataWidthInPixelsL(const TCellRef& aCell) const;
	IMPORT_C virtual TBool DoesCellContainDataL(const TCellRef& aCell) const;
// reserved virtual function
	IMPORT_C virtual void Reserved_1();
private:
	void SetBurstingData(TInt aBurstColOffset=0,TInt aBurstLeft=0,TInt aBurstRight=0);
private:
	enum { EIsHorizontalGridLines = 0x1, EIsVerticalGridLines = 0x2 };
protected:
	TGridColors iGridColors;
private:
	TInt iBurstColOffset;
	TInt iBurstLeft;
	TInt iBurstRight;
	TUint32 iGridLineFlags;
	};

class MGridCursorMoveCallBack
	{
public:
	virtual void HandleCursorMoveL()=0;
	};

class RWindow;
class CWindowGc;

class CGridImg : public CBase
	{
	friend class CGridLay;
public:
	enum
		{
		EIsWithSelect=0x0001,
		EIsWithControl=0x0002,
		EIsWithDrag=0x0004,
		EIsAtBoundary=0x0008,
		EIsAbsoluteMove=0x0010,
		EIsRowSelected=0x0020,
		EIsColumnSelected=0x0040
		};
	enum { EScaleOneToOne=100};
	enum TSelectType
		{ ESelectOverwrite, ESelectAppend };
public:
	IMPORT_C virtual ~CGridImg();
	IMPORT_C static CGridImg* NewL(CGraphicsDevice* aGraphicsDevice,CGridCellImg* aGridCellImg,CGridLay* aGridLay);
	IMPORT_C static CGridImg* NewL(CGridCellImg* aGridCellImg,CGridLay* aGridLay); //Creates Partial GridImg
	inline void SetGridLay(CGridLay* aGridLay);
	inline void SetWindow(RWindow* aWin);
////////////////////////->
	IMPORT_C void SetGridLabelImg(CGridLabelImg* aGridLabelImg);
////////////////////////->
	inline void SetCursorMoveCallBack(MGridCursorMoveCallBack* aCursorMoveCallBack);
	inline const CGridCellRegion* Selected() const;
	inline const CGridLabelImg* GridLabelImg() const;

	IMPORT_C void ScrollL(const TPoint &aOffset);
	IMPORT_C void MoveCursorL(TMoveDirectionAndAmount aCursorMove,TUint aSelectState);
   	IMPORT_C void SetCursorWithPointerL(const TPoint& aPoint,TUint aFlagList);
	IMPORT_C void ResetSelectedL();
	IMPORT_C void AddRangeToSelectedL(const TRangeRef& aRange,TSelectType aType=ESelectOverwrite);
	IMPORT_C void AddRegionToSelectedL(const CArrayFix<TRangeRef>* aCellRegion,TSelectType aType=ESelectOverwrite);
	IMPORT_C void AddRowToSelectedL(TInt aRow,TSelectType aType=ESelectOverwrite);
	IMPORT_C void AddColToSelectedL(TInt aCol,TSelectType aType=ESelectOverwrite);
	IMPORT_C void DrawL(CGraphicsContext* aGc) const;
	IMPORT_C void DrawL(CGraphicsContext* aGc,const TRect& aRect) const;
	IMPORT_C void DrawCellL(const TCellRef& aCell) const;
	IMPORT_C void DrawRangeL(const TRangeRef& aRange) const;
	IMPORT_C void DrawSelectedL() const;
	IMPORT_C void DrawTitleLines() const;
	IMPORT_C void ClearTitleLineRegionL(const TPoint& aCrossPoint) const;
	IMPORT_C void PrintGridLinesAndCellsInRangeL(CGraphicsContext* aPrinterGc,const TRangeRef& aRange,
		TInt aScaleFactor) const;

	inline TCellRef CursorPos() const;
	IMPORT_C void SetCursorPosL(const TCellRef& aCursorPos);
	inline TCellRef NewCursorPos() const;
	inline TCellRef AnchorPos() const;
	IMPORT_C void SetAnchorPosL(const TCellRef& aAnchorPos);
	inline TRect GridRect() const;
	IMPORT_C void SetGridRect(const TRect& aNewRect);
	IMPORT_C void SetPrintGridRect(const TRect& aPrintRect);
	inline TPoint TitlePoint() const;
	inline TPoint MainPoint() const;
	inline TRect MainRect() const;
	IMPORT_C void ResetReferencePoints();
	IMPORT_C void NotifyGridRangeResize();

	IMPORT_C void CheckSideLabelWidthAndScrollL();
	IMPORT_C TInt CheckSideLabelWidth();
	IMPORT_C TInt SideLabelWidthInPixels() const;
	IMPORT_C TInt MaxSideLabelWidthInPixels() const;
	IMPORT_C TInt TopLabelHeightInPixels() const;
	IMPORT_C void FinishLabelDragL();
	IMPORT_C TBool StartLabelDrag(const TPoint &aPoint);
	IMPORT_C TBool UpdateLabelDrag(const TPoint &aPoint);
	IMPORT_C TBool StartLabelResize(TBool aIsColumnLabel, TInt aIndex);
	IMPORT_C TBool UpdateLabelResize(TInt aDelta);
	IMPORT_C void FinishLabelResizeL(TBool aResize);
private:
	enum TDragDim {EXDrag,EYDrag,ENoDrag};
	enum TRefPoint {ETitleRef,EMainRef};
	enum TDragDraw {EDragDrawWithBitmap,EDragDrawWithoutBitmap};
	enum TArrows {EBothArrows,ESecondArrowOnly};
	enum
		{
		EIsLabelDraggingIgnored = 0x1,
		EIsSidewaysScrollIgnored = 0x2
		};
private:
	void DrawResizingDragHiglights(const TRect& aRect);
	void DrawAllGridLabelsL() const;
	void DrawTopLeftGridLabelL() const;
	void DrawTopGridLabelsL(TInt aStartCol,TInt aEndCol,TRefPoint aXRef=EMainRef) const;
	void DrawSideGridLabelsL(TInt aStartRow,TInt aEndRow,TRefPoint aYRef=EMainRef) const;
	void DrawSideGridLabelIfOnScreenL(TInt aRow) const;
	void DrawAllGridLinesAndCellsL() const;
	void DrawGridLinesAndCellsInRangeL(const TRangeRef& aRange,const TRect& aClipRect,
		TRefPoint aXRef=EMainRef,TRefPoint aYRef=EMainRef) const;
	void DrawCellsToGcL(CGraphicsContext* aGc,const TRangeRef& aRange,const TRect& aClipRect,
		const TPoint& aStartPoint,TInt aScaleFactor=EScaleOneToOne) const;
	void DrawBurstingCellL(CGraphicsContext* aGc,const TCellRef& aCell,const TRect& aRect,const TRect& aClipRect,
		TInt aScaleFactor,TInt aBurstLeft,const TCellRef& aBurstCell) const;
	TInt CalcBurstLeftL(TCellRef& aBurstCell,TInt aScaleFactor) const;
	TInt CalcBurstRightL(const TCellRef& aCell,TInt aExcessRight,TInt aScaleFactor) const;
	void DrawVerticalTitleLine() const;
	void DrawHorizontalTitleLine() const;
	void BeginRedrawAndDrawL() const;
	void BeginRedrawAndDrawL(const TRect& aRect) const;

	void AppendTotalHighlightRegionL(TRegion& aRegion) const;
	void AppendPartialHighlightRegionL(TRegion& aRegion,const TRect& aClipRect,
		TRefPoint aXRef=EMainRef,TRefPoint aYRef=EMainRef) const;
	void RemoveRowLabelFromRegionL(TInt aRow,TRegion& aRegion) const;
	void HighlightMinRegionL(const TRegion &aOldRegion,const TRegion &aNewRegion);
	void HighlightRegion(const TRegion &aRegion) const;
	void HighlightNewRegionFromOldL(const TRegion& aOldRegion);
	void DrawCursorOrRegionL(TUint aMoveFlags);
	void UpdateSelectedRegion(TInt aSelectCount,TUint aMoveFlags);
	void AddLabelToRegionL(TUint aMoveFlags);
	void StartSelectedRegionL(TUint aMoveFlags);
	TBool ScanColumnsForDrag(TInt aFromColumn,TInt aToColumn,TInt aPointerPos,TInt& aPrevious,TInt& aCurrent);
	TBool ScanRowsForDrag(TInt aFromRow,TInt aToRow,TInt aPointerPos,TInt& aPrevious,TInt& aCurrent);
	void DrawDraggingHighlight(const TRect aLine,TDragDraw aDragDraw);
	void DrawArrowsToInMemoryBitmap(TArrows aArrows);
	TPoint RelativeCellToPoint(const TCellRef& aCell,TRefPoint aXRef=EMainRef,
		TRefPoint aYRef=EMainRef) const;
	TCellRef RelativePointToCell(const TPoint& aPoint,TRefPoint aXRef=EMainRef,
		TRefPoint aYRef=EMainRef) const;
	TRect PartialCellRectL(const TCellRef& aCell,const TRect& aClipRect,
		TRefPoint aXRef=EMainRef,TRefPoint aYRef=EMainRef) const;
	TRect PartialRangeRect(const TRangeRef& aRange,const TRect& aClipRect,
		TRefPoint aXRef=EMainRef,TRefPoint aYRef=EMainRef) const;
	void CreateGc(CGraphicsContext* aGc);
	void DeleteGc();
	static void CleanupGc(TAny* aObject);
	void ResetGcToDefault(CGraphicsContext* aGc) const;
	void ScaleDown(TPoint& aPoint,TInt aScaleFactor) const;
	void ConstructSelectedL(const TRangeRef& aGridRange);

	CGridImg(CGraphicsDevice* aGraphicsDevice,CGridCellImg* aGridCellImg,CGridLay* aGridLay);
	CGridImg(CGridCellImg* aGridCellImg,CGridLay* aGridLay);
	void ConstructL();

////////////////////////->
	void SetGridColors(const TGridColors& aGridColors);
////////////////////////->
private:
	TRect		iGridRect;
	TPoint		iTitlePoint;
	TPoint		iMainPoint;
	TCellRef	iCursorPos;							// Persisted
	TCellRef 	iNewCursorPos;
	TCellRef	iAnchorPos;

	CGraphicsDevice*	iGraphicsDevice;
	CGraphicsContext*	iGcPtr;
	CWindowGc*			iGc;
	RWindow*			iWin;
	CGridCellImg*		iGridCellImg;				//*
	CGridLabelImg*		iGridLabelImg;              //*
	CGridLay*			iGridLay;					//* Starred items are used in printing
	CGridCellRegion*		iSelected;
	MGridCursorMoveCallBack*	iCursorMoveCallBack;
	TBool		iDrawResizeLines;
	TInt 		iDragLabel;
	TInt		iCurrentDragPos;
	TInt		iDragDiff;
	TInt		iDragFlags;
	TDragDim	iDragDim;
	CFbsBitmap*	iDragBmp;
	TRefPoint 	iXRefPoint;
	TRefPoint	iYRefPoint;
	};

class TGridUtils
	{
public:
	IMPORT_C static void FillRect(CGraphicsContext* aGc,TRgb aColor,const TRect &aRect);
	};


#include <grdstd.inl>
#endif
