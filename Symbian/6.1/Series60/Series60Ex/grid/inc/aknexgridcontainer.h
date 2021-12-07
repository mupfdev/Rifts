/*
* ============================================================================
*  Name     : CAknExGridContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDCONTAINER_H
#define AKNEXGRIDCONTAINER_H

// INCLUDES
#include <aknview.h>
   
// FORWARD DECLARATIONS
class CEikLabel;        // for example labels
class CAknGrid;         // Grid

// CLASS DECLARATION

//CONSTANTS
#define VIEW_MAIN_LABEL_POINT TPoint( 10, 10 )
#define VIEW_MAIN_DOLABEL_POINT TPoint( 10, 100 )

const TInt KLengthOfLabelString = 256;
const TInt KLengthOfToDoLabelString = 256;
const TInt KNumberOfComponentMain = 2;

/**
*  CAknExGridContainer  container control class.
*  
*/
class CAknExGridContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExGridContainer();

    public: // New functions

    public: // Functions from base classes

    private: // Functions from base classes

       /**
        * From CoeControl, Called by framework when the view size is changed.
        */
        void SizeChanged();

       /**
        * From CoeControl, Returns number of component.
        * @return Number of component controls
        */
        TInt CountComponentControls() const;

       /**
        * From CCoeControl, Returns pointer to particular component.
        * @param Specification for component pointer
        * @return Pointer to component control
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

       /**
        * From CCoeControl, Draw function
        * @param Specified area for drawing
        */
        void Draw( const TRect& aRect ) const;

        /**
        * From MCoeControlObserver,
        *   Handles an event of type aEventType reported
        *   by the control aControl to this observer.
        *   And it is a pure virtual function in MCoeControlObserver.
        *   We must implement it, despite empty.
        * @param Pointer to component control
        * @param Event Code
        */
        // event handling section
        // e.g Listbox events
        void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );
        
    private: //data
        
        CEikLabel* iLabel;          // example label
        CEikLabel* iToDoLabel;      // example label
        CAknGrid* iGrid;            // Grid 

        //Enumeration
        enum TPointerToComponentViewMain
            {
            ELabel = 0,
            EToDoLabel,
            EGrid
            };

    };

#endif     //AKNEXGRIDCONTAINER_H

// End of File
