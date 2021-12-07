/*
* =============================================================================
*  Name     : CAknExQueryView
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYVIEW_H
#define AKNEXQUERYVIEW_H

// INCLUDES
#include <aknview.h>

// CONSTANTS
const TUid KViewId = { 1 }; // UID of view

// FORWARD DECLARATIONS
class CAknExQueryContainer;

// CLASS DECLARATION

/**
*  CAknExQueryView view class.
*/
class CAknExQueryView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        */
        CAknExQueryView();

        /**
        * Destructor.
        */
        virtual ~CAknExQueryView();

    public: // New functions.

        /**
        * Display next outline.
        */
        void DisplayNextOutlineL();

    public: // From CAknView

        /**
        * From CAknView, Id.
        * Returns the ID of view.
        * @return The ID of view.
        */
        TUid Id() const;

        /**
        * From CAknView, HandleCommandL.
        * handles the commands. if the command is command which is require to
        * display outline-screen, the command is reported to container class.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

    private: // New functions

        /**
        * Set titletext for titlepane.
        */
        void SetTitlePaneL( TInt aOutlineId );

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

        CAknExQueryContainer* iContainer;
        TInt iCurrentOutline;

    };

#endif

// End of File
