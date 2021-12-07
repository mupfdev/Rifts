/*
* ============================================================================
*  Name     : CAknExGridContainerAsMenu
*             from CCoeControl, MCoeControlObserver, CAknexGridContainerAsSelection
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDCONTAINERASMENU_H
#define AKNEXGRIDCONTAINERASMENU_H

// INCLUDES
#include <aknview.h>

#include "AknExGridContainerAsSelection.h"

// CONSTANTS

const TInt KNumberOfComponentMenu = 2;  // do not include iGrid

// the initial number of items in primary orient
const TInt KNumOfColumnsInMenu = 9;
const TInt KNumOfRowsInMenu = 3;

// the initial number of items to be created.
const TInt KInitialNumOfItemsInMenu = 27;

// the length of strings
const TInt KLengthOfTitle = 40;

#define VIEW_MENU_LABEL_POINT TPoint( 10, 10 )
#define VIEW_MENU_DOLABEL_POINT TPoint( 10, 100 )


// FORWARD DECLARATIONS
class CEikLabel;        // for example labels

// CLASS DECLARATION

/**
*  CAknExGridContainerAsMenu  container control class.
*  
*/
class CAknExGridContainerAsMenu : public CAknExGridContainerAsSelection
    {
    public: // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CAknExGridContainerAsMenu();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExGridContainerAsMenu();

    public: // New functions

        /**
        * create a grid in the menu and show it.
        */
        void ShowGridInMenuL( void );

    public: // Functions from base classes

       /**
        * show a dialog to determine change size.
        */
        void DetermineChangeSizeL( void );

    protected:  // New functions


    protected:  // Functions from base classes

    private:

    private: // Functions from base classes

       /**
        * From CoeControl Called by framework when the view size is changed.
        */
        void SizeChanged();

       /**
        * From CoeControl return the number of controls.
        * @return the number of controls.
        */
        TInt CountComponentControls() const;

       /**
        * From CCoeControl return the pointer to specified control.
        * @param aIndex the index of control.
        * @return the pointer to the control.
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

       /**
        * From CCoeControl handle the message when client region must be redrawn.
        * @param the region of the control to be redrawn.
        */
        void Draw( const TRect& aRect ) const;

     private: // Functions from base classes

        /**
        * From MCoeControlObserver handle event from observed control.
        * @param aControl The control that sent the event.
        * @param The event type.
        */
        void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

    private: //data
        
        CEikLabel* iLabel;          // label for the selection grid
        CEikLabel* iToDoLabel;      // dolabel for the selection grid

    public:
        TBool AutoTestL();

    private: //data
        CDesCArrayFlat* iTitles;    // Title list
        TInt iTestNumber;

        enum TMenuTitles
            {
            EMenuTest1=0,
            EMenuTest2,
            EMenuTest3,
            EMenuTest4,
            EMenuTest5,
            EMenuTest6,
            EMenuTest7,
            EMenuTest8,
            EMenuTest9,
            EMenuTest10,
            EMenuTest11,
            EMenuTest12,
            EMenuTest13,
            ENumberOfMenuTitles
            };

    };

#endif      // AKNEXGRIDCONTAINERASMENU_H

// End of File
