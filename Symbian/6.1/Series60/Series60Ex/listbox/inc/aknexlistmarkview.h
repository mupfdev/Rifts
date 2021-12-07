/*
* =============================================================================
*  Name     : CAknExListMarkView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTMARKVIEW_H
#define AKNEXLISTMARKVIEW_H

// INCLUDES
#include "AknExListBaseView.h"

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExListMarkContainer;

// CLASS DECLARATION

/**
* CAknExListMarkView view class.
*/
class CAknExListMarkView : public CAknExListBaseView
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExListMarkView();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExListMarkView();

    public: // From CAknView

        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * Handles the commands. Commands about marked items is executed. Other
        * commands is passed HandleCommandL() of CAknExListBaseView class.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

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

    private: // From MEikMenuObserver

        /**
        * From MEikMenuObserver, DynInitMenuPaneL.
        * This function is called by the EIKON framework just before it
        * displays a menu pane.
        * @param aResourceId The ID of command which defined in resource file.
        * @param aMenuPane Pointer to menu-pane object.
        */
        void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane );

    private: // Data

        CAknExListMarkContainer* iContainer;

    };

#endif

// End of File
