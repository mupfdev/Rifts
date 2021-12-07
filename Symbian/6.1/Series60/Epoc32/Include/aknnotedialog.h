/*
* ============================================================================
*  Name     : AknNoteDialog.h
*  Part of  : Avkon
*
*  Description:
*     Provides the CAknDialog-derived interface to Avkon Notes.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNNOTEDIALOG__
#define __AKNNOTEDIALOG__

#include <eikdialg.h>
#include "avkon.hrh"
class CEikImage;
class CAknKeySoundSystem;
class CAknNoteControl;
class CAknNoteAttributes;

/**
 * The note dialog.
 *
 * Display a note to the user for: <UL> <LI> Giving notifications. </LI>
 * <LI> Asking questions. </LI> <LI> Showing progress. </LI> </UL>
 *
 * @see CAknNoteControl, CAknNoteAttributes, CAknText
 */
class CAknNoteDialog : public CEikDialog
{
public:
	/**
	 * The timeout in microseconds for 
	 * automatically deleting the dialog.
	 */
  enum TTimeout {
	/// Deprecated (not used) 
	EUndefinedTimeout = 0,   
	/// No timeout  
    ENoTimeout = 0,         
	/// 1.5 seconds 
    EShortTimeout = 1500000,
	/// 3 seconds
    ELongTimeout = 3000000   
    };

   /**
   * The tone played before the dialog is shown.
   Application specific tones may be played by casting the application
   defined Sound ID (SID), to TTone
   */
  enum TTone {
	/// No tone is played 
    ENoTone = 0,		
	/// A confirmation tone is played 
    EConfirmationTone = EAvkonSIDConfirmationTone, 
	/// A warning tone is played 
    EWarningTone = EAvkonSIDWarningTone,      
	/// An error tone is played  
    EErrorTone = EAvkonSIDErrorTone         
    };

public:
  /**
	* The class default constructor. 
	*
	* Initialise the tone to ENoTone and the timeout to ENoTimeout. 
	*
	* @see TTone, TTimeout
	*/
	IMPORT_C CAknNoteDialog();
   /**
	* Another class constructor. 
	*
	* Initialise the tone to aTone and the timeout to aTimeout. 
	*
	* @param aTone    The tone
	* @param aTimeout The timeout (microseconds)
	*
	* @see TTone, TTimeout
	*/
	IMPORT_C CAknNoteDialog(const TTone& aTone, const TTimeout& aTimeout = ENoTimeout);
   /**
	* Another class constructor. 
	*
	* Initialise the tone to aTone and the timeout to aTimeout. 
	* Accept a pointer to CEikDialog*. This must be the
	* address of the dialog pointer. When the dialog deletes 
	* itself after a timeout, the address pointed to by this 
	* pointer is set to NULL. The dialog must not be on the stack, it must
	* be on the heap!
	*
	*
	* @param aSelfPtr Pointer to the address of the dialog.
	* @param aTone    The tone
	* @param aTimeout The timeout (microseconds)
	*
	* @see TTone, TTimeout
	*/
	IMPORT_C CAknNoteDialog(CEikDialog** aSelfPtr, const TTone& aTone = ENoTone, const TTimeout& aTimeout = ENoTimeout);
   /**
	* The class destructor. 
	*
	* Delete timer and control attributes. If the
	* self pointer is not null, set to NULL what
	* it points to. 
	*
	*/
	IMPORT_C virtual ~CAknNoteDialog();
   /**
	* Set the dialog timeout 
	*
	* @see TTimeout
	*
	* @param aTimeout		The dialog timeout
	*/
	IMPORT_C void SetTimeout(const TTimeout& aTimeout);
   /**
	* Set the dialog tone 
	*
	* @see TTone
	*
	* @param aTone		The dialog tone
	*/
	IMPORT_C void SetTone(const TTone& aTone);
   /**
	* Enable of disable text wrapping. 
	*
	* Enable or disable text wrapping depending on the values
	* of aEnabled (true enables text wrapping). When text wrapping is
	* disabled a new line in the note dialog starts only after a newline character
	* in the note text. If a line does not fit into the dialog width it is
	* clipped (the last character is replaced with an ellipsis sign).
	*
	* This method must be called before SetTextL as it only influences the
	* wrapping of text that it is yet to be set via API.
	*
	* @param aEnabled   True for enabling text wrapping, false for disabling it
	*
	*/
	IMPORT_C void SetTextWrapping(TBool aEnabled);
   /**
	* Set the dialog image. 
	*
	* Change the image in the note control. Override the image which was set in the
	* resource file. The dialog takes ownership of the pointer. The note image is the big
	* image or icon which is top right. 
	*
	* @param aImage		Pointer to the new image. 
	*
	*/
	IMPORT_C void SetImageL(CEikImage* aImage);
   /**
	* Set the dialog icon. 
	*
	* Change the numbertype icon in the note control. 
	* Override the icon which was set in the
	* resource file. The dialog takes ownership of the pointer 
	* The numbertype icon is the small icon which is bottom left
	* in the note (thumbnail icon). 
	* 
	* @param aIcon		    Pointer to the icon
	*
	*/
	IMPORT_C void SetIconL(CEikImage* aIcon);
   /**
	* Set the number in the dialog text. 
	*
	* Set a number in the note text. If the text specified in resource file
	* or via SetTextL has a \%d in it, e.g. "You have \%d new messages",
	* this number is inserted at the location specified by \%d. 
	*
	* Suggestion for the future:
	*   A SetTextL method with a variable number of arguments could make 
	*   SetTextNumberL and SetTextPluralityL obsolete.
	*    
	*   <code> SetText("You have \%d new SMS messages and \%d new e-mails", 2,3); </code>
	*   at the moment the current API does not support this scenario!
	*
	* @param aNumber		The number to be inserted in the text 
	*
	*/
	IMPORT_C void SetTextNumberL(TInt aNumber);
   /**
	* Set the text plurality for the dialog 
	*
	* Indicates whether to use plural or singular text. These texts must 
	* have been specified in the resource file.
	*
	* @see SetTextNumberL
	*
	* @param aIsPlural		True if plural text should be used, false otherwise.
	*
	*/
	IMPORT_C void SetTextPluralityL(const TBool isPlural);
   /**
	* Set the dialog text 
	*
	* This method can set a formatted text, 
	* e.g. "You have 1 new message". It can however set an 
	* unformatted text as well, e.g. "You have \%d messages". The plurality of
	* the dialog must have been previously specified - if not singular plurality
	* is used unless there was no singular text specified in the resource file.
	*
	* @see SetTextNumberL, SetTextPluralityL
	*
	* @param aLabel		The note text.
	*
	*/
	IMPORT_C void SetTextL(const TDesC& aLabel);
	
   /**
	* Handle key events. 
	*
	* Any event which is not a key press is forwarded to CEikDialog::OfferKeyEventL.
	* Short key presses dismiss the note by calling StaticDeleteL.
	*
	* @see StaticDeleteL, TKeyEvent, TEventCode
	*
	* @param aKeyEvent   Key event details
	* @param aType       Type of event (key down, key press, key release, etc)
	*
	*/
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType) ;
   /**
	* Do layout and draw. 
	*
	* Needed when changing control components (e.g. the text) dynamically. 
	* This is needed because the size of the dialog might change 
	* (e.g. because of bigger text displayed in more lines, etc.) 
	* Set methods call LayoutAndDraw if there is a change that
	* might affect the dialog layout (e.g. text becames bigger and hence
	* requires an extra line).
	* Derived classes that implement this kind of methods should call
	* LayoutAndDraw.
	* 
	*/
	IMPORT_C void LayoutAndDraw();
   /**
	* Execute dialog.
	*
	* Play a tone (if one was defined) and simulate user activity.
	* Forward call to CEikDialog::RunLD.
	*
	*/
    IMPORT_C virtual TInt RunLD();
	
protected:
  /**
	* Set size and position for layout 
	*
	* The dialog height and width are retrieved from the control 
	* (if it exists already).If it does not exist, 
	* then default values are used. 
	* The client rect is obtained from the application UI. 
	* AknLayoutUtils::LayoutControl 
	* is then executed using the client rect and the note width and height.
	* 
	* @see AknLayoutUtils::LayoutControl
	*
	* @param aSize ignored
	*/
	IMPORT_C void SetSizeAndPosition(const TSize& aSize);
   /**
	* Perform dynamic operations before layout. 
	*
	* Called by the uikon framework before the dialog layout is executed, this
	* method can be overrwritten to perform specific operations.
	*
	* The following operations are performed:- <UL> <LI> The control attributes are 
	* transferred to the control. The local control attributes are copied into the real
	* control attributes. The local attributes are then deleted. </LI> <LI> If a timeout
	* has been specified the timer is started. The callback is StaticDeleteL. </LI> <LI> 
	* SetEditableL(ETrue) is called. </LI> </UL> 
	* 
	* @see CAknNoteAttributes, TTimer, SetEditableL
	*
	*/
	IMPORT_C void PreLayoutDynInitL(void);
   /**
	* Perform dynamic operations after layout. 
	*
	* Called by the uikon framework after the dialog layout is executed, this
	* method can be overrwritten to perform specific operations.
	*
	*  The following operations are performed:- <UL> <LI> StartAnimationL is called. 
	* </LI> </UL> 
	* 
	* @see CAknNoteControl::StartAnimationL.
	*
	*/
	IMPORT_C void PostLayoutDynInitL();
   /**
	*  Play a tone. 
	*
	* The tone must have been previously specified. 
	* The sound ID is set depending on the tone type. 
	* The tone is played using CAknKeySoundSystem::playSound(). 
	* Derived classes must call this method if they override RunLD
	* and they wish to play a tone. 
	*
	* @see TTone, CAknKeySoundSystem, CAknNoteDialog::RunLD 
	*/
	IMPORT_C void PlayTone();
   /**
	* Indicate that there is user acitivity. 
	*
	* Reset timers monitoring user inactivity. Will make applications
	* using these timers react, e.g. if the screen saver is running,
	* this will deactivate it (as from screen saver specs).
	* Derived classes must call this method if thye override RunLD
	* and they wish to report user activity in order to dismiss applications
	* such as the screen saver.
	*
	* @see User::ResetInactivityTime
	*/
	IMPORT_C void ReportUserActivity() const;
   /**
	*  Delete the note dialog 
	*
	*  Called when the timer completes, this method deletes the dialog. A
	*     reinterpret_cast to CAknNoteDialog* is performed on aThis. If the
	*     dialog is not a sleeping note then it is deleted. If it is a sleeping
	*     dialog then the timer is stopped, OkToExitL is called with KErrCancel
	*     and ExitSleepingDialog is executed. 
	* 
	* @see TTimer, OkToExitL, ExitSleepingDialog
	*
	* @param aThis Pointer to the dialog
	*/
    IMPORT_C static TInt StaticDeleteL(TAny* aThis);
   /**
	* Return the control attributes.
	*
	* If the control has already been created return the attributes
	* stored inside the control. If not return the local attributes.
	* Local attributes are transferred to the control in PreLayoutDynInitL().
	* Derived classes should use this method when trying to access the control
	* attributes.
	*
	*/
	IMPORT_C CAknNoteAttributes* ControlAttributes();
   /**
	* Transfer the control attributes from the dialog to the control
	*
	* Must be called by derived classes in PreLayoutDynInitL
	* If this is not called then Set API methods called before the
	* control is created will not work
	*/
	IMPORT_C void TransferControlAttributes();
   /**
	* Return a pointer to CAknKeySoundSystem
	*
	* Call iEikonEnv->AppUi()->KeySounds() and return the pointer returned by it.
	* If there is not app UI return NULL. 
	*
	* @see CAknKeySoundSystem, CAknAppUi
	*/
	IMPORT_C CAknKeySoundSystem* SoundSystem() const;
   /**
	* Return the Note control 
	*
	* Return the first control on the active page, which is of type
	* CAknNoteControl. If no control is found (usually because the 
	* control has not been created yet) then return NULL. 
	* Derived classes must use this method to get access to the note
	* control.
	*
	* @return The note control or NULL
	* 
	*/
    IMPORT_C CAknNoteControl* NoteControl();

private:
    void DbgCheckSelfPtr(CEikDialog** aSelfPtr);

protected:
    CPeriodic*          iTimer;			///Implement the note timeout
    TInt                iTimeoutInMicroseconds; ///Specify the timeout
	
    CEikDialog**        iSelfPtr; ///Used for notes that aren't modal, the calling app 
								  ///has no way to know when the note is deleted
    TTone               iTone;	  ///Specify the tone
    CAknNoteAttributes* iControlAttributes;  ///The note control attributes
private:
	TInt iSpare;

public:
	/**
	* These methods are deprecated - do not use
	*/
	IMPORT_C TInt ExecuteDlgLD(const TTimeout aTimeout,const TTone aTone,TInt aResourceID);
	IMPORT_C TInt ExecuteDlgLD(const TTone aTone,TInt aResourceID);
	IMPORT_C TInt ExecuteDlgLD(TInt aResourceId, TInt aNoteControlId=0);
	IMPORT_C TInt RunDlgLD(const TTimeout aTimeout,const TTone aTone);
	IMPORT_C TInt RunDlgLD(const TTone aTone);
	IMPORT_C TInt RunDlgLD();
	IMPORT_C TInt RunDlgLD(TInt aNoteControlId);
	IMPORT_C void SetCurrentLabelL(TInt aControlId,const TDesC& aLabel);
	private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: // new virtual function.
	IMPORT_C virtual void CAknNoteDialog_Reserved();
protected:
	/**
	 * Deprecated, use StaticDeleteL instead
	 */
	IMPORT_C static TInt StaticDelete(TAny* aThis);
	};

#endif 
