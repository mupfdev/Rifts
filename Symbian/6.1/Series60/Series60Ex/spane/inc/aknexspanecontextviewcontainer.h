/*
* ============================================================================
*  Name     : CAknExSpaneContextViewContainer from Control, MCoeControlObserver
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANECONTEXTVIEWCONTAINER_H
#define AKNEXSPANECONTEXTVIEWCONTAINER_H

// INCLUDES
#include <aknview.h>

// CONSTANTS
_LIT(KContextBitMapFile, "\\system\\apps\\aknexspane\\aknexspane.mbm");
const TInt KLengthOfContextTempString = 100;


// FORWARD DECLARATIONS
class CAknContextPane;

// CLASS DECLARATION
/**
*  CAknExSpaneContextViewContainer  
*  container control class for View.
*  
*/
class CAknExSpaneContextViewContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExSpaneContextViewContainer();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExSpaneContextViewContainer();

    public: // New functions
        /**
        * Run next test 
        * @return Ture: success, False: all of he test steps has been done, role back.
        */
        TBool RunNextTestL();

        /**
        * Run last test 
        * @return Ture: success, False: all of he test steps has been done, role back.
        */
        TBool RunLastTestL();

        /**
        * Run one test 
        * @param aTestId Test item number.
        */
        void RunTestL(TInt aTestId);

        /**
        * Reset the test processing
        */
        void ResetTest();
    
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
        CEikLabel* iContextLabel;
        CEikLabel* iInfoLabel;
        CEikLabel* iStLabel;

        CFbsBitmap* iBitmap;
        CFbsBitmap* iBitmapM;

        TInt iTestNumber;
        CAknContextPane* iContextPane;
        CDesCArrayFlat* iItems;                // message list

        enum TContextTests     // Test steps, total 6
            {
            // DO NOT MODIFY THE SEQUENCE
            //  You can add or delete items at tail,
            //  but  do not insert or delete an items in the queue.
            //  This Enum declare is related with the resource 
            //  r_aknexspane_Context_items in rss file.
            //  If the change is inevasible, modify both together.
            EDefault = 0,
            ESmallImage,
            EMediumImage,
            EBigImage,
            EMediumImageFromFile,
            EImageFromResources,
            ESwitchLayoutOff,
            ESwitchLayoutOn,
            ESwitchVisibilityOff,
            ESwitchVisibilityOn,
            ENumberOfContextTests
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

#endif // AKNEXSPANECONTEXTVIEWCONTAINER_H

// End of File
