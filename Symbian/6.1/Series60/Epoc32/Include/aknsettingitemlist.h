/*
* ============================================================================
*  Name     : AknSettingItemList.h
*  Part of  : Avkon
*
*  Description:
*     Support for Setting Item Lists (See Selection Service specification)
*		Contains setting item classes (whole hierarchy) and the 
*		array classes used to set up the setting item listbox
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#if !defined(__AKNSETTINGITEMLIST_H__)
#define __AKNSETTINGITEMLIST_H__

#include <in_sock.h>
// For coecontrol
#include <coecntrl.h>

// For graphics API
#include <gulicon.h>

// For CEikFormattedListBox
#include <eikfrlb.h>

// For setting page
#include <aknsettingpage.h>

// For query stuff
#include <aknqueryvaluetext.h>


// Maximum length of the blanking text
const TInt KMaxPasswordBlankingTextLength = 10;


/**
* CAknSettingItem is the base class for all setting items. The abstracted functionality
* is implemented in this class if possible.  
*
* All array of setting items is held in CAknSettingItemArray, which in turn is owned by
* CAknSettingItemList, a listbox type.
* 
*/
class CAknSettingItem : public CBase, public MAknSettingPageObserver
	{

friend class CAknSettingItemArray;

public:
	enum TFlags
		{
		EIsHidden = 0x1,
		EHasIcon = 0x2,
		EIsNumberedStyle = 0x4
		} ;
public:
	/**
	* Constructor
	*
	* @param the unique identifier fo the setting item (not its number)
	*/
	IMPORT_C CAknSettingItem( TInt identifier );

	/**
	* Destructor
	*/
	IMPORT_C ~CAknSettingItem();

	/**
	* 
	* 2nd-stage constuctor.  Resource for setting item is read externally in setting item list
	* and the values are passed here.
	*/
	IMPORT_C void ConstructL( 
		const TBool aIsNumberedStyle,
		const TInt aOrdinal, 
		const TDesC& aSettingTitle, 
		CArrayPtr<CGulIcon>* aIconArray,
		const TInt aSettingPageResource, 
		const TInt aEditorControlType,
		const TInt aSettingEditorResource = 0, 
		const TInt aAssociatedResource = 0 );
	
	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();
	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*/
	IMPORT_C virtual void LoadL(); 
	/**
	*
	* This launches the setting page 
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );
	/**
	*
	* This method is called by framework in order to update the text in the setting
	* item.  It may be called by the client.
	*
	*/
	IMPORT_C virtual void UpdateListBoxTextL();

	/**
	* Access to the setting Name 
	*.@return	the setting name
	*/
	IMPORT_C TPtrC SettingName();
	/**
	* Access to the setting number
	* @return the setting number
	*/
	IMPORT_C TInt SettingNumber() const;
	/**
	* Access to the setting visibility
	* @return ETrue if the setting item is hidden
	*/
	IMPORT_C TBool IsHidden() const;
	/**
	* Access to the numbering style of the setting item
	* @return	ETrue if it is numbered
	*/
	IMPORT_C TBool IsNumberedStyle() const;
	/**
	* Set the visibility 
	* @param		Set to Etrue to hide the item; EFalse to make it visible
	*
	*				Note that the setting item array must have be notified of this
	*				by calling CAknSettingItemList::HandleChangeInItemArrayOrVisibility
	*/
	IMPORT_C void SetHidden(TBool aHidden );
	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();
	/**
	* This gives access to the listbox text content at this item (fully decorated)
	*
	* @return	pointer to listboxtext. No allocation is performed and no change of ownership
	*/
	IMPORT_C HBufC* ListBoxText();
	/**
	* Access to the setting item's identifier. This is set in the setting item's constructor
	* but usually comes via resource in the setting item list read of its resource structure
	*
	* @return The identifier of this setting item
	*/
	IMPORT_C TInt Identifier() const;
	/**
	* Checks if the setting item has a bitmap in its setting contents 
	* @return	ETrue if it has a bitmap
	*/
	IMPORT_C TBool HasIcon() const;
	/**
	* This sets the text to display if the current setting is empty. 
	*
	* @param		text to make display when there is empty setting. A copy is made in the setting item
	*/
	IMPORT_C void SetEmptyItemTextL( const TDesC& aEmptyItemText );
	IMPORT_C void SetCompulsoryIndTextL( const TDesC& aCompulsoryInd );

	// From MAknSettingPageObserver
	IMPORT_C virtual void HandleSettingPageEventL(CAknSettingPage* aSettingPage,TAknSettingPageEvent aEventType );
	/**
	* Get the index at which this item appears in the listbox
	*
	* @return index in listbox
	*/
	IMPORT_C TInt VisibleIndex();

	/**
	* Set the flags that are required for some of the setting page constructors
	*
	* @param aFlagPattern	Flag pattern to set
	*/
	IMPORT_C void SetSettingPageFlags( TInt aFlagPattern);

	/**
	* Access method for the setting page specific flags
	* @return the flag pattern
	*/
	IMPORT_C TInt SettingPageFlags( ) const;

protected:


	/**
	* Method called by framework to complete the construction.  Extra allocations of
	* memory or extra resource reading can happen here.
	*
	*/
	IMPORT_C virtual void CompleteConstructionL();
	/**
	*
	* Method to obtain a new bitmap for the setting content
	*
	* This method is usually empty in setting items classes except for volume and slider
	*
	*/
	IMPORT_C virtual CFbsBitmap* CreateBitmapL();

// Utilities
	/**
	*
	* A setting page should know when it is "Editing". This is set in EditItemL
	* and cleared to 0 when the dialog is finished.
	*
	* @param		pointer to the currently executing settting page dialog
	*
	*/
	IMPORT_C void SetSettingPage( CAknSettingPage* aSettingPage );
	/*
	* Access to the current setting page
	*
	* @return	pointer to the currently executing setting page. 0 if there is none
	*/
	IMPORT_C CAknSettingPage* SettingPage() const;
	/**
	* Performs standard setup on a setting page
	*
	*/
	IMPORT_C void SetUpStandardSettingPageL();
	/**
	* Access to the empty text that has been set, or is default
	*
	* @return	ref to empty text descriptor
	*/
	IMPORT_C TDesC& EmptyItemText() const; // Assumed only needs to be used by SettingTextL

	/**
	* Access to the setting page resource id that might have been read by
	* the setting item resource.
	* 
	* @return	0 or the setting page resource id
	*/
	IMPORT_C TInt SettingPageResourceId() const;
	/**
	* Access to the setting page editor's resource id that might have been read by
	* the setting item resource.
	* 
	* @return	0 or the setting page editor's id
	*/
	IMPORT_C TInt SettingEditorResourceId() const;
	/**
	* Returns the associate editor resource.  This is an LLINK in the seting item 
	* resource that subclasses can use in CompleteContstructionL
	*
	* @return	0 or the extra resource id
	*/
	IMPORT_C TInt AssociatedResourceId() const;
	/**
	* 
	* @return the control type of the settin page editor
	*
	*/
	TInt EditorControlType() const;

private:
	/**
	* This routine causes any bitmaps that are extracted from setting pages to be updated
	* according to the current (internal) setting value
	*/
	void UpdateBitmapL();

	/**
	* Set the index at which the item is to appear in the setting item list 
	* Only needed by CAknSettingItemArray
	*/
	void SetVisibleIndex( TInt aVisibleIndex );

	/**
	* Set the ordinal value.  This is used for dynamic changing of the ordinal by 
	* CAknSettingItemArray
	*
	*/
	void SetOrdinal( TInt aOrdinal );

	/**
	*
	* Clean up a setting text for display by replacing all non printing characters 
	* by spaces
	*
	*/
	TPtrC ReplaceNonPrintingCharacters( TDes& aTextToClean );
private:
	IMPORT_C void CAknSettingItem_Reserved();

private:
	TUint iFlags;
	TInt iIdentifier;
	TInt iOrdinal;
	TInt iSettingIdentifier;
	TInt iSettingPageResourceId;
	TInt iEditorControlType;
	TInt iSettingEditorResourceId;
	TInt iAssociatedResourceId;
	TInt iIconIndex; // Only valid if relevant bit is set in iFlags
	HBufC* iEmptyItemText; // Owned 

	HBufC* iSettingName;  // Owned
	HBufC* iListBoxText;  // Owned
	HBufC* iCompulsoryText; // Owned


	// Following are not owned
	CAknSettingPage* iSettingPage; // This is a ref that is valid when non-0 - when the SP is "up"
	CArrayPtr<CGulIcon>* iIconArray;	// Reference to the array only !

	TInt iVisibleIndex;
	// Set flags that are in the Setting pages' constructors 
	TInt iSettingPageFlags;
	TInt iSpare_1;
	TInt iSpare_2;
	};

/**
* Support for abstact text setting type.  Corresponds to CAknTextSettingPage
*
*/
class CAknTextSettingItem : public CAknSettingItem
{
public:
	/*
	* Constructor 
	*
	* @param		resource identifier for this setting item
	* @param		Setting text
	*
	*/
	IMPORT_C CAknTextSettingItem( TInt aIdentifier, TDes& aText );

	/**
	* Destructor
	*/ 
	IMPORT_C ~CAknTextSettingItem();

	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();

	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*/
	IMPORT_C virtual void LoadL(); // Called from 2nd stage constructors

	/*
	* This method obtains the current value's setting text.
	* 
	* The reference is returned and is not a copy of the text, but refers to the current
	* internal text value.  This is the value that would be externalized if StoreL were called. 
	* An exception to this is if the current text is zero length. In that case a reference to the 
	* empty text is returned (which would not be externalized if StoreL is called).
	*
	* @return	Reference to descriptor with the current internal text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();

	/**
	*
	* This launches the setting page for text editing
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

protected:

	/**
	*  Access for re-implementors to the internal text 
	*
	* @return	reference to a TPtr holding the internal text
	*/
	IMPORT_C TPtr& InternalTextPtr();

	/**
	*  Access for re-implementors to the external text
	*
	* @return	TPtrC pointing to the external text
	*/
	IMPORT_C TPtrC ExternalText();

	/**
	* Allows re-implementors to set the external text
	* No change of ownership is implied.
	*
	* @param	 a reference to the external text
	*
	*/
	IMPORT_C void SetExternalText( TDesC& aNewExternalText );
private:
	IMPORT_C void CAknSettingItem_Reserved();

private:
	TDes& iExternalText;
	HBufC* iInternalText;	// Owned
	TPtr iInternalTextPtr;
	TInt iSpare_Text_1;
};


/**
*
* Abstract setting item for integer editing. 
* 
* This class is not disposed toward any particular type of setting page
*
*/
class CAknIntegerSettingItem : public CAknSettingItem 
	{
	public:
	/*
	* Constructor 
	*
	* @param		resource identifier for this setting item
	* @param		integer value to edit. 
	*
	*/
	IMPORT_C CAknIntegerSettingItem( TInt aIdentifier, TInt& aValue );
	IMPORT_C ~CAknIntegerSettingItem();
	
	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();
	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*/
	IMPORT_C virtual void LoadL();

	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();

	/**
	*
	* Pure virtual editItemL
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu ) = 0;

	protected:
	/**
	* Method called by framework to complete the construction.  Extra allocations of
	* memory or extra resource reading can happen here.
	*
	*/
	IMPORT_C virtual void CompleteConstructionL();

	/**
	* Method to access the internal value. 
	*
	* @return	 a reference to the internal integer value
	*/
	IMPORT_C TInt& InternalValueRef();

	/**
	* Method to access the external reference to the external value. Note that this class
	* only accesses the external integer via a copy of a reference to it.
	*
	* @return	 a reference to the external integer value
	*/
	IMPORT_C TInt& ExternalValueRef();
	
	/**
	* Sets the external value's reference.  The external vlue is externally owned, so
	* this does not make a copy.
	* @param	TInt& aValue	a reference to the external value	
	*/
	IMPORT_C void SetExternalValue( TInt& aValue );
private:
	IMPORT_C void CAknSettingItem_Reserved();

	private:
	TInt iInternalValue;
	TInt& iExternalValue;
	HBufC* iInternalText;	// Owned
	TPtr iInternalTextPtr;
	};


class CAknIntegerEdwinSettingItem : public CAknIntegerSettingItem 
	{
	public:
	IMPORT_C CAknIntegerEdwinSettingItem( TInt aIdentifier, TInt& aValue );
	/**
	*
	* This launches the setting page for editing using the integer edwin class
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );
private:
	IMPORT_C void CAknSettingItem_Reserved();
	};

/**
*
* Class for holding a password setting item
*
*/
class CAknPasswordSettingItem : public CAknTextSettingItem
{
public:
	enum TAknPasswordSettingItemMode
		{
		EAlpha,		// password held is alphanumeric
		ENumeric	// password is numeric ( digits 0 - 9 only used )
		};

	/*
	* Constructor 
	*
	* @param		resource identifier for this setting item
	* @param		password mode; text or numeric
	* @param		password to change
	*/
	IMPORT_C CAknPasswordSettingItem( TInt aIdentifier, enum TAknPasswordSettingItemMode aMode, TDes& aPassword );

	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();
	/**
	*
	* This launches the setting page for password editing
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

protected:

	/**
	* Method called by framework to complete the construction.  Extra allocations of
	* memory or extra resource reading can happen here.
	*
	*/
	IMPORT_C virtual void CompleteConstructionL();
private:
	IMPORT_C void CAknSettingItem_Reserved();

private:
	TAknPasswordSettingItemMode iPasswordMode;
	// For holding the text to blank the setting item text
	TBuf<KMaxPasswordBlankingTextLength> iBlankingText;
	// For holding the resouce for a password query
	TInt iOldPasswordQueryResourceId;
};


/**
* An abstrct integer setting that uses the volume control as its editor
*
*/
class CAknVolumeSettingItem : public CAknSettingItem
	{
public:
	/*
	* Constructor 
	*
	* @param		resource identifier for this setting item
	* @param		volume value. Must be in range 0 to 10, inclusive
	*
	*/
	IMPORT_C CAknVolumeSettingItem( TInt aIdentifier, TInt& aExternalVolume );
	
	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();
	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*/
	IMPORT_C virtual void LoadL();
	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();
	/**
	*
	* This launches the setting page for volume editing
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

protected:
	/**
	* Protected access to the volume value
	*
	* @return	Reference to the internal volume value
	*/
	IMPORT_C TInt& InternalVolumeValue(); // For access to internal value for derived classes

	//From CAknSettingItem
	/**
	*
	* Obtain a bitmap from the CAknVolume
	*
	*/
	IMPORT_C virtual CFbsBitmap* CreateBitmapL();
private:
	IMPORT_C void CAknSettingItem_Reserved();

private:
	TInt& iExternalVolume;
	TInt iInternalVolume;

	};

/**
* Slider control setting item
*
*
*/

class CAknSliderSettingItem : public CAknSettingItem
	{
public:
	/*
	* Constructor 
	*
	* @param		resource identifier for this setting item
	* @param		Slider value; must be within the minimum and maximum values in resource
	*
	*/
	IMPORT_C CAknSliderSettingItem( TInt aIdentifier, TInt& aExternalSliderValue );

	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();
	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*/
	IMPORT_C virtual void LoadL(); 
	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();
	/**
	*
	* This launches the setting page for slider editing
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

protected:
	/**
	* Method to create a setting page 
	*/
	IMPORT_C virtual CAknSettingPage* CreateSettingPageL();

	/**
	* Method to contruct the setting page (via CreateSettingPageL), and execute it
	*/
	IMPORT_C virtual void CreateAndExecuteSettingPageL();

	/**
	* For access to internal value for derived classes
	*
	* @return	A ref to the internal value
	*/
	IMPORT_C TInt& InternalSliderValue();

	// From CAknSettingItem
	/**
	*
	* Obtain a bitmap from the CAknSlider
	*
	*/
	IMPORT_C virtual CFbsBitmap* CreateBitmapL();
private:
	IMPORT_C void CAknSettingItem_Reserved();

private:
	TInt& iExternalSliderValue;
	TInt iInternalSliderValue; // required for use in derived classes

	};

	
/**
*
* Time or Date Setting Item
*
* This class combines the time and the date functionality, as determined by a mode
* passed to the constructor.
*
* Time or Date setting pages are launched from here, which use Time or date editor 
* MFNEs to do the editing.
*
*/
class CAknTimeOrDateSettingItem : public CAknSettingItem
	{
public:
	enum TAknTimeOrDateSettingItemMode
		{
		ETime,
		EDate
		};
	/*
	* Constructor 
	*
	* @param		resource identifier for this setting item
	* @param		construct a Time or a Date setting item
	* @param		IP address to be controlled by the setting editing
	*
	*/
	IMPORT_C CAknTimeOrDateSettingItem( TInt aIdentifier, enum TAknTimeOrDateSettingItemMode aMode, TTime& aTime );
	/**
	* Destructor
	*/
	IMPORT_C ~CAknTimeOrDateSettingItem();
	/**
	* Method called by framework to complete the construction.  Extra allocations of
	* memory or extra resource reading can happen here.
	*
	*/
	IMPORT_C void CompleteConstructionL( );
	
	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();
	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*/
	IMPORT_C virtual void LoadL(); 
	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();
	/**
	*
	* This launches the setting page for Time or Date editing
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );
	/**
	*
	* Set the time or date format string.  If this is not called, then a 
	* localized, default string is used
	*
	*/
	IMPORT_C void SetTimeFormatStringL( const TDesC& aTimeFormat );
	/**
	*
	* Obtain the time format string
	*
	* @return	A pointer descriptor to the date/time format string
	*/
	IMPORT_C const TPtrC TimeFormatString();
private:
	IMPORT_C void CAknSettingItem_Reserved();
private:
	TTime& iExternalTime;
	TTime iInternalTime;
	HBufC* iInternalText; // Owned
	TPtr iInternalTextPtr;
	HBufC* iTimeFormat;
	TPtr iTimeFormatPtr;
	TAknTimeOrDateSettingItemMode iTimeOrDateMode;
	};


/**
*
* IP Address setting item
*
* Abstract data type for IP address setting. Launches a CAknIpFieldSettingPage 
* that in turn uses the CAknIpFieldEditor
*
*/
class CAknIpFieldSettingItem : public CAknSettingItem
	{
public:
	/*
	* Constructor 
	*
	* @param		resource identifier for this setting item
	* @param		IP address to be controlled by the setting editing
	*
	*/
	IMPORT_C CAknIpFieldSettingItem( TInt aIdentifier, TInetAddr& aIpAddress );
	/**
	*
	* Destructor
	*
	*/
	IMPORT_C ~CAknIpFieldSettingItem();
	
	/**
	* Method called by framework to complete the construction.  Extra allocations of
	* memory or extra resource reading can happen here.
	*
	*/
	IMPORT_C void CompleteConstructionL( );
	
	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();
	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*
	*/
	IMPORT_C virtual void LoadL(); // Called from 2nd stage constructors
	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();
	/**
	*
	* This launches the setting page for IP address editing
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );
private:
	IMPORT_C void CAknSettingItem_Reserved();

private:
	TInetAddr& iExternalIpAddress;
	TInetAddr iInternalIpAddress;
	HBufC* iInternalText; // Owned
	TPtr iInternalTextPtr;
	};

/**
* Base class for a data object to hold a pointer and a corresponding integer value.
* This is used to make a template class by CAknEnumeratedItem
*
*/
class CAknEnumeratedItemBase : public CBase
	{
public:
	/**
	* Construct an item consisting of an integer value and its co-ordinate pointer
	*/
	IMPORT_C CAknEnumeratedItemBase( TInt aEnumeratedValue, TAny* aValue );
	/**
	* Destructor
	*/
	IMPORT_C ~CAknEnumeratedItemBase();
	/** 
	* Access the integer value
	*
	* @return the integer value of this item
	*/
	IMPORT_C TInt EnumerationValue() const;
	/**
	* Set the integer part of the object
	*
	* @param aNewValue	Value to set
	*/
	IMPORT_C void SetEnumerationValue( TInt aNewValue );
	/**
	* Access the pointer part of the object
	*
	* @return TAny* pointer to any type
	*/
	IMPORT_C TAny* Value() const;
	/**
	* Set the pointer part of the object
	*
	* @param	pointer to store in the object; no copy madel, no ownership transfer
	*/
	IMPORT_C void SetValue( TAny* aPtr );
private:
	TInt iEnumerationValue;
	TAny* iValue;
	};


/**
* Makes a template class from CAknEnumeratedItemBase
*
*/
template <class T>
class CAknEnumeratedItem : public CAknEnumeratedItemBase
	{
public:
	inline CAknEnumeratedItem( TInt aEnumeratedValue, T* aValue );
	inline ~CAknEnumeratedItem();
	inline T* Value();
	inline void SetValue( T* );
	};


template <class T>
inline CAknEnumeratedItem<T>::CAknEnumeratedItem( TInt aEnumValue, T* aValue ) : 
	CAknEnumeratedItemBase( aEnumValue, (TAny*)aValue)
	{
	}

template <class T>
inline CAknEnumeratedItem<T>::~CAknEnumeratedItem()
	{
	delete (T*)Value();
	}

template <class T>
inline T* CAknEnumeratedItem<T>::Value()
	{
	return ( ( T* ) CAknEnumeratedItemBase::Value() );
	}

template <class T>
inline void CAknEnumeratedItem<T>::SetValue( T* aNewValue )
	{
	CAknEnumeratedItemBase::SetValue( aNewValue );
	}



/**
* Definition of CAknEnumeratedText
*/
typedef CAknEnumeratedItem<HBufC> CAknEnumeratedText;



/**
* CAknEnumeratedTextSettingItem
* 
* Abstract Base class for deriving listbox setting page related setting items
* 
* The class provides standard array support for these setting items and their
* listboxes.  Then approach is centred upon the CAknEnumeratedText type. 
*
* The texts are exposed to the user, and appear in two versions, if desired - the text shown
* in the setting list when not being edited, and the "popped-up" version of the texts.
* 
*/
class CAknEnumeratedTextSettingItem : public CAknSettingItem
	{
public:
	/**
	* Constructor.  Resource Id for the setting item
	*
	*/
	IMPORT_C CAknEnumeratedTextSettingItem( TInt aResourceId );

	/**
	* Destructor
	*/
	IMPORT_C ~CAknEnumeratedTextSettingItem();

//
// From CAknSettingItem
//
protected:

	/**
	*
	* Virtual method called by framework to complete the construction.  
	* In this class, the two arrays, pointers to which can be obtained by calling 
	* EnumeratedTextArray() and PoppedUpTextArray() are created.
	*
	*/
	IMPORT_C void CompleteConstructionL();

private:
	IMPORT_C void CAknSettingItem_Reserved();

public:

	/**
	* Access to the enumerated text array. Texts here are used in the setting item list
	* display.
	* No ownership of the array or its contents is transferred
	*
	* @return a pointer to an array of HBufC*s
	*/
	IMPORT_C CArrayPtr<CAknEnumeratedText>* EnumeratedTextArray() const;

	/**
	* Access to the "popped up" array of texts. They may be defined differently from 
	* those in the enumerated text array so that the setting page items can be different
	* from those displayed in the setting item editing list
	* No ownership of the array or its contents is transferred
	*
	* @return a pointer to an array of HBufC*s
	*/
	IMPORT_C CArrayPtr<HBufC>* PoppedUpTextArray() const;

	/**
	* Set the enumerated arrays. 
	* Ownership of these arrays and their contents is wholly given over to the setting item 
	* object.  The client must call HandleTextArrayUpdateL() after making this call.
	* 
	* After calling SetEnumeratedTextArrays(), it is the client code's responsibility to ensure that 
	* the current value of the external Tint value corresponds to one of the enumerated texts.  This can
	* be done, for instance, after calling SetEnumeratedTextArrays() by calling IndexFromValue() and
	* ensuring a return value of a valid index (not -1 ).  Otherwise, there will be a panic in 
	* HandleTextArrayUpdateL() when it is called.
	* 
	* This call transfers the ownership of the arrays, and the items pointed to by the arrays
	* 
	* @param	aEnumeratedTextArray	array of Integer-Text pairs to be the new basis for display
	*			This is the master array, and its Count() determines the number of entries to display
	* @param	aPoppedUpTextArray		array of Text descriptors that provide versions of the text
	*			to display in the setting page listbox.  The array pointer must be valid, but the 
	*			array need not contain any entries.  Only those entries that need to be different
	*			from those in aEnumeratedTextArray needs be present; 
	*/
	IMPORT_C void SetEnumeratedTextArrays( CArrayPtr<CAknEnumeratedText>* aEnumeratedTextArray,
													CArrayPtr<HBufC>* PoppedUpTextArray );
	/**
	* Called to execute any code that might need to run when the text arrays are replaced.
	* This class has a null implementation
	*
	*/
	IMPORT_C virtual void HandleTextArrayUpdateL();
	
	/** 
	* Access to the number of items in the arrays
	*
	* @return	The number of items in the array returned by EnumeratedTextArray()
	*/
	IMPORT_C TInt NumberOfItems() const;

	/**
	* Routine to find the index in the enumerated text list that corresponds to the value
	* passed in. 
	*
	* @param	aInputValue		value to search for in the enumerated items
	* @return	0 - based index in the item found. -1 if not found.
	*
	*/
	IMPORT_C TInt IndexFromValue( TInt aInputValue ) const;

protected:

	/**
	* Implementors of subclasses can call this non-virtual method to set up the list of texts
	* to be used for the setting page. (Although it is not useful for CAknCheckBoxSettingPage)
	* The list is constructed from the contents of the two 
	* text arrays, EnumeratedTextArray() and PoppedUpTextArray() . This is usually to be done 
	* "On the fly" immediately prior to the raising of a setting page. 
	*/
	IMPORT_C void SetSettingPageTextL();

	/** 
	* Accessor for the setting page text array
	*/
	IMPORT_C CDesCArray* SettingPageTextArray() const;

private:

	/**
	* The primary text arrays (those set by SetEnumeratedTextArrays) are deleted and their 
	* references zeroed.
	*/
	void DeleteAndZeroPrimaryArrays();

private:
	TInt iTextPopupFlags;
	CArrayPtr<CAknEnumeratedText>* iEnumeratedTextArray; // Owned and pointed to objects are owned
	CArrayPtr<HBufC>* iPoppedUpTextArray; // Owned and the HBufCs are owned here
	TInt iEnumeratedTextArrayResourceId;
	TInt iPoppedUpTextArrayResourceId;
	CDesCArrayFlat* iSettingPageText; // Owned
	HBufC* iSpare; // Formerly space was used by iEmptyText;
	};



/**
* Setting item type for CAknEnumeratedItems. 
* 
* The main use case for this is for list of texts that are being manipulated in the 
* client source code as a set of enumerations, while the texts, read from resource, 
* are not strongly exposed to the client.
*
* They are exposed to the user, and appear in two versions, if desired - the text shown
* in the setting list when not being edited, and the "popped-up" version of the texts.
*
*/
class CAknEnumeratedTextPopupSettingItem : public CAknEnumeratedTextSettingItem
	{
public:
	/**
	* Construct a list, storing in it a resource (to be read at 2nd stage construction)
	* and a reference to na externally owned integer - the value to be manipulated
	*
	*/
	IMPORT_C CAknEnumeratedTextPopupSettingItem( TInt aResourceId, TInt& aValue );

	/** 
	* Deprecated: To be removed
	*/
	IMPORT_C CAknEnumeratedTextPopupSettingItem(  TInt& aValue );

	/**
	* Destructor
	*/
	IMPORT_C ~CAknEnumeratedTextPopupSettingItem();
	
	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();

	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*/
	IMPORT_C virtual void LoadL(); 

	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();
	/**
	*
	* This launches the setting page for popup list setting page 
	*
	* @param		aCalledFromMenu - ignored in this class
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

public:
	/**
	* Access to the enumerated text array. Texts here are used in the setting item list
	* display.
	*
	* @return a pointer to an array of HBufC*s
	*/
	IMPORT_C CArrayPtr<CAknEnumeratedText>* EnumeratedTextArray() const;

	/**
	* Access to the "popped up" array of texts. They may be defined differently from 
	* those in the enumerated text arry
	*
	* @return a pointer to an array of HBufC*s
	*/
	IMPORT_C CArrayPtr<HBufC>* PoppedUpTextArray() const;

protected:
	/**
	* Framework method for constructing the launching setting page
	* @return	a constructed CAknSettingPage object on the heap
	*/
	IMPORT_C virtual CAknSettingPage* CreateSettingPageL();

	/**
	* Framework method to creaate and execute setting page
	*/
	IMPORT_C virtual void CreateAndExecuteSettingPageL();

	/**
	* Method called by framework to complete the construction.  Extra allocations of
	* memory or extra resource reading can happen here.
	*
	*/
	IMPORT_C virtual void CompleteConstructionL();

	/**
	* Sets the value of the (unowned) external value using the reference to it held 
	* internally. 
	* Note that this does not change the value of the reference itself.  
	* That is, aNewValue's address is not copied in to be used as the external reference.
	* @param	aNewValue	Value to be copied via the external reference.  
	*/
	IMPORT_C void SetExternalValue( TInt aNewValue );
	/** 
	* Sets the internal value. The value of aNewValue is copied into the internal storage
	* holding the internal value
	* @param aNewValue
	*/ 
	IMPORT_C void SetInternalValue( TInt aNewValue );

	/**
	* Set the item that is selected in the associated popup.  This should be done so
	* as to keep the selected index consistent with the internal value
	*
	* @param aNewIndex
	*/
	IMPORT_C void SetSelectedIndex( TInt aNewIndex );

	/**
	* Returns the index in the enuerated item array, given the value of the enueration 
	*
	* @param aInputValue	Value to look up; Returns -1 if value is not found
	*/
	IMPORT_C TInt IndexFromValue( TInt aInputValue ) const ;
	
	/**
	* Get the external value 
	* @return	TInt
	*/
	IMPORT_C TInt ExternalValue() const;
	/**
	* Access the internl value
	* @return	TInt
	*/
	IMPORT_C TInt InternalValue() const;
	/**
	* Return a reference to the MAknQueryValue that is constructed for the CAknPopupListSettingPagae
	* @return MAknQueryValue
	*/
	IMPORT_C MAknQueryValue* QueryValue() const;
private:
	IMPORT_C void CAknSettingItem_Reserved();

private:
	void SetSettingPageTextL();
	void CreateTextArrayL();
	void CreateQueryValueL();
	void UpdateInternalValuesL();
	/**
	*
	* This routine looks at the current enumeration values and returns the next integer
	* higher than the highest enumeration.  For internal use only, although it is possible
	* that clients or derivers might want to use somthing like it.
	*
	* @return a new unique value that can be used for extending the enumeration
	*/
	TInt FindNextEnumerationValue() const;

private:
	TInt& iExternalValue;
	TInt iInternalValue;
	TInt iNumberOfItems;
	TInt iSelectedIndex;
	CAknQueryValueText* iQueryValue;
	CAknQueryValueTextArray* iQueryTextArray; 
	TInt iSpare_EnumeratedTextPopup_1;
	};


class CAknBinaryPopupSettingItem : public CAknEnumeratedTextPopupSettingItem
	{
public:
	/**
	* Constructs a binary setting value, given a resource id and a reference to
	* an externally owned external boolen setting item.
	* Resource supplied is just as for CAknEnumeratedTextPopupSettingItem
	*
	* @param aIdentifier	Resource id for the associated values and texts; 
	*
	*/
	IMPORT_C CAknBinaryPopupSettingItem( TInt aIdentifier, TBool& aBinaryValue );

	/**
	* This command externalizes the current setting.  The displayed (internal) copy
	* is transferred to the external copy (the one referenced in the constructor).
	*
	* This must be called by the client if he wants this to happen.  Note that StoreAllL() 
	* on the setting item list will call this for each setting item.
	*/
	IMPORT_C virtual void StoreL();
	/*
	* The external value is transferred to the internal value
	* This occurs at construction, but may be called by client code when required.
	*/
	IMPORT_C virtual void LoadL(); 
	/**
	*
	* This launches the setting page (or just toggles) the binary setting
	*
	* @param		aCalledFromMenu - This flag determines if the setting page actually
	*				launches or not.  It does not if this flag is EFalse - the value is just toggled
	*
	*/
	IMPORT_C virtual void EditItemL( TBool aCalledFromMenu );

protected:
	/**
	* Method called by framework to complete the construction.  Extra allocations of
	* memory or extra resource reading can happen here.
	*
	*/
	IMPORT_C virtual void CompleteConstructionL();
private:
	IMPORT_C void CAknSettingItem_Reserved();
private:
	TAny* iUnused;
	};


/**
 * This class can be used as a base class for "Big Settings". The additional 
 * functionality is small - merely to ensure that there is an empty string
 * in the list box text.
 * 
 * To derive from this class, the client code is usually expected to add a new constructor,
 * re-implement StoreL, LoadL() and EditItemL().
 *
 */
class CAknBigSettingItemBase : public CAknSettingItem
	{
public:
	/**
	* Contruct the "Big" setting item. The passed resource identifier all that is needed
	* There is no external value to reference.
	*/
	IMPORT_C CAknBigSettingItemBase( TInt aIdentifier );

protected: 
	/*
	* This method obtains the current value's setting text
	*
	* @return	Reference to descriptor with the text 
	*/
	IMPORT_C virtual const TDesC& SettingTextL();
private:
	IMPORT_C void CAknSettingItem_Reserved();

private:
	const TDesC& iEmptyString;

	};


/**
 * This class holds the setting items themselves and also manages the bitmap array
 */
class CAknSettingItemArray : public CArrayPtrFlat<CAknSettingItem>, public MDesCArray
	{
public:
	/**
	* CAknSettingItemArray is constructed as a numbered or unnumbered array.
	* @param aGranularity	- number of items to extend when the aarray needs extention
	* @param aIsNumbered	- flags the array as numbered or not
	* @param aInitialOrdinal - value to start the numbering at
	*/
	IMPORT_C CAknSettingItemArray( TInt aGranularity, TBool aIsNumbered, TInt aInitialOrdinal );
	/**
	* Destructor
	*/
	IMPORT_C virtual ~CAknSettingItemArray();

	// from MDesC16Array
	/**
	* Method by which the CAknSetStyleListBox accesses the number of items in the array
	* @return	number of items in the array
	*/ 
	IMPORT_C TInt MdcaCount() const;
	/**
	* Method by which the setting item list accesses the text for the aIndex-th item in the 
	* array.
	*
	* @param	aIndex	index at which to access the listbox text
	* @return	Descriptor for this item to be used by the listbox.
	*/
	IMPORT_C TPtrC16 MdcaPoint(TInt aIndex) const;
	// For hidden item support
	/**
	* This method returns the true index in the array given the index as would be 
	* calculated by looking at the visible items. 
	*
	* @param aVisibleIndex	- index amoung the visible items
	* @return the corresponding "true" index in the array
	*/
	IMPORT_C TInt ItemIndexFromVisibleIndex( TInt aVisibleIndex ) const;
	/**
	* Update date the mapping of visible indices. To be called when an item is made
	* visible or invisible.
	* 
	*/
	IMPORT_C virtual void RecalculateVisibleIndicesL();
	/**
	* This is used to update the initial setting number for the top index.  The number set is for the 
	* is the for the 0-th "true" or data index.  That is, the this numbered item may not show up
	*
	*/
	IMPORT_C void SetInitialOrdinal( TInt aInitialOrdinal );
	/*
	* Method used to transfer flags from the CAknSettingItemList to this array
	*/
	IMPORT_C void SetFlags( TInt aFlags );
protected:

	/** 
	* Set the number of visible items. 
	* @param aCount	number of items that are visible.
	*/
	IMPORT_C void SetVisibleCount( TInt aCount );
	/**
	* Returns the number of visible items
	*
	* @return the number of visible items
	*/
	IMPORT_C TInt VisibleCount() const;

private:
	TBool iIsNumbered;
	TInt iInitialOrdinal;
	TInt iVisibleCount;
	TInt iFlags;
	};



class CAknSettingItemList : public CCoeControl , public MEikListBoxObserver
{

public:
	enum TAknSettingItemStyle
	{
	ENumberedStyle,		// The setting item list displays number
	EUnnumberedStyle	// The setting item list does not disply number
	};

public:
	/**
	* Constructs the setting item list
	*/
	IMPORT_C CAknSettingItemList();
	/**
	* Destructor
	*/
	IMPORT_C ~CAknSettingItemList();

	// From CCoeControl
	/**
	* 2nd-stage construction from resource id
	*/
	IMPORT_C void ConstructFromResourceL(TInt aResourceId );
	/**
	* 2nd-stage construction from constructed resource reader
	*/
	IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

	/**
	* @return the number of component controls
	*/ 
	IMPORT_C TInt CountComponentControls() const;
	/**
	* @param TInt aId
	* @return  a reference to the component control at index aId
	*/
	IMPORT_C CCoeControl* ComponentControl(TInt aId ) const;

	/**
	* Handles keys sent to this control
	*/
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	/**
	* Take action necessary when the focus is change
	*/
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);

// from MEikListBoxObserver
	IMPORT_C virtual void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);
public:
	// Framework methods
	/**
	*
	* This launches the setting page for the current item by calling EditItemL on it
	*
	* @param		aIndex			- current item's (Visible) index in the list
	*				aCalledFromMenu- ignored in most classes; may alter the behaviour
	*									of the setting page
	*/
	IMPORT_C virtual void EditItemL(TInt aIndex, TBool aCalledFromMenu);
	/**
	*
	* Calls LoadL() on each item in the MAknSettingItemArray. 
	*
	*/
	IMPORT_C virtual void LoadSettingsL();
	/**
	* This command calls StoreL on all the setting items (hidden or not)
	*
	* This must be called by the client if he wants it to occur
	*/
	IMPORT_C virtual void StoreSettingsL(); //  call StoreL() on each item in the MAknSettingItemArray

	/**
	* @param	aInclude	If EFalse, numbering does not include hidden items
	*						Otherwise, they are
	*/
	IMPORT_C void SetIncludeHiddenInOrdinal( TBool aInclude );

	/** 
	* @return	EFalse if the listbox is not numbered style; Not EFalse otherwise
	*/
	IMPORT_C TBool IsNumberedStyle();
	/**
	* @return	the listbox used by setting item list
	*/
	IMPORT_C CEikFormattedCellListBox* ListBox(); // get the listbox
	/**
	* @return	a pointer to the setting item array; No ownership is transferred
	*/
	IMPORT_C CAknSettingItemArray* SettingItemArray() const;
	/**
	* Method to be called when the client code has added or removed items or their visibility;
	* This should be called when a single event's batch of array or visibility changes
	* is complete in order to avoid more re-draws than is necessary
	*/
	IMPORT_C void HandleChangeInItemArrayOrVisibilityL();

protected:
	/**
	* Framework method to create a setting item based upon the user id aSettingId. The 
	* client code decides what type to contruct.  new (ELeave) must then be used and the resulting 
	* pointer returned. Ownership is thereafter base class's responsiblity.
	*
	* @param aSettingId	ID to use to determine the type of the setting item
	* @return a constructed (not 2nd-stage constructed) setting item.
	*/
	IMPORT_C virtual CAknSettingItem* CreateSettingItemL( TInt aSettingId );


private:

	// Owned objects:
	CEikFormattedCellListBox* iSettingItemListBox;
	CAknSettingItemArray* iSettingItemArray;

	// Other non-CBase classes 
	HBufC* iSettingItemListTitle;	// Owned

	// Internal information
	TInt iFlags;
	TInt iInitialOrdinal;

	TInt iSpare_1;
	TInt iSpare_2;
};




#endif
