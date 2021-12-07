// GRDCELLS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GRDCELLS_H__)
#define __GRDCELLS_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__BACELL_H__)
#include <bacell.h>
#endif


class CGridCellRegion : public CBase
	{
public:
	IMPORT_C static CGridCellRegion* NewL(const TRangeRef& aBounds);
	IMPORT_C virtual ~CGridCellRegion();
	IMPORT_C void AddColL(TInt aCol);
	IMPORT_C void AddRowL(TInt aRow);
	IMPORT_C void AddCellRangeL(const TRangeRef& aCellRange);
	IMPORT_C void SetLastCellRange(const TRangeRef& aCellRange);
	IMPORT_C void ResizeBounds(const TCellRef& aNewToBounds);
	IMPORT_C void Reset();
	IMPORT_C TInt Count() const;
	IMPORT_C TBool IsCellSelected(const TCellRef &aCell) const;
	IMPORT_C TBool IsCellSelected(const TCellRef &aCell,TInt aIndex) const;
	IMPORT_C TBool IsCellSelectedLastIndex(const TCellRef &aCell) const;
	IMPORT_C TBool IsRowSelected(TInt aRow) const;
	IMPORT_C TBool IsRowSelected(TInt aRow,TInt aIndex) const;
	IMPORT_C TBool IsRowSelectedLastIndex(TInt aRow) const;
	IMPORT_C TBool IsAnyRowSelected() const;
	IMPORT_C TBool IsColSelected(TInt aCol) const;
	IMPORT_C TBool IsColSelected(TInt aCol,TInt aIndex) const;
	IMPORT_C TBool IsColSelectedLastIndex(TInt aCol) const;
	IMPORT_C TBool IsAnyColSelected() const;
	IMPORT_C TBool IsRangeSelected(const TRangeRef &aRange) const;
	IMPORT_C TBool IsRangeSelected(const TRangeRef &aRange,TInt aIndex) const;
	IMPORT_C TBool IsRangeSelectedLastIndex(const TRangeRef &aRange) const;
	IMPORT_C TRangeRef operator[](TInt aIndex) const;
	IMPORT_C const CArrayFix<TRangeRef>* RangeList() const;
private:
	CGridCellRegion(const TRangeRef& aBounds);
	void ConstructL();
private:
	TRangeRef iBounds;
	CArrayFix<TRangeRef>* iRangeList;
	};
#endif
