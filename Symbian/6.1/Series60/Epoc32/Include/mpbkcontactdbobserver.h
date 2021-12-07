/*
* ============================================================================
*  Name     : MPbkContactDbObserver.h
*  Part of  : PbkEng.dll
*
*  Description:
*       Interface class declaration for Phonebook contact database observers.
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

#ifndef __MPbkContactDbObserver_H__
#define __MPbkContactDbObserver_H__

//  INCLUDES
#include <cntdef.h>     // cntdbobs.h requires TContactItemId from this header
#include <cntdbobs.h>   // MContactDbObserver

// FORWARD DECLARATIONS
class CPbkContactEngine;

// CLASS DECLARATION

/**
 * Interface class for Phonebook contact database observers.
 *
 * @see MContactDbObserver
 * @see CPbkContactChangeNotifier
 */
class MPbkContactDbObserver : public MContactDbObserver
    {
    protected:  // Derived class interface
        /**
         * Called by CPbkContactEngine when it receives a database 
         * change event. From MContactDbObserver.
		 * @param aEvent the database event.
         */
        virtual void HandleDatabaseEventL(TContactDbObserverEvent aEvent) = 0;

        /**
         * Called by CPbkContactEngine after HandleDatabaseEventL has been 
         * called for all observers.
         * In other words: CPbkContactEngine calls first HandleDatabaseEventL
         * for all its observers and then this function again for all 
         * observers. You can think of it as an "all observers have seen 
         * aEvent" -notification. This used in Phonebook view activation for 
         * now. Default implementation does nothing.
         *
         * @param aEvent the database event
         */
        virtual void DatabaseEventHandledL(TContactDbObserverEvent /*aEvent*/)
            {
            // Empty default implementation
            }

        /**
         * Protected destructor. 
         * Observers are not destroyed via this interface.
         */
        virtual ~MPbkContactDbObserver() { }

    private:  // friend declarations
        /// CPbkContactEngine calls protected functions of this class.
        friend class CPbkContactEngine;
    };


#endif // __MPbkContactDbObserver_H__

// End of File
