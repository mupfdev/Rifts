/*
* =============================================================================
*  Name     : CAknExSettingListView
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/



#ifndef AKNEXSETTINGLISTVIEW_H
#define AKNEXSETTINGLISTVIEW_H

// INCLUDES
#include <aknview.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExSettingListContainer;
class CAknExSettingListListbox;
class CAknExSettingListItemData;


// CLASS DECLARATION

/**
* CAknExSettingListView view class.
*/
class CAknExSettingListView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExSettingListView();

        /**
        * Destructor.
        */
        virtual ~CAknExSettingListView();

    public: // New function

        /**
        * Requires to display next outline screen.
        * @param aOutlineId ID of current outline.
        */
        void DisplayNextOutlineL();
        void DisplayPreviousOutlineL();

        /**
        * Set iCurrentOutline
        * @param  aOutlineId ID of current outline
        */
        void SetCurrentOutlineId(const TInt aOutlineId);

    public: // From CAknView

        /**
        * From CAknView, Id.
        * Returns ID of View.
        * @return ID of View.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * Handles the commands. If the command is command which is required to
        * display outline-screen, the command is reported to container class.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

        /**
        * Returns current outline id
        * @return current outline id
        */
        TInt CurrentOutlineId();

    private: // New functions

        /**
        * Sets text on title pane by ID of resource.
        * @param aCommand Command selected in menu.
        */
        void IndicateTitlePaneTextL( const TInt aCommand );

        /**
        * Swaps container window
        * @param bActiveContainer Becames container
        */
        void SwapContainerL(TBool aActiveContainer);
        /**
        * Swaps container window
        * @param aResourceId for ListBox initialization
        */
        void CreateListBoxL(TInt aResourceId);

    private: // From CAknView

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

        CAknExSettingListContainer* iContainer;
        CAknExSettingListListbox* iListBox;
        TBool iActiveContainer;
        CAknExSettingListItemData* iData;
        TInt iCurrentOutlineId;

    };

#endif

// End of File
