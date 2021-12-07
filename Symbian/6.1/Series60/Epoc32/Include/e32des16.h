// E32DES16.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __E32DES16_H__
#define __E32DES16_H__

const TUint KMaskDesLength16=0xfffffff;
const TInt KShiftDesType16=28;

class TBufCBase16;
class HBufC16;
class TDes16;
class TPtrC16;
class TPtr16;
struct TCollationMethod;

class TDesC16
    {
public:
	inline TInt operator<(const TDesC16 &aDes) const;
	inline TInt operator<=(const TDesC16 &aDes) const;
	inline TInt operator>(const TDesC16 &aDes) const;
	inline TInt operator>=(const TDesC16 &aDes) const;
	inline TInt operator==(const TDesC16 &aDes) const;
	inline TInt operator!=(const TDesC16 &aDes) const;
	inline const TUint16 &operator[](TInt anIndex) const;
	inline TInt Length() const;
	inline TInt Size() const;
	IMPORT_C const TUint16 *Ptr() const;
	IMPORT_C TInt Compare(const TDesC16 &aDes) const;
	IMPORT_C TInt CompareF(const TDesC16 &aDes) const;
	IMPORT_C TInt CompareC(const TDesC16 &aDes) const;
#ifdef _UNICODE
	IMPORT_C TInt CompareC(const TDesC16& aDes,TInt aMaxLevel,const TCollationMethod* aCollationMethod) const;	
#endif
	IMPORT_C TInt Match(const TDesC16 &aDes) const;
	IMPORT_C TInt MatchF(const TDesC16 &aDes) const;
	IMPORT_C TInt MatchC(const TDesC16 &aDes) const;
	IMPORT_C TInt Locate(TChar aChar) const;
	IMPORT_C TInt LocateF(TChar aChar) const;
	IMPORT_C TInt LocateReverse(TChar aChar) const;
	IMPORT_C TInt LocateReverseF(TChar aChar) const;
	IMPORT_C TInt Find(const TDesC16 &aDes) const;
	IMPORT_C TInt Find(const TUint16 *aBuf,TInt aLen) const;
	IMPORT_C TInt FindF(const TDesC16 &aDes) const;
	IMPORT_C TInt FindF(const TUint16 *aBuf,TInt aLen) const;
	IMPORT_C TInt FindC(const TDesC16 &aDes) const;
	IMPORT_C TInt FindC(const TUint16 *aBuf,TInt aLen) const;
	IMPORT_C TPtrC16 Left(TInt aLength) const;
	IMPORT_C TPtrC16 Right(TInt aLength) const;
	IMPORT_C TPtrC16 Mid(TInt aPos) const;
	IMPORT_C TPtrC16 Mid(TInt aPos,TInt aLength) const;
	IMPORT_C HBufC16 *Alloc() const;
	IMPORT_C HBufC16 *AllocL() const;
	IMPORT_C HBufC16 *AllocLC() const;
protected:
	inline TDesC16() {}
	inline TDesC16(TInt aType,TInt aLength);
//	inline ~TDesC16() {}			Commented out for the moment since it breaks code
	inline TInt Type() const;
	inline void DoSetLength(TInt aLength);
	IMPORT_C const TUint16 &AtC(TInt anIndex) const;
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
class TPtrC16 : public TDesC16
	{
public:
	IMPORT_C TPtrC16();
	IMPORT_C TPtrC16(const TDesC16 &aDes);
	IMPORT_C TPtrC16(const TUint16 *aString);
	IMPORT_C TPtrC16(const TUint16 *aBuf,TInt aLength);
	inline void Set(const TUint16 *aBuf,TInt aLength);
	inline void Set(const TDesC16 &aDes);
	inline void Set(const TPtrC16 &aPtr);
private:
	TPtrC16& operator=(const TPtrC16 &aDes);
protected:
	const TUint16 *iPtr;
private:
	__DECLARE_TEST;
	};
//
class TDes16Overflow
	{
public:
	virtual void Overflow(TDes16 &aDes)=0;
	};
//
class TDes16 : public TDesC16
	{
public:
	inline TDes16& operator=(const TUint16 *aString);
	inline TDes16& operator=(const TDesC16 &aDes);
	inline TDes16& operator=(const TDes16 &aDes);
	inline TInt MaxLength() const;
	inline TInt MaxSize() const;
	inline const TUint16 &operator[](TInt anIndex) const;
	inline TUint16 &operator[](TInt anIndex);
	inline TDes16 &operator+=(const TDesC16 &aDes);
	IMPORT_C void Zero();
	IMPORT_C const TUint16 *PtrZ();
 	IMPORT_C void SetLength(TInt aLength);
 	IMPORT_C void SetMax();
	IMPORT_C void Copy(const TDesC8 &aDes);
	IMPORT_C void Copy(const TDesC16 &aDes);
	IMPORT_C void Copy(const TUint16 *aBuf,TInt aLength);
	IMPORT_C void Copy(const TUint16 *aString);
	IMPORT_C void CopyF(const TDesC16 &aDes);
	IMPORT_C void CopyC(const TDesC16 &aDes);
	IMPORT_C void CopyLC(const TDesC16 &aDes);
	IMPORT_C void CopyUC(const TDesC16 &aDes);
	IMPORT_C void CopyCP(const TDesC16 &aDes);
	IMPORT_C void Append(TChar aChar);
	IMPORT_C void Append(const TDesC16 &aDes);
	IMPORT_C void Append(const TUint16 *aBuf,TInt aLength);
	IMPORT_C void AppendFill(TChar aChar,TInt aLength);
	IMPORT_C void ZeroTerminate();
	IMPORT_C void Fill(TChar aChar);
	IMPORT_C void Fill(TChar aChar,TInt aLength);
	IMPORT_C void FillZ();
	IMPORT_C void FillZ(TInt aLength);
	IMPORT_C void Swap(TDes16 &aDes);
	IMPORT_C void Fold();
	IMPORT_C void Collate();
	IMPORT_C void LowerCase();
	IMPORT_C void UpperCase();
	IMPORT_C void Capitalize();
	IMPORT_C void Repeat(const TDesC16 &aDes);
	IMPORT_C void Repeat(const TUint16 *aBuf,TInt aLength);
	IMPORT_C void Trim();
	IMPORT_C void TrimAll();
	IMPORT_C void TrimLeft();
	IMPORT_C void TrimRight();
	IMPORT_C void Insert(TInt aPos,const TDesC16 &aDes);
	IMPORT_C void Delete(TInt aPos,TInt aLength);
	IMPORT_C void Replace(TInt aPos,TInt aLength,const TDesC16 &aDes);
	IMPORT_C void Justify(const TDesC16 &aDes,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void Num(TInt aVal);
	IMPORT_C void Num(TUint aVal,TRadix aRadix=EDecimal);
	IMPORT_C void NumUC(TUint aVal,TRadix aRadix=EDecimal);
	IMPORT_C void NumFixedWidth(TUint aVal,TRadix aRadix,TInt aWidth);
	IMPORT_C void NumFixedWidthUC(TUint aVal,TRadix aRadix,TInt aWidth);
	IMPORT_C void Num(TInt64 aVal);
	IMPORT_C void Num(TInt64 aVal,TRadix aRadix);
	IMPORT_C void NumUC(TInt64 aVal,TRadix aRadix=EDecimal);
	IMPORT_C TInt Num(TReal aVal,const TRealFormat &aFormat);
	IMPORT_C void Format(TRefByValue<const TDesC16> aFmt,...);
	IMPORT_C void FormatList(const TDesC16 &aFmt,VA_LIST aList);
	IMPORT_C void AppendJustify(const TDesC16 &Des,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void AppendJustify(const TDesC16 &Des,TInt aLength,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void AppendJustify(const TUint16 *aString,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void AppendJustify(const TUint16 *aString,TInt aLength,TInt aWidth,TAlign anAlignment,TChar aFill);
	IMPORT_C void AppendNum(TInt aVal);
	IMPORT_C void AppendNum(TUint aVal,TRadix aRadix=EDecimal);
	IMPORT_C void AppendNumUC(TUint aVal,TRadix aRadix=EDecimal);
	IMPORT_C void AppendNumFixedWidth(TUint aVal,TRadix aRadix,TInt aWidth);
	IMPORT_C void AppendNumFixedWidthUC(TUint aVal,TRadix aRadix,TInt aWidth);
	IMPORT_C void AppendNum(TInt64 aVal);
	IMPORT_C void AppendNum(TInt64 aVal,TRadix aRadix);
	IMPORT_C void AppendNumUC(TInt64 aVal,TRadix aRadix=EDecimal);
	IMPORT_C TInt AppendNum(TReal aVal,const TRealFormat &aFormat);
	IMPORT_C void AppendFormat(TRefByValue<const TDesC16> aFmt,TDes16Overflow *aOverflowHandler,...);
	IMPORT_C void AppendFormat(TRefByValue<const TDesC16> aFmt,...);
	IMPORT_C void AppendFormatList(const TDesC16 &aFmt,VA_LIST aList,TDes16Overflow *aOverflowHandler=NULL);
protected:
	inline TDes16() {}
	inline TDes16(TInt aType,TInt aLength,TInt aMaxLength);
	inline TUint16 *WPtr() const;
//	inline ~TDes16() {}			Commented out for the moment since it breaks code
protected:
	TInt iMaxLength;
	__DECLARE_TEST;
    };
//
class TPtr16 : public TDes16
	{
public:
	IMPORT_C TPtr16(TUint16 *aBuf,TInt aMaxLength);
	IMPORT_C TPtr16(TUint16 *aBuf,TInt aLength,TInt aMaxLength);
	inline TPtr16& operator=(const TUint16 *aString);
	inline TPtr16& operator=(const TDesC16& aDes);
	inline TPtr16& operator=(const TPtr16& aDes);
	inline void Set(TUint16 *aBuf,TInt aLength,TInt aMaxLength);
	inline void Set(const TPtr16 &aPtr);
private:
	IMPORT_C TPtr16(TBufCBase16 &aLcb,TInt aMaxLength);
protected:
	TUint16 *iPtr;
private:
	friend class TBufCBase16;
	__DECLARE_TEST;
	};
//
class TBufCBase16 : public TDesC16
	{
protected:
	IMPORT_C TBufCBase16();
	inline TBufCBase16(TInt aLength);
	IMPORT_C TBufCBase16(const TUint16 *aString,TInt aMaxLength);
	IMPORT_C TBufCBase16(const TDesC16 &aDes,TInt aMaxLength);
	IMPORT_C void Copy(const TUint16 *aString,TInt aMaxLength);
	IMPORT_C void Copy(const TDesC16 &aDes,TInt aMaxLength);
	inline TPtr16 DoDes(TInt aMaxLength);
	inline TUint16 *WPtr() const;
	};
//
class RReadStream;
class HBufC16 : public TBufCBase16
	{
public:
	IMPORT_C static HBufC16 *New(TInt aMaxLength);
	IMPORT_C static HBufC16 *NewL(TInt aMaxLength);
	IMPORT_C static HBufC16 *NewLC(TInt aMaxLength);
	IMPORT_C static HBufC16 *NewMax(TInt aMaxLength);
	IMPORT_C static HBufC16 *NewMaxL(TInt aMaxLength);
	IMPORT_C static HBufC16 *NewMaxLC(TInt aMaxLength);
	IMPORT_C static HBufC16 *NewL(RReadStream &aStream,TInt aMaxLength);
	IMPORT_C static HBufC16 *NewLC(RReadStream &aStream,TInt aMaxLength);
	IMPORT_C HBufC16& operator=(const TUint16 *aString);
	IMPORT_C HBufC16& operator=(const TDesC16 &aDes);
	inline HBufC16& operator=(const HBufC16 &aLcb);
	IMPORT_C HBufC16 *ReAlloc(TInt aMaxLength);
	IMPORT_C HBufC16 *ReAllocL(TInt aMaxLength);
	IMPORT_C TPtr16 Des();
private:
	inline HBufC16(TInt aLength);
private:
	TText16 iBuf[1];
	__DECLARE_TEST;
	};
//
#define __Size16 (sizeof(TInt)/sizeof(TInt16))
#define __Align16(s) ((((s)+__Size16-1)/__Size16)*__Size16)
//
template <TInt S>
class TBufC16 : public TBufCBase16
	{
public:
	inline TBufC16();
    inline TBufC16(const TUint16 *aString);
	inline TBufC16(const TDesC16 &aDes);
	inline TBufC16<S> &operator=(const TUint16 *aString);
	inline TBufC16<S> &operator=(const TDesC16 &aDes);
	inline TPtr16 Des();
protected:
	TUint16 iBuf[__Align16(S)];
	};
//
class TBufBase16 : public TDes16
	{
protected:
	IMPORT_C TBufBase16(TInt aMaxLength);
	IMPORT_C TBufBase16(TInt aLength,TInt aMaxLength);
	IMPORT_C TBufBase16(const TUint16* aString,TInt aMaxLength);
	IMPORT_C TBufBase16(const TDesC16& aDes,TInt aMaxLength);
	};
//
template <TInt S>
class TBuf16 : public TBufBase16
	{
public:
	inline TBuf16();
	inline TBuf16(TInt aLength);
    inline TBuf16(const TUint16* aString);
	inline TBuf16(const TDesC16& aDes);
	inline TBuf16<S>& operator=(const TUint16* aString);
	inline TBuf16<S>& operator=(const TDesC16& aDes);
	inline TBuf16<S>& operator=(const TBuf16<S>& aDes);
protected:
	TUint16 iBuf[__Align16(S)];
	};
//
typedef TRefByValue<const TDesC16> __TRefDesC16;
template <TInt S>
class TLitC16
	{
public:
	inline const TDesC16* operator&() const;
	inline operator const TDesC16&() const;
	inline const TDesC16& operator()() const;
	inline operator const __TRefDesC16() const;
public:
#if defined(__GCC32__)
	typedef __wchar_t __TText;
#elif defined(__VC32__)
	typedef TUint16 __TText;
#else
#error	no typedef for __TText
#endif
public:
	TUint iTypeLength;
	__TText iBuf[__Align16(S)];
	};

#endif
