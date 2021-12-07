// E32DES8.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __E32DES8_H__
#define __E32DES8_H__

const TUint KMaskDesLength8=0xfffffff;
const TInt KShiftDesType8=28;

class TBufCBase8;
class HBufC8;
class TDes8;
class TPtrC8;
class TPtr8;
class TDesC8
    {
public:
	inline TInt operator<(const TDesC8 &aDes) const;
	inline TInt operator<=(const TDesC8 &aDes) const;
	inline TInt operator>(const TDesC8 &aDes) const;
	inline TInt operator>=(const TDesC8 &aDes) const;
	inline TInt operator==(const TDesC8 &aDes) const;
	inline TInt operator!=(const TDesC8 &aDes) const;
	inline const TUint8 &operator[](TInt anIndex) const;
	inline TInt Length() const;
	inline TInt Size() const;
	IMPORT_C const TUint8 *Ptr() const;
	IMPORT_C TInt Compare(const TDesC8 &aDes) const;
	IMPORT_C TInt CompareF(const TDesC8 &aDes) const;
	IMPORT_C TInt CompareC(const TDesC8 &aDes) const;
	IMPORT_C TInt Match(const TDesC8 &aDes) const;
	IMPORT_C TInt MatchF(const TDesC8 &aDes) const;
	IMPORT_C TInt MatchC(const TDesC8 &aDes) const;
	IMPORT_C TInt Locate(TChar aChar) const;
	IMPORT_C TInt LocateF(TChar aChar) const;
	IMPORT_C TInt LocateReverse(TChar aChar) const;
	IMPORT_C TInt LocateReverseF(TChar aChar) const;
	IMPORT_C TInt Find(const TDesC8 &aDes) const;
	IMPORT_C TInt Find(const TUint8 *pS,TInt aLenS) const;
	IMPORT_C TInt FindF(const TDesC8 &aDes) const;
	IMPORT_C TInt FindF(const TUint8 *pS,TInt aLenS) const;
	IMPORT_C TInt FindC(const TDesC8 &aDes) const;
	IMPORT_C TInt FindC(const TUint8 *pS,TInt aLenS) const;
	IMPORT_C TPtrC8 Left(TInt aLength) const;
	IMPORT_C TPtrC8 Right(TInt aLength) const;
	IMPORT_C TPtrC8 Mid(TInt aPos) const;
	IMPORT_C TPtrC8 Mid(TInt aPos,TInt aLength) const;
	IMPORT_C HBufC8 *Alloc() const;
	IMPORT_C HBufC8 *AllocL() const;
	IMPORT_C HBufC8 *AllocLC() const;
protected:
	inline TDesC8(TInt aType,TInt aLength);
	inline TDesC8() {}
//	inline ~TDesC8() {}			Commented out for the moment since it breaks code
	inline TInt Type() const;
	inline void DoSetLength(TInt aLength);
	IMPORT_C const TUint8 &AtC(TInt anIndex) const;
private:
#if defined(__DESC_NO_BIT_FIELDS__)
	TUint iLength;
#else
	unsigned int iLength:28;
	unsigned int iType:4;
#endif
	__DECLARE_TEST;
    };
//
class TPtrC8 : public TDesC8
	{
public:
	IMPORT_C TPtrC8();
	IMPORT_C TPtrC8(const TDesC8 &aDes);
	IMPORT_C TPtrC8(const TUint8 *aString);
	IMPORT_C TPtrC8(const TUint8 *aBuf,TInt aLength);
	inline void Set(const TUint8 *aBuf,TInt aLength);
	inline void Set(const TDesC8 &aDes);
	inline void Set(const TPtrC8& aPtr);
private:
	TPtrC8& operator=(const TPtrC8 &aDes);
protected:
	const TUint8 *iPtr;
private:
	__DECLARE_TEST;
	};
//
class TDes8Overflow
	{
public:
	virtual void Overflow(TDes8 &aDes)=0;
	};
//
class TDesC16;
class TDes8 : public TDesC8
	{
public:
	inline TDes8& operator=(const TUint8 *aString);
	inline TDes8& operator=(const TDesC8 &aDes);
	inline TDes8& operator=(const TDes8 &aDes);
	inline TInt MaxLength() const;
	inline TInt MaxSize() const;
	inline const TUint8 &operator[](TInt anIndex) const;
	inline TUint8 &operator[](TInt anIndex);
	inline TDes8 &operator+=(const TDesC8 &aDes);
	IMPORT_C void Zero();
	IMPORT_C const TUint8 *PtrZ();
 	IMPORT_C void SetLength(TInt aLength);
 	IMPORT_C void SetMax();
	IMPORT_C void Copy(const TDesC8 &aDes);
	IMPORT_C void Copy(const TUint8 *aBuf,TInt aLength);
	IMPORT_C void Copy(const TUint8 *aString);
	IMPORT_C void Copy(const TDesC16 &aDes);
	IMPORT_C void CopyF(const TDesC8 &aDes);
	IMPORT_C void CopyC(const TDesC8 &aDes);
	IMPORT_C void CopyLC(const TDesC8 &aDes);
	IMPORT_C void CopyUC(const TDesC8 &aDes);
	IMPORT_C void CopyCP(const TDesC8 &aDes);
	IMPORT_C void Append(TChar aChar);
	IMPORT_C void Append(const TDesC8 &aDes);
	IMPORT_C void Append(const TDesC16 &aDes);
	IMPORT_C void Append(const TUint8 *aBuf,TInt aLength);
	IMPORT_C void AppendFill(TChar aChar,TInt aLength);
	IMPORT_C void ZeroTerminate();
	IMPORT_C void Fill(TChar aChar);
	IMPORT_C void Fill(TChar aChar,TInt aLength);
	IMPORT_C void FillZ();
	IMPORT_C void FillZ(TInt aLength);
	IMPORT_C void Swap(TDes8 &aDes);
	IMPORT_C void Fold();
	IMPORT_C void Collate();
	IMPORT_C void LowerCase();
	IMPORT_C void UpperCase();
	IMPORT_C void Capitalize();
	IMPORT_C void Repeat(const TUint8 *aBuf,TInt aLength);
	IMPORT_C void Repeat(const TDesC8 &aDes);
	IMPORT_C void Trim();
	IMPORT_C void TrimAll();
	IMPORT_C void TrimLeft();
	IMPORT_C void TrimRight();
	IMPORT_C void Insert(TInt aPos,const TDesC8 &aDes);
	IMPORT_C void Delete(TInt aPos,TInt aLength);
	IMPORT_C void Replace(TInt aPos,TInt aLength,const TDesC8 &aDes);
	IMPORT_C void Justify(const TDesC8 &aDes,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void Num(TInt aVal);
	IMPORT_C void Num(TUint aVal,TRadix aRadix=EDecimal);
	IMPORT_C void NumUC(TUint aVal,TRadix aRadix=EDecimal);
	IMPORT_C void NumFixedWidth(TUint aVal,TRadix aRadix,TInt aWidth);
	IMPORT_C void NumFixedWidthUC(TUint aVal,TRadix aRadix,TInt aWidth);
	IMPORT_C void Num(TInt64 aVal);
	IMPORT_C void Num(TInt64 aVal,TRadix aRadix);
	IMPORT_C void NumUC(TInt64 aVal,TRadix aRadix=EDecimal);
	IMPORT_C TInt Num(TReal aVal,const TRealFormat &aFormat);
	IMPORT_C void Format(TRefByValue<const TDesC8> aFmt,...);
	IMPORT_C void FormatList(const TDesC8 &aFmt,VA_LIST aList);
	IMPORT_C void AppendJustify(const TDesC8 &Des,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void AppendJustify(const TDesC8 &Des,TInt aLength,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void AppendJustify(const TUint8 *aString,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void AppendJustify(const TUint8 *aString,TInt aLength,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void AppendNum(TInt aVal);
	IMPORT_C void AppendNum(TUint aVal,TRadix aRadix=EDecimal);
	IMPORT_C void AppendNumUC(TUint aVal,TRadix aRadix=EDecimal);
	IMPORT_C void AppendNumFixedWidth(TUint aVal,TRadix aRadix,TInt aWidth);
	IMPORT_C void AppendNumFixedWidthUC(TUint aVal,TRadix aRadix,TInt aWidth);
	IMPORT_C void AppendNum(TInt64 aVal);
	IMPORT_C void AppendNum(TInt64 aVal,TRadix aRadix);
	IMPORT_C void AppendNumUC(TInt64 aVal,TRadix aRadix=EDecimal);
	IMPORT_C TInt AppendNum(TReal aVal,const TRealFormat &aFormat);
	IMPORT_C void AppendFormat(TRefByValue<const TDesC8> aFmt,TDes8Overflow *aOverflowHandler,...);
	IMPORT_C void AppendFormat(TRefByValue<const TDesC8> aFmt,...);
	IMPORT_C void AppendFormatList(const TDesC8 &aFmt,VA_LIST aList,TDes8Overflow *aOverflowHandler=NULL);
protected:
	inline TDes8(TInt aType,TInt aLength,TInt aMaxLength);
	inline TUint8 *WPtr() const;
	inline TDes8() {}
//	inline ~TDes8() {}			Commented out for the moment since it breaks code
protected:
	TInt iMaxLength;
	__DECLARE_TEST;
    };
//
class TPtr8 : public TDes8
	{
public:
	IMPORT_C TPtr8(TUint8 *aBuf,TInt aMaxLength);
	IMPORT_C TPtr8(TUint8 *aBuf,TInt aLength,TInt aMaxLength);
	inline TPtr8& operator=(const TUint8 *aString);
	inline TPtr8& operator=(const TDesC8& aDes);
	inline TPtr8& operator=(const TPtr8& aPtr);
	inline void Set(TUint8 *aBuf,TInt aLength,TInt aMaxLength);
	inline void Set(const TPtr8 &aPtr);
private:
	IMPORT_C TPtr8(TBufCBase8 &aLcb,TInt aMaxLength);
protected:
	TUint8 *iPtr;
private:
	friend class TBufCBase8;
	__DECLARE_TEST;
	};
//
class TBufCBase8 : public TDesC8
	{
protected:
	IMPORT_C TBufCBase8();
	inline TBufCBase8(TInt aLength);
	IMPORT_C TBufCBase8(const TUint8 *aString,TInt aMaxLength);
	IMPORT_C TBufCBase8(const TDesC8 &aDes,TInt aMaxLength);
	IMPORT_C void Copy(const TUint8 *aString,TInt aMaxLength);
	IMPORT_C void Copy(const TDesC8 &aDes,TInt aMaxLength);
	inline TPtr8 DoDes(TInt aMaxLength);
	inline TUint8 *WPtr() const;
	};
//
class RReadStream;
class HBufC8 : public TBufCBase8
	{
public:
	IMPORT_C static HBufC8 *New(TInt aMaxLength);
	IMPORT_C static HBufC8 *NewL(TInt aMaxLength);
	IMPORT_C static HBufC8 *NewLC(TInt aMaxLength);
	IMPORT_C static HBufC8 *NewMax(TInt aMaxLength);
	IMPORT_C static HBufC8 *NewMaxL(TInt aMaxLength);
	IMPORT_C static HBufC8 *NewMaxLC(TInt aMaxLength);
	IMPORT_C static HBufC8 *NewL(RReadStream &aStream,TInt aMaxLength);
	IMPORT_C static HBufC8 *NewLC(RReadStream &aStream,TInt aMaxLength);
	IMPORT_C HBufC8& operator=(const TUint8 *aString);
	IMPORT_C HBufC8& operator=(const TDesC8 &aDes);
	inline HBufC8& operator=(const HBufC8 &aLcb);
	IMPORT_C HBufC8 *ReAlloc(TInt aMaxLength);
	IMPORT_C HBufC8 *ReAllocL(TInt aMaxLength);
	IMPORT_C TPtr8 Des();
private:
	inline HBufC8(TInt aLength);
private:
	TText8 iBuf[1];
	__DECLARE_TEST;
	};
//
#define __Size8 (sizeof(TInt)/sizeof(TInt8))
#define __Align8(s) ((((s)+__Size8-1)/__Size8)*__Size8)
//
template <TInt S>
class TBufC8 : public TBufCBase8
	{
public:
	inline TBufC8();
    inline TBufC8(const TUint8 *aString);
	inline TBufC8(const TDesC8 &aDes);
	inline TBufC8<S> &operator=(const TUint8 *aString);
	inline TBufC8<S> &operator=(const TDesC8 &aDes);
	inline TPtr8 Des();
protected:
	TUint8 iBuf[__Align8(S)];
	};
//
class TBufBase8 : public TDes8
	{
protected:
	IMPORT_C TBufBase8(TInt aMaxLength);
	IMPORT_C TBufBase8(TInt aLength,TInt aMaxLength);
	IMPORT_C TBufBase8(const TUint8* aString,TInt aMaxLength);
	IMPORT_C TBufBase8(const TDesC8& aDes,TInt aMaxLength);
	};
//
template <TInt S>
class TBuf8 : public TBufBase8
	{
public:
	inline TBuf8();
	inline TBuf8(TInt aLength);
    inline TBuf8(const TUint8* aString);
	inline TBuf8(const TDesC8& aDes);
	inline TBuf8<S>& operator=(const TUint8* aString);
	inline TBuf8<S>& operator=(const TDesC8& aDes);
	inline TBuf8<S>& operator=(const TBuf8<S>& aBuf);
protected:
	TUint8 iBuf[__Align8(S)];
	};
//
typedef TRefByValue<const TDesC8> __TRefDesC8;
template <TInt S>
class TLitC8
	{
public:
	inline const TDesC8* operator&() const;
	inline operator const TDesC8&() const;
	inline const TDesC8& operator()() const;
	inline operator const __TRefDesC8() const;
public:
	TUint iTypeLength;
	TText8 iBuf[__Align8(S)];
	};

#endif
