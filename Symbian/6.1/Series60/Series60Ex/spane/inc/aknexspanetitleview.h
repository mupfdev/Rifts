/*
* ============================================================================
*  Name     : CAknExSpaneTitleView from CAknView
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANETITLEVIEW_H
#define AKNEXSPANETITLEVIEW_H

//  INCLUDES
#include <aknview.h>

// FORWARD DECLARATIONS
class CAknExSpaneTitleViewContainer;

// CLASS DECLARATION
/**
*  View used by Title pane test
*/    
class CAknExSpaneTitleView : public CAknView
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */      
        CAknExSpaneTitleView();

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExSpaneTitleView();

    public: // Functions from base classes
        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * handles the commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL(TInt aCommand);

    private: // from CAknView

        /**
        * From CAknView, HandleStatusPaneSizeChange.
        * The MEikStatusPaneObserver interface allows a status pane observer to pick up
        * changes in the size or position of the status pane. Such events will be as a
        * result of layout changes which cause an actual change in the status pane
        * rectangle.
        */
        void HandleStatusPaneSizeChange();

        /**
        * From CAknView, DoActivateL.
        * Creates the Container class object.
        * @param aPrevViewId aPrevViewId is not used.
        * @param aCustomMessageId aCustomMessageId is not used.
        * @param aCustomMessage aCustomMessage is not used.
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,TUid aCustomMessageId,const TDesC8& aCustomMessage);

        /**
        * From CAknView, DoDeactivate.
        * Deletes the Container class object.
        */
        void DoDeactivate();

    private:    // Data
        CAknExSpaneTitleViewContainer* iView;  // Component container
    };

#endif // AKNEXSPANETITLEVIEW_H

// End of File