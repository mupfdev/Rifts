/*
* ============================================================================
*  Name     : ApListItemList.h
*  Part of  : Access Point Engine
*
*  Description: Declaration of the CApListItemList class.
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

#ifndef CAPLISTITEMLIST_H
#define CAPLISTITEMLIST_H

//  INCLUDES
#include <e32base.h>
#include <ApEngineVer.h>

// FORWARD DECLARATION

class CApListItem;

// CLASS DECLARATION
/**
*  A list of CApListItem-s pointers; items are owned.
*/
class CApListItemList : public CArrayPtrFlat<CApListItem>
    {
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
        IMPORT_C CApListItemList();

        /**
        * Destructor. Items in the list are destroyed.
        */
        IMPORT_C virtual ~CApListItemList();

    public:  // New methods

        /**
        * Get pointer to the item having aUid,
        * or NULL if no such item is in the
        * list.
        * @param aUid Uid of item to get.
        * @return Pointer to the item having uid aUid, or NULL. Ownership
        * not passed (the list still owns the item).
        */
        IMPORT_C CApListItem* ItemForUid( TUint32 aUid ) const;

    };

#endif

// End of File
