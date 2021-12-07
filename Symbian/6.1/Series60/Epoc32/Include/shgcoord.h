// SHGCOORD.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.

#if !defined(__SHGCOORD_H__)
#define __SHGCOORD_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__BACELL_H__)
#include <bacell.h>
#endif

#if !defined(__SHGAPI_H__)
#include <shgapi.h>
#endif

#if !defined(__SHGPANIC_H__)
#include "shgpanic.h"
#endif

class CShgFormulaViewer;

class TShgCellRef
// Cell reference class - relative or absolute (row,col) coord of cell.
	{
public:
	enum {EAbsoluteIndicator='$'};
private:
	enum {EExternalizedSize=6};
	friend class CShgFormulaViewer;
public:
	inline TShgCellRef();
	inline TShgCellRef(TInt aRow,TInt aCol,TInt aWorkSheetNo);
	inline TShgCellRef(const TShgCellRef& aCell);
	TBool operator==(const TShgCellRef& aCell) const;

	inline void SetRow(TInt aRow);
	inline TInt Row() const;
	inline void SetCol(TInt aCol);
	inline TInt Col() const;
	inline void SetRowCol(TInt aRow,TInt aCol);
	inline void SetWorkSheetNo(TInt aWorkSheetNo);
	inline TInt WorkSheetNo() const;

	inline TCellRef AsCellRef() const;
	TCellRef AsCellRef(const TCellRef& aCell) const;
	void MakeAbsolute(const TCellRef& aCell);
	TInt MakeAbsoluteReturningError(const TCellRef& aCell);
	inline TBool IsAbs() const;
	inline TBool IsRowAbs() const;
	inline TBool IsColAbs() const;
	inline void SetRowRel();
	inline void SetRowAbs();
	inline void SetColRel();
	inline void SetColAbs();
	inline void SetWorkSheetExplicit();
	inline void SetWorkSheetNotExplicit();
	inline TBool IsWorkSheetExplicit() const;

	void AppendTextValue(TDes& aCellRefBuf,const TCellRef& aCell) const;
	IMPORT_C void Externalize(CBufBase* aBuf) const; // previously was exported for test code
	IMPORT_C void Externalize(TDes8& aDes) const;
	IMPORT_C TInt Internalize(const TUint8* aPtr);
	static void StoreL(CBufBase* aBuf,const TDesC8& aDes);
	static void StoreL(CBufBase* aBuf,const TDesC16& aDes);
	static const TPtrC8 LexDes8(const TUint8*& aPtr);
	static const TPtrC LexDes(const TUint8*& aPtr);
	static const TUint8* LexPastDes(const TUint8* aPtr);
private:
	enum {EAbsFlag=0x4000,ESignBit=0x8000};
	enum {EWorkSheetExplicit=0x80000000};
	enum {EWorkSheetExplicitExternalize=0x80};
private:
	TInt iRow;
	TInt iCol;
private:
	TUint iWorkSheetNo;
	};

class TShgRangeRef
	{
public:
	enum {ERangeSeparator=':'};
	enum {EWorkSheetSeparator='!'};
	enum {EWorkSheetNameStartAndEndIndicator='\''};
private:
	enum {EExternalizedSize=12};
	friend class CShgFormulaViewer;
public:
	inline TShgRangeRef();
	inline TShgRangeRef(const TShgCellRef& aFrom,const TShgCellRef& aTo);
	inline TShgRangeRef(const TShgRangeRef& aRangeRef);
	TBool IsAbs() const;
	void MakeAbsolute(const TCellRef& aCell);
	TInt MakeAbsoluteReturningError(const TCellRef& aCell);
	TBool Contains(const TCellRef& aCell) const;
	TRangeRef AsRangeRef() const;
	TRangeRef AsRangeRef(const TCellRef& aCell) const;
	void AppendTextValue(TDes& aRangeRefBuf,const TCellRef& aCell) const;
	TInt NoRows() const;
	TInt NoCols() const;
	void Externalize(CBufBase* aBuf) const;
	void Externalize(TDes8& aLex) const;
	TInt Internalize(const TUint8* aPtr);
public:
	TShgCellRef iFrom;
	TShgCellRef iTo;
	};

inline TShgCellRef::TShgCellRef()
	{}
inline TShgCellRef::TShgCellRef(TInt aRow,TInt aCol,TInt aWorkSheetNo)
	: iRow(aRow),iCol(aCol),iWorkSheetNo(aWorkSheetNo) {if (iRow<0) iRow = ((-iRow)|ESignBit); if (iCol<0) iCol = ((-iCol)|ESignBit);}
inline TShgCellRef::TShgCellRef(const TShgCellRef& aCell)
	: iRow(aCell.iRow),iCol(aCell.iCol),iWorkSheetNo(aCell.iWorkSheetNo) {}
inline void TShgCellRef::SetRow(TInt aRow)
	{if (aRow<0) aRow = ((-aRow)|ESignBit); __ASSERT_DEBUG((aRow&~ESignBit)>=0 && (aRow&~ESignBit)<ESheetMaxRows && !(aRow&EAbsFlag),Panic(EShgPanicBug)); iRow = (iRow&EAbsFlag)|aRow;}
inline TInt TShgCellRef::Row() const
	{TInt row = iRow&~EAbsFlag; __ASSERT_DEBUG((row&~ESignBit)>=0 && (row&~ESignBit)<ESheetMaxRows,Panic(EShgPanicBug)); if (row&ESignBit) row = -(row&~ESignBit); return row;}
inline void TShgCellRef::SetCol(TInt aCol)
	{if (aCol<0) aCol = ((-aCol)|ESignBit); __ASSERT_DEBUG((aCol&~ESignBit)>=0 && (aCol&~ESignBit)<ESheetMaxColumns && !(aCol&EAbsFlag),Panic(EShgPanicBug)); iCol = (iCol&EAbsFlag)|aCol;}
inline TInt TShgCellRef::Col() const
	{TInt col = iCol&~EAbsFlag; __ASSERT_DEBUG((col&~ESignBit)>=0 && (col&~ESignBit)<ESheetMaxColumns,Panic(EShgPanicBug)); if (col&ESignBit) col = -(col&~ESignBit); return col;}
inline void TShgCellRef::SetRowCol(TInt aRow,TInt aCol)
	{SetRow(aRow); SetCol(aCol);}
inline void TShgCellRef::SetRowRel()
	{iRow &= ~EAbsFlag;}
inline void TShgCellRef::SetColRel()
	{iCol &= ~EAbsFlag;}
inline void TShgCellRef::SetRowAbs()
	{iRow |= EAbsFlag;}
inline void TShgCellRef::SetColAbs()
	{iCol |= EAbsFlag;}
inline TBool TShgCellRef::IsAbs() const
	{return IsRowAbs() && IsColAbs();}
inline TBool TShgCellRef::IsRowAbs() const
	{return iRow&EAbsFlag;}
inline TBool TShgCellRef::IsColAbs() const
	{return iCol&EAbsFlag;}
inline TCellRef TShgCellRef::AsCellRef() const
	{return TCellRef(Row(),Col());}
inline void TShgCellRef::SetWorkSheetNo(TInt aWorkSheetNo)
	{iWorkSheetNo = (iWorkSheetNo&EWorkSheetExplicit)|aWorkSheetNo;}
inline TInt TShgCellRef::WorkSheetNo() const
	{return iWorkSheetNo&~EWorkSheetExplicit;}
inline void TShgCellRef::SetWorkSheetExplicit()
	{iWorkSheetNo |= EWorkSheetExplicit;}
inline void TShgCellRef::SetWorkSheetNotExplicit()
	{iWorkSheetNo &= ~EWorkSheetExplicit;}
inline TBool TShgCellRef::IsWorkSheetExplicit() const
	{return iWorkSheetNo&EWorkSheetExplicit;}
inline TShgRangeRef::TShgRangeRef()
	{}
inline TShgRangeRef::TShgRangeRef(const TShgCellRef& aFrom,const TShgCellRef& aTo)
	: iFrom(aFrom),iTo(aTo) {}
inline TShgRangeRef::TShgRangeRef(const TShgRangeRef& aRangeRef)
	: iFrom(aRangeRef.iFrom),iTo(aRangeRef.iTo) {}
#endif
