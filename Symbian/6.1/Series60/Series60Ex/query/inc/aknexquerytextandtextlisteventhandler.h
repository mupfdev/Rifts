/*
* =============================================================================
*  Name     : CAknExQueryTextAndTextListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYTEXTANDTEXTLISTEVENTHANDLER_H
#define AKNEXQUERYTEXTANDTEXTLISTEVENTHANDLER_H

// INCLUDES
#include "AknExQueryBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExQueryContainer;

// CLASS DECLARATION

/**
* CAknExQueryTextAndTextListEventHandler class.
*/
class CAknExQueryTextAndTextListEventHandler :
    public CAknExQueryBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aContainer Pointer to Container class object.
        */
        CAknExQueryTextAndTextListEventHandler(
            CAknExQueryContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExQueryTextAndTextListEventHandler();

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
