/*
* ============================================================================
*  Name     : CAknExSliderView
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSLIDERVIEW_H
#define AKNEXSLIDERVIEW_H

// INCLUDES
#include <aknview.h>

// CONSTANTS
const TUid KViewId = { 1 }; // UID of view

// FORWARD DECLARATIONS
class CAknExSliderContainer;

// CLASS DECLARATION

/**
* CAknExSliderView view class.
*/
class CAknExSliderView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * Default onstructor.
        */
        CAknExSliderView();

        /**
        * Destructor.
        */
        virtual ~CAknExSliderView();

    public: // From CAknView

        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommand.
        * Handles the commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

    public: // New Functions
        /**
        * Set Title and Show Outline Number
        */
        void SetTitleL(const TInt aResouceId);

    private: // New Functions

        /**
        * Deletes the Container class object.
        */
        void CloseContainer();

    private: // From AknView

        /**
        * From AknView, DoActivateL.
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
        * From AknView, DoDeactivate.
        * Deletes the Container class object.
        */
        void DoDeactivate();

    private: // Data

        CAknExSliderContainer* iContainer;

    };

#endif

// End of File
