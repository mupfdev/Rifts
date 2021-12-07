/*
* =============================================================================
*  Name     : CAknExNoteBaseListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTEBASELISTEVENTHANDLER_H
#define AKNEXNOTEBASELISTEVENTHANDLER_H

// INCLUDES
#include <e32base.h>
#include <eiklbo.h> // For MEikListBoxObserver

// FORWARD DECLARATIONS
class CAknExNoteContainer;

// CONSTANTS

// CLASS DECLARATION

/**
* CAknExNoteBaseListEventHandler container control class.
*/
class CAknExNoteBaseListEventHandler :
    public CBase,
    public MEikListBoxObserver
    {
    public: // Constructors and destructor

        /**
        * Overload constructors.
        * @param aContainer Pointer to CAknExNoteContainer class object
        */
        CAknExNoteBaseListEventHandler( CAknExNoteContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExNoteBaseListEventHandler();

    public: // New funcsion

        /**
        * Handles events that list item selected.
        * Pure virtual function.
        * @param aCommand Selected list item index
        */
        virtual void HandleSelectedListItemL( TInt aCommand ) = 0;

    public: // From MEikListBoxObserver

        /**
        * From MEikListBoxObserver, HandleListBoxEventL.
        * Handles the list box events.
        * When list item is selected, HandleSelectedListItemL() is called.
        * @param aListBox Pointer to list box object
        * @param aEventType Type of list box event
        */
        void HandleListBoxEventL(
            CEikListBox* aListBox,
            TListBoxEvent aEventType );

    protected: // Data

        CAknExNoteContainer* iContainer;

    };

#endif

// End of File
