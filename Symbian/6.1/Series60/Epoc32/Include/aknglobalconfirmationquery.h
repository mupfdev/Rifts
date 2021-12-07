/*
* ============================================================================
*  Name     : AknGlobalConfirmationQuery.h
*  Part of  : Avkon
*
*  Description:
*   Uses notification framework to show a global listquery.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNGLOBALCONFIRMATIONQUERY_H__
#define __AKNGLOBALCONFIRMATIONQUERY_H__

#include <AknNotify.h>
#include <aknnotifystd.h>
#include <aknquerydialog.h>

/**
* CAknGlobalConfirmationQuery
*   Uses notification framework to show a global confirmation query.
*   Usage:
*       Create an active object, start it and pass its TRequestStatus as a
*       parameter to ShowConfirmationQueryL. After the user presses a softkey,
*       the request status will hold the id of the
*       pressed softkey. E.g. If the user selected Cancel, the request status will
*       hold -1.
*
*   Example 1. Show the global confirmation query:
*        if ( iConfObserver )
*            {
*            iConfObserver->Cancel();
*            delete iConfObserver;
*            }
*        iConfObserver = new(ELeave) CGlobalConfirmationObserver(iEikonEnv);
*        iConfObserver->Start();
*        iGlobalConfirmationQuery->ShowMsgQueryL(iConfObserver->iStatus, 
*                                       iPrompt, 
*                                       R_AVKON_SOFTKEYS_OK_CANCEL,
*                                       R_QUERY_NOTE_ANIMATION);
*
*
*   Example 2. Get and handle the result in active object.
*        void CMyActiveObject::RunL() 
*            {
*            TBuf<120> msg = _L("Received: ");
*            msg.AppendNum( iStatus.Int() );
*            iEnv->InfoMsg(msg);
*            Cancel();
*            }
*
*   Example 3. Update the query (softkeys)
*       iGlobalConfirmationQuery->UpdateConfirmationQuery( R_AVKON_SOFTKEYS_BACK );
*
*   Example 4. Cancel the query
*       iGlobalConfirmationQuery->CancelConfirmationQuery();
*
* NOTE !!! All descriptors passed as parameters need to be class members, i.e.
*           they cannot be local variables of a method. That is because
*           they need to exist when server gets the message.
*/

class CAknGlobalConfirmationQuery : public CBase
    {
    public:
	    
	    IMPORT_C static CAknGlobalConfirmationQuery* NewL();
	    IMPORT_C static CAknGlobalConfirmationQuery* NewLC();
	    IMPORT_C ~CAknGlobalConfirmationQuery();

        /**
        * Shows global Confirmation query synchronously
        *
        * @param    aStatus         TRequestStatus which will be completed when user
        *                               selects one item from the list query.
        * @param    aPrompt         Prompt text
        * @param    aSoftkeys       Softkey resource 
        * @param    aAnimation      Animation resource
        * @param    aTone           Tone id
        * @param    aDismissWithAllKeys If set ETrue the query gets dismissed with all
        *                                   keypresses
        */
        IMPORT_C void ShowConfirmationQueryL( TRequestStatus& aStatus,
                                    const TDesC& aPrompt,
                                    TInt aSoftkeys = 0,
                                    TInt aAnimation = 0,
                                    const TDesC& aImageFile = KNullDesC,
                                    TInt aImageId = 0,
                                    TInt aImageMaskId = 0,
                                    CAknQueryDialog::TTone aTone = CAknQueryDialog::ENoTone,
                                    TBool aDismissWithAllKeys = EFalse );
        /**
        * Update the softkeys of the confirmation query
        *
        * @param    aSoftkeys  New resource for softkeys
        */
        IMPORT_C void UpdateConfirmationQuery( TInt aSoftkeys );


        /**
        * Cancel the confirmation query
        */
        IMPORT_C void CancelConfirmationQuery();

    
    private:
	    CAknGlobalConfirmationQuery();
	    void ConstructL(); 

    private:
        TAknGlobalQueryCmd iCmd;
        TInt iSoftkeys;
        TInt iAnimation;
        CAknQueryDialog::TTone iTone;
        RNotifier iNotify;
		CBufFlat *iBuffer;
		TPtrC8 iBufferPtr;
    };


#endif
