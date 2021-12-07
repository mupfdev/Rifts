/*
* =============================================================================
*  Name     : CAknExQueryRollerListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYROLLERLISTEVENTHANDLER_H
#define AKNEXQUERYROLLERLISTEVENTHANDLER_H

// INCLUDES
#include "AknExQueryBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExQueryContainer;

// CLASS DECLARATION

/**
*  CAknExQueryRollerListEventHandler class.
*/
class CAknExQueryRollerListEventHandler :
    public CAknExQueryBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aContainer Pointer to Container class object.
        */
        CAknExQueryRollerListEventHandler( CAknExQueryContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExQueryRollerListEventHandler();

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
