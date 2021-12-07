/*
* ============================================================================
*  Name     : CAknExGridContainerAsSelection
*             from CCoeControl, MCoeControlObserver
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDCONTAINERASSELECTION_H
#define AKNEXGRIDCONTAINERASSELECTION_H

// INCLUDES
#include <aknview.h>
#include <AknGridView.h>    // for TScrollingType
#include <AknForm.h>        // for CAknDialog
#include "AknExGrid.hrh"
#include "AknExGridAppUi.h"

// CONSTANTS
// the initial number of items in primary orient
const TInt KNumOfColumns = 3;
const TInt KNumOfRows = 3;

const TInt KLengthOfAboutString = 256;

// the initial number of items to be created.
const TInt KInitialNumOfItems = 10;

const TInt KNumberOfComponentSelection = 3;

const TInt KDefaultTextColor = 215;   // default text color is black.

// in a cell, the area of graphics : text = 1 : ( KGraphicAreaRatio - 1 )
const TInt KTextAreaRatio = 3;

// for grid layout.
const TInt KAknExGridItemLeft = 0;  // left
const TInt KAknExGridItemTop = 0;   // top

// index of a graphic and text in the resource
const TInt KIndexOfGraphic = 0;
const TInt KIndexOfText = 1;

// the maximum number of bitmaps to use as graphics in the cell
const TInt KNumberOfBitmap = 10;

const TInt KLengthOfPathEikonMbm = 256;

// the length of strings
const TInt KLengthOfStringToShowIndex = 40;
const TInt KLengthOfItemResourceString = 40;
const TInt KLengthOfLabel = 256;
const TInt KLengthOfDoLabel = 256;
const TInt KLengthOfEmptyText = 40;

const TInt KMarginEmptyText = 20;

// If RemoveDataL() is called with KRemoveAllItems, it removes all items.
const TInt KRemoveAllItems = -1;
// If RemoveDataL() is called with KRemoveFromCurrent, items remove from current index.
const TBool KRemoveFromCurrent = ETrue;
// If RemoveDataL() is called with KRemoveFromLast, items remove from current index.
const TBool KRemoveFromLast = EFalse;

// For "MarkableGrid"
const TInt KAknExGridMarkSize = 19;
const TInt KAknExGridMarkableIconPosition = 0;
const TInt KAknExGridMarkableMarkPosition = 1;
const TInt KAknExGridMarkableTextPosition = 2;
#define KAknExGridMarkableMarkReplace _L("2")

// Enumeration
enum TPointerToComponentSelection
    {
    ELabel = 0,
    EDoLabel,
    EGrid
    };

enum TContentType
    {
    EContainText = 0x0001,         // contain only text
    EContainGraphic = 0x0002,      // contain only graphic
    EContainBoth = 0x0004          // contain both text and graphic
    };

enum TAknExGridGridType
    {
    EAknExGridSelectionGrid = 0,    // Show grid as "Selection Grid"
    EAknExGridMarkableGrid         // Show grid as "Markable Grid"
    };

// FORWARD DECLARATIONS
class CEikLabel;        // for example labels
class CAknGrid;         // for iGrid
class CAknGridM;        // for iGridM

// CLASS DECLARATION

/**
*  CAknExGridContainerAsSelection  container control class.
*  
*/
class CAknExGridContainerAsSelection : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CAknExGridContainerAsSelection();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        * @param aGridType Grid type.
        */
        void ConstructL( const TRect& aRect, TAknExGridGridType aGridType);

        /**
        * Destructor.
        */
        virtual ~CAknExGridContainerAsSelection();

    public: // New functions
        
        /**
        * Insert data to the current index in grid.
        * @param the number of items which is inserted.
        */
        void InsertDataL( TInt aNum );

        /**
        * Add data to the last in grid.
        * @param the number of items which is added.
        */
        void AddDataL( TInt aNum );

        /**
        * Remove data from the currnet index or the last in grid.
        * @param aNum the number of items which is deleted.
        * @param aWhere if True,delete items from the current index.if TFalse,delete items from the last. 
        */
        void RemoveDataL( TInt aNum , TBool aWhere );

       /**
        * set vertical scrolling type to member variables.
        * @param aScrollingType vertical scrolling type shown in AknGridView.h.
        */
        void SetVerticalScrollingTypeL( CAknGridView::TScrollingType aScrollingType );

        /**
        * set horizontal scrolling type to member variables.
        * @param aScrollingType horizontal scrolling type shown in AknGridView.h.
        */
        void SetHorizontalScrollingTypeL( CAknGridView::TScrollingType aScrollingType );
 
        /**
        * set orientation to member variables.
        * @param aVerticalOrientation if ETrue, primary orientation is vertical.
        * @param aToRight if ETrue, filling order is from left to right.
        * @param aToBottom if ETrue, filling order is from top to bottom.
        */
        void SetOrientation( TBool aVerticalOrientation, TBool aToRight, TBool aToBottom );  

        /**
        * get orientation from member variables.
        * @param aVerticalOrientation if ETrue, primary orientation is vertical.
        * @param aToRight if ETrue, filling order is from left to right.
        * @param aToBottom if ETrue, filling order is from top to bottom.
        */
        void GetOrientation( TBool& aVerticalOrientation, TBool& aToRight, TBool& aToBottom );

        /**
        * show a dialog to determine filling order.
        */
        void DetermineFillingOrderL( void );

        /**
        * get the number of columns and set the number of columns to ChangeSize dialog.
        * @return the number of columns in Selection Grid.
        */
        int NumberOfColumns();

        /**
        * get the number of rows and set the number of rows to ChangeSize dialog.
        * @return the number of rows in Selection Grid.
        */
        int NumberOfRows();

        /**
        * Updata the number of columns of Selection Grid with the number of columns in ChangeSize dialog.
        * @param the number of colulmns in ChangeSize dialog.
        */
        void SetNumberOfColumns( TInt aNumberOfColumns );

        /**
        * updata the number of rows of Selection Grid with the number of rows in ChangeSize dialog.
        * @param the number of rows in ChangeSize dialog.
        */
        void SetNumberOfRows( TInt aNumberOfRows );

        /**
        * show a dialog to determine change size.
        */
        virtual void DetermineChangeSizeL( void );

        /**
        * select a kind of contents.
        * @param aContents set TContentType
        */
        void SelectContents( TInt aContents );

        /**
        * return the number of items stored away in the grid.
        */
        TInt NumberOfItems( void );

        /**
        * set the number of items stored away in the grid.
        * @param aNumberOfItems the number of items
        */
        void SetNumberOfItems( TInt aNumberOfItems );

        /**
        * show dialog to enter the number of items.
        */
        void EnterNumberOfItemsL( void );
    
        /**
        * Select/Deselect/Toggle selection of all items.
        * @param aCommand menu-command that specifies how to set marks.
        */
        void MarkAllItemsL( TInt aCommand );

    public: // Functions from base classes

    protected:  // New functions

        /**
        * prepare resources for the grid.
        */
        void CreateGridResourceL( void );

        /**
        * load bitmap resources.
        */
        void LoadGraphicsL( void );

        /**
        * set layout to the grid.
        * @param client rect.
        */
        void SetGridLayoutL( void );

        /**
        * set layout to cells in the grid.
        */
        void ApplySelGridGraphicStyleL( void );

        /**
        * show the current index.
        */
        void CheckIndex( void );

    protected:  // Functions from base classes

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

     protected : //data

        CAknGrid* iGrid;            // Grid class 
        CAknGridM* iGridM;          // Grid class 
 
        TBool iVerticalOrientation; // params used by SetGridLayoutL()
        TBool iLeftToRight;
        TBool iTopToBottom;
        TInt iNumOfColumns;
        TInt iNumOfRows;
        TInt iContentType;
        TSize iSizeOfItems;
        TInt iNumOfItems;
        TBool iInstantsCreated;      // indicate wether the Select or menu grid is using

        CAknGridView::TScrollingType iVerticalScrollingType; // Scrolling type
        CAknGridView::TScrollingType iHorizontalScrollingType; 
    
        TAknExGridGridType          iGridType;

    private: //data
        CEikLabel* iLabel;          // label for the selection grid
        CEikLabel* iToDoLabel;      // dolabel for the selection grid

    public:
        TBool AutoTestL();

    private: //data
        CDesCArrayFlat* iTitles;    // Title list
        TInt iTestNumber;

        enum TSelectionTitles
            {
            ESelectionTest1=0,
            ESelectionTest2,
            ESelectionTest3,
            ESelectionTest4,
            ESelectionTest5,
            ESelectionTest6,
            ESelectionTest7,
            ESelectionTest8,
            ESelectionTest9,
            ESelectionTest10,
            ESelectionTest11,
            ESelectionTest12,
            ESelectionTest13,
            ESelectionTest14,
            ESelectionTest15,
            ESelectionTest16,
            ESelectionTest17,
            ESelectionTest18,
            ENumberOfSelectionTitles
            };

        enum TMarkableTitles
            {
            EMarkableTest1=0,
            ENumberOfMarkableTitles
            };
    };

#endif      // AKNEXGRIDCONTAINERASSELECTION_H
// End of File
