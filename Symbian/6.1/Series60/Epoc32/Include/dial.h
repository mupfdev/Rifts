// DIAL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __DIAL_H__
#define __DIAL_H__

#include <t32wld.h>

// Charge Card
const TInt KChargeCardRuleSize=32;
const TInt KChargeCardAccountNumberSize=32;
const TInt KChargeCardPinSize=8;

typedef TBuf<KChargeCardRuleSize> TChargeCardRule ;
typedef TBuf<KChargeCardAccountNumberSize> TChargeCardAccount ;
typedef TBuf<KChargeCardPinSize> TChargeCardPin;

class TChargeCard
	{
public:
	IMPORT_C TChargeCard () ;
	IMPORT_C TChargeCard( 
				const TChargeCardAccount& aNumber,
				const TChargeCardPin&  aPin ,
				const TChargeCardRule& aLocalRule,
				const TChargeCardRule& aNatRule,
				const TChargeCardRule& aIntlRule) ;

	IMPORT_C void SetNumber(const TDesC&);
	IMPORT_C void SetPin(const TDesC&);
	IMPORT_C void SetLocalRule (const TDesC&);
	IMPORT_C void SetNatRule(const TDesC&);
	IMPORT_C void SetIntlRule(const TDesC&);

	IMPORT_C TBool ValidateChargeCardInfo() const;
	IMPORT_C TPtrC Number() const;
	IMPORT_C TPtrC Pin() const;
	IMPORT_C TPtrC LocalRule () const;
	IMPORT_C TPtrC NatRule() const;
	IMPORT_C TPtrC IntlRule() const;
private:

	TChargeCardAccount iNumber;
	TChargeCardPin	iPin;
	TChargeCardRule iLocalRule;
	TChargeCardRule iNatRule;
	TChargeCardRule iIntlRule;
	};

// Dial Location
enum TParseMode
	{
	EForDialing,
	EForDisplay
	} ;

const TInt KDialOutLocalCodeSize=4;
const TInt KDialOutLongDistanceCodeSize=4;
const TInt KDisableCallWaitingCodeSize=8;
const TInt KPhoneNumberSize=100;

typedef	TBuf<KDialOutLocalCodeSize> TDialOutLocalCode ;
typedef	TBuf<KDialOutLongDistanceCodeSize> TDialOutLongDistanceCode ;
typedef	TBuf<KDisableCallWaitingCodeSize> TDisableCallWaitingCode ;
typedef TBuf<KPhoneNumberSize> TPhoneNumber ;


enum {
	KPhoneNumberMobile              =0x00000001,
	KPhoneNumberUsePulseDial        =0x00000002,
	KPhoneNumberPbxUsePulseDial     =0x00000004,
	KPhoneNumberWaitForDialingTone  =0x00000008,
	KPhoneNumberWaitForProceedTone  =0x00000010,
    KReturnPhoneNumberWithPlusFormat=0x00000020
	};

const TInt KPhoneNumberDefaultFlags=KPhoneNumberUsePulseDial;

class TDialLocation
	{
public:
	IMPORT_C TDialLocation() ;
	IMPORT_C TDialLocation(
		const TIntlPrefCode & aIntlPrefCode,
		const TNatPrefCode& aNatPrefCode,
		const TNatCode& aNatCode,
		const TAreaCode& aAreaCode,
		const TDialOutLocalCode& aDialOutLocalCode,
		const TDialOutLongDistanceCode& aDialOutLongDistanceCode,
		const TDisableCallWaitingCode& aDisableCallWaitingCode,
		TUint aFlags,
		TUint aPauseAfterDialout ) ;

	IMPORT_C	void SetIntlPrefCode(const TDesC&) ;
	IMPORT_C	void SetNatPrefCode(const TDesC&);
	IMPORT_C	void SetNatCode(const TDesC&);
	IMPORT_C	void SetAreaCode(const TDesC&);
	IMPORT_C	void SetDialOutLocalCode(const TDesC&);
	IMPORT_C	void SetDialOutLongDistanceCode(const TDesC&);
	IMPORT_C	void SetDisableCallWaitingCode(const TDesC&);
	IMPORT_C	void SetDialLocationFlags (TUint);
	inline  	void ClearDialLocationFlags (TUint);
	IMPORT_C	void SetPauseAfterDialout ( TUint);
	IMPORT_C TPtrC IntlPrefCode() const ;
	IMPORT_C TPtrC NatPrefCode() const;
	IMPORT_C TPtrC NatCode() const;
	IMPORT_C TPtrC AreaCode() const;
	IMPORT_C TPtrC DialOutLocalCode() const;
	IMPORT_C TPtrC DialOutLongDistanceCode() const;
	IMPORT_C TPtrC DisableCallWaitingCode() const;
	IMPORT_C TInt  PauseAfterDialout () const;
	IMPORT_C TBool IsMobile () const ;
    inline   TBool IsReturnPhoneNumberWithPlusFormat() const;
	IMPORT_C TBool IsUsePulseDial () const;
	IMPORT_C TBool IsPbxUsePulseDial () const ;
	IMPORT_C TBool IsWaitForDialingTone () const ;
	IMPORT_C TBool IsWaitForProceedTone () const;
	IMPORT_C TBool IsDialOutRequired () const;
	IMPORT_C TBool IsDisableCallWaitingCode() const;

private:
	TIntlPrefCode iIntlPrefCode;
	TNatPrefCode iNatPrefCode;
	TNatCode iNatCode;
	TAreaCode iAreaCode;
	TDialOutLocalCode iDialOutLocalCode;
	TDialOutLongDistanceCode iDialOutLongDistanceCode;
	TDisableCallWaitingCode iDisableCallWaitingCode;
	TUint iFlags;
	TUint iPauseAfterDialout;
};

// TCityDialCodes for time world resolver
// --------------------------------------
enum TPlusFormatDialOptions
	{
	EPlusFormatDialNotAllow ,
	EPlusFormatDialAllow
	};

enum TCityDialOptions
	{
	EDialCityStripDuplicateAreaCode,
	EDialCityAllowDuplicateAreaCode
	};

class TCityDialCodes
{
public:
TAreaCode iAreaCode;
TNatCode iNatCode;
TNatPrefCode iNatPref;
TIntlPrefCode iIntlPref;
};


// Main interface

class TelephoneNumber
{
public:
IMPORT_C static TInt Parse( 
              TDialString& aDialString ,
			  const TDialLocation& aDialLocation , 
			  const TChargeCard& aChargeCard,
			  const TDesC& aPhoneNumber,
			  TParseMode aParseMode ) ;

IMPORT_C static TInt Parse ( TDialString& aDialString ,
								const TDialLocation& aDialLocation, 
								const TDesC& aPhoneNumber ); 

IMPORT_C static TInt CalculateDialCityPrefix(
						TDialString& aDialString ,
						const TCityDialCodes& aFrom,
						const TCityDialCodes& aTo,
						TCityDialOptions aOption,
						TChar aCodeSeparator ,
						TPlusFormatDialOptions aPlusOption ) ;
//
IMPORT_C static TInt Parse ( TDialString& aDialString ,
								const TDialLocation& aDialLocation, 
								const TDesC& aPhoneNumber, 
								TCityDialOptions aOption) ;
};

#include<DIAL.INL>

#endif
