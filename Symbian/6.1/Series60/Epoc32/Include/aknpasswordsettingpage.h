/*
* ============================================================================
*  Name     : AknPasswordSettingPage.h
*  Part of  : Avkon
*
*  Description:
*     Support for passwords in Settings Pages
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNPASSWORDSETTINGPAGE__
#define __AKNPASSWORDSETTINGPAGE__ 

#include <eikdef.h>
#include <eikbtgpc.h>

// for the alphanumeric secret editor:
#include <eikseced.h>
#include <aknsettingpage.h>

const TInt KDefaultAlphaPasswordLength = 12;
const TInt KDefaultNumericPasswordLength = 4;

/** 
 * Structure to hold the required resoureces for a password confirmation sequence 
 * This holds 3 resource IDs.  One for a query, and a note each for 
 * success or failure
 * This structure contains the information read in from a AVKON_PASSWORD_CONFIRMATION
 * resource structure.
 */
class SAknConfirmationResource 
{
public:

	/**
	* Resource for the password query, if non-zero
	*/
	TInt iEntryQueryResourceId;
	/** 
	* Resource for the success note, if non-zero
	*/
	TInt iSuccessNoteResourceId;
	/** 
	* Resource for the failure note, if non-zero
	*/
	TInt iFailureNoteResourceId;
};


/**
 * Base class for Password editors to ensure that their general functionality is 
 * consistent.  
 * 
 * All contained-editor-specific stuff should be in the derived classes.
 *
 * THIS CLASS IS NOT INSTANTIATABLE
 * 
 */
class CAknPasswordSettingPage : public CAknSettingPage
{
public:
	/**
	*
	* Modes to be used for the matching of password texts
	*
	*/
	enum TAknPasswordMatchingMode
	{
	ECaseSensitive,
	ECaseInsensitive
	};
public:
	/**
	 * Simple constructor depending only on a single resource Id and the new and old password.
	 * Editor resource is given via the link in the setting page resource. 
	 *
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aNewPassword
	 * @param aOldPassword					password to be checked against
	 */
	IMPORT_C CAknPasswordSettingPage(
		TInt aResourceID, 
		TDes& aNewPassword, 
		const TDesC& aOldPassword);

	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0					present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				= 0					Default Avkon SP resource if used + this editor resource
	 *			 = 0					= 0					uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
	 * cannot initialize such a member without allocation or having an internal dummy buffer.
	 * This descriptor must be owned by the client since not copy is taken until ExecuteLD()
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText	Text at top of setting pane; EXTERNALLY OWNED
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aNewPassword			Descriptor for the new password
	 * @param aOldPassword			Descriptor for the old password
	 */

	IMPORT_C CAknPasswordSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,	
								TDes& aNewPassword, 
								const TDesC& aOldPassword );


	/**
	* Set the resource Id set for the old password confirmation sequence. 
	* Resource Id should be for a AVKON_PASSWORD_CONFIRMATION structure
	*
	* @param resource for old password sequence
	*/
	IMPORT_C void SetOldPasswordConfirmationResourceId( TInt aOldPasswordConfirmationResourceId ); 

	/** 
	* Set the resource Id set for the new password confirmation sequence
	* Resource Id should be for a AVKON_PASSWORD_CONFIRMATION structure
	*
	* @param resource for new password sequence
	*/
	IMPORT_C void SetNewPasswordConfirmationResourceId( TInt aNewPasswordConfirmationResourceId );
	
	/**
	* Sets the matching mode to be used in the password validation
	* @param	one of 	ECaseSensitive or ECaseInsensitive
	*/
	IMPORT_C void SetMatchingMode( TAknPasswordMatchingMode aMode );
	
	/**
	* Returns the matching mode to be used in the password validation
	* @return	one of 	ECaseSensitive or ECaseInsensitive
	*/
	IMPORT_C TAknPasswordMatchingMode MatchingMode();
	
	
	/**
	* Sets the maximum length of the password.  User will not be able to enter
	* more than this number of characters/keys
	*
	* @param	set the max length
	*/
	IMPORT_C void SetMaxPasswordLength( TInt aLength );
	
	
	/** 
	* Access the maximum password length
	*
	* @return the maximum length
	*/
	IMPORT_C TInt MaxPasswordLength() const;
protected:

	/**
	* Implementation of CAknSettingPage framework method
	* Called when the client's value is updated.  Frequency of calling depends 
	* upon the flag passed to ExecuteLD()
	*
	*/
	IMPORT_C virtual void UpdateSettingL();
	
	
	/** 
	* Implementation of CAknSettingPage framework method
	* Perform necessary operations when the user accepts. 
	* Default implementation has password checking 
	*/
	IMPORT_C virtual void AcceptSettingL();
	
	
	/**
	* Acts upon changes in the hosted control's state. 
	*
	* @param	aControl	The control changing its state (not used)
	* @param	aEventType	The type of control event 
	*/
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType );	
	
	
	/** 
	* Implementation of CAknSettingPage framework method
	*  
	* Method called after full construction and activation of the setting page
	*/
	IMPORT_C virtual void PostDisplayInitL();
	
	/** 
	* Implementation of CAknSettingPage framework method
	* Called after display of the setting page, but before the start of the 
	* setting page "waiting".  
	*
	* If overidden, would normally hold a query.
	*
	* @return	ETrue if OK to carry on; EFalse if setting it to be abandoned
	*
	*/
	IMPORT_C virtual TBool PostDisplayCheckL();
	
	
	/** 
	* Implementation of CAknSettingPage framework method
	*
	*/
	IMPORT_C virtual TBool OkToExitL(TBool aAccept);

	/** 
	* Implementation of CCoeControl framework method
	* Called when the control has its size changed
	*/
	IMPORT_C virtual void SizeChanged();
	
	/** 
	* Implementation of CCoeControl framework method
	* Called when required to draw
	*/
	IMPORT_C void Draw(const TRect& aRect) const;

	/**
	* Only implemented in the derived classes
	* Updates the text in the referenced password descriptor using a utility routine.
	*
	*/
	IMPORT_C virtual void UpdateTextL() = 0;

	/**
	* Framework for password handling
	* Called when the old password is to be confirmed
	* @param	aPassword	old password
	* @param	aResourceId	AVKON_PASSWORD_CONFIRMATION id to use
	*/
	IMPORT_C virtual TBool ExecuteOldPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId );
		
	/**
	* Framework for password handling
	* Called when the new password is to be confirmed
	* @param	aPassword	new password
	* @param	aResourceId	AVKON_PASSWORD_CONFIRMATION id to use
	*/
	IMPORT_C virtual TBool ExecuteNewPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId );
		
	/**
	* Framework for password handling
	* Called to compare the two passwords
	* @param	reference (old) password
	* @param	candidate password; password just entered
	*/
	IMPORT_C virtual TInt ComparePasswords( const TDesC& aRefPassword, const TDesC& aCandidatePassword, TAknPasswordMatchingMode ) const;

	/**
	* Utility method
	* Access to the old password confirmation resource
	* @return	id for AVKON_PASSWORD_CONFIRMATION structure
	*/
	IMPORT_C TInt OldPasswordConfirmationResourceId() const;

	/**
	* Utility method
	* Access to the new password confirmation resource
	* @return	id for AVKON_PASSWORD_CONFIRMATION structure
	*/
	IMPORT_C TInt NewPasswordConfirmationResourceId() const;

	/**
	* Utility method
	* Read in the confirmation resource structure
	* @param	aPasswordResourceId		id to use
	* @param	aResourceGroup		structure to fill
	*/
	IMPORT_C void ReadConfirmationResourceL( TInt aPasswordResourceId, SAknConfirmationResource& aResourceGroup );

	/**
	* Utility method
	* Run the password confirmation
	*/
	IMPORT_C TBool DoPasswordConfirmationL(const TDesC& aPassword, TInt aPasswordConfirmationResourceId, TAknPasswordMatchingMode aMatchMode, TInt& aTries );

	/**
	* Utility method
	* Access to new password candidate
	*/

	IMPORT_C TDes& NewPassword() const;

	/**
	* Utility method
	* Access to old password
	*/
	IMPORT_C const TDesC& OldPassword() const;

//
// CoeControl Framework and reserved methods
//
protected:

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @param	aWriteSteam		A connected write stream
 */	
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

private:
/**
 *	Reserved method derived from CCoeControl
 */
	IMPORT_C virtual void Reserved_2();

/**
 * New reserved methods for CAknSettingPage hierarchy
 */ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();

private:
	TDes& iNewPassword;
	const TDesC& iOldPassword;
	TInt iOldPasswordConfirmationResourceId;
	TInt iNewPasswordConfirmationResourceId;
	TAknPasswordMatchingMode iMatchingMode;
	TInt iMaxPasswordLength;

	TAknLayoutRect iSecretEditorLayoutRect;
	TAknLayoutRect iHorizontalShadow;
	TAknLayoutRect iVerticalShadow;
	TAknLayoutRect iOutlineFrame;

	TInt iSpare_1;

};


/** 
 *
 * This class is used for alphanumeric passwords
 *
 */

class CAknAlphaPasswordSettingPage : public CAknPasswordSettingPage
{
public:
	/**
	 * Simple constructor depending only on a single resource Id and the new and old password.
	 * Editor resource is given via the link in the setting page resource. 
	 *
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aNewPassword
	 * @param aOldPassword					password to be checked against
	 */
	IMPORT_C CAknAlphaPasswordSettingPage(
		TInt aResourceID, 
		TDes& aNewPassword, 
		const TDesC& aOldPassword);
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0					present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				= 0					Default Avkon SP resource if used + this editor resource
	 *			 = 0					= 0					uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
	 * cannot initialize such a member without allocation or having an internal dummy buffer.
	 * This descriptor must be owned by the client since not copy is taken until ExecuteLD()
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText		Text at top of setting pane; EXTERNALLY OWNED
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aNewPassword			Descriptor for the new password
	 * @param aOldPassword			Descriptor for the old password
	 */
	IMPORT_C CAknAlphaPasswordSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,	
								TDes& aNewPassword, 
								const TDesC& aOldPassword );

	/**
	*
	* 2nd stage construction.  This uses stored values from the conststuctor to allocate the 
	* required aggregate objects, and then set the Date value. 
	*
	*/
	IMPORT_C virtual void ConstructL();

	/**
	* Type specific access to hosted editor
	* @return	the hosted (alpha secret) editor
	*/
	IMPORT_C CEikSecretEditor* AlphaPasswordEditor();

protected:
	/**
	* Destructor
	*/
	IMPORT_C virtual ~CAknAlphaPasswordSettingPage();

    /**
	* From CAknPasswordSettingPage - Implemented in this class
	* Copy text from the editor to the client's descriptor
	*/
	IMPORT_C virtual void UpdateTextL();

//
// CoeControl Framework and reserved methods
//
protected:

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @param	aWriteSteam		A connected write stream
 */	
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

private:
/**
 *	Reserved method derived from CCoeControl
 */
	IMPORT_C virtual void Reserved_2();

/**
 * New reserved methods for CAknSettingPage hierarchy
 */ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();


};


/** 
 *
 * This class is used for numeric passwords.  The API uses text descriptors rather than
 * integers for the PIN numbers as this is the usage
 *
 */

#include <aknnumseced.h>

class CAknNumericPasswordSettingPage : public CAknPasswordSettingPage
{
public:
	/**
	 * Simple constructor depending only on a single resource Id and the new and old password.
	 * Editor resource is given via the link in the setting page resource. 
	 *
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aNewPassword
	 * @param aOldPassword					password to be checked against
	 */
	IMPORT_C CAknNumericPasswordSettingPage(
		TInt aResourceID, 
		TDes& aNewPassword, 
		const TDesC& aOldPassword);
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0					present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				= 0					Default Avkon SP resource if used + this editor resource
	 *			 = 0					= 0					uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
	 * cannot initialize such a member without allocation or having an internal dummy buffer.
	 * This descriptor must be owned by the client since not copy is taken until ExecuteLD()
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText	Text at top of setting pane; EXTERNALLY OWNED
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aNewPassword			Descriptor for the new password
	 * @param aOldPassword			Descriptor for the old password
	 */
	IMPORT_C CAknNumericPasswordSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,	
								TDes& aNewPassword, 
								const TDesC& aOldPassword );

	/**
	*
	* 2nd stage construction.  This uses stored values from the conststuctor to allocate the 
	* required aggregate objects, and then set the Date value. 
	*
	*/
	IMPORT_C virtual void ConstructL();
	
	/**
	* Type specific access to hosted editor
	* @return	the hosted (numeric secret) editor
	*/
	IMPORT_C CAknNumericSecretEditor* NumericPasswordEditor();

protected:
	/**
	* Destructor
	*/
	IMPORT_C virtual ~CAknNumericPasswordSettingPage();

    /**
	* From CAknPasswordSettingPage - Implemented in this class
	* Copy text from the editor to the client's descriptor
	*/
	IMPORT_C virtual void UpdateTextL();

//
// CoeControl Framework and reserved methods
//
protected:

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @param	aWriteSteam		A connected write stream
 */	
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

private:
/**
 *	Reserved method derived from CCoeControl
 */
	IMPORT_C virtual void Reserved_2();

/**
 * New reserved methods for CAknSettingPage hierarchy
 */ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();


};


#endif 
