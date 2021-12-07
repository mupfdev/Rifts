/*
* =============================================================================
*  Name     : CAknExNoteGeneralListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTEGENERALLISTEVENTHANDLER_H
#define AKNEXNOTEGENERALLISTEVENTHANDLER_H

// INCLUDES
#include "AknExNoteBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExNoteContainer;

// CONSTANTS

// CLASS DECLARATION

/**
* CAknExNoteGeneralListEventHandler container control class.
*/
class CAknExNoteGeneralListEventHandler :
    public CAknExNoteBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Overload constructors.
        * @param aContainer Pointer to CAknExNoteContainer class object.
        */
        CAknExNoteGeneralListEventHandler( CAknExNoteContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExNoteGeneralListEventHandler();

    private: // From CAknExNoteBaseListEventHandler

        /**
        * From CAknExNoteBaseListEventHandler, HandlerSelectedListItem.
        * Handles the event which list item selected.
        * @param aCommand Selected item index
        */
        void HandleSelectedListItemL( TInt aCommand );

    };

#endif

// End of File
