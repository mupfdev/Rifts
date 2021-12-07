/*
* =============================================================================
*  Name     : CAknExPopFieldView
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDVIEW_H
#define AKNEXPOPFIELDVIEW_H

// INCLUDES
#include <aknview.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExPopFieldContainer;

// CLASS DECLARATION

/**
* CAknExPopFieldView view class.
*
*/
class CAknExPopFieldView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExPopFieldView();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldView();

    public: // New functions

        /**
        *
        * @param aIndex
        */
        void DisplayNextOutlineL();

    public: // From CAknView.

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
        * Set title text to status-pane
        * @param aCommand
        */
        void IndicateTitlePaneTextL( TInt aCommand );

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

        CAknExPopFieldContainer* iContainer;
        TInt iCurrentOutline;

    };

#endif

// End of File
