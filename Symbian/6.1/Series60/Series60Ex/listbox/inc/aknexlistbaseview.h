/*
* =============================================================================
*  Name     : CAknExListBaseView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTBASEVIEW_H
#define AKNEXLISTBASEVIEW_H

// INCLUDES
#include <aknview.h>

// CONSTANTS
const TInt KAknExListInitTitleId = 0; // for initialization.

// UID of each view
const TUid KAknExListColumnViewId = { 1 };
const TUid KAknExListFormViewId = { 2 };
const TUid KAknExListSettingViewId = { 3 };
const TUid KAknExListMarkViewId = { 4 };
const TUid KAknExListFlagTestViewId = { 5 };
const TUid KAknExListSetPageViewId = { 6 };


// FORWARD DECLARATIONS
class CAknTitlePane;
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CAknTabGroup;

// CLASS DECLARATION

/**
* CAknExListBaseView view class.
*/
class CAknExListBaseView : public CAknView
    {
    protected: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExListBaseView();

        /**
        * Destructor.
        */
        virtual ~CAknExListBaseView();

    public: // New functions

        /**
        * Returns pointer to tab group object.
        * @return Pointer to tab group object.
        */
        CAknTabGroup* TabGroup();

        /**
        * Switches screen by outline.
        * @param aOutlineId The ID of outline to displayed next.
        */
        void SwitchDisplayOutlineL( const TInt aOutlineId );

        /**
        * Sets ID of outline to displayed next.
        */
        void DisplayNextOutlineL();

        /**
        * Sets text to titie pane.
        * @param aTitle Text of title pane.
        */
        void IndicateTitlePaneTextL( const TDesC& aTitle );


    public: // From CAknView

        /**
        * From CAknView, HandleCommandL.
        * Handles the commands. If the command is command which is require to
        * display outline-screen, the command display outline-screen
        * corresponded to required.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

    protected: // New functions

        /**
        * Sets text by resource ID in title pane.
        * @param aResourceId The ID of outline number to displayed next.
        */
        void IndicateTitlePaneTextL( const TInt aResourceId );

        /**
        * Displays initial outline when view changed.
        */
        void DisplayInitOutlineL();

    private: // New functions

        /**
        * Sets Navigation pane.
        */
        void SetNavigationPaneL();

        /**
        * Sets text of title pane by outline ID.
        * @param aOutlineId The ID of outline to displayed next.
        */
        virtual void SetTitlePaneL( const TInt aOutlineId );

        /**
        * This function makes container class display listbox.
        * This is pure virtual function.
        * @param aOutlineId The ID of outline to displayed next.
        */
        virtual void DisplayListBoxL( const TInt aOutlineId ) = 0;

        /**
        * Deletes tab group.
        */
        void DeleteTabGroup();

    private: // Data

        CAknNavigationControlContainer* iNaviPane;
        CAknNavigationDecorator* iDecoratedTabGroup;
        CAknTabGroup* iTabGroup;

    };

#endif

// End of File
