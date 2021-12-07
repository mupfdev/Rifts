/*
* ============================================================================
*  Name     : FavouritesDbNotifier.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of class RFavouritesDbNotifier.
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

#ifndef FAVOURITES_DB_NOTIFIER_H
#define FAVOURITES_DB_NOTIFIER_H

//  INCLUDES

#include <d32dbms.h>

// FORWARD DECLARATIONS

class CFavouritesDb;

// CLASS DECLARATION

/**
* Favourites database change notifier for the Favourites Engine.
* This class provides notification of database changes.
*/
class RFavouritesDbNotifier
    {
    public:     // update

        /**
        * Open the notifier.
        * @param aDb The database to be watched.
        * @return Error code.
        */
        IMPORT_C TInt Open( CFavouritesDb& aDb );

        /**
        * Close the notifier.
        */
        IMPORT_C void Close();

        /**
        * Request notification about all database events.
        * @param aStatus Request status.
        */
        IMPORT_C void NotifyAllEvents( TRequestStatus& aStatus );

        /**
        * Request notification about database changes.
        * @param aStatus Request status.
        */
        IMPORT_C void NotifyChange( TRequestStatus& aStatus );

        /**
        * Cancel the outstanding request (if any).
        */
        IMPORT_C void Cancel();

    private:        // Data

        RDbNotifier iNotifier;  ///< DBMS notifier object.
    };

#endif
            
// End of File
