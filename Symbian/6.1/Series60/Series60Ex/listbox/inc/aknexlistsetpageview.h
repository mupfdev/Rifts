/*
* =============================================================================
*  Name     : AknExListSetPageView.h
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTSETPAGEVIEW_H
#define AKNEXLISTSETPAGEVIEW_H

// INCLUDES
#include "AknExListBaseView.h" 

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExListSetPageContainer;

// CLASS DECLARATION

/**
* CAknExListSetPageView class.
*/
class CAknExListSetPageView : public CAknExListBaseView
    {
    public: // Constructors and destructor
        /**
        * 2-phase constructor.
        */
        static CAknExListSetPageView* NewLC();
        
        /**
        * Destructor.
        */
        virtual ~CAknExListSetPageView();

    public: // From CAknView
        /**
        * From CAknView.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

    private:  // Constructors and destructor
        /**
        * Default constructor.
        */
        CAknExListSetPageView();
        
        /**
        * Second-phase constructor.
        */
        void ConstructL();

    private: // From CAknExListBaseView
        /**
        * From CAknExListBaseView
        * Set text of title pane according to current outline
        * @param aOutlineId The ID of outline to displayed next.
        */
        void SetTitlePaneL(const TInt aOutlineId);

        /**
        * From CAknExListBaseView
        * Create and display setting page.
        * @param aOutlineId The ID of outline to displayed next.
        */
        void DisplayListBoxL(const TInt aOutlineId);

    private: //From CAknView
        /**
        * From CAknView, DoActivateL.
        * Creates the Container class object.
        * @param aPrevViewId aPrevViewId is not used.
        * @param aCustomMessageId aCustomMessageId is not used.
        * @param aCustomMessage aCustomMessage is not used.
        */
        void DoActivateL(
            const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

        /**
        * From CAknView, DoDeactivate.
        * Deletes the Container class object.
        */
        void DoDeactivate();

    private:
        CAknExListSetPageContainer* iContainer; // Own
    };


#endif // AKNEXLISTSETPAGEVIEW_H

// End of File
 