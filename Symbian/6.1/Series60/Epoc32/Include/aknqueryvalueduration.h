/*
* ============================================================================
*  Name     : AknQueryValueDuration.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknQueryValueDuration.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUEDURATION_H__)
#define __AKNQUERYVALUEDURATION_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValueDurationArray;

/**
 * Encapsulates a TTimeIntervalSeconds. Provides an interface to create a dialog
 * containing a duration query control, which will edit the value. Optionally 
 * allows the value to be changed by selecting from a list of values. 
 *
 */
class CAknQueryValueDuration : public CAknQueryValue
    {
public:
	IMPORT_C static CAknQueryValueDuration* NewL();
	IMPORT_C static CAknQueryValueDuration* NewLC();
    IMPORT_C virtual ~CAknQueryValueDuration();
	IMPORT_C void SetArrayL(const CAknQueryValueDurationArray* aArray);
	IMPORT_C void SetQueryCaption(TInt aResourceId);
	IMPORT_C TTimeIntervalSeconds Value() const;
public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
protected:
	CAknQueryValueDuration();
	void ConstructL();
	void CalculateCurrentIndex();
	virtual void AppendValueIfNewL();
private: // from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();
private:
	// the following are member variables
	TInt iQueryCaptionId;
	TTimeIntervalSeconds iDuration;
	TInt iCurrentIndex;
	// the following are not owned
	const CAknQueryValueDurationArray* iArray;
    };


/**
 * Wraps an array of numeric values, adapts it into a descriptor array.
 *
 */
class CAknQueryValueDurationArray : public CBase, public MDesCArray
	{
public:
	typedef CArrayFix<TTimeIntervalSeconds> DurationArray;
	enum {KSafeSizeOfDescriptorForDurationFormat = 32};
public:
	IMPORT_C static CAknQueryValueDurationArray* NewL(TInt aResourceId);
	IMPORT_C static CAknQueryValueDurationArray* NewLC(TInt aResourceId);
	IMPORT_C ~CAknQueryValueDurationArray();
	IMPORT_C void SetArray(DurationArray& aArray);
	IMPORT_C DurationArray* Array() const;
	IMPORT_C const HBufC* FormatString() const;
	IMPORT_C const TInt FormattedStringSize() const;
	IMPORT_C void FormatDuration(TPtr& aText, TTimeIntervalSeconds aDuration) const;
public:
	// from MDesCArray
    IMPORT_C virtual TInt MdcaCount() const;
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
protected:
	CAknQueryValueDurationArray();
	void ConstructL(TInt aResourceId);
private:
	// the following members are owned
	HBufC* iLastGeneratedTextValue;
	HBufC* iFormatString;
	// the following members are not owned
	DurationArray* iArray;
	TInt iFormattedStringSize;
	};


#endif // __AKNQUERYVALUEDURATION_H__

