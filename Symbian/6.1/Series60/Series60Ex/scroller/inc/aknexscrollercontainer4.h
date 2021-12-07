/*
* ============================================================================
*  Name     : CAknExScrollerContainer4 from CCoeControl, MCoeControlObserver
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSCROLLERCONTAINER4_H
#define AKNEXSCROLLERCONTAINER4_H

// INCLUDES
#include <aknview.h>

   
// FORWARD DECLARATIONS
class CEikLabel;        // labels
class CEikEdwin;        // editor

// CLASS DECLARATION
/**
*  CAknExScrollerContainer4  
*  container control class for View1.
*  
*/
class CAknExScrollerContainer4 : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExScrollerContainer4();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExScrollerContainer4();


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
      
        /**
         * From CCoeControl, Handles key event.
         * @param aKeyEvent The key event.
         * @param aType The type of the event.
         * @return Indicates whether or not the key event was
         *           used by this control.
         */
         TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,
                                    TEventCode aType);

    public:
         TBool RunNextTestL();
    private:
         void RunTestL(TInt aTestId);
         void SetCursorPosL(TInt aPos);

    private: //data
        CEikLabel* iLabel;        // label
        CEikLabel* iDoLabel;      // label
        CEikEdwin* iEdwin;        // editor

        TInt iTestNumber;
        CDesCArrayFlat* iItems;

        enum TView4Tests
            {
            EView4SetString1,
            EView4CursorPosition10,
            EView4CursorPosition20,
            EView4CursorPosition30,
            EView4CursorPosition40,
            EView4CursorPosition50,
            EView4CursorPosition60,
            EView4CursorPosition70,
            EView4CursorPosition80,
            EView4CursorPosition90,
            EView4CursorPosition100,
            EView4CursorPosition110,
            EView4CursorPosition120,
            EView4CursorPosition130,
            EView4CursorPosition140,
            EView4CursorPosition150,
            EView4CursorPosition160,
            EView4CursorPosition170,
            EView4CursorPosition180,
            EView4CursorPosition190,
            EView4CursorPosition200,
            ESetScrollBarVisibilityOn,
            EView4DeleteString1,
            ESetScrollBarVisibilityAuto,
            EView4SetString2,
            EScrollBarExists1,
            EScrollBarExists2,
            EOperatorTest,
            EScrollbarUseful,
            EScrollbarUseful2,
            EMaxThumbPos,
            ECheckBounds,
            EThumbPosition,
            EIncreaseNudgeButton,
            EDecreaseNudgeButton,
            ESetScrollBarVisibilityOff,
            EView4DeleteString2,
            ENumberOfOtherTests
            };

    };

#endif // AKNEXSCROLLERCONTAINER4_H

// End of File
