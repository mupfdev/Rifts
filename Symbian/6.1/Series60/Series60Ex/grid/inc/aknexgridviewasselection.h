/*
* ============================================================================
*  Name     : CAknExGridViewAsSelection from CAknView
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDVIEWASSELECTION_H
#define AKNEXGRIDVIEWASSELECTION_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KViewSelectionId = { 2 };

// FORWARD DECLARATIONS
class CAknExGridContainerAsSelection;

// CLASS DECLARATION

/**
*  CAknExGridViewAsSelection view class.
* 
*/
class CAknExGridViewAsSelection : public CAknView
    {
    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExGridViewAsSelection();

    public: // Functions from base classes
        
        /**
        * From CAknView return the view ID.
        * @return view ID.
        */
        TUid Id() const;

        /**
        * From CAknView handle command IDs such as menu commands.
        * @param command ID.
        */
        void HandleCommandL( TInt aCommand );

        /**
        * From CAknView handle the message when client rect is changed.
        */
        void HandleClientRectChange();

    private:

        /**
        * From AknView create a container object.
        * @param aPrevViewId Specified TVwsViewId.
        * @param aCustomMessageId Specified TUid.
        * @param aCustomMessage Specified TDesC8.
        */
        void DoActivateL( const TVwsViewId& aPrevViewId, TUid aCustomMessageId,
            const TDesC8& aCustomMessage );

        /**
        * From AknView destroy the container object.
        */
        void DoDeactivate();

    private: // Data

        CAknExGridContainerAsSelection* iContainer;

    };

#endif      // AKNEXGRIDVIEWASSELECTION_H

// End of File
