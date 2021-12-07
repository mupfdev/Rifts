/*
* ============================================================================
*  Name     : CAknExScrollerContainer2 from CCoeControl, MCoeControlObserver
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSCROLLERCONTAINER2_H
#define AKNEXSCROLLERCONTAINER2_H

// INCLUDES
#include <aknview.h>
#include <eiklbo.h>

   
// FORWARD DECLARATIONS
class CEikLabel;        // for labels
class CEikListBox;
class CEikFormattedCellListBox;
class CEikButtonGroupContainer;

class CAknExScrollerCbaHandler;


// CLASS DECLARATION
/**
*  CAknExScrollerContainer2  container control class.
*  
*/
class CAknExScrollerContainer2 : public CCoeControl, MCoeControlObserver, MEikListBoxObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExScrollerContainer2();
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExScrollerContainer2();

    public: // From MEikListBoxObserver

        /**
        * Handles listbox event.
        * @param aListBox Pointer to ListBox object is not used.
        * @param aEventType Type of listbox event.
        */
        void HandleListBoxEventL(
            CEikListBox* aListBox,
            TListBoxEvent aEventType );

    public:  // New functions
       /**
        * Adds an item to list box
        */
        void AddItemToListBoxL();

       /**
        * Remove an item from list box
        */
        void RemoveItemFromListBox();


    private: // Functions from base classes
       /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

       /**
        * From CoeControl,CountComponentControls.
        * @return Number of component controls 
        */
        TInt CountComponentControls() const;

       /**
        * From CCoeControl,ComponentControl.
        * @param Specification for component pointer
        * @return Pointer to component control
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

       /**
        * From CCoeControl,Draw.
        * @param Specified area for drawing
        */
        void Draw( const TRect& aRect ) const;

        /**
        * From CCoeControl, OfferKeyEventL.
        * Handles the key events.
        * @param aKeyEvent Key event
        * @param aType Type of key event
        *        (EEventKey, EEventKeyUp or EEventKeyDown)
        * @return if key-event is consumed, EKeyWasConsumed. 
        *         Else EKeyWasNotConsumed
        */
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                     TEventCode aType );

        /**
        * From MCoeControlObserver,
        *   Handles an event of type aEventType reported
        *   by the control aControl to this observer.
        *   And it is a pure virtual function in MCoeControlObserver.
        *   We must implement it, despite empty.
        * @param Pointer to component control
        * @param Event Code
        */
        void HandleControlEventL( CCoeControl* /* aControl */,
                                  TCoeEvent /* aEventType */ );


    private: // New functions

        // List Box
       /**
        * Creates list box
        */
        void CreateListBox();

       /**
        * Closes list box
        */
        void CloseListBox();

    private: //data
        
        CEikListBox*              iListBox;       // List box
        CEikFormattedCellListBox*        iDoubleListBox;       // List box
    };

#endif // AKNEXSCROLLERCONTAINER2_H

// End of File
