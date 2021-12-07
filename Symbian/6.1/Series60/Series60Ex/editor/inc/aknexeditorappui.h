/*
* ============================================================================
*  Name     : CAknExEditorAppUi from CAknViewAppUi
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef AKNEXEDITORAPPUI_H
#define AKNEXEDITORAPPUI_H

// INCLUDES
#include <eikapp.h>
#include <e32std.h>
#include <coeccntx.h>
#include <aknviewappui.h>

// FORWARD DECLARATIONS
class CAknExEditorContainer;
class CAknExEditorScenarioManager;
class CAknNavigationControlContainer;
class CAknTabGroup;
class CAknNavigationDecorator;
class CAknTitlePane;

// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
* 
*/
class CAknExEditorAppUi : public CAknViewAppUi
    {
    public: // // Constructors and destructor

        /**
        * C++ default constructor.
        */
        CAknExEditorAppUi::CAknExEditorAppUi();

        /**
        * EPOC default constructor.
        */      
        void ConstructL();

        /**
        * Destructor.
        */      
        ~CAknExEditorAppUi();
        
    private: // New functions
        /**
        * Activate next view to current view.
        */
        void ActivateNextViewL();

        /**
        * Activate previous view to current view.
        */
        void ActivatePrevViewL();

        /**
        * Activate specified view.
        * @param aViewId View id.
        */
        void ActivateViewL(TUid aViewId); 

    private:
        /**
        * From MEikMenuObserver, DynInitMenuPaneL.
        * @param aResourceID specifies dialog-resource ID.
        * @param aMenuPane specifies menu pane
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
            const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/);

    private: //Data
        CAknNavigationControlContainer* iNaviPane;
        CAknTabGroup*                   iTabGroup;
        CAknNavigationDecorator*        iDecoratedTabGroup;
        CAknTitlePane*                  iTitlePane;

        CAknExEditorScenarioManager*    iScenarioManager;
        TUid                            iCurrentViewId;
        // This is NOT iAppView since this is REALLY a container ptr.
//        CAknExEditorContainer* iAppContainer; 
    };

#endif

// End of File
