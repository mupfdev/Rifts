/*
* ============================================================================
*  Name     : CSendAppUi from Sendui.h
*  Part of  : Sendui
*  Description:
*     API for 'Send as...' menu.
*
*  Version  : %version: 11 %
*       %date_modified: Fri Oct 25 15:46:21 2002 %
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
* ============================================================================
*/

#ifndef INC_SENDUI_H
#define INC_SENDUI_H

#include <e32base.h>

class CEikMenuPane;
class CEikHotKeyTable;
class MDesC16Array;
class CRichText;
class CSendBaseUi;

/**
* TSendingCapabilities
* Used by sendui to filter mtm's from "Send as..." submenu,
* see for ex. CSendAppUi::DisplaySendMenuItemL.
* or can be used to check mtm's capabilities see CSendAppUi::MtmCapabilitiesL.
*/
class TSendingCapabilities
{
public:

    enum TSendingFlags
    {
        EAllMTMs = 0,
        ESupportsAttachments = 1,
        ESupportsBodyText = 2,
        ESupportsBioSending = 4,
        ESupportsAttachmentsOrBodyText = 8
    };

public:

    /**
    * default C++ constructor
    */
    IMPORT_C TSendingCapabilities();

    /**
    * C++ constructor
    * @param aBodySize: max body size
    * @param aMessageSize: max whole message size (inc. attachments)
    * @param aFlags: TSendingFlags.
    */
    IMPORT_C TSendingCapabilities(TInt aBodySize, TInt aMessageSize, TInt aFlags);

public:

    TInt iBodySize;
    TInt iMessageSize;
    TInt iFlags;
};

/**
* CSendAppUi
* Offers API for 'Send as...' menu and functions to create messages
* and launch messaging editors.
*/
class CSendAppUi : public CBase
{
public:

    /**
     * Creates object of CSendAppUi.
     * @param aCommandId: command id of the 'Send as...' menu item.
     * @param aHotKeyTable: not used.
     * @return Pointer to object of CSendAppUi.
     */
    IMPORT_C static CSendAppUi* NewL(
        const TInt aCommandId,
        CEikHotKeyTable* aHotKeyTable = NULL );

    /**
     * Creates object of CSendAppUi, leaves pointer to cleanup stack.
     * @param aCommandId: command id of the 'Send as...' menu item.
     * @param aHotKeyTable: not used.
     * @return Pointer to object of CSendAppUi.
     */
    IMPORT_C static CSendAppUi* NewLC(
        const TInt aCommandId,
        CEikHotKeyTable* aHotKeyTable = NULL );

    /**
     * Destructor.
     */
    IMPORT_C virtual ~CSendAppUi();

    /**
     * Adds 'Send as...' menu item to menupane.
     * @param aMenuPane: menu pane where 'Send as...' menu item is added.
     * @param aIndex: index of the 'Send as...' menu item.
     * @param aRequiredCapabilities: capabilities required by mtms to be displayed.
     * @return none
     */
    IMPORT_C virtual void DisplaySendMenuItemL(
        CEikMenuPane& aMenuPane,
        const TInt aIndex,
        TSendingCapabilities aRequiredCapabilities );

    /**
     * Displayes 'Send as...' submenu.
     * @param aMenuPane: menupane where all the mtm's are added.
     * @param aMtmsToDim: array of mtm uids not wanted to cascade menu.
     * @return none
     */
    IMPORT_C virtual void DisplaySendCascadeMenuL(
        CEikMenuPane& aMenuPane,
        CArrayFix<TUid>* aMtmsToDim = NULL );

    /**
     * Can be used to check if command is valid.
     * @param aCommandId: command id to be checked, see CreateAndSendMessageL
     * @param aRequiredCapabilities: like in DisplaySendMenuItemL.
     * @param aMtmsToDim: like in DisplaySendCascadeMenuL.
     * @return ETrue if command is ok, otherwise EFalse.
     */
    IMPORT_C virtual TBool CommandIsValidL(
        const TInt aCommandId,
        TSendingCapabilities aRequiredCapabilities,
        CArrayFix<TUid>* aMtmsToDim = NULL );

    /**
     * Returns mtm uid for the command.
     * @param aCommandId: command id to be returned.
     * @return TUid of the mtm for the command id.
     */
    IMPORT_C virtual TUid MtmForCommand( const TInt aCommandId );

    /**
     * Retuns capabilities of the mtm
     * @param aUid: TUid of the mtm which capabilities are requested
     * @return TSendingCapabilities class
     */
    IMPORT_C virtual TSendingCapabilities MtmCapabilitiesL( const TUid aUid );

    /**
     * Creates message to be sent and then calls corresponding mtm to edit the message.
     * @param aCommandId: Command id of the cascade menu. Command id's are calculated so that
     *    first item in cascade menu has command id aCommandId+1 and second aCommandId+2 etc.
     *    and here aCommandId is command id given to NewL function!
     * @param aBodyText: pointer to body text to be added to message
     * @param aAttachments: pointer to attachment array which includes file paths of the attachments
     *    to be added to the message
     * @param aBioTypeUid: bio type uid
     * @param aRealAddresses: pointer to the array which includes real addresses (in email's case
     *    real email addresses for ex: "my.address@host.com"
     * @param aAliases: pointer to the array which includes alias names to be displayed in editor
     *    (in email's case for ex: "My name").
     * @param aLaunchEmbedded: ETrue if editor should be launched embedded. Otherwise editor is launched stand-alone.
     * @return none
     */
    IMPORT_C virtual void CreateAndSendMessageL(
        const TInt aCommandId,
        const CRichText* aBodyText = NULL,
        MDesC16Array* aAttachments = NULL,
        const TUid aBioTypeUid = KNullUid,
        MDesC16Array* aRealAddresses = NULL,
        MDesC16Array* aAliases = NULL,
        TBool aLaunchEmbedded = ETrue);

    /**
     * Creates message to be sent and then calls corresponding mtm to edit the message.
     * @param aMtmUid: uid of the mtm
     * @param aBodyText: pointer to body text to be added to message
     * @param aAttachments: pointer to attachment array which includes file paths of the attachments
     *    to be added to the message
     * @param aBioTypeUid: bio type uid
     * @param aRealAddresses: pointer to the array which includes real addresses (in email's case
     *    real email addresses for ex: "my.address@host.com"
     * @param aAliases: pointer to the array which includes alias names to be displayed in editor
     *    (in email's case for ex: "My name").
     * @param aLaunchEmbedded: ETrue if editor should be launched embedded. Otherwise editor is launched stand-alone.
     * @return none
     */
    IMPORT_C virtual void CreateAndSendMessageL(
        const TUid aMtmUid,
        const CRichText* aBodyText = NULL,
        MDesC16Array* aAttachments = NULL,
        const TUid aBioTypeUid = KNullUid,
        MDesC16Array* aRealAddresses = NULL,
        MDesC16Array* aAliases = NULL,
        TBool aLaunchEmbedded = ETrue);

    /**
     * Displayes first list query with available mtms and is one of message type selected
     * then calls CreateAndSendMessageL to create message
     * @param aTitleText: title of the list query
     * @param aRequiredCapabilities: like in DisplaySendMenuItemL
     * @param aBodyText: like in CreateAndSendMessageL
     * @param aAttachments: like in CreateAndSendMessageL
     * @param aBioTypeUid: like in CreateAndSendMessageL
     * @param aRealAddresses: like in CreateAndSendMessageL
     * @param aAliases: like in CreateAndSendMessageL
     * @param aLaunchEmbedded: like in CreateAndSendMessageL
     * @return none
     */
    IMPORT_C virtual void CreateAndSendMessagePopupQueryL(
        const TDesC& aTitleText,
        TSendingCapabilities aRequiredCapabilities,
        const CRichText* aBodyText = NULL,
        MDesC16Array* aAttachments = NULL,
        const TUid aBioTypeUid = KNullUid,
        MDesC16Array* aRealAddresses = NULL,
        MDesC16Array* aAliases = NULL,
        CArrayFix<TUid>* aMtmsToDim = NULL,
        TBool aLaunchEmbedded = ETrue);

    /**
     * Checks if mtm can be added e.g. to menu. This can be used if Send menu
     * is created without calling DisplaySendMenuItemL or DisplaySendCascadeMenuL.
     * @param aMtmUid: uid of the mtm
     * @param aRequiredCapabilities: like in DisplaySendMenuItemL
     * @return EFalse if mtm cannot be added (for example there is no mailbox created).
     */
    IMPORT_C virtual TBool CanAddMtmL(
        TUid                    aMtmUid,
        TSendingCapabilities    aRequiredCapabilities);

    /**
     * Sendui internal function
     * @return pointer to RLibrary
     */
    inline RLibrary* UiDll()
    {
        return iUiDll;
    };

    /**
     * Sendui internal function
     * Sets RLibrary
     * @param aLibrary: pointer to RLibrary
     * @return none
     */
    inline void SetUiDll(RLibrary* aLibrary)
    {
        iUiDll = aLibrary;
    };

    /**
     * Sendui internal function
     * @return pointer to CSendBaseUi
     */
    inline CSendBaseUi* SendUi()
    {
        return iSendUi;
    };

    /**
     * Sendui internal function
     * @param aSendUi: sets sendui object
     * @return none
     */
    inline void SetSendUi(CSendBaseUi* aSendUi)
    {
        iSendUi = aSendUi;
    };

private:  // data

    RLibrary*    iUiDll;
    CSendBaseUi* iSendUi;

};

#endif

// End of File
