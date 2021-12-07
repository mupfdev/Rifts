/*
* ============================================================================
*  Name       : DocumentHandler.h
*  Part of    : CommonCUI
*  Description: Definition of CDocumentHandler class.
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
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

#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

//  INCLUDES
#include <e32base.h>
#ifdef __SERIES60_DRM
#include <bldvariant.hrh>
#endif

// CONSTANTS

// App UIDs for handlers. Handlers are identified by the handler application's
// UID. E.g. The handler for WMLC (binary format of Wireless Markup Language)
// is responsible for launching the WMLBrowser. The data type
// application/wap.vnd.wmlc is therefore mapped to the browser's UID,
// 0x10008D39.

const TInt KTextHandler         = 0x1000599d;   // Notepad viever
const TInt KWmlcHandler         = 0x10008D39;   // WML Browser
const TInt KJamHandler          = 0x100009C1;   // JAM
const TInt KAppInstHandler      = 0x10000419;   // AppInst
const TInt KBioViewerAppHandler = 0x0FC99F01;   // BVA
const TInt KImageViewerHandler  = 0x101F4CED;   // Image viever
const TInt KCertSaveAppHandler  = 0x100095D2;   // Cert response handler app
const TInt KCODHandler          = 0x10008d4a;   // COD handler
const TInt KDDhandler           = 0x10008d3f;   // DD Handler

// A global external mime type for all nokia games.
_LIT8( KGameMimeType, "application/x-NokiaGameData" );

#ifdef ENABLE_DRM
//_LIT8(KDataTypeODC,"application/vnd.oma.drm.content"); // 31
_LIT8(KDataTypeODM,"application/vnd.oma.drm.message"); // 31

#endif

                                                     
// Fail reasons
const TInt KBadMimeType         = -12002;        // Mime type conflict etc.
const TInt KMimeNotSupported    = -12003;        // No handler found
const TInt KNullContent         = -12005;        // Empty content
const TInt KDataDirNotFound     = -12006;        // No data dir found
const TInt KExecNotAllowed      = -12007;        // Executables not allowed
const TInt KNoHostProcess       = -12008;        // Embedding without host
const TInt KNotInitialized      = -12009;        // Not initialized
const TInt KUserCancel          = -12010;        // User cancelled operation

// MACROS
// DATA TYPES

// API operations to inform special handlers of the entry function.
enum TDocOperation
    {
    EDocCopy,               // CopyL( aFileNameOld, aNameNew, aDataType, aAttr)
    EDocSave,               // SaveL( aContent, aDataType, aAttr )
    EDocSaveAs,             // SaveL( aContent, aDataType,aFileName, aAttr )
    EDocOpenFile,           // OpenFileL( aFileName, aDataType )
    EDocOpenFileEmb,        // OpenFileEmbeddedL( aFileName, aDataType) 
    EDocOpenBuf,            // OpenBufferL( aContent, aDataType )
    EDocOpenBufAs,          // OpenBufferL( aContent, aDataType, aName, aAttr )
    EDocOpenBufEmb,         // OpenBufferEmbeddedL( aContent, aDataType )
    EDocOpenBufEmbAs        // OpenBufferEmbeddedL( aCont, aDataT, aName, attr)
    };

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
class CDocHandlerBase;                       // Base class for handlers
class CEikProcess;                           // The host process
class MApaEmbeddedDocObserver;               // Viewer app exit observer
class TDataType;                             // Mime type handling
class RApaLsSession;                         // App list server session

// CLASS DECLARATION

/**
* Utility class for opening and saving any supported content.
* This class declares an interface for the DocumentHandler, a
* common component in Series60.
*
* The CDocumentHandler class will not itself implement any content
* handling routines. It's responsible for finding out which application
* can handle given data type and constructing a correct handler implementation
* for that application. If the given data type is supported by the system
* but no specific handler is found, the CDocDefaltHandler is then constructed.
* The default handler is an implementation of the CDoCDocHandlerBase class with
* standard "Epoc-style" content handling.
*
*
* The handler application can be lauched standalone or embedded. The
* Embedded launching is preferred way in Series60.
* Standalone launching means that the application will run in
* it's own process. Embedded launching means that the UI of an
* application, which is responsible for handling given data type,
* is embedded into the parent application. There will be only
* parent applications icon shown in the fast swap window when an
* application is embedded.
*
* Link your application against CommonUI.lib.
*
* <b>An example:</b>
*<pre> 
* #include <DocumentHandler.h>
*
* <i>// Define DocHandler</i>
* CDocumentHandler* iDocHandler;
* 
* <i>// Construct DocHandler</i>
* void ConstructL()
*    {
*    iDocHandler = CDocumentHandler::NewL(
*                  (CEikProcess*)Application()->Process());
*
*    <i>// I want to be notified when exit happends. Because I
*    // pass "this" pointer, I have to derive from
*    // MApaEmbeddedDocObserver class.</i>
*    docHandler->SetExitObserver(this)     
*    }
*
* <i>// delete DocHandler</i>
* void ~Myapp()
*    {
*    delete docHandler;
*    }
*
*
* <i>// and use like this</i>
*
* void OpenAttachmentL( TDesC8& aContent,       <i>// A buffer</i>
*                       TDataType& aDataType )  <i>// DataType can be empty</i>
*   {
*   TInt error = KErrNone;
*   TFileName path;
*
*   <i>
*   // Leaves on system wide errors like disk full, out of memory etc.</i>
*   error = docHandler->OpenBufferEmbeddedL( aContent, aDataType );
*   // The status code can be either KErrNone or KUserCancel
*
*   // Check where the attachment was saved
*   docHandler->GetPath( path );
*   // Do something for the path
*
*    }
* </pre>
*
*/
class CDocumentHandler : public CBase
    {
    public:        // Constructors and destructor

        /**
        * Two-phased constructor. Leaves on failure.
        *
        * @param aProcess   The host process, which will be
        *                   used for embedded launching.
        *
        * @return           The constructed CDocumentHandler
        */
        IMPORT_C static CDocumentHandler* NewL( CEikProcess* aProcess );

        /**
        * Two-phased constructor. Leaves on failure.
        *
        * @param aProcess   The host process, which will be
        *                   used for embedded launching.
        *
        * @return           The constructed CDocumentHandler
        */
        IMPORT_C static CDocumentHandler* NewLC( CEikProcess* aProcess );

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CDocumentHandler();

    private:        // Constructors and destructor

        /**
        * C++ default constructor.
        * 
        * @param aProcess   The host process, which will be
        *                   used for embedded launching.
        */
        CDocumentHandler( CEikProcess* aProcess );

        /**
        * C++ copy constructor
        */
        CDocumentHandler( const CDocumentHandler& );

        /**
        * By default EPOC constructor is private.
        */
        void ConstructL();

    public:       // New functions

        /**
        * Launches an application standalone capable of handling
        * aContent of aDataType. By default the content is first saved
        * to a temporary directory with a generated name. But if the
        * handler application can open a buffer, the saving to a file
        * is not performed.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. These
        * errors are usually trapped by the application framework.
        *
        * @param aContent   A content data buffer. Narrow descriptor that
        *                   can contain any kind of data.
        * @param aDataType  A data type of the content. If the data type is
        *                   empty, the DocumentHandler tries to recognize it.
        *                   If the content is not recognized, the error code
        *                   is returned and the content should be discarded,
        *                   because there is nothing we can do with the content.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt OpenBufferL(
            const TDesC8& aContent,
            TDataType& aDataType );

        /**
        * Launches an application standalone capable of handling
        * aContent of aDataType. Saves the content to the correct
        * storage. The storage can be anything from filesystem to application
        * specific data structures or database.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. These
        * errors are usually trapped by the application framework.
        * 
        * @param aContent   A content data buffer. Narrow descriptor that
        *                   can contain any kind of data.
        * @param aDataType  A data type of the content. If the data type is
        *                   empty, the DocumentHandler tries to recognize it.
        *                   If the content is not recognized, the error code
        *                   is returned and the content should be discarded,
        * @param aName      Use this name for saving the content. The name 
        *                   would normally be a file name, but some 
        *                   applications have their own storage mechanism. 
        *                   The file name must not contain any directory 
        *                   information.
        * @param aAttr      Use these file attributes for saving. Your can 
        *                   find these attributes from 
        *                   \epoc32\include\f32file.h header file. If the 
        *                   storage is not a filesystem these 
        *                   attributes are ignored.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt OpenBufferL(
            const TDesC8& aContent,
            TDataType& aDataType,
            const TDesC& aName,
            const TUint aAttr );

        /**
        * Launches an application standalone capable of handling
        * data in aFilename, with aDataType. Doesn't copy data
        * from the file.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. These
        * errors are usually trapped by the application framework.
        *
        * @param aFileName  Name of the file. Directory path included.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt OpenFileL(
            const TDesC& aFileName,
            TDataType& aDataType );

        /**
        * Launches an application embedded capable of handling
        * aContent of aDataType. By default the content is first saved
        * to a temporary directory with a generated name. But if the
        * handler application can open a buffer, the saving to a file
        * is not performed.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. These
        * errors are usually trapped by the application framework.
        *
        * @param aContent   A content data buffer. Narrow descriptor that
        *                   can contain any kind of data.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt OpenBufferEmbeddedL(
            const TDesC8& aContent,
            TDataType& aDataType );

        /**
        * Launches an application capable of handling aContent of aDataType.
        * Saves the content to the correct storage. The storage can be
        * anything from filesystem to application specific data structures
        * or database.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. These
        * errors are usually trapped by the application framework.
        *
        * @param aContent   A content data buffer. Narrow descriptor that
        *                   can contain any kind of data.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @param aName      Use this name for saving the content. The name 
        *                   would normally be a file name, but some 
        *                   applications have their own storage mechanism. 
        *                   The file name must not contain any directory 
        *                   information.
        * @param aAttr      Use these file attributes for saving. Your can 
        *                   find these attributes from 
        *                   \epoc32\include\f32file.h header file. 
        *                   If the storage is not a filesystem these 
        *                   attributes are ignored. 
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt OpenBufferEmbeddedL(
            const TDesC8& aContent,
            TDataType& aDataType,
            const TDesC& aName,
            const TUint aAttr );

        /**
        * Launches an application embedded capable of handling data in
        * aFilename with aDataType. Doesn't copy data from the file.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. These
        * errors are usually trapped by the application framework.
        *
        * @param aFileName  Name of the file. Directory path included.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt OpenFileEmbeddedL(
            const TDesC& aFileName,
            TDataType& aDataType );

        /**
        * Save aContent with aDataType using aAttr to a correct directory.
        * Generates a new name for saving.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. These
        * errors are usually trapped by the application framework.
        *
        * @param aContent   A content data buffer. Narrow descriptor that
        *                   can contain any kind of data.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @param aAttr      Use these file attributes for saving. Your can 
        *                   find these attributes from 
        *                   \epoc32\include\f32file.h header file. 
        *                   If the storage is not a filesystem these 
        *                   attributes are ignored.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt SaveL(
            const TDesC8& aContent,
            TDataType& aDataType,
            const TUint aAttr );

        /**
        * Save aBuffer with aDataType using aAttr to a correct storage with a
        * supplied name. The storage is usually a filesystem, but can be 
        * anything from application spesific data structures to a database.
        *
        * This function can leave in some system wide error situation.
        * E.g. out of memory, not enough space in filesystem etc. These
        * errors are usually trapped by the application framework.
        *
        * @param aContent   A content data buffer. Narrow descriptor that
        *                   can contain any kind of data.
        * @param aDataType  A data type for the content of the file. If empty
        *                   the DocumentHandler tries to recognize the content.
        * @param aName      Use this name for saving. The name must not 
        *                   contain any directory information.
        * @param aAttr      Use these file attributes for saving. Your can 
        *                   find these attributes from 
        *                   \epoc32\include\f32file.h header file. 
        *                   If the storage is not a filesystem these 
        *                   attributes are ignored.
        * @return           KErrNone if success. KUserCancel if the user 
        *                   cancelled the operation.
        */
        IMPORT_C TInt SaveL(
            const TDesC8& aContent,
            TDataType& aDataType,
            const TDesC& aFileName,
            const TUint aAttr );

        /**
        * Copy a file named aFileNameOld to the correct storage using
        * name aNameNew and aFileAttr. If aNameNew is empty, use
        * the old name.
        *
        * @param aFileNameOld   Name of the file being copied.
        * @param aFileNameNew   Name of the new file. If null, use the 
        *                       old name.
        * @param aDataType      The content type of the file.
        * @param aAttr          Use these file attributes for saving. 
        *                       ReadOnly, ReadWrite.
        * @return               KErrNone if success. KUserCancel if the user 
        *                       cancelled the operation.
        */
        IMPORT_C TInt CopyL(
            const TDesC& aFileNameOld,
            const TDesC& aNameNew,
            TDataType& aDataType,
            const TUint aAttr );

        // QUERY FUNCTIONS

        /**
        * Is the aDataType supported by the system.
        *
        * @param    aDataType Data type for content.
        *
        * @return   True if there is an application capable of handling
        *           aDataType. False if no application can handle
        *           this mime type.
        */
        IMPORT_C TBool CanHandleL( const TDataType& aDataType );

        /**
        * Is opening of aDataType supported by the system.
        *
        * @param    aDataType Data type for content.
        *
        * @return   True if there is an application capable of handling
        *           aDataType. False if no application can handle
        *           this mime type.
        */
        IMPORT_C TBool CanOpenL( const TDataType& aDataType );

        /**
        * Is saving aDataType supported by the system.
        *
        * @param    aDataType Data type for content.
        *
        * @return   True if there is an application capable of handling
        *           aDataType. False if no application can handle
        *           this mime type.
        */
        IMPORT_C TBool CanSaveL( const TDataType& aDataType );

        /**
        * Get the whole path including filename where the content was saved.
        * If the content was not saved to a file, this function returns
        * a name that represents the saved object.  
        * 
        * It may not be possible to open the object with the returned 
        * value, if it's not a real file in the filesystem. This situation
        * may happen when e.g. the handler application stores it's contents in
        * some weird data structure.
        *
        * @param    aPath The path of the saved content.
        *
        * @return   KErrNone if the path was found. If the user cancelled the
        *           the operation KErrUserCance. 
        */
        IMPORT_C TInt GetPath( TDes& aPath );

        /**
        * Set an oberver for embedded application exit events. 
        * DocumentHandler's CDefaulHandler delegates events to
        * aObserver if it's not NULL:
        * 
        * @param    aObserver Exit observer
        */
        IMPORT_C void SetExitObserver( MApaEmbeddedDocObserver* aObserver );

        /**
        * Get the RApaLsSession.
        *
        * @return Pointer to RApaLsSession
        */
        inline RApaLsSession* ApaLs();

        /**
        * Get the exit observer.    
        *
        * @return Pointer to exit observer
        */
        inline MApaEmbeddedDocObserver* ExitObserver() const;

        /**
        * Get the operation code of the api entry function.
        */
        inline TDocOperation DocOperation() const;

    protected:      // New functions

    private:        // New functions

        /**
        * Construct a handler for a given data type. A previous handler will 
        * be destroyed and the new one is constructed.
        *
        * The desicion of which handler implementation to use is
        * based on Apparc's AppForDataType query. If the app uid is
        * found for aDataType and there is a hardcoded handler for it,
        * the right handler will be constucted. If the app uid is not found
        * try to match a data type for some handler. The default handler is
        * constructed if no handler entry is found.
        *
        * @param    aUid UID of the handler application.
        * @return   Error code
        */
        TInt FindHandlerL(
            const TDataType& aDataType,
            const TUid& aUid );

        /**
        * Try to find a handler for aUid. Constructs iHandler if found.
        *
        * @param aDataType A data type to pass to a handler
        * @param aUid An uid to search a handler for
        */
        void FindHandlerByUidL( const TUid& aUid, const TDataType& aDataType);

        /**
        * Try to find a handler for aDataType. Constructs iHandler if found.
        *
        * @param aUid      An Uid for handler application.
        * @param aDataType A data type to search a handler for.
        */
        void FindHandlerByMimeTypeL( const TUid& aUid, const TDataType& aDataType );

        /**
        * Makes all the nesessary security checks and maps aDataType to 
        * an UID of the handler application. If any of the following 
        * checks is failed the error code is returned.
        *   <ul>
        *     <li>The file must not be an executable.</li>
        *     <li>The system must be able to handle the content type.</li>
        *   </ul>
        *
        * @param aFileName  Filename
        * @param aDataType  Data type for the file
        * @param aUid       An application UID will be returned if a handler 
        *                   was found.
        * @return           KErrNone if success, error code if failure.
        */
        TInt RecognizeAndCheckFileL(
            const TDesC& aFileName,
            TDataType& aDataType,
            TUid& aUid );

        /**
        * Makes all the nesessary security checks and maps aDataType 
        * to an UID of the handler application. If any of the 
        * following checks is failed the error code
        * is returned.
        *   <ul>
        *     <li>The content must not be an executable.</li>
        *     <li>The system must be able to handle the content type.</li>
        *    </ul>
        *
        * @param aContent   A content buffer
        * @param aDataType  Data type for the buffer
        * @param aUid       An application UID will be returned if a handler was found.
        * @return           KErrNone if success, error code if failure.
        */
        TInt RecognizeAndCheckBuf(
            const TDesC8& aContent,
            const TFileName& aFileName,
            TDataType& aDataType,
            TUid& aUid );        

        /**
        * Prohibit the assignment operation
        */
        CDocumentHandler operator=( const CDocumentHandler& )  const;

    public:           // Data

    private:          // Data

        /**
        * The entry operation. Handlers can query about the entry function
        * when they need to implement some special behaviour.
        */
        TDocOperation iOperation;

        /**
        * A handler providing operations. 
        */
        CDocHandlerBase* iHandler;

        /**
        * A ApaLs session client.
        */
        RApaLsSession* iApaLs;

        /**
        * A Host process into which to embed a handler app's UI.
        */
        CEikProcess* iHostProcess;

        /**
        * Notify embedded app's exit event to this observer.
        */
        MApaEmbeddedDocObserver* iExitObserver;

    public:         // Friend classes

    protected:      // Friend classes

    private:        // Friend classes

    };

#endif              // DOCUMENTHANDLER_H

// End of File
