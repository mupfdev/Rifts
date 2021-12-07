/*
* =============================================================================
*  Name     : CAknExListFlagTestView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTFLAGTESTVIEW_H
#define AKNEXLISTFLAGTESTVIEW_H

// INCLUDES
#include "AknExListBaseView.h"

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExListFlagTestContainer;

// CLASS DECLARATION

/**
* CAknExListFlagTestView view class.
*/
class CAknExListFlagTestView : public CAknExListBaseView
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExListFlagTestView();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExListFlagTestView();

    public: // New functions

        /**
        * Returns current outline ID.
        * @return outline ID.
        */
        TInt OutlineId() const;

    public: // From CAknView

        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

    private: // New functions

        /**
        * Sets text of title pane.
        * @param aOutlineId The ID of outline to displayed next.
        */
        void SetTitlePaneL( const TInt aOutlineId );

    private: // From AknExListBaseView

        /**
        * Displays the listbox by outline ID.
        * @param aOutlineId the ID of outline to displayed next.
        */
        void DisplayListBoxL( const TInt aOutlineId );

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

    private: // Data

        CAknExListFlagTestContainer* iContainer;

    };

#endif

// End of File
