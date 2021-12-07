/*
* ============================================================================
*  Name     : CAknExScrollerAppUi from CAknViewAppUi
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSCROLLERAPPUI_H
#define AKNEXSCROLLERAPPUI_H

// INCLUDES
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>

// FORWARD DECLARATIONS


// CLASS DECLARATION

/**
* CAknExScrollerAppUi
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
*
*/
class CAknExScrollerAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExScrollerAppUi();

        /**
        * EPOC default constructor.
        */      
        void ConstructL();

        /**
        * Destructor.
        */      
        virtual ~CAknExScrollerAppUi();

    private:
        /**
        * From CEikAppUi, takes care of command handling.
        * @param aCommand command to be handled
        */
        void HandleCommandL( TInt aCommand );

        /**
        * From CEikAppUi, handles key events.
        * @param aKeyEvent Event to handled.
        * @param aType Type of the key event. 
        * @return Reponse code (EKeyWasConsumed, EKeyWasNotConsumed). 
        */
        virtual TKeyResponse HandleKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

    private: //Data
        CAknNavigationControlContainer* iNaviPane;
        CAknTabGroup*                   iTabGroup;
        CAknNavigationDecorator*        iDecoratedTabGroup;

    };

#endif // AKNEXSCROLLERAPPUI_H

// End of File
