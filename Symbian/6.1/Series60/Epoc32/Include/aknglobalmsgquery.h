/*
* ============================================================================
*  Name     : AknGlobalMsgQuery.h
*  Part of  : Avkon
*
*  Description:
*   Uses notification framework to show a global listquery.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNGLOBALMSGQUERY_H__
#define __AKNGLOBALMSGQUERY_H__

#include <AknNotify.h>
#include <aknnotifystd.h>
#include <aknquerydialog.h>

/**
* CAknGlobalMsgQuery
*   Uses notification framework to show a global message query.
*   Usage:
*       Create an active object, start it and pass its TRequestStatus as a
*       parameter to ShowMsgQueryL. After the user presses a softkey,
*       the request status will hold the id of the
*       pressed softkey. E.g. If the user selected Cancel, the request status will
*       hold -1.
*
*   Example 1. Show the global message query:
*        if ( iListObserver )
*            {
*            iListObserver->Cancel();
*            delete iListObserver;
*            }
*        iMsgObserver = new(ELeave) CGlobalMsgObserver(iEikonEnv);
*        iMsgObserver->Start();
*        iGlobalMsgQuery->ShowMsgQueryL(iMsgObserver->iStatus, iMsgText, 
*                                       R_AVKON_SOFTKEYS_OK_CANCEL, iMsgHeader,
*                                       iHeaderImageFile, EImageId, EMaskId );
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
*       iGlobalMsgQuery->UpdateMsgQuery( R_AVKON_SOFTKEYS_BACK );
*
*   Example 4. Cancel the query
*       iGlobalMsgQuery->CancelMsgQuery();
*
* NOTE !!! All descriptors passed as parameters need to be class members, i.e.
*           they cannot be local variables of a method. That is because
*           they need to exist when server gets the message.
*/

class CAknGlobalMsgQuery : public CBase
    {
    public:
	    
	    IMPORT_C static CAknGlobalMsgQuery* NewL();
	    IMPORT_C static CAknGlobalMsgQuery* NewLC();
	    IMPORT_C ~CAknGlobalMsgQuery();

        /**
        * Shows global message query synchronously
        *
        * @param    aMsgText        Message text
        * @param    aHeaderText     Header text
        * @param    aSoftkeys       Softkey resource 
        * @param    aStatus         TRequestStatus which will be completed when user
        *                               selects one item from the list query.
        */
        IMPORT_C void ShowMsgQueryL( TRequestStatus& aStatus,
                                    const TDesC& aMsgText,
                                    TInt aSoftkeys,
                                    const TDesC& aHeaderText,
                                    const TDesC& aHeaderImageFile,
                                    TInt aImageId = 0,
                                    TInt aImageMaskId = -1,
                                    CAknQueryDialog::TTone aTone = CAknQueryDialog::ENoTone);
        /**
        * DO NOT USE !!! Will be discarded !!!
        */
        IMPORT_C void ShowMsgQuery( TRequestStatus& aStatus,
                                    const TDesC& aMsgText,
                                    TInt aSoftkeys,
                                    const TDesC& aHeaderText,
                                    const TDesC& aHeaderImageFile,
                                    TInt aImageId = 0,
                                    TInt aImageMaskId = -1,
                                    CAknQueryDialog::TTone aTone = CAknQueryDialog::ENoTone);
        /**
        * Update the softkeys of the message query
        *
        * @param    aSoftkeys  New resource for softkeys
        */
        IMPORT_C void UpdateMsgQuery( TInt aSoftkeys );


        /**
        * Cancel the message query
        */
        IMPORT_C void CancelMsgQuery();

    
    private:
	    CAknGlobalMsgQuery();
	    void ConstructL(); 

    private:
        TAknGlobalQueryCmd iCmd;
        TInt iSoftkeys;
        TInt iImageId;
        TInt iImageMaskId;
        CAknQueryDialog::TTone iTone;
        RNotifier iNotify;
		CBufFlat *iBuffer;
		TPtrC8 iBufferPtr;
    };


#endif
