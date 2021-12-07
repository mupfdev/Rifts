/*
* ============================================================================
*  Name     : AknProgressDialog.h
*  Part of  : Avkon
*
*  Description:
*       CAknProgressDialog should be used when the progress of the process
*       can be traced and the length of the process is known. If that's not
*       the case please use CAknWaitDialog.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKN_PROGRESS_DIALOG__
#define __AKN_PROGRESS_DIALOG__

#include <aknnotedialog.h>
#include <aknprogresstimer.h>

class CEikProgressInfo;

/**
 * MProgressDialogCallBack
 *   Inherit from this class and implement DialogDismissed to
 *   get a callback when/if a dialog is dismissed.
 */
class MProgressDialogCallback
    {
    public:
        /**
        * Callback method
        *   Get's called when a dialog is dismissed.
        */
        virtual void DialogDismissedL( TInt aButtonId ) = 0;
    };


/**
* CAknProgressDialog
*
* A note dialog with a timer. Display the note only if the process is at least 1 second long
* in order to avoid a note quickly flashing on the screen. Display the note for at least 1.5
* seconds (even if the client process is shorter that this). The client can specify an initial
* delay when displaying the note. Timer events are used for displaying and dismissing the dialog.
* The client can set the progress by specyfing the values in the constructors provided.
*
* Usage:<UL> 
*   <LI> Fixed process length
*      
*        iProgressDialog = new(ELeave)CAknProgressDialog(model->FinalValue(),model->Increment(),
*                                model->Interval(),
*                                (REINTERPRET_CAST(CEikDialog**,&iProgressDialog)));
*        iProgressDialog->ExecuteLD(R_PROGRESS_NOTE);
*   </LI>
*
*   <LI> Variable process length
*      
*        iProgressDialog = new(ELeave)CAknProgressDialog(
*                                (REINTERPRET_CAST(CEikDialog**,&iProgressDialog)));
*        iProgressInfo = iProgressDialog->GetProgressInfoL();
*        iProgressInfo->SetFinalValue(model->FinalValue());
*        iProgressDialog->ExecuteLD(R_PROGRESS_NOTE);
* 
*        // Incrementing progress of the process:
*        iProgressInfo->IncrementAndDraw(model->Increment());
* 
*        // Process finished
*        iProgressDialog->ProcessFinishedL(); // deletes the dialog
*   </LI> 
*   <LI> Variable process length, modal dialog
*      
*        Set following flags in resources: EEikDialogFlagWait and EAknProgressNoteFlags
*
*        iProgressDialog = new(ELeave)CAknProgressDialog(
*                                (REINTERPRET_CAST(CEikDialog**,&iProgressDialog)));
*        iProgressInfo = iProgressDialog->GetProgressInfoL();
*        iProgressInfo->SetFinalValue(model->FinalValue());
*        iProgressInfo->SetTone( CAknNoteDialog::EConfirmationTone );
*        iProgressDialog->ExecuteLD(R_PROGRESS_NOTE);
* 
*        // Incrementing progress of the process:
*        iProgressInfo->IncrementAndDraw(model->Increment());
* 
*        // Process finished
*        iProgressDialog->ProcessFinishedL(); // deletes the dialog
*
*   <LI> Setting label dynamically
*     
*        iProgressDialog = new(ELeave)CAknProgressDialog(
*                                (REINTERPRET_CAST(CEikDialog**,&iProgressDialog)));
*        iProgressDialog->PrepareLC(R_PROGRESS_NOTE);
*        iProgressDialog->SetTextL(_L("Hello AVKON!"));
*        iProgressDialog->RunLD();
*
*    </LI></UL>
* <P>Callback:
*       To get a callback when/if the dialog has been dismissed
*       use SetCallBack API:
*           With class which uses a progressdialog:
*           - Inherit from pure virtual class MProgressDialogCallback
*           - Implement DialogDismissedL
*           - Call CAknProgressDialog->SetCallback(this);
*       
*       Or make your dialog modal. If the dialog is used as a modal, RunLD
*       returns 0 if the dialog is dismissed and EAknSoftkeyDone if not.
* </P>
* <P>Resource flags:
*        -   Always set EEikDialogFlagNotifyEsc. (or use preset avkon
*                   dialog resource flag, i.e. EAknProgressNoteFlags).
*        -   To make a dialog modal use EEikDialogFlagWait
* </P>
* <P>Note! If aVisibilityDelayOff is set to ETrue in constructor the dialog
*   will be visible immediality. This should only be used in cases where
*   the process lasts ALWAYS atleast 1.5 seconds.
* </P>
*  <P> For comprehensive example, see \Akndemo\Notesapp </P>
*/

class CAknProgressDialog : public CAknNoteDialog  
{
public:
    /**
    * Constructor
    *   Use this when the length (in time) of the process is known.
    * @param    aFinalValue     Final value for the process
    * @param    anIncrement     Increment of the process
    * @param    anInterval      Interval of the process
    * @param    aSelfPtr        Pointer to itself. The pointer must be
    *                           valid when the dialog is dismissed and it 
	*                           must not be on the stack.
    * @param    aNoteControlId  Note control's id set in resources.
    */
	IMPORT_C CAknProgressDialog(TInt aFinalValue,TInt anIncrement,TInt anInterval, CEikDialog** aSelfPtr);

    /**
    * Constructor
    *   Use this if the length of the process is unknown but the progress
    *   can be calculated.
    * @param    aNoteControlId  Note control's id set in resources.
    * @param    aSelfPtr        Pointer to itself. The pointer must be
    *                           valid when the dialog is dismissed and it
	*                           must not be on the stack.
    */
	IMPORT_C CAknProgressDialog(CEikDialog** aSelfPtr);

    /**
    * Constructor
    *   Use this if the length of the process is unknown but the progress
    *   can be calculated.
    * @param    aNoteControlId  Note control's id set in resources.
    * @param    aSelfPtr        Pointer to itself. The pointer must be
    *                           valid when the dialog is dismissed and it must
	*                           not be on the stack.
    * @param    aVisibilityDelayOff If set ETrue the dialog will be visible
    *                                   immediality. Use only when the length of
    *                                   the process is ALWAYS over 1.5 seconds.
    */
	IMPORT_C CAknProgressDialog(CEikDialog** aSelfPtr,TBool aVisibilityDelayOff);

    /**
    * Destructor
    */
	IMPORT_C virtual ~CAknProgressDialog();

	/**
    * Executes the dialog (part of dialog framework).
	* PrepareLC needs to be called before this. 
    */
	IMPORT_C virtual TInt RunLD();

    /**
    *   Get a handle to the progress bar.
    */
	IMPORT_C CEikProgressInfo* GetProgressInfoL();

    /**
    *  Handle key events (part of CONE framework)
    */
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    /**
    * This must be called when the dialog must be dismissed. 
	* It stops the timer and deletes the dialog.
    */
    IMPORT_C void ProcessFinishedL();

    /**
    * This callback notifies the client when the dialog is dismissed.
    * @param    aCallBack   A pointer to a class that inherits from
    *                       MProgressDialogCallback.
    */
    IMPORT_C void SetCallback( MProgressDialogCallback* aCallback );

protected:
    /**
    * Enumeration to handle progress states
    */
    enum TProgressDialogState
        {
        EProcessOnDisplayOff, /// cannot be dismissed
        EProcessOnDisplayOn, /// cannot be dismissed
        EProcessOffDisplayOff, /// can be dismissed
        EProcessOffDisplayOn, /// cannot be dismissed
        EProcessOffDisplayOnCanBeDismissed, /// can be dismissed
        EProcessOnDisplayOnCanBeDismissed /// can be dismissed when process ends
        };

    /**
    *   Initializes dialog before layout is executed (part of dialog framework).
    */
    IMPORT_C void PreLayoutDynInitL(void);

    /**
    * Timer callback.
	*
    * @param aPtr   Pointer to this
    */
    static TInt DialogTimerCallback(TAny* aPtr);

    /**
    *   Handles timer events.
    */
    TInt DialogTimerEvent();

    /**
    * Called by the dialog framework, returns true if the 
	* dialog can exit, false otherwise.
	*
    * @param aButtonId  Id of the softkey which was pressed
    * @return           ETrue if the dialog can exit, false otherwise.
    */
    IMPORT_C TBool OkToExitL(TInt aButtonId);

protected:
    /// Timer to handle dialog's visibility and existence
    CPeriodic* iProgressDialogTimer;
    /// State to handle dialog's visibility and existence
    TProgressDialogState iState;
    /// Contains progress timer's variables
    TTimerModel iModel;
    /// Callback pointer
    MProgressDialogCallback* iCallback;
    /// Boolean to declare whether the visibility delay should
    ///  be on or off.
    TBool iVisibilityDelayOff;

private:
    // Boolean to declare whether the progress is handled by
    //  an internal timer
	TBool iInternalTimerControl;
    // Timer to handle progress if iInternalTimerControl is
    //  set to ETrue
    CAknProgressTimer* iProgressTimer;

private: 
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();	
private: 
	IMPORT_C virtual void CAknNoteDialog_Reserved();
};

#endif
