/*
* ============================================================================
*  Name     : CAknExMenuAppUi from CAknViewAppUi
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXMNEUAPPUI_H
#define AKNEXMNEUAPPUI_H

// INCLUDES
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>
#include <akntitle.h>

// FORWARD DECLARATIONS
class CAknExMenuContainer;



// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
* 
*/
class CAknExMenuAppUi : public CAknViewAppUi
    {
    public: // // Constructors and destructor

        /**
        * EPOC default constructor.
        */      
        void ConstructL();

        /**
        * Destructor.
        */      
        virtual ~CAknExMenuAppUi();
        
    public: // New functions

    public: // Functions from base classes

    private:
        /** 
        * From MEikMenuObserver
        * @param aResourceId menu pane resource ID
        * @param aMenuPane menu pane pointer
        */
        void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

    private:
        /**
        * From CEikAppUi, takes care of command handling.
        * @param aCommand command to be handled
        */
        void HandleCommandL(TInt aCommand);

        /**
        * From CEikAppUi, handles key events.
        * @param aKeyEvent Event to handled.
        * @param aType Type of the key event. 
        * @return Reponse code (EKeyWasConsumed, EKeyWasNotConsumed). 
        */
        virtual TKeyResponse HandleKeyEventL(
            const TKeyEvent& aKeyEvent,TEventCode aType);

    public: //Data
        CAknNavigationControlContainer* iNaviPane;
        CAknTabGroup*                   iTabGroup;
        CAknNavigationDecorator*        iDecoratedTabGroup;
        CAknTitlePane*                  iTitlePane;
        // This is NOT iAppView since this is REALLY a container ptr.
    private:
        CAknExMenuContainer* iAppContainer; 
    };

#endif    // AKNEXMNEUAPPUI_H

// End of File
