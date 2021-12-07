/*
* ============================================================================
*  Name     : CAknExGridContainerAsGMS
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

const TInt KNumberOfComponentGMS = 1;  // only iGridGMS

// the initial number of items to be created.
const TInt KInitialNumOfItemsInGMS = 10;

// the length of strings
const TInt KLengthOfTitle = 40;

// the hight of GMS grid
const TInt KHightOfGrid = 139;

// the width of GMS grid
const TInt KWidthOfGrid = 161;

// the top horizontal value in relation to its parent's top side
const TInt KTopOfGrid = 2;

// the left vertical value in relation to its parent's left side
const TInt KLeftOfGrid = 8;

// the color index number
const TInt KColorIndex = 0;

// the number of rows in grid
const TInt KRows = 3;

// the number of rows in grid
const TInt KColumns = 2;

// Enumeration
enum TPointerToComponentGMS
    {
    EGmsGrid = 0
    };

enum TAknExGridGMSGridType
    {
    EAknExGridGMSGrid = 0,          // Show grid as "GMS Grid"
    EAknExGridMarkableGMSGrid       // Show grid as "Markable GMS Grid"
    };

// FORWARD DECLARATIONS
class CAknGMSStyleGrid;

// CLASS DECLARATION

/**
*  CAknExGridContainerAsGMS  container control class.
*  
*/
class CAknExGridContainerAsGMS : public CAknExGridContainerAsSelection
    {
    public: // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CAknExGridContainerAsGMS();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExGridContainerAsGMS();

    public: // New functions

        /**
        * create a popup GMS grid and show it.
        */
        void ShowPopupGMSGridL( void );

    protected:  // New functions
        /**
        * show the current index.
        */
        void CheckIndex( void );

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
        
       /**
        * From CCoeControl handle key events.
        * @param aKeyEvent the key event.
        * @param aType The type of the event: EEventKey, EEventKeyUp or EEventKeyDown.
        * @return Indicates whether or not the key event was used by this control.
        */
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

     private: // Functions from base classes

        /**
        * From MCoeControlObserver handle event from observed control.
        * @param aControl The control that sent the event.
        * @param The event type.
        */
        void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

    private: //data
        
        CAknGMSStyleGrid* iGridGMS;
    public:
        TBool AutoTestL();

    private: //data
        CDesCArrayFlat* iTitles;    // Title list
        TInt iTestNumber;

        enum TSelectionTitles
            {
            EGMSTest1=0,
            EGMSTest2
            };
    };

#endif      // AKNEXGRIDCONTAINERASMENU_H

// End of File
