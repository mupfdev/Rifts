/*
* ============================================================================
*  Name     : CAknExSpanePopupViewContainer from Control, MCoeControlObserver
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANEPOPUPVIEWCONTAINER_H
#define AKNEXSPANEPOPUPVIEWCONTAINER_H

// INCLUDES
#include <aknview.h>
#include <aknnavi.h>

// CONSTANTS
const TInt KLengthOfPopupTempString = 100;

// FORWARD DECLARATIONS
class CAknExSpanePopUpWindow;

// CLASS DECLARATION
/**
*  CAknExSpanePopupViewContainer  
*  container control class for View.
*  
*/
class CAknExSpanePopupViewContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExSpanePopupViewContainer();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExSpanePopupViewContainer();
        
    public: // New functions
        /**
        * Run last test 
        * @return Ture: success, False: it is just the first test step, can not role back.
        */
        TBool RunLastTestL();

        /**
        * Run next test 
        * @return Ture: success, False: all of he test steps has been done, role back.
        */
        TBool RunNextTestL();

        /**
        * Run one test 
        * @param aTestId Test item number.
        */
        void RunTestL(TInt aTestId);

        /**
        * Reset the test processing
        */
        void ResetTestL();

    private: // Functions from base classes, CoeControl
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
        CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * From CCoeControl,Draw.
        * @param Specified area for drawing
        */
        void Draw(const TRect& aRect) const;

    private: // Functions from base classes, MCoeControlObserver
        /**
        * From MCoeControlObserver,
        *   Handles an event of type aEventType reported
        *   by the control aControl to this observer.
        *   And it is a pure virtual function in MCoeControlObserver.
        *   We must implement it, despite empty.
        * @param Pointer to component control
        * @param Event Code
        */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

    private: //data
        CEikLabel* iPopupLabel;
        CEikLabel* iInfoLabel;
        CEikLabel* iStLabel;
        CFbsBitmap* iBitmap;
        
        TInt iTestNumber;
        CAknExSpanePopUpWindow* iPopUpControl;
        CAknExSpanePopUpWindow* iSpecialContentControl;
        CCoeControl* iDefaultNaviControl;

        CDesCArrayFlat* iItems;                // message list

        enum TTitleTests     // Test steps
            {
            // DO NOT MODIFY THE SEQUENCE
            //  You can add or delete items at tail,
            //  but  do not insert or delete an items in the queue.
            //  This Enum declare is related with the resource 
            //  r_aknexspane_popup_items in rss file.
            //  If the change is inevasible, modify both together.
            EPopUpOverContextPane = 0,
            EPopUpOverContextAndMainPane,
            EPopUpOverSignaAndContextPane,
            EPopUpOverTitleAndNaviPane,
            ENaviSpecialContents,
            ENaviNormalContents,
            ESwitchLayoutOff,
            ESwitchLayoutOn,
            ESwitchVisibilityOff,
            ESwitchVisibilityOn,
            ENumberOfPopupTests
            };
        // Enumeration  (The last element ENumberOfComponent, indicates the number of items)
        enum TPointerToComponetIndicView
            {
            ETitleLabel = 0,
            EInfoLabel,
            EStLabel,
            ENumberOfComponent
            };
    };


#endif // AKNEXSPANEPOPUPVIEWCONTAINER_H

// End of File
