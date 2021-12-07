//
// bigint.h
//
// (c) 1999 Symbian

#ifndef __BIGINT_H__
#define __BIGINT_H__

#ifndef __E32_BASE_H__
#include <e32base.h>
#endif

struct bignum_st;
struct bn_mont_ctx_st;

const TUint KDefaultPrimalityChecks = 32;	//for the paranoid...

class CInteger : public CBase
	{
public:
	IMPORT_C static CInteger* NewL(const TPtrC8& aValue);
	IMPORT_C static CInteger* NewLC(const TPtrC8& aValue);
	IMPORT_C static CInteger* NewL(const CInteger& aInt);
	IMPORT_C static CInteger* NewLC(const CInteger& aInt);
	IMPORT_C static CInteger* NewL(TInt aInteger);
	IMPORT_C static CInteger* NewLC(TInt aInteger);
	IMPORT_C static CInteger* NewRandomL(TInt aBits, TBool aTop, TBool aBottom);
	IMPORT_C static CInteger* NewRandomLC(TInt aBits, TBool aTop, TBool aBottom);
	IMPORT_C static CInteger* NewPrimeL(TInt aBits, TBool aStrong,
										CInteger& aAdd, CInteger& aRem, TUint aChecks = KDefaultPrimalityChecks);
	IMPORT_C static CInteger* NewPrimeLC(TInt aBits, TBool aStrong, 
										CInteger& aAdd, CInteger& aRem, TUint aChecks = KDefaultPrimalityChecks);
	IMPORT_C static CInteger* NewPrimeL(TInt aBits, TBool aStrong, TUint aChecks = KDefaultPrimalityChecks);
	IMPORT_C static CInteger* NewPrimeLC(TInt aBits, TBool aStrong, TUint aChecks = KDefaultPrimalityChecks);
	IMPORT_C ~CInteger();
//overloaded arithmetic operators; ***THESE CAN ALL LEAVE***
	IMPORT_C CInteger& operator += (const CInteger& aOperand);
	IMPORT_C CInteger& operator -= (const CInteger& aOperand);
	IMPORT_C CInteger& operator *= (const CInteger& aOperand);
	IMPORT_C CInteger& operator /= (const CInteger& aOperand);
	IMPORT_C CInteger& operator %= (const CInteger& aOperand);

	IMPORT_C CInteger& operator += (TInt aOperand);
	IMPORT_C CInteger& operator -= (TInt aOperand);
	IMPORT_C CInteger& operator *= (TInt aOperand);
	IMPORT_C CInteger& operator /= (TInt aOperand);
	IMPORT_C CInteger& operator %= (TInt aOperand);
//assignment
	IMPORT_C CInteger& operator = (const CInteger& aInteger);
	IMPORT_C CInteger& operator = (TInt aInteger);

//more 'rithmetic
	IMPORT_C void SquareL();
	IMPORT_C void ReciprocalL(const CInteger& aMod);
	IMPORT_C void ExpL(const CInteger& aOperand);
	IMPORT_C void ModExpL(const CInteger& aOperand, const CInteger& aMod) const;
	IMPORT_C void ModMulL(const CInteger& aOperand, const CInteger& aMod) const;
	IMPORT_C void GCDL(const CInteger& aOperand, CInteger& aResult) const;
	IMPORT_C void ModInvL(const CInteger& aMod);
//comparison
	IMPORT_C TBool Ucmp(const CInteger& aInteger) const; //unsigned compare
	IMPORT_C TBool operator == (const CInteger& aInteger) const;
	IMPORT_C TBool operator <= (const CInteger& aInteger) const;
	IMPORT_C TBool operator >= (const CInteger& aInteger) const;
	IMPORT_C TBool operator < (const CInteger& aInteger) const;
	IMPORT_C TBool operator > (const CInteger& aInteger) const;
	
	IMPORT_C TBool operator == (TInt aInteger) const;
	IMPORT_C TBool operator <= (TInt aInteger) const;
	IMPORT_C TBool operator >= (TInt aInteger) const;
	IMPORT_C TBool operator < (TInt aInteger) const;
	IMPORT_C TBool operator > (TInt aInteger) const;
//bit stuff
	IMPORT_C CInteger& operator <<= (TUint aBits);
	IMPORT_C CInteger& operator >>= (TUint aBits);
	IMPORT_C void MaskBits(TUint aBits);
	IMPORT_C void SetBit(TUint aBit);				//offset from zero
	IMPORT_C TBool IsBitSet(TUint aBitPos) const;	//offset from zero

//accessors, queries
	IMPORT_C HBufC8* BufferLC() const;
	IMPORT_C TInt IntL() const;
	IMPORT_C TUint Bytes() const;
	IMPORT_C TUint Bits() const;
	IMPORT_C TBool IsPrimeL(TUint aNumChecks = KDefaultPrimalityChecks) const;
private:
	CInteger();
	void ConstructL(const TPtrC8& aValue);
	void ConstructL(const CInteger& aInteger);
	void ConstructL(TInt aInteger);
	void ConstructL(TInt aBits, TBool aTop, TBool aBottom);
	void ConstructL(TInt aBits, TBool aStrong, TUint aChecks,
					CInteger& aAdd, CInteger& aRem);
	void ConstructL(	TInt aBits, TBool aStrong, TUint aChecks);
	bignum_st* iValue;
	friend class CMontgomeryStructure;
	};

class CMontgomeryStructure : public CBase
	{
public:
	IMPORT_C static CMontgomeryStructure* NewL(const CInteger& aMod);
	IMPORT_C static CMontgomeryStructure* NewLC(const CInteger& aMod);
	IMPORT_C ~CMontgomeryStructure();
	IMPORT_C CInteger* ModMulMontgomeryL(const CInteger& aOperand1, const CInteger& aOperand2) const;
	IMPORT_C CInteger* ModExpMontL(const CInteger& aOperand, const CInteger& aPower) const;
	IMPORT_C void ModMulMontgomeryL(const CInteger& aResult, const CInteger& aOperand1, const CInteger& aOperand2) const;
	IMPORT_C void ModExpMontL(const CInteger& aResult, const CInteger& aOperand, const CInteger& aPower) const;	
	IMPORT_C CInteger* ModExp2MontL(	const CInteger& aOperand1, const CInteger& aPower1,
										const CInteger& aOperand2, const CInteger& aPower2) const;
	IMPORT_C void ModExp2MontL(	CInteger& aResult, const CInteger& aOperand1, const CInteger& aPower1,
								const CInteger& aOperand2, const CInteger& aPower2) const;
private:
	CMontgomeryStructure();
	void ConstructL(const CInteger& aMod);
	bn_mont_ctx_st* iMont;
	CInteger* iMod;
	};

#endif // __BIGINT_H__
