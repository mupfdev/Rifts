/*
* ============================================================================
*  Name     : CTextResolver from TextResolver.h
*  Part of  : CommonEngine.dll
*
*  Description:
*  - resolve an error code to display text
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
* ============================================================================
*/


#if !defined TEXT_RESOLVER_H
#define TEXT_RESOLVER_H

#include <coemain.h>    //  CCoeEnv
#include <TextResolver.hrh> // Resource flags 

// The size of text buffer used by the class.
const TInt KErrorResolverMaxTextLength( 256 );
const TInt KAppIdentifierMaxLength( 20 );

typedef CArrayFixFlat<TInt> CErrorResourceIdArray;
typedef CArrayFixFlat<TInt> CErrorResourceFlagArray;

/**
* This class offers methods to
*  - load common text resource in use
*  - resolve an error code to display text
*
*
* Usage (typically as instance variable)
*
*   CTextResolver* iTextResolver = CTextResolver::NewLC(*iCoeEnv); 
*   // or CTextResolver* iTextResolver = CTextResolver::NewL();
*   // if used only for error resolving, LoadCommonText requires CCoeEnv instance     
*
*   //... code producing an KErr*...
*
*   // Error Resolving, Simple:
*   TBuf<KErrorResolverMaxTextLength> buf;
*   if (err != KErrNone)
*        buf = iTextResolver->ResolveError(err); // Add Context to 2nd param if needed!
*
*   // Error Resolving, Advanced:
*   TInt textId;
*   TUint flags;
*   TBuf<KErrorResolverMaxTextLength> buf;
*   if (err != KErrNone)
*        buf = iTextResolver->ResolveError(err, textId, flags); // Add context to 4th param, if needed
*    
*   // Common Texts, iCoeEnv must be present !
*   iTextResolver->LoadCommonTextsL();
*   iCoeEnv.ReadResource(buf, myresourceId);
*   //..
*   CleanupStack::PopAndDestroy(); // iTextResolver, Free loaded resources 
*
*/

class CTextResolver : public CBase
    {

    public:

        // Optional error contexes for aiding the mapping of
        // error codes to texts in a unique way.
        // If no context is given the assumption is that error codes
        // are unique.
        enum TErrorContext
            {
            // Context defined automatically from error code value.
            // Here it is assumed that each error code is in unique and in
            // own range. This applies for Symbian OS, Etel, BIO errors
            ECtxAutomatic = 0,

            ECtxRBCore = 1, // Rainbow Status Codes
            
            ECtxBTErr = 2,   // Bluetooth Errors ( Symbian OS general errors with "Bluetooth: " prefix )

            ECtxNoCtx = 3, // No context in returned string, just ':' and newline
            
            ECtxRBHttp = 4, // Rainbow HTTP statuses

            ECtxBrowser = 5 // HTTP Browser errors

            // More contexes to be added, if needed !
            // caller error is not in unique among all the errors.
            // (for example -15 or -23 used as subsystem error and they mean totally else
            // for some else subsystem)
            // For those errors we need to add a context which must is set
            // by the caller
            };
    public:
        /**
         * Constructors.
         */
        IMPORT_C static CTextResolver* NewL(CCoeEnv& aEnv);
        IMPORT_C static CTextResolver* NewLC(CCoeEnv& aEnv);

        IMPORT_C static CTextResolver* NewL();
        IMPORT_C static CTextResolver* NewLC();

        
        /** Destructor */
        IMPORT_C ~CTextResolver();

        /**
         * DO NOT USE, WILL BE REMOVED !!!     
         */        
        IMPORT_C void LoadCommonTextsL();
        
        /**
         * This version is for advanced use:
         * Resolve given Symbian OS error (KErr*) and return the resolved text.
         * @param aError any error code, for example ETel error.
         * @param aTextId ID of the returned text.
         * @param aFlags Priority of the returned error.
         *        The priority is defined by the this module !
         * @param aContext Reserved for future use. 
         * @return Error text for the mapped error.
         *         For non-mapped errors returns "Unmapped error" with
         *         error code included.
         */
        IMPORT_C const TDesC& ResolveError(
             TInt aError,
             TInt& aTextId,
             TUint& aFlags,
             TErrorContext aContext = ECtxAutomatic);
        /**
         * For "Normal" Use:
         * This version is for advanced use:
         * Resolve given Symbian OS error (KErr*) and return the resolved text.
         * @param aError any error code, for example ETel error.
         * @param aContext Reserved for future use. 
         * @return Error text for the mapped error.
         *         For non-mapped errors returns "Unmapped error" with
         *         error code included.
         */
        IMPORT_C const TDesC& ResolveError(
             TInt aError,
             TErrorContext aContext = ECtxAutomatic);

    private:
        
        virtual TInt ResourceForError(TInt aError);
        virtual void LoadResourceFilesL();

        // Construction
        CTextResolver(CCoeEnv& aEnv);
        CTextResolver();
        void ConstructL();

        // Utility
        void FindFullPathOfResourceFileL(TFileName& aResFile) const;
        void ReadResourcesToArraysL(TInt& aError, TInt& aTextId);
        void Reset();
        void PrepareReaderLC(TResourceReader& reader);
        void ReadUnicodeString(
            TDes& aTextBuffer, 
            const TInt& aTextId);
        void AddContextAndSeparator(TBool aAddContext);

    private:
        
        CCoeEnv*                            iCoe;
        RResourceFile                       iRFile;
        TInt                                iRDSupport;
        TInt                                iBaseResourceFileOffset;
        CArrayFix<TInt>*                    iStartError;
        CArrayFix<TInt>*                    iAppTexts;
        CArrayPtr<CErrorResourceIdArray>*   iErrorTexts;
        CArrayPtr<CErrorResourceFlagArray>* iFlags;
        TBuf<KErrorResolverMaxTextLength>   iTextBuffer;
        TBuf<KAppIdentifierMaxLength>       iAppNameText;
        TBuf<2>                             iContextSeparator;
    };

#endif

// Enf of File
