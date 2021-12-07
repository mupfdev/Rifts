/*
* ============================================================================
*  Name     : AknQueryValueTime.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknQueryValueTime.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUETIME_H__)
#define __AKNQUERYVALUETIME_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValueTimeArray;

/**
 * Encapsulates a TTime value. Provides an interface to create a dialog
 * containing a time query control, which will edit the value. Optionally 
 * Allows the value to be changed by selecting from a list of values. 
 *
 */
class CAknQueryValueTime : public CAknQueryValue
    {
public:
	IMPORT_C static CAknQueryValueTime* NewL();
	IMPORT_C static CAknQueryValueTime* NewLC();
    IMPORT_C virtual ~CAknQueryValueTime();
	IMPORT_C void SetArrayL(const CAknQueryValueTimeArray* aArray);
	IMPORT_C void SetQueryCaption(TInt aResourceId);
	IMPORT_C TTime Value() const;
public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
protected:
	CAknQueryValueTime();
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
	const CAknQueryValueTimeArray* iArray;
    };


/**
 * Wraps an array of TTime, adapts it into a descriptor array.
 *
 */
class CAknQueryValueTimeArray : public CBase, public MDesCArray
	{
public:
	typedef CArrayFix<TTime> TimeArray;
	enum {KSafeSizeOfDescriptorForTTimeFormat = 128};
public:
	IMPORT_C static CAknQueryValueTimeArray* NewL(TInt aResourceId);
	IMPORT_C static CAknQueryValueTimeArray* NewLC(TInt aResourceId);
	IMPORT_C ~CAknQueryValueTimeArray();
	IMPORT_C void SetArray(TimeArray& aArray);
	IMPORT_C TimeArray* Array() const;
	IMPORT_C const HBufC* FormatString() const;
	IMPORT_C const TInt FormattedStringSize() const;
public:
	// from MDesCArray
    IMPORT_C virtual TInt MdcaCount() const;
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
protected:
	CAknQueryValueTimeArray();
	void ConstructL(TInt aResourceId);
private:
	// the following members are owned
	HBufC* iLastGeneratedTextValue;
	HBufC* iFormatString;
	// the following members are not owned
	TimeArray* iArray;
	TInt iFormattedStringSize;
	};

#endif // __AKNQUERYVALUETIME_H__

