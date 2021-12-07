/*
* =============================================================================
*  Name     : CAknExNoteContainer
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTECONTAINER_H
#define AKNEXNOTECONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <aknnotedialog.h>
#include <AknNotifyStd.h>
#include <apadef.h>
#include <aknprogressdialog.h>
// FORWARD DECLARATIONS
class CEikLabel;
class CAknExNoteView;
class CEikColumnListBox;
class CAknExNoteBaseListEventHandler;
class CAknStaticNoteDialog;

// CONSTANTS

// CLASS DECLARATION

/**
* CAknExNoteContainer container control class.
*/
class CAknExNoteContainer : public CCoeControl, MProgressDialogCallback
    {
    private: // Enumerations

        enum TAknExNoteComponentControls
            {
            EAknExNoteComponentLabel,
            EAknExNoteComponentListbox
            };

    public: // Constructors and destructor

        /**
        * constructors.
        * @param aView Pointer to view class object.
        */
        CAknExNoteContainer( CAknExNoteView* aView );

        /**
        * EPOC constructors.
        * @param aRect Client rectangle
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExNoteContainer();

    public: // New functions

        /**
        *
        * @param aResourceId
        */
        void SetTextToLabelL( TInt aResourceId );

        /**
        * Indicates general note
        * @param aResourceId
        * @param TTimeout
        * @param TTone
        */
        void ShowGeneralNoteL(
            TInt aResourceId,
            const CAknNoteDialog::TTimeout aTimeout,
            const CAknNoteDialog::TTone aTone );

        /**
        * Indicates general note.
        * @param aResourceId
        * @param aControlId
        * @param aTimeout
        * @param aTone
        * @param aPlural
        */
        void ShowGeneralNoteL(
            TInt aResourceId,
            TInt aControlId,
            const CAknNoteDialog::TTimeout aTimeout,
            const CAknNoteDialog::TTone aTone,
            TBool aPlural );

        /**
        * Indicates note
        */
        void ShowDynamicNumberNoteL();

        /**
        * Indicates progress note.
        * @param aResourceId
        * @param aControlId
        */
        void ShowProgressNoteL(
            TInt aResourceId,
            TInt aControlId );

        /**
        * Indicates wait note.
        * @param aResourceId
        * @param aControlId
        */
        void ShowWaitNoteL(
            TInt aResourceId,
            TInt aControlId );

        /*
        * Indicates permanent note
        * @param aResourceId
        */
        void ShowPermanentNoteL( TInt aResourceId );

        /*
        * Indicates global note.
        * @param TAknGlobalNoteType aType
        * @param TInt aResourceId
        */
        void ShowGlobalNoteL(
            TAknGlobalNoteType aType,
            TPtrC aNoteText );

        /*
        * Pop out listbox.
        * @param aCommand
        */
        void PopoutListBoxL( TInt aCommand );

        /*
        * Discard listbox and timer, if there are listbox and timer.
        */
        void DiscardListboxAndTimer();

        /**
        * Creates the timer object.
        * @param aFunction
        * @param aPriorityTimer
        * @param aDelayTIme
        * @aIntervalTime
        */
        void CreateTimerL( const TCallBack& aCallBack,
                           TInt aPriorityTimer,
                           TInt aDelayTime,
                           TInt aIntervalTime );

        /**
        * The other application are made forward.
        * @param aApplicationName
        */
        void ForwardOtherApplicationL( TApaAppFileName& aApplicationName );

        /*
        * Indicates Note Wrappers Confirmation.
        */
        void ShowNoteWrappersConfirmationL(); 

        /*
        * Indicates Note Wrappers Information.
        */
        void  ShowNoteWrappersInformationL(); 

        /*
        * Indicates Note Wrappers Warning.
        */
        void  ShowNoteWrappersWarningL(); 

        /*
        * Indicates Note Wrappers Error.
        */
        void  ShowNoteWrappersErrorL(); 


	    /*
	     * Indicates ProgressNote.
	     */
	    void ShowProgressNoteUnderSingleProcessL(TInt aResourceId,   
						     TInt aControlId );

        // Should insert comment.
        void ShowSetNewImageL(const TDesC& aFileName, 
                              TInt aBitmapId, TInt aMaskId=-1);
        void ShowSetNewIconL(const TDesC& aFileName, 
                             TInt aBitmapId, TInt aMaskId=-1);
        void ShowSetDynamicNumberL(TInt aNumber, TBool aFlag);
        void ShowSetCurrentLabelL(TInt aResourceId);
        void ShowLayoutAndDraw();
        void ShowShowNoteL(TAknGlobalNoteType aType, TInt aResourceId, 
                           TBool aFlag=EFalse);
        void ShowCancelNoteL(TBool aFlag);
        void ShowSetPriority(TBool aFlag);
        void ShowSetSoftkeys(TInt aId);
        void ShowSetGraphic(TInt aBitmapId, TInt aMaskId=-1);
        void ShowSetAnimation(TInt aResourceId);
        void ShowProgressSetCurrentLabelL(TInt aId, TInt aResourceId);
        
        /**
        * Show wait dialog by using CAknWaitDialog class.
        * @param aNoteControlId : ID of note control
        * @param aVisibilityDelayOff : If ETrue, dialog is displayed 
        *                              as soon as call ExecuteLD();
        *                              If EFalse wait 1.5 seconds.
        * @param aResourceId : resource ID.
        */
        void ShowNoteByCAknWaitDialogL(
             TInt aNoteControlId, TBool aVisibilityDelayOff, TInt aResourceId);

        /**
        * Callback function to increment progress note
        * Return 0 when work is done, otherwise return 1.
        */
        static TInt CallbackIncrementProgressNoteL( TAny* aThis );
        
        /**
        * The entity of ProgressCallBackL() function
        * Return 0 when work is done, otherwise return 1.
        */
        TInt UpdateProgressNote();

        /**
        * Callback function for displaying the global general note.
        */
        static TInt CallbackShowGlobalGeneralNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global warning note.
        */
        static TInt CallbackShowGlobalWarningNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global confirmation note.
        */
        static TInt CallbackShowGlobalConfirmationNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global error note.
        */
        static TInt CallbackShowGlobalErrorNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global changing note.
        */
        static TInt CallbackShowGlobalChargingNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global no changing note.
        */
        static TInt CallbackShowGlobalNotChargingNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global battery full note.
        */
        static TInt CallbackShowGlobalBatteryFullNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global battery low note.
        */
        static TInt CallbackShowGlobalBatteryLowNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global recharge battery note.
        */
        static TInt CallbackShowGlobalRechargeBatteryNoteL( TAny* aThis );

        /**
        * Callback function for displaying the local note.
        */
        static TInt CallbackShowPriorityLocalNoteL( TAny* aThis );

        /**
        * Callback function for displaying the global note.
        */
        static TInt CallbackShowPriorityGlobalNoteL( TAny* aThis );

        /**
        * Callback function for deleting permanent note.
        * @param : aThis : this pointer
        * @return : always 0.
        */
        static TInt PermanentNoteTimeoutL( TAny* aThis );

        /**
        * Callback function for deleting wait note.
        * @param : aThis : this pointer
        * @return : always 0.
        */
        static TInt WaitNoteTimeoutL( TAny* aThis );

    public: // From MProgressDialogCallback
        /**
        * Called when/if the dialog has been dismissed.
        */
        void DialogDismissedL(TInt aButtonId);

    private: // New functions

        /**
        * Creates the label object.
        */
        void CreateLabelL();

        /**
        * Creates the List box.
        * @param aCommand
        */
        TBool CreateListBoxL( TInt aCommand );

    private: // From CCoeControl

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @return if key-event is consumed, EKeyWasConsumed. Else EKeyWasNotConsumed
        * @param aKeyEvent Key event
        * @param aType Type of key event (EEventKey, EEventKeyUp or EEventKeyDown)
        */
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

        /**
        * From CCoeControl, SizeChanged.
        */
        void SizeChanged();

        /**
        * From CCoeControl, CountComponentControls.
        * Returns number of component.
        * @return Number of controls
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl, ComponentControl.
        * Returns pointer to particular component.
        * @return Pointer to Control's component control, identified by index
        * @param aIndex Index of the control
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * From CCoeControl, Draw.
        * @param aRect Region of the control to be (re)drawn.
        */
        void Draw( const TRect& aRect ) const;

    private: // Data

        CEikLabel* iLabel;
        CAknExNoteView* iView;
        CEikColumnListBox* iListBox;
        CAknExNoteBaseListEventHandler* iHandler;
        CPeriodic* iTimer;
        CPeriodic* iPermanentTimer;
        CPeriodic* iWaitNoteTimer;
        CIdle* iIdle;
        CAknProgressDialog* iProgressDialog;
        CEikProgressInfo* iProgressInfo;
        TInt iGlobalNoteId;
        TInt iPermanentNoteId;
        TRequestStatus iStatus;
    };

#endif

// End of File
