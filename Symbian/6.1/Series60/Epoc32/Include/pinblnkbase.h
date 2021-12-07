/*
* ============================================================================
*  Name        : PinbLnkBase.h
*  Part of     : PinbMdl / PinbMdl.dll
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Define CPinbLinkBase.
*                It is base class for each shortcut.
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
* ============================================================================
*/

#ifndef PINBLINKBASE_H
#define PINBLINKBASE_H

//  INCLUDES
#include <e32base.h>
#include <apgcli.h>     // for TLaunchType
#include <apacmdln.h>   // for CApaCommandLine
#include <barsread.h>   // for TResourceReader
#include <barsc.h>      // for RResourceFile
#include <BldVariant.hrh>

//  CONSTANTS

const TInt KLinkUidBaseValue           = 0;
const TInt KLinkUidApplicationValue    = 1;
const TInt KLinkUidDocumentValue       = 2;
const TInt KLinkUidFileManagerValue    = 3;
const TInt KLinkUidUrlValue            = 4;
const TInt KLinkUidWmlCardValue        = 5;
const TInt KLinkUidContactValue        = 6;
const TInt KLinkUidPhoneValue          = 7;
const TInt KLinkUidFolderValue         = 8;
const TInt KLinkUidMessageCentreValue  = 9;
const TInt KLinkUidNoteValue           = 10;

const TInt KLinkUidFirstFreeValue      = 50;

// define TUid of the link object type.
const TUid KLinkUidBase            = {KLinkUidBaseValue};          // not used.
const TUid KLinkUidApplication     = {KLinkUidApplicationValue};   // for Application shortcut
const TUid KLinkUidDocument        = {KLinkUidDocumentValue};      // for file base document shortcut
const TUid KLinkUidFileManager     = {KLinkUidFileManagerValue};   // not used.
const TUid KLinkUidUrl             = {KLinkUidUrlValue};           // for WAP bookmard shortcut
const TUid KLinkUidWmlCard         = {KLinkUidWmlCardValue};       // for WML card shortcut
const TUid KLinkUidContact         = {KLinkUidContactValue};       // not used.
const TUid KLinkUidPhone           = {KLinkUidPhoneValue};         // not used.
const TUid KLinkUidFolder          = {KLinkUidFolderValue};        // not used.
const TUid KLinkUidMessageCentre   = {KLinkUidMessageCentreValue}; // not used.
const TUid KLinkUidNote            = {KLinkUidNoteValue};          // for Notepad shortcut

// 
const TInt KUidApaMessagePinboardValue(0x1000590C);
const TUid KUidApaMessagePinboard       = {KUidApaMessagePinboardValue};
const TUid KUidGlobalDefaultDocumentDirectory = { 0x10005127 };
const TInt KMaxLabelNameLength(30);	// Maximum length of a label name.

//  FORWARD DECLARATIONS

class   CStreamDictionary;
class   CStreamStore;
class   CPinbModel;
class   CPinbLinkFile;
class   CCoeAppUi;
class   CEikonEnv;
class   CCoeEnv;
class   CPinbModel;
class   CEikonEnv;
class   CPinbHistory;
class   CPinbModelResource;

//
// Don't change following values.
// 
const TInt KPinbIdentifierIconBase(1000);
//
// It is necessary to match this value to the number of TPinbDocumentIconId.
// 
const TInt KPinbIdentifierDefineCount(9);
//
// Define Identifier Icon ID of the each Pinboard shortcuts.
// NOTE: If you will add some identifier icon IDs to TPinbDocumentIconId,
//       it is necessary to add it to an application which look up it.
//
enum TPinbDocumentIconId
    {
    // for "WAP bookmark" linked indication.
    EPinbBookMarkIcon   = KPinbIdentifierIconBase + 1,	
    // for "Picture in Photo Album" linked indication.
    EPinbImageIcon      = KPinbIdentifierIconBase + 2,  
    // for "Message inbox" linked indication. 	
    EPinbMessageIcon    = KPinbIdentifierIconBase + 3, 	
    // for "Notepad memo" linked indication.
    EPinbNoteIcon       = KPinbIdentifierIconBase + 4,    
    // for "Saved WML cards" liked indication.
    EPinbWmlBrowserIcon = KPinbIdentifierIconBase + 5,    
    // for "Tones" linked indication.
    EPinbToneIcon       = KPinbIdentifierIconBase + 6,    
    // for "Voice recorder file" linked indication.
    EPinbVoiceIcon      = KPinbIdentifierIconBase + 7,  
    // for "Video recorder file" linked indication. 	
	EPinbVideoIcon		= KPinbIdentifierIconBase + 8,	
    // for link source unknown indication.
    EPinbUnknown        = KPinbIdentifierIconBase + 9  	
    };

// MACRO
// Identifier icon store macro.
// If Identifier icon is stored directly, use this macro.
// e.g. 
// SetDocumentIdIconL(PINB_DIRECT_ICONID(EMbmPinbidentifierQgn_prop_pinb_xxxx_id))
//
#define PINB_DIRECT_ICONID(nn)	STATIC_CAST(TPinbDocumentIconId, nn>>1)

//
typedef CArrayPtrFlat<CPinbHistory> CPinbHistoryArray;

//  CLASS DEFINITIONS

/**
* CPinbLinkBase class.
* CPinbLinkBase is a base class which creates 
* application shortcut or document shortcut.
*/
class CPinbLinkBase :public CBase
    {
    public:  // Constructors and destructor

        /**
        * Two phased construtor.
        * @param aUid : UID of link type.
        */
        IMPORT_C static CPinbLinkBase* CPinbLinkBase::NewL(const TUid& aUid);

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CPinbLinkBase();

    public: // New functions
        /**
        * Starts the linked document with the default launch type.
        * @return Id of a thread started/switched to
        */
        IMPORT_C TThreadId  StartLinkL();

        /**
        * Returns the name of the link
        * @return Name of the link
        */
        IMPORT_C TPtrC Name() const;

        /**
        *
        * Sets the name of the link - this is the name of the item linked. 
        * It can be displayed in preference to the item name. 
        * @param aName The name of the link which does not include the folder name.
        */
        IMPORT_C void SetNameL(const TDesC& aName);

        /**
        * Returns the link file name.
        * @return TPtrC object pointing to the descriptor containing
        *         the name of the link file which does not include the folder name.
        */
        IMPORT_C TPtrC FileName() const;

        /**
        *
        * Sets the name of the link - this is the name of the link file.
        * This allows the link
        * to contain characters that are invalid in the filing system.
        * @param aName Reference to the descriptor containig the name of the link file.
        */
        IMPORT_C void SetFileNameL(const TDesC& aName);

        /**
        * Returns the link type UID
        * @return type of a link
        */
        IMPORT_C TUid Type() const;

        /**
        * Returns an icon bitmap for the link
        * @return Pointer to the CApaMaskedBitmap object which contains an
        *         application icon with a mask.
        */
        IMPORT_C CApaMaskedBitmap* Icon() const;
        
        /**
        * Returns a icon bitmap for the link by the size.
        * @param aSize : Size of an icon.
        * @return Pointer to an icon bitmap.
        */
        IMPORT_C CApaMaskedBitmap* Icon(TSize aSize) const;
        
        /**
        * Returns a icon for the link
        * @param aIndex : Index of the icon array.
        * @return Pointer to a bitmap object.
        */
        IMPORT_C CApaMaskedBitmap* Icon(TInt aIndex) const;
        
        /**
        * Sets a icon for the link, only used if a custom icon is required.
        * @param aMaskedBitmap pointer to the icon bitmap to be set
        */
        IMPORT_C void SetIconL(CApaMaskedBitmap* aMaskedBitmap);

        /**
        * Sets a icon for the link, only used if a custom icon is required.
        * @param aMaskedBitmap pointer to the icon bitmap to be set
        */
        IMPORT_C void AddIconL(CApaMaskedBitmap* aMaskedBitmap);

        /**
        * Updates link file in disk
        */
        IMPORT_C virtual void UpdateLinkInDiskL();

        /**
        * Update shortcut file.
        * If needs, rename shortcut file name.
        * @param aFileName : Changed file name.
        * @param aTimeStamp : The time when aFileName is updated.
        * @param aModelResource : Information of shortcut.
        */
        void UpdateLinkInDiskAndRenameL(const TDesC& aFileName, const TTime& aTimeStamp, 
                    const CPinbModelResource* aModelResource);

        /**
        * Returns the link file name
        * @return A descriptor containing the file name of the link
        */
        IMPORT_C virtual TDesC& LinkFileName() const;

        /**
        * Sets the link file name
        * @param aFileName the descriptor containing a file name
        */
        IMPORT_C void SetLinkFileNameL(const TFileName& aFileName);

        /**
        * Checks the availability of the linked volume
        * @return Return ETrue if volume is available
        */
        IMPORT_C TBool IsVolumeAvailable() const;

        /**
        * Sets the unique id of the volume, where the linked object is
        * stored. Volume id can be used for deciding if the link is available
        * in current volume of removable media.
        * @param aVolumeId const reference to the volume id
        */
        IMPORT_C void SetVolumeId(const TUint aVolumeId);

        /**
        * Gets the information about the linked volume
        * @return volume id
        */
        IMPORT_C TUint VolumeId() const;

        /**
        * Sets the tailend on the command line according to given parameters
        * used for launching the link.
        * @param aParameters the parameters for application
        */
        IMPORT_C void SetParametersL(const TDesC8 &aParameters);

        /**
        * Returns the link parameters.
        * @param aCommandLine reference to a descriptor to be containing 
        *                     command line parameters
        */
        IMPORT_C void GetParametersL(TDes8& aParameters) const;

        /**
        * Sets the unique of document icon-id, where the icon bitmap is stored.
        * @param aIconId the icon id of document.
        * 
        */
        IMPORT_C virtual void SetDocumentIdIconL(TPinbDocumentIconId aIconId);

        /**
        * Sets the linked application UID
        * @param aUid the application UID that is linked
        */
        IMPORT_C virtual void SetApplicationUidL(const TUid& aUid);

        /**
        * Gets the UID of the linked application
        * @return : UID of the linked application
        */
        IMPORT_C virtual TUid ApplicationUid() const;

        /**
        * Returns whether the link is invalid or not.
        * @return : ETrue if the shortcut is logically deleted.
        */
        IMPORT_C TBool LogicalDelete() const;

        /**
        * Reutrns whether exist identifier icon or not.
        * @return Returns ETrue if the shorcut has identifier icon.
        */
        IMPORT_C TBool ExistSubIcon() const;

        /**
        * Returns the identifier icon ID value.
        * @return identifier icon ID
        */
        IMPORT_C TInt IdentifierIconId() const;

        /**
        * Validates whether an attempt to start the link will succeed or fail.
        * @return a boolean value whether the link is valid or not
        */
        IMPORT_C virtual TBool ValidateLinkL();

        /**
        * Store the link onto a CStreamStore object.
        * This allows for complex storage of the object onto more than
        * one stream.
        * @param aRoot Stream dictionary for the link
        * @param aStore the stream store object containing link's streams
        */
        virtual void StoreL(CStreamDictionary& aRoot, CStreamStore& aStore) const;

        /**
        * Restore a link from a CStreamStore object.
        * @param aRoot Stream dictionary for the link
        * @param aStore the stream store object containing link's streams
        */
        virtual void RestoreL(CStreamDictionary& aRoot, CStreamStore& aStore);

        /**
        * Get store object size.
        * @return aSize Size of the stream object.
        */
        virtual void GetFileWriteSize(TInt& aSize) const;

        /**
        * Set Pointer to the CPinbModel object.
        * @param aModelControl : Pointer to the CPinbModel object
        */
        void SetModelControl(CPinbModel* aModelControl);

        /**
        * Set command link parameters to tail parameter.
        */
        virtual void SetTailParametersL();

        /**
        * Sets logical delete mark.
        */
        void SetLogicalDelete();

        /**
        * Remakes the shortcut file by using aFileName.
        * Nothing is carried out as default.
        * @param aFileName : File name to remake
        */
        virtual void RemakeFileNameL(const TDesC& aFileName);

        /**
        * Gets Pointer to the history array.
        * @return Return pointer to the history array.
        */
        IMPORT_C const CPinbHistoryArray* HistoryArray() const;

        /**
        * Reset and destroy the history array.
        */
        IMPORT_C void ResetAndDestroyHistoryArray();

		/**
		* Set drive unit of a shortcut file.
		* @param aDriveUnit A drive unit of a shortcut file.
		*/
        void SetDrive(TDriveUnit aDriveUnit);
	
		/**
		* Return drive unit of a shortcut file.
		* @return A drive unit of a shortcut file.
		*/
        const TDriveUnit Drive() const;

		/**
		* Set current drive unit and drive volume ID.
		*/
        void SaveCurrentDriveAndVolumeId();
 
		/**
		* Returns whether a shortcut file exist on MMC or not.
		* @return Return ETrue if a shortcut file exist on MMC, 
        *                otherwise return EFalse.
		*/
        IMPORT_C TBool IsMMCDrive() const;

		/**
		* Returns MMC volume ID.
		*/
        IMPORT_C TUint MMCVolumeId() const;


    protected:  // New function
        /**
        * Sets the command line to be used to launch the link
        * @param aCommandLine the commandline to be set
        */
        void SetCommandLineL(CApaCommandLine& aCommandLine);
 
        /**
        * Returns the command line to be used to launch the link
        * @param aCommandLine the commandline to be changed
        */
        void GetCommandLineL(CApaCommandLine& aCommandLine) const;

        /**
        * Starts the linked document, policy is:
        *  If the application is not running start the application with
        *  the TApaCommandLinike specified. Othewise, send the TApaTask::
        *  SendMessage() to the application.
        *
        * @param aType Type of launching a link
        * @return Id of a thread started/switched to
        */
        virtual TThreadId StartLinkL
            (RApaLsSession::TLaunchType aType);

    protected:  // Constructors and destructor
        /**
        * C++ default constructor.
        */
        CPinbLinkBase();
        /**
        * Second phase constructor
        */
        void ConstructL();
 
    protected:  // New functions
        /**
        * Sets the link type
        * @param aType the Uid of the link type
        */
        void SetType(const TUid& aType);

        /**
        * Sets the command line for launching the link
        */
        virtual void SetCommandLineFromAppUidL();

        /**
        * Sets tail end string. It adds, when the string is already set up.
        * @param Reference to the descriptor of the tail end string.
        */
        void SetTailEndL(const TPtrC8& aDataPtr);

        /**
        * Sets bitmap size of the application icon from resource.
        */
        void SetIconSizeL();

        /**
        * Sets an identifier icon ID.
        * @param aIconId : identifier icon ID 
        */
        void SetIdentifierIconId(TInt aIconId);

        /**
        * Return whether the icon ID or bitmaps is set or not.
        * @return If the icon is set return ETrue, othewize return EFalse.
        *
        */
        TBool IsValidateIconL() const;

    protected:  // Data
        RApaLsSession iAppArcSession;
        TRect iIconRect;
        CArrayPtr<CApaMaskedBitmap>* iIconArray; //own
        CApaCommandLine* iCommandLine; //own
        TApaAppInfo iAppInfo;   // AppInfo of the linked application
        CEikonEnv* iEnv;       // cache.
        CPinbModel* iModelControl; // no own
        HBufC8* iParameters; // own
        TInt iIdentifierIconId;
        TDriveUnit iDriveUnit;

        TDriveUnit iPrevDriveUnit;
        TUint iPrevVolumeId;
		TInt iVersion;

    private:    // Data

        enum TLinkStatus
            {
            ELogicalDelete  = 0x00000001
            };

        TInt iStatus;          // Status flags
        HBufC* iName;          // own
        TUid iType;            // link type
        HBufC* iLinkFileName;  // own
        TUint iVolumeId;
        CPinbLinkFile* iLinkFile; // own
        HBufC* iFileName; // own
        CPinbHistoryArray* iNameHistory; //own
    };

#endif      //  PINBLINKBASE_H

// End of File
