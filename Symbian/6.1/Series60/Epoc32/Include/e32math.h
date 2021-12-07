// E32MATH.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32MATH_H__
#define __E32MATH_H__
#include <e32std.h>

const TInt KMaxPrecision=15;
const TInt KPrecisionLimit=12;
const TInt KMantissaBits=53;
const TInt KMaxExponent=1023;
const TInt KExponentBias=1022;
const TInt KSpecialExponent=2047;
//
const TInt KTReal32MaxExponent=128;			// changed from 127
const TInt KTReal32MinExponent=-125;
const TInt KTReal32ExponentBias=126;
const TInt KTReal32SpecialExponent=255;		// changed from KTReal32ExponentBad
const TInt KTReal32ZeroExponent=0;
//
const TInt KTReal64MaxExponent=1024;		// changed from 1023
const TInt KTReal64MinExponent=-1021;
const TInt KTReal64ExponentBias=1022;
const TInt KTReal64SpecialExponent=2047;	// changed from KTReal64BadExponent
const TInt KTReal64ZeroExponent=0;
//
const TReal KMinTReal=2.2250738585072015E-308;	// changed from TReal64
const TReal KMaxTReal=1.7976931348623157E+308;	//
//
const TReal32 KMinTReal32=1.17549435E-38f;
const TReal32 KMaxTReal32=3.40282347E+38f;
//
const TReal64 KMinTReal64=2.2250738585072015E-308;
const TReal64 KMaxTReal64=1.7976931348623157E+308;
//
const TReal KSqhf=0.70710678118654752440;
const TReal KRln2=1.4426950408889634;
const TReal KRln10=0.4342944819032518;
const TReal KRlg2=0.3010299956639812;
const TReal KPi=3.1415926535897932;
const TReal KPiInv=0.3183098861837907;
const TReal KPiBy2=1.5707963267948966;
const TReal KDrpi=0.6366197723675813;
const TReal KSqt3=1.7320508075688773;
const TReal KMsq3=0.2679491924311227;
const TReal KRadToDeg=57.29577951308232;
const TReal KDegToRad=0.017453292519943296;

class TRealX
	{
public:
	enum TRealXOrder {ELessThan=1,EEqual=2,EGreaterThan=4,EUnordered=8};
public:
	IMPORT_C TRealX();
	IMPORT_C TRealX(TInt aInt);
	IMPORT_C TRealX(TUint aInt);
	IMPORT_C TRealX(TUint aExp, TUint aMantHi, TUint aMantLo);
	IMPORT_C TRealX(const TInt64 &aInt);
	IMPORT_C TRealX(TReal32 aReal);
	IMPORT_C TRealX(TReal64 aReal);
	IMPORT_C TRealX &operator=(TInt aInt);
	IMPORT_C TRealX &operator=(TUint aInt);
	IMPORT_C TRealX &operator=(const TInt64& aInt);
	IMPORT_C TRealX &operator=(TReal32 aReal);
	IMPORT_C TRealX &operator=(TReal64 aReal);
	IMPORT_C TInt Set(TInt aInt);
	IMPORT_C TInt Set(TUint aInt);
	IMPORT_C TInt Set(const TInt64& aInt);
	IMPORT_C TInt Set(TReal32 aReal);
	IMPORT_C TInt Set(TReal64 aReal);
	IMPORT_C operator TInt();
	IMPORT_C operator TUint();
	IMPORT_C operator TInt64();
	IMPORT_C operator TReal32();
	IMPORT_C operator TReal64();
	IMPORT_C TInt GetTReal(TReal32 &aVal) const;
	IMPORT_C TInt GetTReal(TReal64 &aVal) const;
	IMPORT_C void SetZero(TBool aNegative=EFalse);
	IMPORT_C void SetNaN();
	IMPORT_C void SetInfinite(TBool aNegative);
	IMPORT_C TBool IsZero() const;
	IMPORT_C TBool IsNaN() const;
	IMPORT_C TBool IsInfinite() const;
	IMPORT_C TBool IsFinite() const;
	IMPORT_C const TRealX &operator+=(const TRealX &aVal);
	IMPORT_C const TRealX &operator-=(const TRealX &aVal);
	IMPORT_C const TRealX &operator*=(const TRealX &aVal);
	IMPORT_C const TRealX &operator/=(const TRealX &aVal);
	IMPORT_C const TRealX &operator%=(const TRealX &aVal);
	IMPORT_C TInt AddEq(const TRealX &aVal);
	IMPORT_C TInt SubEq(const TRealX &aVal);
	IMPORT_C TInt MultEq(const TRealX &aVal);
	IMPORT_C TInt DivEq(const TRealX &aVal);
	IMPORT_C TInt ModEq(const TRealX &aVal);
	IMPORT_C TRealX operator+() const;
	IMPORT_C TRealX operator-() const;
	IMPORT_C TRealX &operator++();
	IMPORT_C TRealX operator++(TInt);
	IMPORT_C TRealX &operator--();
	IMPORT_C TRealX operator--(TInt);
	IMPORT_C TRealX operator+(const TRealX &aVal) const;
	IMPORT_C TRealX operator-(const TRealX &aVal) const;
	IMPORT_C TRealX operator*(const TRealX &aVal) const;
	IMPORT_C TRealX operator/(const TRealX &aVal) const;
	IMPORT_C TRealX operator%(const TRealX &aVal) const;
	IMPORT_C TInt Add(TRealX& aResult,const TRealX &aVal) const;
	IMPORT_C TInt Sub(TRealX& aResult,const TRealX &aVal) const;
	IMPORT_C TInt Mult(TRealX& aResult,const TRealX &aVal) const;
	IMPORT_C TInt Div(TRealX& aResult,const TRealX &aVal) const;
	IMPORT_C TInt Mod(TRealX& aResult,const TRealX &aVal) const;
	IMPORT_C TRealXOrder Compare(const TRealX& aVal) const;
	inline TBool operator==(const TRealX &aVal) const;
	inline TBool operator!=(const TRealX &aVal) const;
	inline TBool operator>=(const TRealX &aVal) const;
	inline TBool operator<=(const TRealX &aVal) const;
	inline TBool operator>(const TRealX &aVal) const;
	inline TBool operator<(const TRealX &aVal) const;
public:
	TInt64 iMant;		// always normalised with bit 63 = 1
	TInt8 iSign;		// 0 for +, 1 for -
	TUint8 iFlag;		// 0 for exact, 1 for rounded down, 2 for rounded up
	TUint16 iExp;		// biased by 32767, iExp=0 => zero, +65535 => infinity or NaN
	};

struct SPoly
    {
    TInt num;
	TReal c[1];
    };

class Math
	{
public:
	IMPORT_C static TInt ACos(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt ASin(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt ATan(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt ATan(TReal &aTrg,const TReal &aSrcY,const TReal &aSrcX);
	IMPORT_C static TInt Cos(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt DtoR(TReal &aTrg,const TDesC &aSrc,TInt &aPos,const TChar aPoint);
	IMPORT_C static TInt Exp(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt Frac(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt Int(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt Int(TInt16 &aTrg,const TReal &aSrc);
	IMPORT_C static TInt Int(TInt32 &aTrg,const TReal &aSrc);
	IMPORT_C static TInt Log(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt Ln(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt Mod(TReal &aTrg,const TReal &aSrc,const TReal &aModulus);
	IMPORT_C static TReal Poly(TReal aVal,const SPoly *aPoly);
	IMPORT_C static TInt Pow(TReal &aTrg,const TReal &aSrc,const TReal &aPower);
	IMPORT_C static TInt Pow10(TReal &aTrg,const TInt exp);
	IMPORT_C static TInt Rand(TInt64 &aSeed);
	IMPORT_C static TReal FRand(TInt64 &aSeed);
	IMPORT_C static TUint32 Random();
	IMPORT_C static TInt Round(TReal &aTrg,const TReal &aSrc,TInt aDecimalPlaces);
	IMPORT_C static TInt Sin(TReal &aTrg,const TReal &aSrc); 
	IMPORT_C static TInt Sqrt(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TInt Tan(TReal &aTrg,const TReal &aSrc);
	IMPORT_C static TBool IsZero(const TReal &aVal);
	IMPORT_C static TBool IsNaN(const TReal &aVal);
	IMPORT_C static TBool IsInfinite(const TReal &aVal);
	IMPORT_C static TBool IsFinite(const TReal &aVal);
	IMPORT_C static void PolyX(TRealX& aY, const TRealX& aX, TInt aDeg, const TRealX *aCoef);
	static TInt MultPow10X(TRealX& aTrg, TInt aPower);
private:
	IMPORT_C static void SetZero(TReal &aVal,TInt aSign=0);
	IMPORT_C static void SetNaN(TReal &aVal);
	IMPORT_C static void SetInfinite(TReal &aVal,TInt aSign);
	};
#endif

#include <e32math.inl>

