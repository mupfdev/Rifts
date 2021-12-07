/*
* ============================================================================
*  Name     : FavouritesWapAp.h
*  Part of  : Favourites Engine
*
*  Description:
*      Declaration of class TFavouritesWapAp.
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

#ifndef FAVOURITES_WAP_AP_H
#define FAVOURITES_WAP_AP_H

//  INCLUDES
#include <e32base.h>

// CLASS DECLARATION

/**
* Representation one the WAP Access Point used in favourites. In addition to
* the WAP AP Uid-s (stored in CommDb), an item may hold more values. These are
* "Use default" and "Unset/Null". Since CommDb has no fixed Uid for these
* purposes, we have to wrap the CommDb Uid with a possibility to store
* specific ones.
*/
class TFavouritesWapAp
    {

    public:     // construction
        
        /**
        * C++ default constructor. Initializes to "Default".
        */
        IMPORT_C TFavouritesWapAp();

    public:     // operators

        /**
        * Assignment operator (from another TFavouritesWapAp).
        * @param aAp WAP AP to assign from.
        */
        IMPORT_C TFavouritesWapAp& operator= ( const TFavouritesWapAp& aAp );

        /**
        * Assignment operator (from TUint32).
        * "Null" and "Default" properties cleared.
        * @param aUid Uid to set.
        */
        IMPORT_C TFavouritesWapAp& operator= ( TUint32 aApId );

    public:     // setters

        /**
        * Set value is unset. Any previous value is lost.
        */
        IMPORT_C void SetNull();

        /**
        * Set value is "Default". Any previous value is lost.
        */
        IMPORT_C void SetDefault();

        /**
        * Set value. "Null" and "Default" properties cleared.
        * @param aApId AP Uid to set.
        */
        IMPORT_C void SetApId( TUint32 aApId );

    public:     // getters

        /**
        * Check if value is unset.
        * @return ETrue if value is unset.
        */
        IMPORT_C TBool IsNull() const;

        /**
        * Check if value is "Default"; meaning "use current default AP".
        * @return ETrue if value is "Default".
        */
        IMPORT_C TBool IsDefault() const;

        /**
        * Get the WAP AP uid. If the value is "Null" or "Default", this method
        * panickes. You have to check those before calling this method!
        * @return CommDb assigned WAP AP uid.
        */
        IMPORT_C TUint32 ApId() const;

    private:    // friends

        /// RFavouritesTable writes this into database.
        friend class RFavouritesTable;
        /// CFavouritesDb makes debug dump of raw data.
        friend class CFavouritesDb;

    private:    // types

        /**
        * This enum holds the value kind ("Null", "Default" or just normal).
        */
        enum TValueKind
            {
            ENormal,    ///< Has real value (not special).
            ENull,      ///< Has "Null" value.
            EDefault    ///< Has "Default value".
            };

    private:    // data

        /**
        * CommDb assigned WAP AP Uid. Meaningless if value is "Null" or
        * "Default".
        */
        TUint32 iApId;

        /**
        * Value kind.
        */
        TValueKind iValueKind;
    };

#endif
            
// End of File
