/*
* ============================================================================
*  Name     : AknQueryValue.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknQueryValue.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUE_H__)
#define __AKNQUERYVALUE_H__


#include <eikenv.h>

class MDesCArray;

/**
 * Mixin class representing a value that is accessed as text.
 * <p> The Value can be changed by creating an editor dialog, 
 * which may be either a query or a setting page
 * or optionally by choosing an entry from an array of values. 
 * The array can be accessed as a descriptor array, and the value 
 * can be accessed as a descriptor.
 */
class MAknQueryValue
	{
public:
	enum TMode
		{
		EQueryMode,
		ESettingPageMode
		};
protected:
	enum TFlagBits
		{
		ESettingPageModeBitIndex = 0,
		EAutoAppendBitIndex		   // if set, the query value auto appends new values
		};
public:
	virtual ~MAknQueryValue() {}
	virtual const MDesCArray* MdcArray() const = 0;
	virtual HBufC* CurrentValueTextLC() = 0;
	virtual TInt CurrentValueIndex() const = 0;
	virtual void SetCurrentValueIndex(const TInt aIndex) = 0;
	virtual TBool CreateEditorL() = 0;
	virtual void SetQueryMode( MAknQueryValue::TMode aMode ) = 0;
	/**
	 * Override the default resource IDs used if a Setting Page mode query is put up.
	 * All Queryvalue implementations should have default resource set up. Hence this
	 * need not be called unless non-default resource is required.
	 *
	 * THE IMPLEMENTATION OF THESE RESOURCE OVERRIDES IS RESERVED FOR FUTURE VERSIONS
	 * OF SERIES 60. NOT CURRENTLY FUNCTIONAL. DO NOT USE.
	 *
	 * The rules for usage of these ids is the same as that for the CAknSettingPage constructors
	 * that take both these resources
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0					present				Editor resource is used via SP resource 
	 *			present					= 0					default SP resource for the query type is used + this editor resource
	 *
	 * The type of the editor resource is fixed. If editor resource override is being
	 * used, then the resource must be for that control type of editor used in the
	 * CAknQueryValueXXXX class.
	 * 
	 * @param aSettingPageResourceId		AVKON_SETTING_PAGE resource ID to use
	 * @param aSettingPageEditorResourceId	Editor resource ID to use (takes precedence)
	 *
	 */
	virtual void SetSettingPageResourceIds( 
		TInt aSettingPageResourceId, 
		TInt aSettingPageEditorResourceId ) = 0;
	/**
	 * Set the QueryValue to append a new user value, if distinct from former value 
	 *
	 */
	virtual void SetAutoAppend( TBool aAppend ) = 0;

protected:
	/**
	 * Method to add the current value to the QueryValueArray if it is new.
	 * The new value is not owned by QueryValue object, but is "given away"
	 *
	 */
	virtual void AppendValueIfNewL() = 0;
private:
	IMPORT_C virtual void Reserved_MAknQueryValue();
   };

/** 
 * Pure virtual class that adds some standard functionality
 *
 */
class CAknQueryValue : public CBase, public MAknQueryValue
	{
public:
	IMPORT_C virtual void SetQueryMode( MAknQueryValue::TMode aMode );
	IMPORT_C virtual void SetSettingPageResourceIds( TInt aSettingPageResourceId, TInt aSettingPageEditorResourceId );
	IMPORT_C virtual void SetAutoAppend( TBool aAppend );
	IMPORT_C virtual void AppendValueIfNewL();
protected:
	TBool IsValidIndex(TInt aIndex) 
	{
	if (MdcArray()->MdcaCount() < 1) return ETrue;
	if (aIndex < 0 || aIndex >= MdcArray()->MdcaCount())
	    return EFalse;
	return ETrue;
	}

protected:
	TBitFlags16	iFlags;
	TInt iSettingPageResourceId;
	TInt iSettingPageEditorResourceId;
private:
	TInt iSpare;
// from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();
	};

#endif // __AKNQUERYVALUE_H__

