/*
* ==============================================================================
*  Name        : ClkDateTimeView.h
*  Part of     : ClkDateTimeView / ClkDateTimeView.dll
*  Interface   : 
*  Description : This class implements the function of
*                common "Date & Time" settings view.
*  Version     : 
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef CLKDATETIMEVIEW_H
#define CLKDATETIMEVIEW_H

//  INCLUDES
#include <coecntrl.h>
#include <aknlists.h>
#include <t32wld.h>
#include <aknview.h>
#include <aknsettingpage.h>
#include <bacntf.h>
#include <ClkMdlObserver.h>

// CONSTANTS
const TInt KMaxItemLength=128;
const TInt KMaxAttrLength=64;
const TInt KMaxValueLength=64;

const TUid KMainViewId = {1};
const TUid KClkDateTimeViewId = {10};

const TInt KNotiferPriority = CActive::EPriorityIdle;

// DATA TYPES
class TClkDateTimeInfo
    {
    public:
        TTime           iTime;
        TDateFormat     iDateFormat;
        TInt            iDateSepar;
        TTimeFormat     iTimeFormat;
        TInt            iTimeSepar;
        TBool           iNITZ;
        TClockFormat    iClockFormat;
    };

enum TClkDateTimeViewPanic
    {
    EClkDateTimeViewBadLocale,
    EClkDateTimeViewBadCommandId,
    EClkDateTimeViewBadItemIndex
    };

#ifdef _DEBUG
// FUNCTION PROTOTYPES
GLREF_C void Panic(TClkDateTimeViewPanic aPanic);
#endif  // _DEBUG

//  FORWARD DECLARATION
class CClkDateTimeViewContainer;
class CAknTimeQueryDialog;
class CClkNitzModel;
class CClkIntermediateObserver;

// CLASS DECLARATION

/**
*  Common "Date & Time" settings view.
*
*/

class CClkDateTimeView : public CAknView,
    public MEikListBoxObserver, public MClkModelObserver
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        * @param aClockUse  ETrue means Clock application uses this.
        *                   EFalse means any application
        *                   except Clock uses this.
        * @param aViewId    Id of a view which is changed to,
        *                   when Back softkey is pressed.
        *                   It is ignored when aClockUse is ETrue.
        * @return CClkDateTimeView*
        */
        IMPORT_C static CClkDateTimeView*
            NewLC(TUid aViewId, TBool aClockUse = EFalse);

        /**
        * Destructor.
        */
        IMPORT_C ~CClkDateTimeView();

    public: // Functions from base classes

        /**
        * From CAknView Returns this view Id.
        */
        TUid Id() const;

        /**
        * From MEikCommandObserver Handles commands.
        */
        void HandleCommandL(TInt aCommandId);

        /**
        * From MClkModelObserver
        * Called when the model is changed.
        * @param aNotification The cause of the notification.
        */
        void HandleUpdateL(TInt aNotification);

    public: // New functions

        /**
        * Moves the current item to the top of the list items.
        */
        IMPORT_C void InitCurrentItem();

        /**
        * Handle options changed by system
        * @param aChange It indicates a cause of the change.
        */
        void HandleSettingsChangeL(const TInt aChange);

        /**
        * Increments the current list item to handle the task swapping event.
        */
        void IncCurrentItem();

        /**
        * Decrements the current list item to handle the task swapping event.
        */
        void DecCurrentItem();

        /**
        * Gets a flag meaning that Clock application is using.
        * @return ETrue means the ClockApp uses this object.
        *         EFalse means the ClockApp doesn't use this object.
        */
        TBool IsClockInUse() const;

        /**
        * Gets a previous view id.
        * @return TVwsViewId
        */
        TVwsViewId PrevViewId() const;

        /**
        * Handles a softkey event "Change".
        * @param aItemId The current item id of the settings list box.
        */
        void HandleChangeCmdL(const TInt aItemId);

    protected:  // Functions from base classes

        /**
        * From CAknView Activates this view.
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId, const TDesC8& aCustomMessage);

        /**
        * From CAknView Deactivates this view.
        */
        void DoDeactivate();


        /**
        * From MEikListBoxObserver Handles an event happend in aListBox.
        */
        void HandleListBoxEventL(
            CEikListBox* aListBox, TListBoxEvent aEventType);

    private:    // New functions

        /**
        * By default Symbian OS constructor is private.
        * @param aClockUse  ETrue means Clock application uses.
        *                   EFalse means any application except Clock uses.
        * @param aViewId    Id of a view which is changed to,
        *                   when Back softkey is pressed.
        *                   It is ignored when aClockUse is ETrue.
        */
        void ConstructL(TUid aViewId, TBool aClockUse);

        /**
        * Reads the resources for settings list.
        * @param aResourceID Resource id for settings list.
        */
        void GetResourcesL(TInt aResourceID);

        /**
        * Makes the list box items.
        */
        void PopulateListBoxL();

        /**
        * Updates the list box items.
        * @param aItemId An item id of the listbox.
        */
        void UpdateListBoxL(TInt aItemId);

        /**
        * Updates all items.
        */
        void UpdateAllL();


        /**
        * Updates the date and the time.
        * @param aTime The new time.
        * @return error code
        */
        TInt SetDateTime(TTime& aTime);

        /**
        * Updates the date format.
        */
        void SetDateFormat();

        /**
        * Updates the date separator.
        */
        void SetDateSeparator();

        /**
        * Updates the time format.
        */
        void SetTimeFormat();

        /**
        * Updates the time format.
        */
        void SetTimeSeparator();

        /**
        * Updates the clock type.
        */
        void SetClockType();

        /**
        * Gets the NITZ state.
        */
        void NITZL();

        /**
        * Updates the NITZ state.
        */
        void SetNITZL();

        /**
        * Gets the device's setting values.
        */
        void SettingsL();

        /**
        * Makes the date item in the list box.
        */
        void MakeDateItemL();

        /**
        * Makes the date format item in the list box.
        */
        void MakeDateFormatItem();

        /**
        * Makes the date separator item in the list box.
        */
        void MakeDateSeparItem();

        /**
        * Makes the time item in the list box.
        */
        void MakeTimeItemL();

        /**
        * Makes the time format item in the list box.
        */
        void MakeTimeFormatItem();

        /**
        * Makes the time separator item in the list box.
        */
        void MakeTimeSeparItem();

        /**
        * Makes the NITZ item in the list box.
        */
        void MakeNITZItem();

        /**
        * Makes the clock control type item in the list box.
        */
        void MakeClockTypeItem();

        /**
        * Deletes the buffers used for the list box resources.
        */
        void DeleteResourceBuf();

        /**
        * Gets the date format of the device.
        */
        TInt DateFmt();

        /**
        * Handles a back softkey command.
        */
        void HandleBackCmdL();

        /**
        * Handles a date command.
        */
        void HandleDateCmdL();

        /**
        * Handles a date format command.
        */
        void HandleDateFrmtCmdL();

        /**
        * Handles a date separator command.
        */
        void HandleDateSeparCmdL();

        /**
        * Handles a time command.
        */
        void HandleTimeCmdL();

        /**
        * Handles a time format command.
        */
        void HandleTimeFrmtCmdL();

        /**
        * Handles a time separator command.
        */
        void HandleTimeSeparCmdL();

        /**
        * Handles a NITZ command.
        * @param aDraw ETrue means this redraws the NITZ item.
        *              EFalse means this doesn't redraw the NITZ item.
        */
        void HandleNitzCmdL(TBool aDraw = ETrue);

        /**
        * Handles a clock type command.
        */
        void HandleClockTypeCmdL();

        /**
        * Shows a popup setting page.
        * @param aItemArray containing setting items.
        * @param aIndex an index of initial item.
        * @param aLabel a text of label.
        * @return an index of selected item.
        */
        TInt QueryPopupSettingPageL(
            CDesCArray& aItemArray, TInt aIndex, TDesC& aLabel);

        /**
        * Callback when enviroment changed.
        * @param aThis This class.
        * @return TInt ETRUE or EFALSE
        */
        static TInt DoNotiferCallbackL(TAny* aThis);

        /**
        * Shows an confirmation note of nits setting off.
        */
        void ShowNitzSetOffConfNoteL();

        /**
        * Callback every interval time.
        * @param aThis This class.
        * @return TInt ETRUE or EFALSE
        */
        static TInt TimerCallback(TAny* aThis);

    private:    // Data
        CClkDateTimeViewContainer*  iContainer; // Owned
        MDesCArray*                 iItemList;
        CDesCArray*                 iItemArray;
        TClkDateTimeInfo            iDateTimeInfo;
        TVwsViewId                  iPrevViewId;
        TUid                        iViewId;
        TInt                        iOffset;
        CDesCArrayFlat*             iDateFrmtItemLists;  // Owned
        CDesCArrayFlat*             iDateSeparItemLists;  // Owned
        CDesCArrayFlat*             iTimeSeparItemLists;  // Owned
        CEnvironmentChangeNotifier* iNotifier;      // Owned
        CClkNitzModel*              iNitzModel;     // Owned
        CClkIntermediateObserver*   iModelObserver; // Owned
        CPeriodic*                  iTimer; // Owned
        // used to control key event
        TBool                       iIsClockInUse;
        TInt                        iCurrentItem;
        TInt                        iTopItem;
        TInt                        iNumOfItemsInView;

        // used to control menu event
        TBool                       iMenuChange;

        // Used in setting list item.
        TBuf<KMaxItemLength>        iItem;
        TBuf<KMaxValueLength>       iValue;

        // From resource.
        HBufC*      iDate;
        HBufC*      iDateFrmt;
        HBufC*      iDateSepar;
        HBufC*      iTime;
        HBufC*      iTimeFrmt;
        HBufC*      iTimeSepar;
        HBufC*      iNITZ;
        HBufC*      iClockType;
        HBufC*      iAbbrev24H;
        HBufC*      iAbbrev12H;
        HBufC*      iNitzOn;
        HBufC*      iNitzOff;
        HBufC*      iAnalog;
        HBufC*      iDigital;
    };

#endif      // CLKDATETIMEVIEW_H

// End of File
