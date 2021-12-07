/*
* ============================================================================
*  Name     : CAknWaitNoteWrapper.h
*  Part of  : Avkon
*
*  Description:
*     Declares a wait note wrapper.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef CAknWaitNoteWrapper_H
#define CAknWaitNoteWrapper_H

// INCLUDES
#include <e32base.h>
#include <AknProgressDialog.h>


// CONSTANTS
class CAknWaitDialog;


// CLASS DECLARATION

/**
 * Abstract process divided into steps.
 */
class MAknBackgroundProcess
    {
    public: // interface
        /**
         * Completes one cycle of the process.
         */
        virtual void StepL()=0;

        /**
         * Return true when the process is done.
         */
        virtual TBool IsProcessDone() const =0;

        /**
         * Callback when the process is finished.
         */
        virtual void ProcessFinished() { }

        /**
        * Callback when the dialog is dismissed
        */
        virtual void DialogDismissedL(TInt /*aButtonId*/) { }

        /**
         * Handles error occurred in StepL
         * @param aError error code that occurred
         * @return translated error code. If this is != KErrNone process will be stopped.
         */
        virtual TInt CycleError(TInt aError) { return aError; }
    };

/**
 * CAknWaitNoteWrapper class.
 */
class CAknWaitNoteWrapper : private CActive, private MProgressDialogCallback
    {
    public: // constructor and destructor
        IMPORT_C static CAknWaitNoteWrapper* NewL();
        
        IMPORT_C ~CAknWaitNoteWrapper();

    public: // interface
        /**
         * Executes the wait note and calls the cycle callback.
		 *
		 * @param aResId                Resource id for the dialog.
         * @param aBackgroundProcess    Callback interface.
         * @param aVisibilityDelayOff   If set ETrue the dialog will be visible
         *                              immediality. Use only when the length of
         *                              the process is ALWAYS over 1.5 seconds.
         * @param aTone                 Will be played when the dialog is shown.
         *
		 * @return true if success, false if wait note was canceled.
         */
        IMPORT_C TBool ExecuteL(TInt aResId, MAknBackgroundProcess& aBackgroundProcess,
            TBool aVisibilityDelayOff = EFalse, const CAknNoteDialog::TTone& aTone = CAknNoteDialog::ENoTone); 


		 /**
         * Executes the wait note and calls the cycle callback.
		 * Dynamically set note prompt.
		 *
		 * @param aResId                Resource id for the dialog.
         * @param aBackgroundProcess    Callback interface.
         * @param aPrompt               Note Prompt
		 * @param aVisibilityDelayOff   If set ETrue the dialog will be visible
         *                              immediality. Use only when the length of
         *                              the process is ALWAYS over 1.5 seconds.
         * @param aTone                 Will be played when the dialog is shown.
         *
		 * @return true if success, false if wait note was canceled.
         */
        IMPORT_C TBool ExecuteL(TInt aResId, MAknBackgroundProcess& aBackgroundProcess,
			const TDesC& aPrompt, TBool aVisibilityDelayOff = EFalse, const CAknNoteDialog::TTone& aTone = CAknNoteDialog::ENoTone); 

		/**
		* Return pointer to dialog
		*/
		inline CAknWaitDialog* WaitDialog() const; 

    private: // from CActive
	    void DoCancel();
	    void RunL();
        TInt RunError(TInt aError);

    private:  // from MProgressDialogCallback
        void DialogDismissedL(TInt aButtonId);

    private: // implementation
        class CWaitNote;

        CAknWaitNoteWrapper();
        void NextCycle();

		TBool NextCycleAndReturnL();
		void CreateDialogL(TBool aVisibilityDelayOff, const CAknNoteDialog::TTone& aTone);


    private: // data members
        /// Ref: callback to client
        MAknBackgroundProcess* iBackgroundProcess;
        /// Own: error code from RunL
        TInt iRunError;
        /// Own: wait note dialog
        CAknWaitDialog* iWaitDialog;
        /// Own: is dialog dismissed
        TBool iIsDialogCanceled;
		/// Own: scheduler wait object, safe to use as direct member data.
		CActiveSchedulerWait iWait;
		///Event generator for this AO (interval is zero seconds)
		RTimer iTimer;

    };

CAknWaitDialog* CAknWaitNoteWrapper::WaitDialog() const { return iWaitDialog;}

#endif

// End of File
