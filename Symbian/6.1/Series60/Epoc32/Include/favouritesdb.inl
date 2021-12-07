/*
* ============================================================================
*  Name     : FavouritesDb.inl
*  Part of  : Favourites Engine
*
*  Description:
*      Implementation of inline methods of class CFavouritesDb.
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

#ifndef FAVOURITES_DB_INL
#define FAVOURITES_DB_INL

// ---------------------------------------------------------
// CFavouritesDb::Database
// ---------------------------------------------------------
//
inline RDbDatabase& CFavouritesDb::Database()
    {
    return iDatabase;
    }

#endif
            
// End of File
