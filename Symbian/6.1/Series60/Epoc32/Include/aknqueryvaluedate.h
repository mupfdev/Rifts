/*
* ============================================================================
*  Name     : AknQueryValueDate.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknQueryValueDate.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUEDATE_H__)
#define __AKNQUERYVALUEDATE_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValueDateArray;

/**
 * Encapsulates a date value. Provides an interface to create a dialog
 * containing a time query control, which will edit the value. Optionally 
 * Allows the value to be changed by selecting from a list of values. 
 *
 */
class CAknQueryValueDate : public CAknQueryValue
    {
public:
	IMPORT_C static CAknQueryValueDate* NewL();
	IMPORT_C static CAknQueryValueDate* NewLC();
	IMPORT_C virtual ~CAknQueryValueDate();
	IMPORT_C void SetArrayL(const CAknQueryValueDateArray* aArray);
	IMPORT_C void SetQueryCaption(TInt aResourceId);
	IMPORT_C TTime Value() const;

public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
protected:
	CAknQueryValueDate();
	void ConstructL();
	void CalculateCurrentIndex();
	virtual void AppendValueIfNewL();
private: // from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();

private:
	// the following are member variables
	TInt iQueryCaptionId;
	TTime iTime;
	TInt iCurrentIndex;
	// the following are not owned
	const CAknQueryValueDateArray* iArray;
    };


/**
 * Wraps an array of dates, adapts it into a descriptor array.
 *
 */
class CAknQueryValueDateArray : public CBase, public MDesCArray
	{
public:
	typedef CArrayFix<TTime> TimeArray;
	enum {KSafeSizeOfDescriptorForTTimeFormat = 128};
public:
	IMPORT_C static CAknQueryValueDateArray* NewL(TInt aResourceId);
	IMPORT_C static CAknQueryValueDateArray* NewLC(TInt aResourceId);
	IMPORT_C ~CAknQueryValueDateArray();
	IMPORT_C void SetArray(TimeArray& aArray);
	IMPORT_C TimeArray* Array() const;
	IMPORT_C const HBufC* FormatString() const;
	IMPORT_C const TInt FormattedStringSize() const;
public:
	// from MDesCArray
    IMPORT_C virtual TInt MdcaCount() const;
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
protected:
	CAknQueryValueDateArray();
	void ConstructL(TInt aResourceId);
private:
	// the following members are owned
	HBufC* iLastGeneratedTextValue;
	HBufC* iFormatString;
	// the following members are not owned
	TimeArray* iArray;
	TInt iFormattedStringSize;
	};

#endif // __AKNQUERYVALUEDATE_H__

