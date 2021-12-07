/*
* ============================================================================
*  Name     : ActiveFavouritesDbNotifier.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of CActiveFavouritesDbNotifier.
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

#ifndef ACTIVE_FAVOURITES_DB_NOTIFIER_H
#define ACTIVE_FAVOURITES_DB_NOTIFIER_H

//  INCLUDES

#include <e32base.h>
#include <d32dbms.h>
#include <FavouritesDbNotifier.h>

// FORWARD DECLARATION

class CFavouritesDb;
class MFavouritesDbObserver;

// CLASS DECLARATION

/**
* Active object encapsulating a favourites database notifier. Once this
* notifier is Start()-ed, it keeps watching the database and notifies the
* observer, until the database is closed by all clients (i.e. released by
* DBMS), or it is Cancel()-led.
*/
class CActiveFavouritesDbNotifier : public CActive
    {
    public:     // construct / destruct

        /**
        * Constructor.
        * @param aDb Favourites database to watch for.
        * @param aObserver Observer to be notified about database events.
        */
        IMPORT_C CActiveFavouritesDbNotifier
            ( CFavouritesDb& aDb, MFavouritesDbObserver& aObserver );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CActiveFavouritesDbNotifier();

    protected:  // from CActive
        /**
        * Invoked when the outstanding request completes.
        */
        IMPORT_C void RunL() ;

        /**
        * Implementation of the Cancel protocol;
        * cancel any outstanding request.
        */
        IMPORT_C void DoCancel();

    public:     // new methods

        /**
        * Start the notifier. The notification request is automatically
        * renewed until it is cancelled, or the database is closed by
        * all clients (i.e. released by DBMS).
        * @return Error code.
        */
        IMPORT_C TInt Start();

    private:

        /**
        * Request database change notification from the Favourites Engine.
        */
        void NotifyChange();

    private:    // data

        RFavouritesDbNotifier iNotifier;    ///< Notifier object.
        CFavouritesDb* iDb;                 ///< Pointer to the database.
        MFavouritesDbObserver* iObserver;   ///< Pointer to observer.
    };

#endif
            
// End of File
