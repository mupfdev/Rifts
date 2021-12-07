/*
* ============================================================================
*  Name     : CAknExSpaneNaviViewContainer from Control, MCoeControlObserver
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANENAVIVIEWCONTAINER_H
#define AKNEXSPANENAVIVIEWCONTAINER_H

// INCLUDES
#include <aknview.h>

// CONSTANTS
_LIT(KNaviBitMapFile, "\\system\\apps\\aknexspane\\aknexspane.mbm");

const TInt KLengthOfNaviTempString = 100;
const TInt KNaviNewTabId = 1;

// FORWARD DECLARATIONS
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CAknTabGroup;


// CLASS DECLARATION
/**
*  CAknExSpaneNaviViewContainer  
*  container control class for View.
*  
*/
class CAknExSpaneNaviViewContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExSpaneNaviViewContainer();

        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        virtual ~CAknExSpaneNaviViewContainer();

    public: // New functions
        /**
        * Reset the test processing
        */
        void ResetTest();

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
        * Load add tab dialog
        * @param aIndex dialog style.
        */
        void OpenNaviTabDlg(TInt aIndex);

        /**
        * Control navi icon
        * @param aIndex command
        */
        void SetNaviIcon(TInt aIndex);

        /**
        * Change navi tab style
        * @param aIndex new style
        */
        void SetTabStyle(TInt aIndex);

        /**
        * Add/Delete/Modify/Select navi tab 
        * @param aIndex new style
        */
        void SetTabOperate(TInt aCommand, 
                           TInt aTabIndex,
                           TDes& aTabTextDes,
                           TInt aTabImageNumber);

        /**
        * Check wether the tab is been displaying
        * @return TRUE/FALSE
        */
        TBool IsTabBeDsiplayed();

        /**
        * Check wether the tab is been displaying
        * @return TRUE/FALSE
        */
        void GetTabIndexRange(TInt* aStartIndex, TInt* aEndIndex, TInt* aCurIndex);

        TBool IsNaviIconMenu();

    private: // New functions
        
        /**
        * Create navi decorators for tab group.
        * @param aResourceId resource used to create the decorator.
        * @return CAknTabGroup pointer. 
        */
        CAknTabGroup* CreateNaviDecoratorsForTabGroupL(TInt aResourceId);
        
        /**
        * Get navi decorators for tab group. If not exist, create it by the resource ID;
        * @param aResourceId resource used to create the decorator.
        * @return CAknTabGroup pointer. 
        */
        CAknTabGroup* GetNaviDecoratorsForTabGroupL(TInt aResourceId);

        /**
        * Create navi decorator for editor indicator container.
        */
        void CreateNaviDecoratorForEditorIndicatorContainerL();
        
        /**
        * Create navi decorator for volume indicator.
        * @param aType .
        */
        void CreateNaviDecoratorForVolumeIndicatorL(TBool aType);

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
        CEikLabel* iNaviLabel;
        CEikLabel* iInfoLabel;
        CEikLabel* iStLabel;
        CFbsBitmap* iBitmap;
        TInt iTestNumber;
        TBool iNewTabFlag;
        CAknNavigationControlContainer* iNaviPane;
        CAknNavigationDecorator* iNaviDecorator;
        CAknNavigationDecorator* iNaviDecoratorForTabs;
        CDesCArrayFlat* iItems;                // message list

        enum TNaviTests    // Test steps.
            {
            // DO NOT MODIFY THE SEQUENCE
            //  You can add or delete items at tail,
            //  but  do not insert or delete an items in the queue.
            //  This Enum declare is related with the resource 
            //  r_aknexspane_navi_items in rss file.
            //  If the change is inevasible, modify both together.
            EDefault = 0,

            ETwoTabs,
            ETwoLongTabs,
            EThreeTabs,
            EThreeLongTabs,
            ELongTabActive0,
            ELongTabActive1,
            ELongTabActive2,
            ELongTabActive3,
            ETabOneTab,
            EFourTabs,
            ETabActiveIllegal1,
            ETabActive0,
            ETabActive1,
            ETabActive2,
            ETabActive3,
            ETabActive4,
            ETabActive5,
            ETabActiveIllegal2,
            ETabAddNew,
            ETabReplaceCurrent,
            ETabDeleteCurrent,
            ETabActiveById,
            ETabActiveByIdIllegal,
            ENaviImage,
            ENaviImageLeftArrow,
            ENaviImageRightArrow,
            ENaviImageBothArrows,
            ENaviLabel,
            ENaviLabelLong,
            ENaviLabelLeftArrow,
            ENaviLabelRightArrow,
            ENaviLabelBothArrows,
            ENaviLongLabelBothArrows,
            ENaviHintText,
            ENaviHintTextLong,


            ENaviVolumeIndicator,
            ENaviVolumeIndicator2,
            ENaviVolumeIndicator3,
            ENaviVolumeIndicator4,

            ESwitchLayoutOff,
            ESwitchLayoutOn,
            ESwitchVisibilityOff,
            ESwitchVisibilityOn,

            ENumberOfNaviTests
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


#endif // AKNEXSPANENAVIVIEWCONTAINER_H

// End of File
