/*
* ============================================================================
*  Name     : CAknExGridView from CAknView
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDVIEW_H
#define AKNEXGRIDVIEW_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KViewId = { 1 };

// FORWARD DECLARATIONS
class CAknExGridContainer;

// CLASS DECLARATION

/**
*  CAknExGridView view class.
* 
*/
class CAknExGridView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExGridView();

    public: // From CAknView
        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */        
        TUid Id() const;

        /**
        * From CAknView, Handles the commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

        /**
        * From CAknView, Handles the clientrect.
        */
        void HandleClientRectChange();

    private:

        /**
        * From CAknView, Creates the Container class object.
        * @param aPrevViewId Spcified TVwsViewId.
        * @param aCustomMessageId Spcified TUid.
        * @param aCustomMessage Spcified TDesC8.
        */
        void DoActivateL( const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

        /**
        * From CAknView, Deletes the Container class object.
        */
        void DoDeactivate();

        void AutoTestL();

    private: // Data
        CAknExGridContainer* iContainer;
        TInt iTestNumber;
    };

#endif   //AKNEXGRIDVIEW_H

// End of File
