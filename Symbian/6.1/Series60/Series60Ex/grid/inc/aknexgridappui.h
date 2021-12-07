/*
* ============================================================================
*  Name     : CAknExGridAppUi from CAknViewAppUi
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDAPPUI_H
#define AKNEXGRIDAPPUI_H

// INCLUDES
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>

// FORWARD DECLARATIONS
class CAknExGridContainer;

// CONSTANTS

// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
* 
*/
class CAknExGridAppUi : public CAknViewAppUi
    {
    public: // // Constructors and destructor

        /**
        * EPOC default constructor.
        */      
        void ConstructL();

        /**
        * Destructor.
        */      
        virtual ~CAknExGridAppUi();
        
    public: // New functions

        /**
        * Change active views and tabs.
        * @param aViewUid UID of the view
        * @param aTabId tab ID of the view
        */
       void ChangeActiveViewAndTabL( TUid aViewUid, TInt aTabId );

        /**
        * set iShortcutFlag.
        * @param aFlag for shortcutflag
        */
       void SetShortcutFlag( TBool aFlag );

        /**
        * get iShortcutFlag.
        * @return the value of shortcutflag (EKeyWasConsumed, EKeyWasNotConsumed). 
        */
       TBool GetShortcutFlag( );

    
    public: // Functions from base classes

    private:
        // From MEikMenuObserver
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

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
            const TKeyEvent& aKeyEvent, TEventCode aType );

    private: //Data
        CAknNavigationControlContainer* iNaviPane;
        CAknTabGroup*                   iTabGroup;
        CAknNavigationDecorator*        iDecoratedTabGroup;
        // This is NOT iAppView since this is REALLY a container ptr.
        CAknExGridContainer* iAppContainer; 
        
        TBool                           iShortcutFlag;
    };

#endif      // AKNEXGRIDAPPUI_H

// End of File
