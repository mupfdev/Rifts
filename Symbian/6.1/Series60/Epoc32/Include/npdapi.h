/*
* ==============================================================================
*  Name        : NpdApi.h
*  Part of     : Notepad / NpdLib.dll
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Declaration of Notepad Library APIs.
*  Version     : ?Version
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

#ifndef NPDAPI_H
#define NPDAPI_H

// INCLUDES
#include <e32base.h>
#include <charconv.h>
#include <ConeResLoader.h>

// CONSTANTS
const TInt KNotepadPseudoKeyIdForNewNote(-1);

// FORWARD DECLARATIONS
class CCoeEnv;
class CEikDialog;
class CNotepadModel;
class CNotepadTableModel;

// CLASS DECLARATION
/**
* APIs of Notepad library.
* CNotepadApi provides APIs for other modules.
*
* @lib NpdLib.lib
*/
class CNotepadApi : public CBase
    {
    public: // Constuctors and destructor

        /**
        * Constructor.
        * Add a resource file of NpdLib.
        *
        * @return constructed CNotepadApi object.
        */
        IMPORT_C static CNotepadApi* NewL();

        /**
        * Constructor, returned value is also kept on the CleanupStack.
        * Add a resource file of NpdLib.
        *
        * @return constructed CNotepadApi object.
        */
        IMPORT_C static CNotepadApi* NewLC();

        /**
        * Destructor.
        * Remove a resource file of NpdLib.
        */
        IMPORT_C virtual ~CNotepadApi();

    public: // API functions

        /**
        * Fetch a memo.
        *
        * No need for a pre-allocated buffer.
        * Return NULL if the popup list is canceled or there is no memo.
        * Caller owns the returned HBufC object.
        *
        * @param aTitle Optional title text.
        * @return fetched string, (NULL if canceled or no memo).
        */
        IMPORT_C static HBufC* FetchMemoL(
            const TDesC* aTitle = NULL);

        /**
        * Fetch a template.
        *
        * No need for a pre-allocated buffer.
        * Return NULL if the popup list is canceled or there is no template.
        * Caller owns the returned HBufC object.
        *
        * @param aTitle Optional title text.
        * @return fetched string, (NULL if canceled or no templates).
        */
        IMPORT_C static HBufC* FetchTemplateL(
            const TDesC* aTitle = NULL);

        /**
        * Execute MCE's "List of templates".
        *
        * @return CEikDialog's exit status.
        */
        IMPORT_C static TInt ExecTemplatesL();

        /**
        * Execute a file viewer dialog.
        *
        * @param aFileName text file to view.
        * @param aTitle  TitlePane string (if NULL, Title will be FileName).
        * @param aDoWait Use wait dialog if ETrue.
        * @param aGuessEncoding guess encoding if ETrue (ignore aEncoding).
        * @param aEncoding encoding of the File
        *   (default ISO-8859-1. This is ignored if aGuessEncoding is ETrue).
        * @return CEikDialog's exit status.
        */
        IMPORT_C static TInt ExecFileViewerL(
            const TDesC& aFileName, 
            const TDesC* aTitle = NULL,
            const TBool aDoWait = ETrue,
            TBool aGuessEncoding = EFalse,
            TUint aEncoding = KCharacterSetIdentifierIso88591);

        /**
        * Save text as a memo.
        *
        * @param aText    memo text to save.
        */
        IMPORT_C static void AddContentL(const TDesC& aText);

        /**
        * Probe a memo (API for Pinboard).
        *
        * @param aKey a serial number of memo.
        * @return ETrue if exists, EFalse otherwise.
        */
        IMPORT_C static TBool ExistsMemoL(const TInt aKey);

        /**
        * Get number of templates.
        *
        * Return an error code (less than zero) if any trouble.
        *
        * @return number of templates. returns error code (less than zero)
        *     if any trouble.
        */
        IMPORT_C static TInt NumberOfTemplates();

        /**
        * Save contents of a specified file as a memo.
        *
        * @param aFileName the name of a file to be saved.
        */
        IMPORT_C static void SaveFileAsMemoL(const TDesC& aFileName);

        /**
        * Return internal Dialog object. (Internal to NpdLib)
        *
        * @internal 
        */
        IMPORT_C CEikDialog* Dialog();

        /**
        * Return internal Model object. (Internal to NpdLib)
        *
        */
        IMPORT_C CNotepadModel* Model();

        /**
        * Create CNotepadListDialog.
        *
        * @param aResId resource id of type NOTEPAD_LIST_DIALOG.
        */
        IMPORT_C void CreateListDialogL(TInt aResId);

        /**
        * Create CNotepadViewerDialog.
        *
        * @param aFileName filename to view.
        * @param aTitle title pane (if NULL, filename is used).
        * @param aDoWait create waiting dialog if ETrue.
        * @param aGuessEncoding guess encoding if ETrue (ignore aEncoding).
        * @param aEncoding encoding of the File
        *     (default ISO-8859-1. This is ignored if aGuessEncoding is ETrue).
        */
        IMPORT_C void CreateViewerDialogL(
            const TDesC& aFileName, 
            const TDesC* aTitle,
            const TBool aDoWait,
            TBool aGuessEncoding = EFalse,
            TUint aEncoding = KCharacterSetIdentifierIso88591);

        /**
        * Create CNotepadViewerDialog.
        *
        * @param aDoWait create waiting dialog if ETrue.
        */
        IMPORT_C void CreateViewerDialogL(const TBool aDoWait);

        /**
        * Create CNotepadModel.
        *
        * @param aResId resource id of type NOTEPAD_MODEL.
        */
        IMPORT_C void CreateModelL(TInt aResId);

        /**
        * Probe a memo (API for Pinboard).
        * This method is more efficient than ExistsMemoL
        * when it is neccessary to probe many memos at a time.
        *
        * @param aKey a serial number of memo.
        * @return ETrue if exists, EFalse otherwise.
        */
        IMPORT_C TBool ProbeMemoL(const TInt aKey);

    private: // Constructor

        /**
        * private c++ constructor.
        */
        CNotepadApi();

    private: // New functions

        /**
        * Show PopupList.
        *
        * @param aTitle title of popup list.
        * @param aModelResId resource id of type NOTEPAD_MODEL.
        * @param aPromptResId resource id of prompt text, which is used when
        *    aTitle is NULL.
        * @param aEmptyTextResId resource id of empty text.
        * @return fetched content, NULL if canceled or no entry.
        */
        HBufC* DoPopupListL(
            const TDesC* aTitle, 
            TInt aModelResId,
            TInt aPromptResId, 
            TInt aEmptyTextResId = 0 );

    private: // Reserved

        /**
        * Reserved API entry.
        * @internal
        */
        IMPORT_C virtual void CNotepadApi_Reserved();

        /**
        * Reserved API entry.
        * @internal
        */
        IMPORT_C static void CNotepadApi_Reserved_Static();

    private: // Data

        CCoeEnv* iEnv; // not own
        CEikDialog* iDialog; // not own
        CNotepadModel* iModel; // own
        RConeResourceLoader iResourceLoader;

    };

#endif // NPDAPI_H

// End of File

