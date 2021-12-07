/*
* ============================================================================
*  Name     : CAknExPbarView from CAknView
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPBARVIEW_H
#define AKNEXPBARVIEW_H

// INCLUDES
#include <aknview.h>

#include "AknExPbartimermodel.h"
// CONSTANTS
// UID of view
const TUid KViewId = { 1 };

// FORWARD DECLARATIONS
class CAknExPbarContainer;
class CAknExPbarTimer;

struct TAknExPbarTimerModel;

// CLASS DECLARATION

/**
*  CAknExPbarView view class.
*
*/
class CAknExPbarView : public CAknView
    {
    public : // Constructors and destructor

        /**
        * C++ default constructor
        */
        CAknExPbarView();

        /**
        * EPOC Default constructor
        */
        void ConstructL();

        /**
        * Destructor
        */
        virtual ~CAknExPbarView();

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

    private: // From CAknView

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

    private: // New Functions
        void ConstructTimerModel();
        void ConstructTimerL();

    private: // Data
        CAknExPbarContainer* iContainer;
        TAknExPbarTimerModel iTimerModel;   // Timer Model
        CAknExPbarTimer*     iTimer;         // Ptr to Timer

    };

#endif // AKNEXPBARVIEW_H

// End of File