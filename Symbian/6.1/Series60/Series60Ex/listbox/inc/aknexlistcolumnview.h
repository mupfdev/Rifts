/*
* =============================================================================
*  Name     : CAknExListColumnView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTCOLUMNVIEW_H
#define AKNEXLISTCOLUMNVIEW_H

// INCLUDES
#include "AknExListBaseView.h"

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExListColumnContainer;

// CLASS DECLARATION

/**
* CAknExListColumnView view class.
*/
class CAknExListColumnView : public CAknExListBaseView
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExListColumnView();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExListColumnView();

        /**
        * Update CBA-key
        * @param : aResourceId : new CBA id.
        */
        void UpdateCbaL(TInt aResourceId);

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

        CAknExListColumnContainer* iContainer;

    };

#endif

// End of File
