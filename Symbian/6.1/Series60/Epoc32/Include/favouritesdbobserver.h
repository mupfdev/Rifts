/*
* ============================================================================
*  Name     : FavouritesDbObserver.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of classes MFavouritesDbObserver.
*      
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
*
* ============================================================================
*/

#ifndef FAVOURITES_DB_OBSERVER_H
#define FAVOURITES_DB_OBSERVER_H

//  INCLUDES

#include <e32base.h>
#include <d32dbms.h>

// CLASS DECLARATION

/**
* Mixin protocol from handling events from an CFavouritesDb. Users of
* CActiveFavouritesDbNotifier must derive from this.
*/
class MFavouritesDbObserver
    {

    public:     // new methods

        /**
        * Derived classes should implement this method, and act accordingly
        * to database events.
        * (Note that when a using a CActiveFavouritesDbNotifier, after a
        * RDbNotifier::EClose event the notifier is Cancel()-led.)
        * @param aEvent Database event.
        */
        IMPORT_C virtual void HandleFavouritesDbEventL
            ( RDbNotifier::TEvent aEvent ) = 0;

    };

#endif
            
// End of File
