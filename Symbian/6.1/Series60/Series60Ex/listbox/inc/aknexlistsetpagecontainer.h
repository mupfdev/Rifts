/*
* =============================================================================
*  Name     : AknExListSetPageContainer.h
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTSETPAGECONTAINER_H
#define AKNEXLISTSETPAGECONTAINER_H

// INCLUDES
#include "AknExListBaseContainer.h" 

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExListSetPage;
class CAknExListSetPageView;

// CLASS DECLARATION

/**
* CAknExListSetPageContainer class.
*/
class CAknExListSetPageContainer : public CAknExListBaseContainer
    {
    public: // Constructors and destructor
        /**
        * 2-phase constructor.
        * @param aView : View class pointer
        */
        static CAknExListSetPageContainer* NewL(
            CAknExListSetPageView* aView);
        
        /**
        * Destructor.
        */
        virtual ~CAknExListSetPageContainer();

    public: // New functions
        /**
        * Try to display setting page.
        * @param aResourceId : resource ID od settinf page.
        */
        void TryDisplaySetPageL(TInt aResourceId);

    private: // Constructors and destructor
        /**
        * Second phase constructor.
        * @param aView : View class pointer
        */
        void ConstructL(CAknExListSetPageView* aView);
        
    private: // From CCoeControl
        /**
        * From CCoeControl : Handling key event.
        * @param aKeyEvent : Information of inputted key. 
        * @param aType : EEventKeyDown | EEventKey | EEventKeyUp
        * @return EKeyWasConsumed if keyevent is used.
        *         Otherwise, return EKeyWasNotConsumed. 
        */
        TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,TEventCode aType);

    private:
        CAknExListSetPage*     iSetPage; // Own
        CAknExListSetPageView* iView;    // Not own.
    };

#endif // AKNEXLISTSETPAGECONTAINER_H 

// End of File
