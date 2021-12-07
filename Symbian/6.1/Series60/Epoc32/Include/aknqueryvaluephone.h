/*
* ============================================================================
*  Name     : AknQueryValuePhone.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknQueryValuePhone.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUEPHONE_H__)
#define __AKNQUERYVALUEPHONE_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValuePhoneArray;

/**
 * Encapsulates a string. Provides an interface to create a dialog
 * containing a phone number query control, which will edit the value. Optionally 
 * allows the value to be changed by selecting from a list of values. 
 *
 */
class CAknQueryValuePhone : public CAknQueryValue
    {
public:
	IMPORT_C static CAknQueryValuePhone* NewL();
	IMPORT_C static CAknQueryValuePhone* NewLC();
    IMPORT_C virtual ~CAknQueryValuePhone();
	IMPORT_C void SetArrayL(const CAknQueryValuePhoneArray* aArray);
	IMPORT_C void SetQueryCaption(TInt aResourceId);
	IMPORT_C HBufC* Value() const;
public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
protected:
	CAknQueryValuePhone();
	void ConstructL();
	void CalculateCurrentIndex();
	virtual void AppendValueIfNewL();
private: // from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();
private:
	// the following are member variables
	TInt iQueryCaptionId;
	HBufC* iText;
	TInt iCurrentIndex;
	// the following are not owned
	const CAknQueryValuePhoneArray* iArray;
    };


/**
 * Wraps a descriptor array.
 *
 */
class CAknQueryValuePhoneArray : public CBase, public MDesCArray
	{
public:
	typedef CDesCArray TextArray;
	enum {KSafeSizeOfDescriptorForPhoneFormat = 64};
public:
	IMPORT_C static CAknQueryValuePhoneArray* NewL();
	IMPORT_C static CAknQueryValuePhoneArray* NewLC();
	IMPORT_C ~CAknQueryValuePhoneArray();
	IMPORT_C void SetArray(TextArray& aArray);
	IMPORT_C TextArray* Array() const;
	IMPORT_C const TInt FormattedStringSize() const;
public:
	// from MDesCArray
    IMPORT_C virtual TInt MdcaCount() const;
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
protected:
	CAknQueryValuePhoneArray();
	void ConstructL();
private:
	// the following members are not owned
	TextArray* iArray;
	TInt iFormattedStringSize;
	};

#endif // __AKNQUERYVALUEPHONE_H__

