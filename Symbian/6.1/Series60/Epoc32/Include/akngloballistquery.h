/*
* ============================================================================
*  Name     : AknGlobalListQuery.h
*  Part of  : Avkon
*
*  Description:
*   Uses notification framework to show a global listquery.
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef __AKNGLOBALLISTQUERY_H__
#define __AKNGLOBALLISTQUERY_H__

#include <AknNotify.h>
#include <aknnotifystd.h>

#include <bamdesca.h>

// Default index for list query
const TInt KGlobalListQueryDefaultIndex = 0;

_LIT( KGlobalListQueryItemSeparator, "\n");

/**
* CAknGlobalListQuery
*   Uses notification framework to show a global listquery.
*   Usage:
*       Create an active object, start it and pass its TRequestStatus as a
*       parameter to ShowListQueryL. After the user selects one item from
*       the listquery, the request status will hold the number of the
*       selected item. If the user selected Cancel, the request status will
*       hold -1.
*
*   Example 1. Show the global list query:
*        CDesCArray* textArray = iCoeEnv->ReadDesCArrayResourceL( R_GLOBAL_LIST_ARRAY );
*        CleanupStack::PushL(textArray);
*        TInt result = -555;
*        if ( iListObserver )
*            {
*            iListObserver->Cancel();
*            delete iListObserver;
*            }
*        iListObserver = new(ELeave) CGlobalListObserver(iEikonEnv);
*        iListObserver->Start();
*        iGlobalListQuery->ShowListQueryL(textArray, iListObserver->iStatus, 4);
*        CleanupStack::PopAndDestroy(); // textArray
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
*/

class CAknGlobalListQuery : public CBase
    {
    public:
        /**
        * Two-phased constructor.
        */
	    IMPORT_C static CAknGlobalListQuery* NewL();

        /**
        * Two-phased constructor.
        *   Leaves the instance to cleanupstack
        */
	    IMPORT_C static CAknGlobalListQuery* NewLC();

        /**
        * Destructor
        */
	    IMPORT_C ~CAknGlobalListQuery();

        /**
        * Shows global list query synchronously
        *
        * @param    aItems  Strings for items
        * @param    aStatus TRequestStatus which will be completed when user
        *                       selects one item from the list query.
        * @param    aIndex  Index which item in the list will be highlighted 
        */
        IMPORT_C void ShowListQueryL( const MDesCArray* aItems,
                                      TRequestStatus& aStatus,
	                                  const TInt aIndex = KGlobalListQueryDefaultIndex
                                      );

        /**
        * Move selection up
        */
        IMPORT_C void MoveSelectionUp();

        /**
        * Move selection down
        */
        IMPORT_C void MoveSelectionDown();

        /**
        * Select currently selected item in the list
        */
        IMPORT_C void SelectItem();

        /**
        * Cancel the list query
        */
        IMPORT_C void CancelListQuery();

    private:
        /**
        * Updates list query
        */
        IMPORT_C void UpdateListQuery();

    private:
        /**
        * Default constructor
        */
	    CAknGlobalListQuery();

        /**
        * EPOC constructor
        */
	    void ConstructL(); 

    private:
        // Command id
        TAknGlobalQueryCmd iCmd;
        // Notifier handle
        RNotifier iNotify;
        // Index to set which item will be selected
        TInt iIndex;
        // Buffer to hold the variables passed to server
		CBufFlat *iBuffer;
        // Pointer to buffer
		TPtrC8 iBufferPtr;
    };


#endif
