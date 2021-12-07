/*
* ============================================================================
*  Name     : AknExSettingListItemData.h
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSETTINGLISTITEMDATA_H
#define AKNEXSETTINGLISTITEMDATA_H

// INCLUDES
#include <e32base.h>


#define KSettingAppMaxSettingTextSize 50
#define KSettingAppMaxPasswordTextSize 20

// FORWARD DECLARATIONS
class CSharedDataI;
// CLASS DECLARATION

/**
* CAknExSettingListItemData 
*/
class CAknExSettingListItemData : public CBase
    {
    public:
        static CAknExSettingListItemData* NewL();
        ~CAknExSettingListItemData();

    private:
        CAknExSettingListItemData();
        void ConstructL();

    public:
        TInt iVolume;
        TInt iSliderValue;
        TInt iLanguageCode;
        TBuf<KSettingAppMaxSettingTextSize> iTextBuf;
        TTime iDate;
        TTime iTime;
        TBool iBinary;
        TBuf<KSettingAppMaxPasswordTextSize> iPw;
        TBuf<KSettingAppMaxPasswordTextSize> iPin;
        TInetAddr iIpAddress;
        TBool iFepEnabled;
        TInt  iFepLanguageCode;
    };


#endif

// End of File
