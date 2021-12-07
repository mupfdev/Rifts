/*
* =============================================================================
*  Name     : CAknExSettingListItemData
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


// INCLUDE FILES
#include <eikenv.h>
#include <in_sock.h>
#include <aknexsettinglist.rsg>
#include "aknexsettinglistitemdata.h"

const TInt KMinFldVal = 20;


// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSettingListListbox::NewL
// Two-phase constructor
// ----------------------------------------------------------------------------
//
CAknExSettingListItemData* CAknExSettingListItemData::NewL()
    {
    CAknExSettingListItemData* data = new(ELeave) CAknExSettingListItemData;
    CleanupStack::PushL(data);
    data->ConstructL();
    CleanupStack::Pop(); // data
    return data;
    }

// Destructor
//
CAknExSettingListItemData::~CAknExSettingListItemData()
    {
    }

// Constructor
//
CAknExSettingListItemData::CAknExSettingListItemData()
    : iVolume(5)
    {
    }

// Epoc default constructor
//
void CAknExSettingListItemData::ConstructL()
    {
    CEikonEnv* env = CEikonEnv::Static();
    env->ReadResource(iTextBuf, R_AKNEXSETTINGLIST_TEXT_INITIAL);

    iTime.HomeTime();
    iDate.HomeTime();

    env->ReadResource(iPw, R_AKNEXSETTINGLISTITEMDATA_MYPASSWORD);
    iPin = _L("1515");
    
    iIpAddress.SetAddress( INET_ADDR(KMinFldVal,
                                     KMinFldVal,
                                     KMinFldVal,
                                     KMinFldVal) );
    }

// End of File
