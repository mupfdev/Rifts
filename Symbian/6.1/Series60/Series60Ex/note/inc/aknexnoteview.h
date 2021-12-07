/*
* =============================================================================
*  Name     : CAknExNoteView
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTEVIEW_H
#define AKNEXNOTEVIEW_H

// INCLUDES
#include <aknview.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExNoteContainer;

// CLASS DECLARATION

/**
* CAknExNoteView view class.
*/
class CAknExNoteView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExNoteView();

        /**
        * Destructor.
        */
        virtual ~CAknExNoteView();

        /**
        * EPOC constructor.
        */
        void ConstructL();

    public: // New functions

        /**
        * Display next outline.
        */
        void DisplayNextOutlineL();

    public: // From CAknView.

        /**
        * Note CAknView, Id.
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

        /*
        * Set title text to status-pane
        */
        void IndicateTitlePaneTextL( TInt aCommand );

    private: // From CAknView

        /*
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

        /*
        * From CAknView, DoDeactivate.
        * Deletes the Container class object.
        */
        void DoDeactivate();

    private: // Data

        CAknExNoteContainer* iContainer;
        TInt iCurrentOutline;

    };

#endif

// End of File
