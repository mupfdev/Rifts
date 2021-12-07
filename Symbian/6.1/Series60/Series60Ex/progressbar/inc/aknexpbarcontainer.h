/*
* ============================================================================
*  Name     : CAknExPbarContainer from CCoeControl, MCoeControlObserver
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPBARCONTAINER_H
#define AKNEXPBARCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include "AknExPbar.hrh"
#include <eikon.hrh>

// FORWARD DECLARATIONS
class CEikProgressInfo;
class CAknTitlePane;


// CLASS DECLARATION

/**
*  CAknExPbarContainer  container control class.
*  
*/
class CAknExPbarContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor
        */
        CAknExPbarContainer();    
            

        /**
        * EPOC default constructor.
        * @param  aRect Frame rectangle for container.
        * 
        */
        void ConstructL( const TRect& aRect );

        /**
        * Destructor.
        */
        virtual ~CAknExPbarContainer();

    public: // New functions

        /**
        * Increase progress bar length
        * @param  increment value
        * 
        */
        void IncrementBarsAndDraw( TInt aIncrement );

        /**
        * Reset progress bar length
        * 
        */
        void ResetAllValues();


    private: // Functions from base classes

        /**
        * From CoeControl,CountComponentControls.
        * @return amount of component controls,
        *         in this application, this is the
        *         number of progress bars.
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl,ComponentControl.
        * @param  each component controls in order
        * @return Ptr to each component controls
        */
        CCoeControl* ComponentControl( TInt aIndex ) const;

        /**
        * From CCoeControl,Draw.
        * @param  Frame rectangle for container
        */
        void Draw( const TRect& aRect ) const;


    private : // Functions from base classes
        /**
        * From MCoeControlObserver
        * @param aControl each component controls
        * @param aEventType event type
        */
        void HandleControlEventL( 
                CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/ );


    private: // New functions

        /**
        * Create progress bars
        */
        void CreateProgressBarsL(TEikProgressTextType aType);

    private: //data
        CEikProgressInfo* iPBar[ KNumberOfBars] ; // Element are pointers
                                                // to Progress bar

    public:
        void ChangeTextType(TEikProgressTextType aType);
        void SetFinalValue(TBool aFlag);
        void ShowInfo(TInt aBarNo);
        void AutoTest();
        void SetTestNumber(TInt aTestNo);

    private: // Data
        TInt iTestNumber;
        CAknTitlePane* iTitlePane;
    };

#endif // AKNEXPBARCONTAINER_H

// End of File
