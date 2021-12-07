// BACELL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by DanH, Sept 1995
#if !defined(__BACELL_H__)
#define __BACELL_H__

#if !defined(__E32DEF_H_)
#include <e32def.h>
#endif

#if !defined(__S32STRM_H__)
#include <s32strm.h>
#endif

//class RReadStream;
//class RWriteStream;

class TCellRef
	{
public:
	inline TCellRef();
	inline TCellRef(TInt aRow,TInt aCol);

	inline TBool operator==(const TCellRef& aCell) const;
	inline TBool operator!=(const TCellRef& aCell) const;

	inline TCellRef& operator+=(const TCellRef& aCell);
	inline TCellRef& operator-=(const TCellRef& aCell);

	IMPORT_C void Offset(TInt aRowOffset,TInt aColOffset);
//
	IMPORT_C void InternalizeL(RReadStream& aStream);
	inline void ExternalizeL(RWriteStream& aStream) const;
public:
	TInt iRow;
	TInt iCol;
	};

IMPORT_C TCellRef operator+(const TCellRef& aLeft,const TCellRef& aRight);
IMPORT_C TCellRef operator-(const TCellRef& aLeft,const TCellRef& aRight);

inline TCellRef::TCellRef()
	{}
inline TCellRef::TCellRef(TInt aRow,TInt aCol)
    : iRow(aRow),iCol(aCol)
	{}
inline TBool TCellRef::operator==(const TCellRef& aCell) const
	{return aCell.iRow==iRow && aCell.iCol==iCol;}
inline TBool TCellRef::operator!=(const TCellRef& aCell) const
	{return aCell.iRow!=iRow || aCell.iCol!=iCol;}
inline TCellRef& TCellRef::operator+=(const TCellRef& aCell)
	{Offset(aCell.iRow,aCell.iCol);return *this;}
inline TCellRef& TCellRef::operator-=(const TCellRef& aCell)
	{Offset(-aCell.iRow,-aCell.iCol);return *this;}
inline void TCellRef::ExternalizeL(RWriteStream& aStream) const
	{aStream.WriteInt32L(iRow);aStream.WriteInt32L(iCol);}


class TRangeRef
	{
public:
	inline TRangeRef();
	inline TRangeRef(const TCellRef& aFrom,const TCellRef& aTo);
	inline TRangeRef(TInt aFromRow,TInt aFromCol,TInt aToRow,TInt aToCol);

	IMPORT_C TBool operator==(const TRangeRef& aRange) const;
	inline TBool operator!=(const TRangeRef& aRange) const;

	inline void SetRange(const TCellRef& aFrom,const TCellRef& aTo);
	inline void SetRange(TInt aFromRow,TInt aFromCol,TInt aToRow,TInt aToCol);
	inline TInt NoRows() const;
	inline TInt NoCols() const;
	IMPORT_C TInt NoCells() const;
	IMPORT_C TBool Contains(const TCellRef& aCell) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TCellRef	iFrom;
	TCellRef	iTo;
public:
	class TIter;	// defined outside TRangeRef class as contains TRangeRef
	};
class TRangeRef::TIter
	{
public:
	IMPORT_C TIter(const TRangeRef& aRangeRef);
	IMPORT_C TBool operator++();
	inline TBool InRange() const;
public:
	TCellRef	iCurrent;
private:
	TRangeRef	iRange;
	};


inline TRangeRef::TRangeRef()
	{}
inline TRangeRef::TRangeRef(const TCellRef& aFrom,const TCellRef& aTo)
	: iFrom(aFrom),iTo(aTo)
	{}
inline TRangeRef::TRangeRef(TInt aFromRow,TInt aFromCol,TInt aToRow,TInt aToCol)
	: iFrom(aFromRow,aFromCol),iTo(aToRow,aToCol)
	{}
inline void TRangeRef::SetRange(const TCellRef& aFrom,const TCellRef& aTo)
	{iFrom=aFrom;iTo=aTo;}
inline void TRangeRef::SetRange(TInt aFromRow,TInt aFromCol,TInt aToRow,TInt aToCol)
	{iFrom.iRow=aFromRow;iFrom.iCol=aFromCol;iTo.iRow=aToRow;iTo.iCol=aToCol;}
inline TBool TRangeRef::operator!=(const TRangeRef& aRange) const
	{return !operator==(aRange);}
inline TInt TRangeRef::NoRows() const
	{return iTo.iRow - iFrom.iRow + 1;}
inline TInt TRangeRef::NoCols() const
	{return iTo.iCol - iFrom.iCol + 1;}
inline TBool TRangeRef::TIter::InRange() const
	{return iRange.Contains(iCurrent);}

#endif
