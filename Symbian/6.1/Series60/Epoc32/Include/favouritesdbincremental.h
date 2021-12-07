/*
* ============================================================================
*  Name     : FavouritesDbIncremental.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of class RFavouritesDbIncremental.
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

#ifndef FAVOURITES_DB_INCREMENTAL_H
#define FAVOURITES_DB_INCREMENTAL_H

//  INCLUDES

#include <d32dbms.h>

// FORWARD DECLARATIONS

class CFavouritesDb;

// CLASS DECLARATION

/**
* Incremental object for Favourites Engine.
* This class provides incremental database administration (recovery,
* compaction). Clients usually need not to use this class.
*/
class RFavouritesDbIncremental
    {
    public:     // update

        /**
        * Start incremental recovery on the given database.
        * @param aDb The database to be recovered.
        * @param aStep Placeholder for the step counter to be returned.
        * @return Error code.
        */
        IMPORT_C TInt Recover( CFavouritesDb& aDb, TInt& aStep );

        /**
        * Start incremental compaction on the given database.
        * @param aDb The database to be compacted.
        * @param aStep Placeholder for the step counter to be returned.
        * @return Error code.
        */
        IMPORT_C TInt Compact( CFavouritesDb& aDb, TInt& aStep );

        /**
        * Perform next step of incremental operation.
        * @param aStep Step counter.
        * @return Error code.
        */
        IMPORT_C TInt Next( TInt& aStep );

        /**
        * Close the incremental object.
        */
        IMPORT_C void Close();

    private:        // Data

        RDbIncremental iIncremental;    ///< DBMS incremental object.
    };

#endif
            
// End of File
