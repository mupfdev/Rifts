/*
* ============================================================================
*  Name     : CAknExPbarAppUi from CAknViewAppUi
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPBARAPPUI_H
#define AKNEXPBARAPPUI_H

// INCLUDES
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>

// FORWARD DECLARATIONS
class CAknExPbarContainer;


// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
* 
*/
class CAknExPbarAppUi : public CAknViewAppUi
    {
    public:  // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExPbarAppUi();

        /**
        * EPOC default constructor.
        */      
        void ConstructL();

        /**
        * Destructor.
        */      
        virtual ~CAknExPbarAppUi();

    private:  // From CEikAppUi

        /**
        * From CEikAppUi, takes care of command handling.
        * @param aCommand command to be handled
        */
        void HandleCommandL( TInt aCommand );

        /**
        * From CEikAppUi, handles key events.
        * @param aKeyEvent Event to handled.
        * @param aType Type of the key event. 
        * @return Reponse code ( EKeyWasConsumed, EKeyWasNotConsumed ). 
        */
        virtual TKeyResponse HandleKeyEventL(
            const TKeyEvent& aKeyEvent, TEventCode aType );

    private:  // New functions

        /**
        * Internal use
        * Set Timer Model
        */
//        void ConstructTimerModel();

        /**
        * Internal use
        * Set Timer
        */
//        void ConstructTimerL();


    private: //Data
        CAknNavigationControlContainer*  iNaviPane;
        CAknTabGroup*                    iTabGroup;
        CAknNavigationDecorator*         iDecoratedTabGroup;

        CAknExPbarContainer* iAppContainer; // Ptr to Container class 
    };

#endif // AKNEXPBARAPPUI_H

// End of File
