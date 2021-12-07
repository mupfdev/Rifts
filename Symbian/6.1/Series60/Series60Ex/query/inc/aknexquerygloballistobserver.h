/*
* =============================================================================
*  Name     : CAknExQueryGlobalListObserver
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYGLOBALLISTOBSERVER_H
#define AKNEXQUERYGLOBALLISTOBSERVER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <AknGlobalListQuery.h>
//#include "AknExQueryContainer.h"

// FORWARD DECLARATIONS
class CAknExQueryContainer;

// CLASS DECLARATION

/**
* CAknExQueryGlobalListObserver class
*/
class CAknExQueryGlobalListObserver:
    public CActive
    {
    public:  // Constructors and destructor
        /**
        * Two-phased constructor.
        */
        static CAknExQueryGlobalListObserver* NewL(CAknExQueryContainer* aContainer);

        /**
        * Destructor.
        */
        virtual ~CAknExQueryGlobalListObserver();

    public:     // New function
        /**
        * Start the activator.
        */
        void Start();

        /*
        * Set iSelectItemFlag.
        */
        void SetSelectItemFlag();

        /*
        * Unset iSelectItemFlag.
        */
        void UnsetSelectItemFlag();

    private:    // New function
        /**
        * C++ default constructor.
        */
        CAknExQueryGlobalListObserver(CAknExQueryContainer* aContainer);

        /**
        * EPOC default constructor.
        */
        void ConstructL();

    private:    // From CActive
        /**
        * From CActive, handle an event.
        */
        void RunL();

        /**
        * From CActive, implement the Cancel protocol.
        */
        void DoCancel();

        
    private: // Data
        CAknExQueryContainer* iContainer;
        TBool                 iSelectItemFlag;
    };

#endif

// End of File
