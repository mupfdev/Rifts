/*
* ============================================================================
*  Name     : FavouritesLimits.h
*  Part of  : Favourites Engine
*
*  Description:
*      Constants (fixed Uids, maximum data sizes, error codes).
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

#ifndef FAVOURITES_LIMITS_H
#define FAVOURITES_LIMITS_H

// CONSTANTS

//========== Favourites attribute limits ==========//

/// Max. length of an item name.
LOCAL_C const TInt KFavouritesMaxName = 50;
/// Max. length of an item URL.
LOCAL_C const TInt KFavouritesMaxUrl = 1024;
/// Max. length of an username.
LOCAL_C const TInt KFavouritesMaxUserName = 40;
/// Max. length of a password.
LOCAL_C const TInt KFavouritesMaxPassword = 40;

//========== Fixed Uid values ==========//

/// Null Uid; never assigned.
LOCAL_C const TInt KFavouritesNullUid = 0;
/// Uid of the root folder.
LOCAL_C const TInt KFavouritesRootUid = -1;
/// Uid of the Homepage.
LOCAL_C const TInt KFavouritesHomepageUid = -2;
/// Uid of the Last Visited Page.
LOCAL_C const TInt KFavouritesLastVisitedUid = -3;
/**
* Support for Start Page bookmark in the WML Browser. That bookmark is created
* in memory dynamically, and never exists in the database.
*/
LOCAL_C const TInt KFavouritesStartPageUid = -4;

//========== Unique name support ==========//

/**
* Maximum length of the postfix that is generated for unique names.
* (Unique names are created by appending a (32 bit) number in parenthesis. The
* longest postfix therefore reads "(4294967296)". That's 12 characters.
*/
LOCAL_C const TInt KFavouritesMaxPostfix = 13;

#endif
            
// End of File
