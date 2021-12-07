/*
* ============================================================================
*  Name     : AknQueryDialog.h
*  Part of  : Avkon
*
*  Description:
*   Implementation of Query dialogs
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNQUERYDIALOG_H
#define AKNQUERYDIALOG_H

//  INCLUDES
#include <eikdialg.h>
#include <aknform.h>
#include <eiklbx.h>
#include <eiktxlbx.h>
#include <eikcmobs.h>
#include <aknpopuplayout.h>
#include <aknintermediate.h>
#include <aknquerycontrol.h>
#include <aknpopuplayout.h>
#include <aknmultilinequerycontrol.h>
#include <aknlistquerycontrol.h>
#include <aknintermediate.h>
#include <aknquerydata.h>
#include <avkon.hrh>

class CAknKeySoundSystem;


/**
 * General query dialog
 *
 * Use for confirmation queries
 */
class CAknQueryDialog : public CAknDialog , public MAknQueryControlObserver 
	{
	public:
        /**
         * Enumeration for tones
	     * The tone played before the dialog is shown.
		 * Application specific tones may be played by casting the application
		 * defined Sound ID (SID), to TTone
		 **/
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
		IMPORT_C static CAknQueryDialog* NewL(const TTone& aTone = ENoTone);
		IMPORT_C static CAknQueryDialog* NewL(TDes& aText, const TTone& aTone = ENoTone);
		IMPORT_C static CAknQueryDialog* NewL(TInt& aNumber, const TTone& aTone = ENoTone);
		IMPORT_C static CAknQueryDialog* NewL(TTime& aTime, const TTone& aTone = ENoTone);
		IMPORT_C static CAknQueryDialog* NewL(TTimeIntervalSeconds& aTime, const TTone& aTone = ENoTone);
		IMPORT_C static CAknQueryDialog* NewL(TReal& aNumber, const TTone& aTone = ENoTone);

	public:
		IMPORT_C virtual ~CAknQueryDialog();

        /**
         * Construction, destruction
		 *
		 * @deprecated: will be made protected - use NewL
         */
	    IMPORT_C CAknQueryDialog(const TTone& aTone);

    public:

		/**
		* Return pointer to query heading or NULL
		*
		*/
		IMPORT_C virtual CAknPopupHeadingPane* QueryHeading() const;

		/**
		* Deprecated method to return pointer to query heading or NULL (use QueryHeading())
		*
		* @deprecated - will be removed (use QueryHeading() method instead)
		*/
		IMPORT_C CAknPopupHeadingPane* Heading() const;

        /**
        * Set prompt text for query. This this will override text given in constructor.
        *
        * @param aDesC  Text for prompt
        */
	    IMPORT_C void SetPromptL(const TDesC& aPrompt);

		/** 
		 * Set visibility of the left softkey. Softkey is hidden when data in the query is not acceptable.
		 * @param aVisible EFalse hides softkey label, ETrue shows it.
		 */
        IMPORT_C void MakeLeftSoftkeyVisible(TBool aVisible);

	    /**
		 * Enable or disable emergency call support.  This method is only valid in 
		 * numeric queries (secret or normal). 
		 *
		 * Default is Off for both.
		 *
		 * @param aOnOff	Sets emergency call support active or inactive, if feature is available in 
		 *					current type of control
		 */
		 IMPORT_C void SetEmergencyCallSupport( TBool aOnOff );

		/**
		 * Removes the editor indicators for this dialog.
		 * Used to ensure this dialog does not own any editor indicators.
		 * before openeing another dialog which outlasts this one.
		 */
		 IMPORT_C void RemoveEditorIndicator();

		 /**
		 * This method can be used to set predictive text entry permitted.  The default
		 * Query behaviour is to supress predictive entry (over-riding editor resource 
		 * flags that may indicate otherwise. 
		 * 
		 * This may be called at any time prior to activation of the query.
		 * 
		 * @param aPermitted	ETrue - allow predictive text entry
		 * 
		 */
		 IMPORT_C void SetPredictiveTextInputPermitted( TBool aPermitted );

        IMPORT_C TInt RunLD();

		IMPORT_C TInt ExecuteLD(TInt aResourceId);

		IMPORT_C TInt ExecuteLD(TInt aResourceId, const TDesC& aPrompt);



    public:// from CCoeControl
        /**
        * From CCoeControl  Handle key events. When a key event occurs, 
        *                   CONE calls this function for each control on the control stack, 
        *                   until one of them returns EKeyWasConsumed to indicate that it processed the key event.  
        * @param aKeyEvent  The key event.
        * @param aType      The type of the event: EEventKey, EEventKeyUp or EEventKeyDown.
        * @return           Indicates whether or not the key event was used by this control.
        */
	    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
	public:
		/**
		* Return the maximum possible length of the query text
		* This is (in order of precedence, and assuming they are valid
		* i.e. less than or equal to the length of the descriptor passed to 
		* return the value) dependent on
		* 1) aApiValue
		* 2) Resource set value held in aControl
		* 3) The MaxLength of the descriptor
		* @return maximum text length
		*/
	IMPORT_C static TInt MaxTextLength(const CAknQueryControl* aControl, const TDes& aDataText, TInt aApiValue) ;

    protected://from CEikdialog
        /**
        * From CEikdialog   EIKON provides an implementation of this function, 
        *                   which positions the dialog in the centre of the screen. 
        *                   However, it can be overridden by derived classes..
        * @param aSize      The size for the dialog.
        */
	    IMPORT_C void SetSizeAndPosition(const TSize& aSize);

        /**
        * From CEikdialog   This function is called by the EIKON dialog framework just
        *                   before the dialog is activated, but before it is sized,
        *                   and before PostLayoutDynInitL() is called.
        */
	    IMPORT_C void PreLayoutDynInitL(void);

        /**
        * From CEikdialog   This function is called by the EIKON dialog framework 
        *                   just before the dialog is activated, after it has called
        *                   PreLayoutDynInitL() and the dialog has been sized.
        */
	    IMPORT_C void PostLayoutDynInitL();

        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
	    IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

    public://from MAknQueryControlObeserver
        /**
        * From MAknQueryControlObserver
        *   Gets called when editor sends size event
        * @param aQueryControl  Pointer to query control
        *                           which sent the event
        * @param aEventType     Type of the event
        */
        IMPORT_C TBool HandleQueryEditorSizeEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType);

        /**
        * From MAknQueryControlObserver
        *   Gets called when editor sends state event
        * @param aQueryControl  Pointer to query control
        *                           which sent the event
        * @param aEventType     Type of the event
        * @param aStatus        Editor validation status
        */
        IMPORT_C TBool HandleQueryEditorStateEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType, TQueryValidationStatus aStatus);

		/**
		* Called by OfferkeyEventL(), gives a change to dismiss the query even with
		* keys different than Enter of Ok.
		*/
		IMPORT_C virtual TBool NeedToDismissQueryL(const TKeyEvent& aKeyEvent);
		
		/**
		* Called by NeedToDismissQueryL(), gives a change to either accept or reject
		* the query. Default implementation is to accept the query if the Left soft
		* key is displayed and reject it otherwise. Left softkey is only displayed if
		* the query has valid data into it.
		*/
		IMPORT_C virtual void DismissQueryL();

	protected:
		/**
		* If the query text is ok (retrieved form query control) then display the 
		* left soft key, otherwise hide it.
		*/
		IMPORT_C virtual void  UpdateLeftSoftKeyL();

		/**
		* Set the prompt inside the query control. If dialog is active redo
		* layout and draw.
		*/
		IMPORT_C virtual void DoSetPromptL();

		/**
		* Return pointer to query control or NULL
		* 
		*/
		IMPORT_C virtual CAknQueryControl* QueryControl() const;

	protected: //implementation, intended to be used but not overwritten
        /**
        * Play's tone
        */
		void  PlayTone();
        /**
        * Resets system's inactivity timer
        */
		void  ReportUserActivity() const ;
        /**
        * Recreates layout and redraws the dialog
        */
		void  LayoutAndDraw();
        /**
        * Returns left CBA short key press
        * @return Id of the left CBA
        */
		TInt  GetLeftCBAShortKeyPress();
        /**
        * Returns right CBA short key press
        * @return Id of the right CBA
        */
        TInt  GetRightCBAShortKeyPress();
        /**
        * Returns whether the left softkey is visible
        * @return ETrue is the left softkey is visible
        */
		TBool IsLeftSoftkeyVisible(); 

	protected:
		/**
		 * Prompt access for derived classes
		 */
		IMPORT_C TPtrC Prompt() const; 

		TTone& Tone() { return iTone; }
		const TTone& Tone() const { return iTone; }

		TBitFlags16& Flags() { return iFlags; }
		const TBitFlags16& Flags() const { return iFlags; }

		CAknKeySoundSystem* SoundSystem() const { return iSoundSystem; }
	protected: // collected code for accessing Dialog state.
		CCoeControl* CAknQueryDialog::FindControlOnAnyPageWithControlType(TInt aControlType, TInt* aLineIndex=0, TInt* aPageIndex=0) const;

    protected:
		/**
		 * These will be made private, use protected methods 
		 *
		 * Deprecated.
		 */
        // Tone which is played when the query is executed
        TTone  iTone;
        // Prompt text
        TDesC *iPrompt;  
        // Spare variable for further development
        TAny* iSpare_2;
        // Flags for emergency call support
        TBitFlags16 iFlags; 	// Need these at least to store the ECS state until the control exists
        // Spare variable for further development
        TInt iSpare_1;			
        // Sound system
		CAknKeySoundSystem* iSoundSystem;

	public:
		/**
		 * deprecated do not use
		 */
		IMPORT_C CAknQueryDialog();
		IMPORT_C CAknQueryDialog(TDesC& aPrompt,const TTone& aTone = ENoTone);

		/**
		 * @deprecated - use QueryHeading() method instead
         */
        IMPORT_C void SetHeaderTextL(const TDesC& aHeader);

        /**
		 * @deprecated - use QueryHeading() method instead
		 */
        IMPORT_C void SetHeaderImageL(CEikImage* aImage);

		/**
		 * @deprecated - use RunLD or ExecuteLD instead
		 */
		IMPORT_C TInt RunDlgLD(TInt aResourceId);

		/**
		 * @ deprecated - use other version of MaxTextLength
		 */
		IMPORT_C static TInt MaxTextLength(const CAknQueryControl* aControl, const TDes* aDataText, TInt aApiValue);
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:// new function  
		IMPORT_C virtual void CAknQueryDialog_Reserved();
    };

//-------------------------------------
//class CAknTextQuerydialog 
//-------------------------------------

//Deprecated
#define CAknStaticSizeDataQuerydialog CAknTextQueryDialog

/**
*This class should be used when user is reguest to enter plain text, secret text, phonenumber or PIN-code
*/
class CAknTextQueryDialog : public CAknQueryDialog
	{
    public://construction and destruction

		IMPORT_C static CAknTextQueryDialog* NewL(TDes& aDataText, const TTone& aTone = ENoTone);

	public:

	    IMPORT_C CAknTextQueryDialog(TDes& aDataText, const TTone& aTone = ENoTone);
	
        /**
         * C++ Destructor.
         */
	    IMPORT_C virtual ~CAknTextQueryDialog();

    public://New functions
        /**
        * Set maax lenght for editor. This override manx lenght gicen in resource.
        *
        * @param aLenght    Max lenght. 
        */
        IMPORT_C void SetMaxLength(TInt aLength);

		/*
		* Return true if the length of the text is bigger 
		* than zero and if there
		* is at least a character which is not a space
		*/
        IMPORT_C  virtual TBool CheckIfEntryTextOk() const;

    protected://from CEikDialog
        /**
        * From CEikdialog   This function is called by the EIKON dialog framework 
        *                   just before the dialog is activated, after it has called
        *                   PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
	    IMPORT_C virtual TBool OkToExitL(TInt aButtonId);
               
    public://from MAknQueryControlObserver
        /**
        * From MAknQueryControlObserver
        *   Gets called when editor sends size event
        * @param aQueryControl  Pointer to query control
        *                           which sent the event
        * @param aEventType     Type of the event
        */
        IMPORT_C TBool HandleQueryEditorSizeEventL(CAknQueryControl* aQueryControl, TQueryControlEvent aEventType);
	
	protected:
		/**
		* Called by PreLayoutDynInit(), set the control observer, the text and 
		* the maximum length of the text
		*/
		void SetControlTextL();

		inline TDes& Text() { return iDataText; }
		inline const TDesC& Text() const { return iDataText; }

	protected: 
		/**
		 * @deprecated 
		 * This data will become private 
		 * Use Text() and MaxTextLength() instead
		 */
        // Max length for text
		TInt  iTextMaxLength; 
        // Text for editor. When query is approved text from editor is stored here
	    TDes& iDataText;
        /// @deprecated - not used anymore
	    TBool iEditorTextOk; 
	
	public:
		/**
		* deprecated do not use
		*/
		IMPORT_C CAknTextQueryDialog(TDes& aDataText, TDesC& aPrompt,const TTone& aTone = ENoTone);
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:
		IMPORT_C virtual void CAknQueryDialog_Reserved();
	};

//---------------------------------
//class CAknNumberQuerydialog 
//---------------------------------

/**
*This class should be used when user is reguest to enter number
*/
class CAknNumberQueryDialog : public CAknQueryDialog
	{
    public:		
		IMPORT_C static CAknNumberQueryDialog* NewL(TInt& aNumber, const TTone& aTone = ENoTone);

	public:
        /**
         * C++ Constructor.
         */
	    IMPORT_C CAknNumberQueryDialog(TInt& aNumber, const TTone& aTone = ENoTone);
        
        /**
         * C++ Destructor.
         */
	    IMPORT_C virtual ~CAknNumberQueryDialog();
    
	public:
        /**
        * Set maximum and minimum to editor. This override values given in resource.
        *
        * @param aMinimumValue    Minimumm number
        * @param aMaximumValue    Maximum number. 
        */
        IMPORT_C void SetMinimumAndMaximum(TInt aMinimumValue, TInt aMaximumValue); // only values inside the initial minimum and maximum are permitted

    protected://from CEikDialog
        /**
        * From CEikdialog   This function is called by the EIKON dialog framework 
        *                   just before the dialog is activated, after it has called
        *                   PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);
    
		inline TInt& Number() { return iNumber; }
		inline const TInt& Number() const { return iNumber; }

	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:
		IMPORT_C virtual void CAknQueryDialog_Reserved();
	protected:
		/**
		 * @deprecated - will become private - use Number() instead
		 */
		 TInt& iNumber;
	};

//-------------------------------------
//class CAknTimeQueryDialog 
//-------------------------------------

/**
*This class should be used when user is reguest to enter time or date
*/
class CAknTimeQueryDialog : public CAknQueryDialog
	{
    public:
		IMPORT_C static CAknTimeQueryDialog* NewL(TTime& aTime, const TTone& aTone = ENoTone);

	public:
        /**
         * C++ Constructor 
         */
        IMPORT_C CAknTimeQueryDialog(TTime& aTime, const TTone& aTone = ENoTone);
       
        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknTimeQueryDialog();

    public://New functions'
        /**
        * Set maximum and minimum times to editor. This override values given in resource.
        *
        * @param aMinimum    Minimumm time
        * @param aMaximum    Maximum time. 
        */
        IMPORT_C void SetMinimumAndMaximum(const TTime& aMinimum, const TTime& aMaximum); // only values inside the initial minimum and maximum are permitted
    
    protected://from CEikDialog
        /**
        * From CEikdialog   This function is called by the EIKON dialog framework 
        *                   just before the dialog is activated, after it has called
        *                   PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);
    
		inline TTime& Time() { return iTime; }
		inline const TTime& Time() const { return iTime; }

	protected:
		/**
		 * @deprecated - will become private - use Time() instead
		 */
	    TTime& iTime;

	public:
		/**
		* deprecated - do not use
		*/
		IMPORT_C CAknTimeQueryDialog(TTime& aTime,TDesC& aPrompt,const TTone& aTone = ENoTone);
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:
		IMPORT_C virtual void CAknQueryDialog_Reserved();
	};

//----------------------------------
//class CAknDurationQuerydialog 
//----------------------------------

/**
*This class should be used when user is reguest to enter duration
*/
class CAknDurationQueryDialog : public CAknQueryDialog
	{
    public:
		IMPORT_C static CAknDurationQueryDialog* NewL(TTimeIntervalSeconds& aTime, const TTone& aTone = ENoTone);

	public:
        /**
         * - deprecated (use NewL instead)
         */
        IMPORT_C CAknDurationQueryDialog(TTimeIntervalSeconds& aDuration, const TTone& aTone = ENoTone);

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknDurationQueryDialog();

    public://new
        /**
        * Set maximum and minimum durations to editor. This override values given in resource.
        *
        * @param aMinimumDuration   Minimumm duration
        * @param aMaximumDuration   Maximum duration. 
        */
        IMPORT_C void SetMinimumAndMaximum(const TTimeIntervalSeconds& aMinimumDuration, const TTimeIntervalSeconds& aMaximumDuration); // only values inside the initial minimum and maximum are permitted

    protected://from CEikDialog
        /**
        * From CEikdialog   This function is called by the EIKON dialog framework 
        *                   just before the dialog is activated, after it has called
        *                   PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

		inline TTimeIntervalSeconds& Duration() { return iDuration; }
		inline const TTimeIntervalSeconds& Duration() const { return iDuration; }
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:
		IMPORT_C virtual void CAknQueryDialog_Reserved();
    protected:
		/**
		 * @deprecated - will become private. Use Duration() instead.
		 */
		 TTimeIntervalSeconds& iDuration;
	};

//----------------------------------
//class CAknFloatingPointQueryDialog 
//----------------------------------

/**
*This class should be used when user is reguest to enter a flotaing point number
*/
class CAknFloatingPointQueryDialog : public CAknQueryDialog
	{
    public:

		IMPORT_C static CAknFloatingPointQueryDialog* NewL(TReal& aNumber, const TTone& aTone = ENoTone);

	public:

        /**
         * deprecated (use NewL instead)
         */
        IMPORT_C CAknFloatingPointQueryDialog(TReal& aNumber, const TTone& aTone = ENoTone);

        /**
         * C++ Destructor.
         */
        IMPORT_C virtual ~CAknFloatingPointQueryDialog();

    public://new
        /**
        * Set maximum and minimum durations to editor. This override values given in resource.
        *
        * @param aMinimumDuration   Minimumm duration
        * @param aMaximumDuration   Maximum duration. 
        */
        IMPORT_C void SetMinimumAndMaximum(const TReal& aMinimumNumber, const TReal& aMaximumNumber); // only values inside the initial minimum and maximum are permitted

    protected://from CEikDialog
        /**
        * From CEikdialog   This function is called by the EIKON dialog framework 
        *                   just before the dialog is activated, after it has called
        *                   PreLayoutDynInitL() and the dialog has been sized.
        */
        IMPORT_C void PreLayoutDynInitL();

        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
        IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

		inline TReal& Number() { return iNumber; }
		inline const TReal& Number() const { return iNumber; }
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:
		IMPORT_C virtual void CAknQueryDialog_Reserved();
    protected:
		/**
		 * @deprecated - will become private - use Number() instead
		 */
	    TReal& iNumber;
	};


//--------------------------------------
//class CAknMultilineDataQuerydialog 
//--------------------------------------

/**
 * Query Dialog with data input on more than one line (2 lines at the moment)
 *
 * Create using NewL methods and passing parameters as appropriate.
 * 
 * Attention: When deriving from this class, you must call SetDataL during 
 *            second phase construction.
 *
 */
class CAknMultiLineDataQueryDialog : public CAknQueryDialog
	{
	public:
		IMPORT_C static CAknMultiLineDataQueryDialog* NewL(TTime& aTime1, TTime& aTime2, TTone aTone = ENoTone);
		IMPORT_C static CAknMultiLineDataQueryDialog* NewL(TDes&  aText1, TDes&  aText2, TTone aTone = ENoTone);
		IMPORT_C static CAknMultiLineDataQueryDialog* NewL(TDes&  aText1, TTime& aTime2, TTone aTone = ENoTone);
		IMPORT_C static CAknMultiLineDataQueryDialog* NewL(TDes&  aText1, TInt&  aNum2,  TTone aTone = ENoTone);
		IMPORT_C static CAknMultiLineDataQueryDialog* NewL(TDes& aText1,  TTimeIntervalSeconds& aDur2, TTone aTone = ENoTone);
		IMPORT_C static CAknMultiLineDataQueryDialog* NewL(TTime& aTime1, TTimeIntervalSeconds& aDur2, TTone aTone = ENoTone);
		IMPORT_C static CAknMultiLineDataQueryDialog* NewL(TInt&  aNum1,  TInt&  aNum2, TTone aTone = ENoTone);

		IMPORT_C virtual ~CAknMultiLineDataQueryDialog();

    protected:
		/**
		 * Set the query data for first and second line
         * Must be called by derived classes during second phase construction
		 * (NewL method)
		 */
		template <class T1, class T2> void SetDataL(T1& aData1, T2& aData2)
			{
			iFirstData  = new (ELeave) TAknQueryData<T1>(aData1);
			iSecondData = new (ELeave) TAknQueryData<T2>(aData2);
			}

		/**
		 * Utility function called by NewL methods - should really be private
		 * but it is left here to show to people extending this class what
		 * their NewL method should do
		 */
		template <class T1, class T2> static CAknMultiLineDataQueryDialog* 
			DoNewL(T1& aData1, T2& aData2, const TTone& aTone)
			{
				CAknMultiLineDataQueryDialog* self = new (ELeave) CAknMultiLineDataQueryDialog(aTone);
				CleanupStack::PushL(self);

				self->SetDataL(aData1,aData2);
	
				CleanupStack::Pop(self);
				return self;
			}
	
	protected:
		/**
		 * Construction and destruction
		 *
		 * @deprecated - will be made protected - use NewL
		 */
		IMPORT_C CAknMultiLineDataQueryDialog(const TTone& aTone);

    public:

        /**
        * Set prompt text for query. This this will override text given in constructor.
        *
        * @param aFirstPrompt   Text for prompt on the first query line 
        * @param aSecondPrompt  Text for prompt on the second query line
        */
	    IMPORT_C void SetPromptL(const TDesC& aFirstPrompt, const TDesC& aSecondPrompt);
		
	public: 

        /**
        * Sets max length for the first editor in a query
        * @param aFirstTextEditorMaxLength  Max length for editor
        */
	    IMPORT_C void SetMaxLengthOfFirstEditor(TInt aFirstTextEditorMaxLength);

        /**
        * Sets max length for the second editor in a query
        * @param aSecondTextEditorMaxLength  Max length for editor
        */
	    IMPORT_C void SetMaxLengthOfSecondEditor(TInt aSecondTextEditorMaxLength);

	protected://from CEikDialog
        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
	    IMPORT_C virtual TBool OkToExitL(TInt aButtonId);

        /**
        * From CEikdialog   This function is called by the EIKON framework 
        *                   if the user activates a button in the button panel. 
        *                   It is not called if the Cancel button is activated, 
        *                   unless the EEikDialogFlagNotifyEsc flag is set.
        * @param aButtonId  The ID of the button that was activated
        * @return           Should return ETrue if the dialog should exit, and EFalse if it should not.
        */
	    IMPORT_C void PreLayoutDynInitL();
	
	protected:
		/**
		* If the query text is ok (retrieved form query controls) then display the 
		* left soft key, otherwise hide it.
		*/
		IMPORT_C void UpdateLeftSoftKeyL();

		/**
		* Set the prompt inside the query control. If dialog is active redo
		* layout and draw.
		*/
		IMPORT_C void DoSetPromptL();

	protected:
        /**
         * Called by OfferkeyEventL(), gives a change to dismiss the query even with
	     * keys different than Enter of Ok.
         *
		 * @param aKeyEvent  Key event which will be checked
         * @return           Should the query be dismissed
         */
		IMPORT_C TBool NeedToDismissQueryL(const TKeyEvent& aKeyEvent);

	protected:
		/**
		 * Access to query controls and heading
		 */
		IMPORT_C CAknMultilineQueryControl* FirstControl() const;
		IMPORT_C CAknMultilineQueryControl* SecondControl() const;
		IMPORT_C CAknQueryControl* QueryControl() const;
		IMPORT_C CAknPopupHeadingPane* QueryHeading() const;

    protected:
		/**
		 * Data access.
		 *
		 * Derived classes can use these methods to get access to the query data
		 * The query data is a reference stored in TAknQueryData, see aknquerydata.h
		 *
		 * The client ultimately owns the data this reference references and so it
		 * should never need to call these methods.
		 *
		 * Derived classes however, might need to set or get the data and hence
		 * these methods have been provided. The derived class is responsible for
		 * choosing the correct type, if not the cast will fail.
		 *
		 */
		template<class T>
			T& FirstData(const T&) { return STATIC_CAST(TAknQueryData<T>*,iFirstData)->iData; }

		template<class T>
			T& SecondData(const T&){ return STATIC_CAST(TAknQueryData<T>*,iSecondData)->iData; }

		template<class T>
			const T& FirstData(const T&) const { return STATIC_CAST(TAknQueryData<T>*,iFirstData)->iData; }

		template<class T>
			const T& SecondData(const T&) const { return STATIC_CAST(TAknQueryData<T>*,iSecondData)->iData; }

		/**
		 * Prompt access for derived classes
		 */
		IMPORT_C TPtrC SecondPrompt() const; 

	private:
	    TDesC* iSecondPrompt;

		MAknQueryData* iFirstData;
		MAknQueryData* iSecondData;

		TInt iFirstEditorMaxLength;
		TInt iSecondEditorMaxLength;

	public:
		/**
		 * Deprecated - use NewL methods instead
		 */
	
        IMPORT_C CAknMultiLineDataQueryDialog(TTime* aTime, TTime* aTime2,TDesC* aPrompt=NULL,TDesC* aPrompt2=NULL, const TTone& aTone = ENoTone);
        IMPORT_C CAknMultiLineDataQueryDialog(TDes* aDataText, TDes* aDataText2,TDesC* aPrompt=NULL,TDesC* aPrompt2=NULL,const TTone& aTone = ENoTone);
        IMPORT_C CAknMultiLineDataQueryDialog(TDes* aDataText, TTime* aTime,TDesC* aPrompt=NULL,TDesC* aPrompt2=NULL,const TTone& aTone = ENoTone);
        IMPORT_C CAknMultiLineDataQueryDialog(TDes* aDataText, TInt* aNumber,TDesC* aPrompt=NULL,TDesC* aPrompt2=NULL,const TTone& aTone = ENoTone);
        IMPORT_C CAknMultiLineDataQueryDialog(TDes* aDataText, TTimeIntervalSeconds* aDuration,TDesC* aPrompt=NULL,TDesC* aPrompt2=NULL,const TTone& aTone = ENoTone);
        IMPORT_C CAknMultiLineDataQueryDialog(TTime* aTime, TTimeIntervalSeconds* aDuration,TDesC* aPrompt=NULL,TDesC* aPrompt2=NULL,const TTone& aTone = ENoTone);
        IMPORT_C CAknMultiLineDataQueryDialog(TInt* aNumber, TInt* aNumber2,TDesC* aPrompt=NULL,TDesC* aPrompt2=NULL,const TTone& aTone = ENoTone);
	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: 
		IMPORT_C virtual void CAknDialog_Reserved();
	private:
		IMPORT_C virtual void CAknQueryDialog_Reserved();
	protected:
		/**
		 * Deprecated - use data access template methods instead
		 */
	    TDes16* iText;       /// Deprecated do not use
	    TDes16* iSecondText; /// Deprecated do not use
	};

///Deprecated
//This one is included here for backwards compatibility
//and will be removed as soon as apps using listquerydialog
//include it directly
#include <aknlistquerydialog.h>

#endif
