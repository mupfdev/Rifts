/*
* ============================================================================
*  Name     : AknQueryValueNumber.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknQueryValueNumber.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUENUMBER_H__)
#define __AKNQUERYVALUENUMBER_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValueNumberArray;

/**
 * Encapsulates a TInt. Provides an interface to create a dialog
 * containing a number query control, which will edit the value. Optionally 
 * allows the value to be changed by selecting from a list of values. 
 *
 */
class CAknQueryValueNumber : public CAknQueryValue
    {
public:
	IMPORT_C static CAknQueryValueNumber* NewL();
	IMPORT_C static CAknQueryValueNumber* NewLC();
    IMPORT_C virtual ~CAknQueryValueNumber();
	IMPORT_C void SetArrayL(const CAknQueryValueNumberArray* aArray);
	IMPORT_C void SetQueryCaption(TInt aResourceId);
	IMPORT_C TInt Value() const;
public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
protected:
	CAknQueryValueNumber();
	void ConstructL();
	void CalculateCurrentIndex();
	virtual void AppendValueIfNewL();
private: // from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();
private:
	// the following are member variables
	TInt iQueryCaptionId;
	TInt iNumber;
	TInt iCurrentIndex;
	// the following are not owned
	const CAknQueryValueNumberArray* iArray;
    };


/**
 * Wraps an array of numeric values, adapts it into a descriptor array.
 *
 */
class CAknQueryValueNumberArray : public CBase, public MDesCArray
	{
public:
	typedef CArrayFix<TInt> NumberArray;
	enum {KSafeSizeOfDescriptorForNumberFormat = 32};
public:
	IMPORT_C static CAknQueryValueNumberArray* NewL(TInt aResourceId);
	IMPORT_C static CAknQueryValueNumberArray* NewLC(TInt aResourceId);
	IMPORT_C ~CAknQueryValueNumberArray();
	IMPORT_C void SetArray(NumberArray& aArray);
	IMPORT_C NumberArray* Array() const;
	IMPORT_C const HBufC* FormatString() const;
	IMPORT_C const TInt FormattedStringSize() const;
public:
	// from MDesCArray
    IMPORT_C virtual TInt MdcaCount() const;
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
protected:
	CAknQueryValueNumberArray();
	void ConstructL(TInt aResourceId);
private:
	// the following members are owned
	HBufC* iLastGeneratedTextValue;
	HBufC* iFormatString;
	// the following members are not owned
	NumberArray* iArray;
	TInt iFormattedStringSize;
	};


#endif // __AKNQUERYVALUENUMBER_H__

