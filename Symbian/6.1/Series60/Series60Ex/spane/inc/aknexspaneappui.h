/*
* ============================================================================
*  Name     : CAknExSpaneAppUi from CAknViewAppUi
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANEAPPUI_H
#define AKNEXSPANEAPPUI_H

// INCLUDES
#include <eikapp.h>
#include <eikdoc.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>

// FORWARD DECLARATIONS
class CAknExSpaneTitleView;
class CAknExSpaneContextView;
class CAknExSpaneNaviView;
class CAknExSpanePopupView;

// CONSTANTS
//const ?type ?constant_var = ?constant;

// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
* 
*/
class CAknExSpaneAppUi : public CAknViewAppUi
    {
    public: // // Constructors and destructor

        /**
        * C++ default constructor.
        */      
        CAknExSpaneAppUi();

        /**
        * EPOC default constructor.
        */      
        void ConstructL();

        /**
        * Destructor.
        */      
        virtual ~CAknExSpaneAppUi();
        
    public: // New functions

    public: // Functions from base classes

    private:
        /**
        * From MEikMenuObserver
        * @param aResourceId Resource Id.
        * @param aMenuPane Menupane pointer. 
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
        virtual TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

    private: //Data
        TBool iLayout;
        TBool iVisible;

        CAknNavigationControlContainer* iNaviPane;
        CAknTabGroup*                   iTabGroup;
        CAknNavigationDecorator*        iDecoratedTabGroup;

    };

#endif  //AKNEXSPANEAPPUI_H

// End of File
