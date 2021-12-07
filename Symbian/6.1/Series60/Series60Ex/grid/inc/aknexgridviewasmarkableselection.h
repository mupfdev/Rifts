/*
* ============================================================================
*  Name     : CAknExGridViewAsMarkableSelection from CAknView
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDVIEWASMARKABLESELECTION_H
#define AKNEXGRIDVIEWASMARKABLESELECTION_H

// INCLUDES
#include <aknview.h>


// CONSTANTS
// UID of view
const TUid KViewMarkableSelectionId = { 5 };

// FORWARD DECLARATIONS
class CAknExGridContainerAsSelection;

// CLASS DECLARATION

/**
*  CAknExGridViewAsMarkableSelection view class.
* 
*/
class CAknExGridViewAsMarkableSelection : public CAknView
    {
    public: // Constructors and destructor

        /**
        * EPOC default constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExGridViewAsMarkableSelection();

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
        * From MEikMenuObserver, DynInitMenuPaneL().
        * @param aResourceId Menu pane resource ID
        * @param aMenuPane Menu pane pointer
        */
        void DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane);

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

#endif      // AKNEXGRIDVIEWASMARKABLESELECTION_H

// End of File
