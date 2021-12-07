/*
* ============================================================================
*  Name     : CAknExScrollerCbaHandler from MEikCommandObserver
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


#ifndef AKNEXSCROLLERCBAHANDLER_H
#define AKNEXSCROLLERCBAHANDLER_H

// INCLUDES
#include <eikcmobs.h>

// FORWARD DECLARATIONS
class CAknExScrollerContainer2;

// CLASS DECLARATION
/**
* CAknExScrollerCbaHandler
* Handling CBA commands
* 
*/
class CAknExScrollerCbaHandler : public MEikCommandObserver
    {
    public: // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CAknExScrollerCbaHandler();

        /**
        * Overload constructor.
        * @param aContainer Pointer to container class object.
        */
        CAknExScrollerCbaHandler( CAknExScrollerContainer2* aContainer );

    public: // From MEikCommandObserver

        /**
        * From MEikCommandObserver, Process CommandL.
        * Handles the commands.
        * @param aCommandId Command which is handled.
        */
        void ProcessCommandL( TInt aCommandId );

    private: // Data
        CAknExScrollerContainer2* iContainer;

    };

#endif // AKNEXSCROLLERCBAHANDLER_H

// End of File
