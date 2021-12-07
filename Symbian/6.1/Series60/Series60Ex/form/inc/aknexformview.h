/*
* ============================================================================
*  Name     : CAknExFormView
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXFORMVIEW_H
#define AKNEXFORMVIEW_H

// INCLUDES
#include <aknview.h>
#include <eikdialg.h>
#include <aknform.h>

// CONSTANTS

// FORWARD DECLARATIONS
class CAknExFormContainer;

// CLASS DECLARATION

/**
* CAknExFormView view class.
*
*/
class CAknExFormView : public CAknView
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExFormView();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExFormView();

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

        CAknExFormContainer* iContainer;
        TInt iCurrentOutline;

    };

/**
* CAknExFormAdd container control class.
*/
class CAknExFormAdd : public CAknForm
    {
    public: // Constructor and Detructor
        /**
        * Default constructor.
        */
        CAknExFormAdd();
        
        /**
        * Destructor.
        */
        virtual ~CAknExFormAdd();

    protected:
        /**
        * From CAknForm,
        * Add item for testing uses customised dialog.
        */
        void AddItemL();
    
    private:
        // In order to prevent adding controls which ID is the same. 
        TInt iNewItemId;
    };

#endif

// End of File
