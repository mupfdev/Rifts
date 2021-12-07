// MIUTPARS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__MIUTPARS_H__)
#define __MIUTPARS_H__

#include <e32base.h>

// comment out line below to switch ON Internet message checking
//#define __NO_EMAIL_ADDRESS_CHECKING__

class TImMessageField
	{
public:
	/*
	//	ValidInternetEmailAddress()
	//
	//	Returns ETrue if:
	//	- the string supplied to it contains only one valid email address
	//		(the email address can contain aliases and comments)
	//
	//	Returns EFalse:
	//	- otherwise.
	*/
	IMPORT_C TBool ValidInternetEmailAddress(const TDesC16& aAddress);
	IMPORT_C TBool ValidInternetEmailAddress(const TDesC16& aAddress, TInt& rFirstBadCharPos);	
	IMPORT_C TBool ValidInternetEmailAddress(const TDesC16& aAddress, TInt& rFirstChar, TInt& rLastChar);
	IMPORT_C TBool ValidInternetEmailAddress(const TDesC16& aAddress, TInt& rFirstChar, TInt& rLastChar, TInt& rFirstBadCharPos);

	/*
	//	ValidInternetEmailAddressChar()
	//
	//	Returns ETrue if:
	//	- the character is not a 'bad' character
	//	
	//	Returns EFalse:
	//	- otherwise.
	*/
	IMPORT_C TBool ValidInternetEmailAddressChar(const TChar& aChar);	

	/*
	//	ValidSubjectLine()
	//
	//	Returns ETrue if:
	//	- the subject line contains no bad characters
	//	
	//	Returns EFalse:
	//	- otherwise.
	*/
	IMPORT_C TBool ValidSubjectLine(const TDesC16& aSubjectLine);
	IMPORT_C TBool ValidSubjectLine(const TDesC16& aSubjectLine, TInt& rFirstBadCharPos);
	
	/*
	//	ValidSubjectLineChar()
	//
	//	Returns ETrue if:
	//	- the character is not a 'bad' character
	//	
	//	Returns EFalse:
	//	- otherwise.
	*/
	IMPORT_C TBool ValidSubjectLineChar(const TChar& aChar);
	
	/*
	//	ValidAliasName()
	//
	//	Returns ETrue if:
	//	- the alias name contains no bad characters
	//	
	//	Returns EFalse:
	//	- otherwise.
	*/
	IMPORT_C TBool ValidAliasName(const TDesC16& aAliasName);
	IMPORT_C TBool ValidAliasName(const TDesC16& aAliasName, TInt& rFirstBadCharPos);

	/*
	//	GetValidInternetEmailAddressFromString()
	//
	//	Returns a valid email address from a string without aliases/comments if:
	//	- the string supplied to it contains a valid email address
	//
	//	Returns NULL:
	//	- otherwise.
	*/
	IMPORT_C TPtrC16 GetValidInternetEmailAddressFromString(const TDesC16& aAddress);
	IMPORT_C TPtrC16 GetValidInternetEmailAddressFromString(const TDesC16& aAddress, TInt& rError);
	IMPORT_C TPtrC16 GetValidInternetEmailAddressFromString(const TDesC16& aAddress, TInt& rFirstChar, TInt& rLastChar);
	IMPORT_C TPtrC16 GetValidInternetEmailAddressFromString(const TDesC16& aAddress, TInt& rFirstChar, TInt& rLastChar, TInt& rError);

	/*
	//	GetValidAlias()
	//
	//	Returns a valid alias if:
	//	- the string supplied to it contains a valid alias
	//
	//	Returns NULL:
	//	- otherwise.
	*/
	IMPORT_C TPtrC16 GetValidAlias(const TDesC16& aAddress);
	IMPORT_C TPtrC16 GetValidAlias(const TDesC16& aAddress, TInt& rError);

	/*
	//	GetValidComment()
	//
	//	Returns a valid comment if:
	//	- the string supplied to it contains a valid comment
	//
	//	Returns NULL:
	//	- otherwise.
	*/
	IMPORT_C TPtrC16 GetValidComment(const TDesC16& aAddress);
	IMPORT_C TPtrC16 GetValidComment(const TDesC16& aAddress, TInt& rError);

private:
	TBool isValidEmailAddress(const TDesC16& aAddress, TInt& rFirstChar, TInt& rLastChar);
	TBool isLegalEmailAddress(const TDesC16& aAddress, TInt& rFirstChar, TInt& rLastChar);
	TBool isSurroundedByRoundBrackets(const TDesC16& aAddress, TInt& rFirstChar, TInt& rLastChar);
	TBool isSurroundedByAngledBrackets(const TDesC16& aAddress, TInt& rFirstChar, TInt& rLastChar);
	TBool isEnclosedSubString(const TDesC16& anAddress, const TChar& aLeftBracket, const TChar& aRightBracket,TInt& aLeftPos, TInt& aRightPos);
    TBool isValidString(const TDesC16& anAddress, TInt& aFirstBadCharPos);
	TBool isValidChar(const TChar& aChar);
    TBool isValidEmailString(const TDesC16& anAddress, TInt& aFirstBadCharPos);
	TBool isValidEmailChar(const TChar& aChar);
	TBool LocateSubString(const TDesC16& anAddress, const TInt atPos, TInt& rFirstChar, TInt& rLastChar);	
	TBool hasAngledBrackets(const TDesC16& anAddress);
	TBool isValidRoutedEmailAddress(const TDesC16& anAddress);
	};


#endif // !defined __MIUTPARS_H__

