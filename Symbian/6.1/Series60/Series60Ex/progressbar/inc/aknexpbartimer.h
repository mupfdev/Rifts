/*
* ============================================================================
*  Name     : CAknExPbarTimer from CTimer
*  Part of  : AknExPbar 
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPBARTIMER_H
#define AKNEXPBARTIMER_H

// INCLUDES
#include <aknappui.h>


// FORWARD DECLARATIONS
class  CAknExPbarContainer;

struct TAknExPbarTimerModel;


// CLASS DECLARATION

/**
* Timer class.
*/
class CAknExPbarTimer : public CTimer
    {

    public:  // Constructors and destructor
        
        /**
        * C++ default constructor.
        */
        CAknExPbarTimer();

        /**
        * default EPOC constructor.
        */
        void ConstructL( TAknExPbarTimerModel* aModel, 
                        CAknExPbarContainer*  aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExPbarTimer();


    private: // from CActive
        
        /**
        * Difinition of what to do,
        * when timer event occurred.
        */
        void RunL();


    private: // New function
        
        /**
        * Set timer event interval.
        */
        void Queue();


    private:  // Data
        TAknExPbarTimerModel* iModel;      // Ptr to Timer model
        CAknExPbarContainer*  iContainer;  // Ptr to Container class
    };

#endif // AKNEXPBARTIMER_H

// End of File
