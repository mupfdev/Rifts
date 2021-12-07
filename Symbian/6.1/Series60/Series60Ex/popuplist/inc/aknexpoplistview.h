/*
* ============================================================================
*  Name     : CAknExPopListView from CAknView
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPOPLISTVIEW_H
#define AKNEXPOPLISTVIEW_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KViewId = {1};

// FORWARD DECLARATIONS
class CAknExPopListContainer;

// CLASS DECLARATION

/**
*  CAknExPopListView view class.
* 
*/
class CAknExPopListView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExPopListView();

    public: // Functions from base classes
        
        /**
        * From CAknView, returns View Id.
        * @return view Id.
        */
        TUid Id() const;

        /**
        * From CAknView, handles commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL(TInt aCommand);

        /**
        * From CAknView, handles client rectangle is changed.
        */
        void HandleClientRectChange();

    private:

        /**
        * From AknView, Creates the container class object.
        * @param aPrevViewId Previeous view id.
        * @param aCustomMessageId messge id.
        * @param aCustomMessage message.
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,
            const TDesC8& aCustomMessage);

        /**
        * From AknView, Deletes the container class object.
        */
        void DoDeactivate();

    private: // New funcitons
        /**
        * Show all kinds of popup-windows except list_single_number_pane,
        * list_single_heading_pane and list_single_number_heading_pane
        * automatically.
        */
        void AutoTestL();

        /**
        * Show "List pane for single item" popup list.
        * @param aShowTitle Specifies whether "Heading pane" is shown or not.
        */
        void ShowSingleItemPopupListL(TBool aShowTitle);

        /**
        * Show "List pane for single item with graphic" popup list.
        * @param aShowTitle Specifies whether "Heading pane" is shown or not.
        */
        void ShowSingleItemPopupListWithGraphicsL(TBool aShowTitle);

        /**
        * Show "List pane for single item with heading and graphic" popup list.
        * @param aShowTitle Specifies whether "Heading pane" is shown or not.
        */
        void ShowSingleItemPopupListWithHeadingAndGraphicsL(TBool aShowTitle);

        /**
        * Show "List pane for Double item" popup list.
        * @param aShowTitle Specifies whether "Heading pane" is shown or not.
        */
        void ShowDoubleItemPopupListL(TBool aShowTitle);

        /**
        * Show "List pane for Double item with large image" popup list.
        * @param aShowTitle Specifies whether "Heading pane" is shown or not.
        */
        void ShowDoubleItemPopupListWithGraphicsL(TBool aShowTitle);

    private: // Data
        CAknExPopListContainer* iContainer;
    };

#endif  // AKNEXPOPLISTVIEW_H

// End of File
