/*
* ============================================================================
*  Name     : CPbkContactChangeNotifier.h
*  Part of  : PbkEng.dll
*
*  Description:
*       Class for registering CPbkContactEngine observers.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __CPbkContactChangeNotifier_H__
#define __CPbkContactChangeNotifier_H__

//  INCLUDES
#include <e32base.h>  // CBase

// FORWARD DECLARATIONS
class CPbkContactEngine;
class MPbkContactDbObserver;


// CLASS DECLARATION

/**
 * Class for registering CPbkContactEngine observers.
 */
class CPbkContactChangeNotifier : public CBase
    {
    public:  // Constructors and destructor
        /**
         * Creates a new instance of this class and registers aObserver as an
         * observer of aEngine.
         *
         * @param aEngine   observed object.
         * @param aObserver observer to call when aEngine changes.
         */
        IMPORT_C static CPbkContactChangeNotifier* NewL
            (CPbkContactEngine& aEngine, MPbkContactDbObserver* aObserver);

        /**
         * Removes aObserver from aEngine given as paramters to NewL and
         * destructs this object.
         */
        ~CPbkContactChangeNotifier();

    private:  // Implementation
        CPbkContactChangeNotifier
            (MPbkContactDbObserver* aObserver);
        void ConstructL(CPbkContactEngine& aEngine);

    private:  // data
        /// Ref: Phonebook engine
        CPbkContactEngine* iEngine;
        /// Ref: the observer
        MPbkContactDbObserver* iObserver;
    };


#endif // __CPbkContactChangeNotifier_H__

// End of File
