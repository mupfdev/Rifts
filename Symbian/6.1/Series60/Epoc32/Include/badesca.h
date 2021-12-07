// BADESCA.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by DavidW, October 1996
// Descriptor arrays
// 

#if !defined(__BADESCA_H__)
#define __BADESCA_H__

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif


class CDesC8Array : public CArrayFixBase, public MDesC8Array
	{
protected:
	IMPORT_C CDesC8Array(TBufRep aRep,TInt aGranularity);
public:
    IMPORT_C ~CDesC8Array();
	IMPORT_C void AppendL(const TDesC8& aPtr);
	IMPORT_C void InsertL(TInt aPos,const TDesC8& aPtr);
	IMPORT_C TInt InsertIsqL(const TDesC8& aPtr,TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C TInt InsertIsqAllowDuplicatesL(const TDesC8& aPtr,TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C void Sort(TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C TInt Find(const TDesC8& aPtr,TInt& aPos,TKeyCmpText aTextComparisonType=ECmpFolded) const;
	IMPORT_C TInt FindIsq(const TDesC8& aPtr,TInt& aPos,TKeyCmpText aTextComparisonType=ECmpFolded) const;
	IMPORT_C void Delete(TInt aPos);
	IMPORT_C void Delete(TInt aIndex,TInt aCount);
	IMPORT_C void Reset();
	inline TPtrC8 operator[](TInt aIndex) const;
// from MDesC8Array
    IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC8 MdcaPoint(TInt aIndex) const;
	};

inline TPtrC8 CDesC8Array::operator[](TInt aIndex) const
	{ return(MdcaPoint(aIndex)); }

class CDesC8ArrayFlat : public CDesC8Array
	{
public:
	IMPORT_C CDesC8ArrayFlat(TInt aGranularity);
    IMPORT_C ~CDesC8ArrayFlat();
	};

class CDesC8ArraySeg : public CDesC8Array
	{
public:
	IMPORT_C CDesC8ArraySeg(TInt aGranularity);
    IMPORT_C ~CDesC8ArraySeg();
	};


class CDesC16Array : public CArrayFixBase, public MDesC16Array
	{
protected:
	IMPORT_C CDesC16Array(TBufRep aRep,TInt aGranularity);
public:
    IMPORT_C ~CDesC16Array();
	IMPORT_C void AppendL(const TDesC16& aPtr);
	IMPORT_C void InsertL(TInt aPos,const TDesC16& aPtr);
	IMPORT_C TInt InsertIsqL(const TDesC16& aPtr,TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C TInt InsertIsqAllowDuplicatesL(const TDesC16& aPtr,TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C void Sort(TKeyCmpText aTextComparisonType=ECmpFolded);
	IMPORT_C TInt Find(const TDesC16& aPtr,TInt& aPos,TKeyCmpText aTextComparisonType=ECmpFolded) const;
	IMPORT_C TInt FindIsq(const TDesC16& aPtr,TInt& aPos,TKeyCmpText aTextComparisonType=ECmpFolded) const;
	IMPORT_C void Delete(TInt aPos);
	IMPORT_C void Delete(TInt aIndex,TInt aCount);
	IMPORT_C void Reset();
	inline TPtrC16 operator[](TInt aIndex) const;
// from MDesC16Array
    IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC16 MdcaPoint(TInt aIndex) const;
	};

inline TPtrC16 CDesC16Array::operator[](TInt aIndex) const
	{ return(MdcaPoint(aIndex)); }

class CDesC16ArrayFlat : public CDesC16Array
	{
public:
	IMPORT_C CDesC16ArrayFlat(TInt aGranularity);
    IMPORT_C ~CDesC16ArrayFlat();
	};

class CDesC16ArraySeg : public CDesC16Array
	{
public:
	IMPORT_C CDesC16ArraySeg(TInt aGranularity);
    IMPORT_C ~CDesC16ArraySeg();
	};

class CPtrC8Array : public CArrayFixFlat<TPtrC8>, public MDesC8Array
	{
public:
	IMPORT_C CPtrC8Array(TInt aGranularity);
	IMPORT_C ~CPtrC8Array();
//
	IMPORT_C void CopyL(const MDesC8Array& aArray);
    inline void operator=(const MDesC8Array& aArray);
// Mixin members
    IMPORT_C TInt MdcaCount() const;
    IMPORT_C TPtrC8 MdcaPoint(TInt aIndex) const;
	};

class CPtrC16Array : public CArrayFixFlat<TPtrC16>, public MDesC16Array
	{
public:
	IMPORT_C CPtrC16Array(TInt aGranularity);
	IMPORT_C ~CPtrC16Array();
//
	IMPORT_C void CopyL(const MDesC16Array& aArray);
    inline void operator=(const MDesC16Array& aArray);
// Mixin members
    IMPORT_C TInt MdcaCount() const;
    IMPORT_C TPtrC16 MdcaPoint(TInt aIndex) const;
	};

//	CPtrC8Array
inline void CPtrC8Array::operator=(const MDesC8Array& aArray)
	{CopyL(aArray);}

//	CPtrC16Array
inline void CPtrC16Array::operator=(const MDesC16Array& aArray)
	{CopyL(aArray);}

// generic text array definitions

#if defined (_UNICODE)
typedef CDesC16Array     CDesCArray;
typedef CDesC16ArrayFlat CDesCArrayFlat;
typedef CDesC16ArraySeg  CDesCArraySeg;
typedef CPtrC16Array CPtrCArray;
#else
typedef CDesC8Array      CDesCArray;
typedef CDesC8ArrayFlat  CDesCArrayFlat;
typedef CDesC8ArraySeg   CDesCArraySeg;
typedef CPtrC8Array CPtrCArray;
#endif


#endif // __BADESCA_H__




