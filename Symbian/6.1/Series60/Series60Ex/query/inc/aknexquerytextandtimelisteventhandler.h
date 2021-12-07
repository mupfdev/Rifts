/*
* =============================================================================
*  Name     : CAknExQueryTextAndTimeListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYTEXTANDTIMELISTEVENTHANDLER_H
#define AKNEXQUERYTEXTANDTIMELISTEVENTHANDLER_H

// INCLUDES
#include "AknExQueryBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExQueryContainer;

// CLASS DECLARATION

/**
* CAknExQueryTextAndTimeListEventHandler class.
*/
class CAknExQueryTextAndTimeListEventHandler :
    public CAknExQueryBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aContainer Pointer to Container class object.
        */
        CAknExQueryTextAndTimeListEventHandler(
            CAknExQueryContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExQueryTextAndTimeListEventHandler();

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
