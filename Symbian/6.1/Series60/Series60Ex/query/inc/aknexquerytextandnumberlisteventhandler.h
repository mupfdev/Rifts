/*
* =============================================================================
*  Name     : CAknExQueryTextAndNumberListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYTEXTANDNUMBERLISTEVENTHANDLER_H
#define AKNEXQUERYTEXTANDNUMBERLISTEVENTHANDLER_H

// INCLUDES
#include "AknExQueryBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExQueryContainer;

// CLASS DECLARATION

/**
* CAknExQueryTextAndNumberListEventHandler class.
*/
class CAknExQueryTextAndNumberListEventHandler :
    public CAknExQueryBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aContainer Pointer to Container class object.
        */
        CAknExQueryTextAndNumberListEventHandler(
            CAknExQueryContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExQueryTextAndNumberListEventHandler();

    private: // From CAknExQueryBaseListEventHandler

        /**
        * From CAknExQueryBaseListEventHandler, HandlerSelectedListItem.
        * Handles the event which list item selected.
        * @param aCommand Selected item index
        */
        void HandleSelectedListItemL( TInt aCommand );

    };

#endif

// End of File
