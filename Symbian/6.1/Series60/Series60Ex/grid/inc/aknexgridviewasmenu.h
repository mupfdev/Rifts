/*
* ============================================================================
*  Name     : CAknExGridViewAsMenu from CAknView
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDVIEWASMENU_H
#define AKNEXGRIDVIEWASMENU_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KViewMenuId = { 4 };

const TInt KLengthOfMenuAboutString = 40;

// FORWARD DECLARATIONS
class CAknExGridContainerAsMenu;

// CLASS DECLARATION

/**
*  CAknExGridViewAsMenu view class.
* 
*/
class CAknExGridViewAsMenu : public CAknView
    {
    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExGridViewAsMenu();

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

    protected :

    
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

        CAknExGridContainerAsMenu* iContainer;

    };

#endif      // AKNEXGRIDVIEWASMENU_H

// End of File
