/*
* =============================================================================
*  Name     : CAknExQueryEditorListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYEDITORLISTEVENTHANDLER_H
#define AKNEXQUERYEDITORLISTEVENTHANDLER_H

// INCLUDES
#include "AknExQueryBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExQueryContainer;

// CLASS DECLARATION

/**
* CAknExQueryEditorListEventHandler class.
*/
class CAknExQueryEditorListEventHandler :
    public CAknExQueryBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aContainer Pointer to Container class object.
        */
        CAknExQueryEditorListEventHandler( CAknExQueryContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExQueryEditorListEventHandler();

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
