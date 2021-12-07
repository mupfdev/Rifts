/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 19999
 *
 * Program          :   OLE2 Library
 *
 * Identification   :   Logical Classes as identified in [OLE2_SDS]
 *
 * SDS Ref          :   [OLE2_SDS]
 *
 * Filename         :   $Locker:  $, $Revision: 1.3 $
 *
 * Author           :   Chris Goldsmith
 *
 * History          :   
 *
 * $Log: ollomain.h,v $
 * Revision 1.3  2001/12/04 14:06:41  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.37  2000/01/17 17:30:18  stefania
 * OR 200, added Ole2File() method to stream package class.
 *
 * Revision 1.36  1999-12-13 12:18:52+00  chrisg
 * OR 301.121.141: Fixed Stream Concatenations
 * OR 301.121.140: Exported Copy Constructor for COle2StreamPackage
 *
 * Revision 1.35  1999-11-10 09:40:07+00  chrisg
 * OR 301.121.111: Updated to include a MoveL method for moving
 * data around within a BigBlock. Also added a copy constructor
 * for COle2StreamPackage.
 *
 * Revision 1.34  1999/10/25 13:24:09  chrisg
 * OR 301.121.071: Updated to make property sets work with Cacheing in teh Writers
 *
 * Revision 1.33  1999-10-15 09:42:26+01  chrisg
 * OR 301.121.051: Updated return type of WriteL and WriteOrderedL methods
 * to be void, thus simplifying a lot of the Excel Writer code
 *
 * Revision 1.32  1999-10-07 15:20:33+01  chrisg
 * OR 301.121.035 Removed uncalled functions COle2File::OpenStreamL(name,handle)
 * and COle2PropertySet::(startblock).
 *
 * Also removed __TEST_INVARIANT from inline functions
 *
 * Revision 1.31  1999-10-06 16:14:31+01  chrisg
 * Added the function COle2File::ConcatenateStreamsL()
 *
 * Revision 1.30  1999-09-30 14:32:41+01  chrisg
 * Updates to make build with the UNICODE TARGET compiler
 *
 * Revision 1.29  1999/09/21 08:24:45  stefania
 * Added const to COle2StreamPackage::Close( ) method and removed reference
 * from COle2File::CloseStream( )
 *
 * Revision 1.28  1999-09-17 09:46:51+01  chrisg
 * Changed Position() to return a TOle2FilePosition (cannot use a reference in these classes)
 * as the Stream may not exist at the COle2File Interface
 *
 * Revision 1.27  1999-09-16 18:06:10+01  chrisg
 * Updated to make it compile
 *
 * Revision 1.26  1999-09-16 17:39:46+01  chrisg
 * Updated algorithm for stepping through PS chain, and added relevant
 * trace points to code
 *
 * Revision 1.25  1999-09-15 16:16:32+01  chrisg
 * Changed as per Steffi's review
 *
 * Revision 1.25  1999-09-15 12:02:35+01  chrisg
 * Updated the Write methods to use TDesC8& instead of TDes8&
 *
 * Revision 1.24  1999/09/14 13:58:34  chrisg
 * Updated for second phase, including writers, and reading small blocks
 *
 * Revision 1.23  1999-09-07 10:53:11+01  chrisg
 * Made the Position Methods const.
 *
 * Revision 1.22  1999-09-07 10:45:00+01  chrisg
 * Added Position() method as per OR 301.121.006
 *
 * Revision 1.21  1999/09/07 09:10:24  chrisg
 * Updates as per OR 301.121.007 New OpenStreamL methods added to COle2File
 *
 * Revision 1.20  1999-09-06 16:21:05+01  eds
 * OR 005 - Added FindStreamL and OpenStreamLC(name) methods.
 *
 * Revision 1.19  1999-09-03 11:10:00+01  stefania
 * Added _readOrdered template method
 *
 * Revision 1.18  1999-09-03 10:23:48+01  stefania
 * Added _read( ) method to COle2File.
 *
 * Revision 1.17  1999-09-02 15:04:00+01  stefania
 * Chain of Read() and ReadOrdered() functions now simplified.
 *
 * Revision 1.15  1999/09/01 16:23:32  chrisg
 * Added const to all Read() methods of COle2StreamPackage
 *
 * Revision 1.14  1999-09-01 17:22:00+01  chrisg
 * Added const to all ReadOrdered() methods in COle2StreamPackage
 *
 * Revision 1.13  1999-09-01 16:31:34+01  chrisg
 * Added ReadOrdered() methods for eight bit integers
 *
 * Revision 1.12  1999-09-01 15:27:53+01  chrisg
 * Made OpenL() have a const for filename
 *
 * Revision 1.11  1999-09-01 14:44:29+01  eds
 * Included "f32file.h" so that this file is not a dependency for ollomain.
 *
 * Revision 1.10  1999-09-01 12:25:08+01  eds
 * Fixed build problems introduced whilst working on MARM build. Doh!
 *
 * Revision 1.9  1999/09/01 10:19:11  eds
 * Added appropriate IMPORT_C/EXPORT_C macros for DLL linkage.
 *
 * Revision 1.8  1999-08-27 15:22:07+01  eds
 * Completed Component Testing.
 *
 * Revision 1.7  1999-08-24 18:13:30+01  eds
 * Can now extract WordDocument stream from docFile.
 *
 * Revision 1.6  1999-08-20 17:34:27+01  eds
 * Code review comments and trace added.
 *
 * Revision 1.5  1999-08-18 14:27:17+01  eds
 * Fixing a few bugs, to make things work properly
 *
 * Revision 1.4  1999/08/17 14:13:06  chrisg
 * COle2StreamPackage class added to encapsulate a handle, and a Ole2File
 *
 * Revision 1.3  1999-08-17 12:01:45+01  chrisg
 * Updated for new partitioning of property set and root chain functionality
 *
 * Revision 1.2  1999-08-16 17:22:19+01  chrisg
 * Updated to make compile and Link
 *
 * Revision 1.1  1999-08-11 16:49:04+01  chrisg
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__OLLOMAIN_H__)
#define __OLLOMAIN_H__

#include <f32file.h>

#include "olphmain.h" // OLE2 Physical Classes

#define OLE2_MAX_OPEN_STREAMS    16  // i.e. 0..15
#define OLE2_MAX_STREAM_NAME   0x40  // Maximum length of a stream name

typedef TInt TOle2StreamHandle; // -1 is used for invalid stream handles
#define OLE2_INVALID_HANDLE     -1

class COle2FileCache;
class COle2StreamPackage;

//
// Heap allocated class to provide logical representation of Ole2 Streams
// This class is only ever used by COle2File, hence there are no IMPORT_C
// functions
//
class COle2Stream:public CBase
{
public:    // methods
    ~COle2Stream(); // destructor
    static COle2Stream* NewL(COle2RootChain       *aRootChain,
                             COle2BigBlockDepot   *aBigBlockDepot,
                             TOle2FilePosition     aFilePosition=0,
                             COle2SmallBlockDepot *aSmallBlockDepot=NULL,
                             COle2BigBlockChain   *aSmallBlocks=NULL);

    void OpenL(MOleFileMediator& aFile);
    void CreateL(      MOleFileMediator& aFile,
                       COle2RootChain   *aRootChain,
                 const TOle2StreamName& aStreamName,
                 const TInt32           aFilePosition,
                 const TOle2StreamType  aStreamType);
    TBool IsOpen();

    //
    // Read methods
    //
    TInt Read(      TDes8& aDes,
              const TOle2FilePosition   aLength);
    TInt Read(const TOle2FilePosition   aPos,
                    TDes8& aDes,
              const TOle2FilePosition   aLength);

    //
    // Write methods
    //
    void WriteL(const TDesC8&             aDes,
                const TOle2FilePosition   aLength);
    void WriteL(const TOle2FilePosition   aPos,
                const TDesC8&             aDes,
                const TOle2FilePosition   aLength);

    void ConcatenateL(const TOle2BlockNumber aStartOfNextChain);

    void MoveL(const TOle2FilePosition aDestPos,
               const TOle2FilePosition aSourcePos,
               const TOle2FilePosition aSize);
    //
    // Position method OR 301.121.006
    //
    TOle2FilePosition Position() const { return iChain->Position(); }

    COle2PropertySet* PropertySet() { return iPropertySet; }

    void Close();

private:   // methods
    // constructor
    COle2Stream(COle2BigBlockDepot   *aBigBlockDepot,
                COle2SmallBlockDepot *aSmallBlockDepot,
                COle2BigBlockChain   *aSmallBlocks);

    // copy constructor not implemented to prevent accidental use
    COle2Stream(const COle2Stream&);
    void ConstructL(COle2RootChain        *aRootChain,
                    TOle2FilePosition     aFilePosition);

private:   // types
    typedef enum { EOle2SmallStreamOpen,
                   EOle2BigStreamOpen,
                   EOle2StreamCreated,
                   EOle2StreamClosed } TOle2StreamState;
private:   // data
    COle2PropertySet     *iPropertySet; // Created at construction (if reading)
    MOle2Chain           *iChain;       // Created by OpenL, or CreateL
    COle2BigBlockDepot   *iBigBlockDepot;   // Used when creating or opening
    COle2SmallBlockDepot *iSmallBlockDepot; // Used when opening
    COle2BigBlockChain   *iSmallBlocks;     // Used when opening
    TOle2StreamState      iStreamState;

    __DECLARE_TEST;
};

//
// Heap allocated class to provide logical representation of Ole2 File
// This is the main interface to the rest of the converters, hence
// all of the public: functions are preceded by an IMPORT_C
//
class COle2File:public CBase
{
public:    // methods
    IMPORT_C ~COle2File(); // destructor
    IMPORT_C static COle2File* NewL(RFs& aFs);
    IMPORT_C static COle2File* NewLC(RFs& aFs);

    //
    // File methods
    //
    IMPORT_C void OpenL  (const TDesC& aFileName);
    IMPORT_C void CreateL(const TDesC& aFileName);
    IMPORT_C TInt CloseL  ();

    //
    // Stream Handling Methods
    //
    IMPORT_C void StreamNameL(TOle2StreamName &aStreamName);
    IMPORT_C TOle2StreamType StreamTypeL();
    IMPORT_C TInt32 StreamSizeL();

    IMPORT_C TInt NextStreamL();
    IMPORT_C TInt PreviousStreamL();

    IMPORT_C TInt FindStreamL(const TOle2StreamName &aStreamName);

    //
    // OpenStreamL() methods
    //
    IMPORT_C void                OpenStreamL(      TOle2StreamHandle& aHandle);
    IMPORT_C COle2StreamPackage *OpenStreamL();
    IMPORT_C COle2StreamPackage *OpenStreamL(const TOle2StreamName& aStreamName);

    //
    // CreateStreamL() methods
    //
    IMPORT_C void                CreateStreamL(const TOle2StreamName&   aStreamName,
                                               const TOle2StreamType    aStreamType,
                                                     TOle2StreamHandle& aHandle);
    IMPORT_C COle2StreamPackage *CreateStreamL(const TOle2StreamName&   aStreamName,
                                               const TOle2StreamType    aStreamType);

    //
    // ConcatenateStreamsL() method
    //
    IMPORT_C TInt ConcatenateStreamsL(const TOle2StreamName& aFirstStream,
                                      const TOle2StreamName& aSecondStream);

    IMPORT_C TInt CloseStream(const TOle2StreamHandle aStreamHandle);

    //
    // Position method OR 301.121.006
    //
    IMPORT_C TOle2FilePosition Position(TOle2StreamHandle aHandle) const;

private:
    //
    // Read method
    //
    TInt _read(const TOle2StreamHandle  aHandle,
               const TOle2FilePosition  aPos,
                     TDes8&             aDes,
               const TOle2FilePosition  aLength);
    //
    // Write method
    //
    void _writeL(const TOle2StreamHandle aHandle,
                 const TOle2FilePosition aPos,
                 const TDesC8&           aDes,
                 const TOle2FilePosition aLength);
    //
    // Method for ensuring big blocks are the correct size
    //
    void _forceBigBlockChainSizeL(const TInt ps);

public:
    IMPORT_C TInt Read(const TOle2StreamHandle  aHandle,
                             TDes8&             aDes);
    IMPORT_C TInt Read(const TOle2StreamHandle  aHandle,
                             TDes8&             aDes,
                       const TOle2FilePosition  aLength);
    IMPORT_C TInt Read(const TOle2StreamHandle  aHandle,
                       const TOle2FilePosition  aPos,
                             TDes8&             aDes);
    IMPORT_C TInt Read(const TOle2StreamHandle  aHandle,
                       const TOle2FilePosition  aPos,
                             TDes8&             aDes,
                       const TOle2FilePosition  aLength);

    IMPORT_C void WriteL(const TOle2StreamHandle aHandle,
                         const TDesC8&           aDes);
    IMPORT_C void WriteL(const TOle2StreamHandle aHandle, 
                         const TDesC8&           aDes,
                         const TOle2FilePosition aLength);
    IMPORT_C void WriteL(const TOle2StreamHandle aHandle, 
                         const TOle2FilePosition aPos,
                         const TDesC8&           aDes);
    IMPORT_C void WriteL(const TOle2StreamHandle aHandle, 
                         const TOle2FilePosition aPos,
                         const TDesC8&           aDes,
                         const TOle2FilePosition aLength);

public:
    IMPORT_C TInt ReadOrdered(const TOle2StreamHandle  aHandle, 
                                    TInt8&             aByte);
    IMPORT_C TInt ReadOrdered(const TOle2StreamHandle  aHandle, 
                              const TOle2FilePosition  aPos,
                                    TInt8&             aByte);
    IMPORT_C TInt ReadOrdered(const TOle2StreamHandle  aHandle,
                                    TInt16&            aWord);
    IMPORT_C TInt ReadOrdered(const TOle2StreamHandle  aHandle,
                              const TOle2FilePosition  aPos,
                                    TInt16&            aWord);
    IMPORT_C TInt ReadOrdered(const TOle2StreamHandle  aHandle,
                                    TInt32&            aLong);
    IMPORT_C TInt ReadOrdered(const TOle2StreamHandle  aHandle,
                              const TOle2FilePosition  aPos,
                                    TInt32&            aLong);
    
    IMPORT_C void WriteOrderedL(const TOle2StreamHandle aHandle,
                                const TInt8             aByte);
    IMPORT_C void WriteOrderedL(const TOle2StreamHandle aHandle,
                                const TOle2FilePosition aPos,
                                const TInt8             aByte);
    IMPORT_C void WriteOrderedL(const TOle2StreamHandle aHandle,
                                const TInt16            aWord);
    IMPORT_C void WriteOrderedL(const TOle2StreamHandle aHandle, 
                                const TOle2FilePosition aPos,
                                const TInt16            aWord);
    IMPORT_C void WriteOrderedL(const TOle2StreamHandle aHandle, 
                                const TInt32            aLong);
    IMPORT_C void WriteOrderedL(const TOle2StreamHandle aHandle, 
                                const TOle2FilePosition aPos,
                                const TInt32            aLong);

    IMPORT_C void MoveL(const TOle2StreamHandle aHandle,
                        const TOle2FilePosition aDestPos,
                        const TOle2FilePosition aSourcePos,
                        const TOle2FilePosition aSize);

private:   // methods
    // constructor
    COle2File(RFs& aFs);
    // copy constructor not implemented to prevent accidental use
    COle2File(const COle2File&);
    
    void ConstructL();
    TInt UpdateCurrentStreamL(); // updates iCurrentStream

    void Cleanup(); // Cleans the instance data (used by CloseL, and 
                    // the destructor)
private:   // types
    typedef enum { EOle2FileOpen,
                   EOle2FileCreated,
                   EOle2FileClosed } TOle2FileState;

private:   // data
    // data below here is constructed when a file is opened
    // and destroyed when a file is closed
    COle2Stream          *iOpenStreams[OLE2_MAX_OPEN_STREAMS];
                          // Nothing flash just an array
    COle2Stream          *iCurrentStream;
    COle2BigBlockDepot   *iBigBlockDepot;
    COle2SmallBlockDepot *iSmallBlockDepot;
    COle2BigBlockChain   *iSmallBlocks;     // From Root Entry
    COle2BigBlockChain   *iSmallBlockDepotChain;
    COle2RootChain       *iRootChain;

    // data below here is actually owned by this class
    TOle2FileState      iFileState; // Used for preventing illegal actions
    TOle2PsNumber       iStreamIndex;

     //RFile               iFile;
    RFs& iFs;
	COle2FileCache* iCachedFile;
   __DECLARE_TEST;
};

class COle2StreamPackage:public CBase
{
public:
    // Constructor
    COle2StreamPackage(TOle2StreamHandle aHandle,   COle2File *aOle2File):
      iOle2File(aOle2File),iHandle(aHandle) {}
    // Copy Constructor 
    IMPORT_C COle2StreamPackage(const COle2StreamPackage&);
     
    //
    // Read methods
    //
    inline TInt Read(TDes8& aDes) const { return iOle2File->Read(iHandle, aDes); }
    inline TInt Read(TDes8& aDes, const TOle2FilePosition aLength) const { return iOle2File->Read(iHandle, aDes, aLength); }
    inline TInt Read(const TOle2FilePosition aPos, TDes8& aDes) const { return iOle2File->Read(iHandle, aPos, aDes); }
    inline TInt Read(const TOle2FilePosition aPos, TDes8& aDes, const TOle2FilePosition aLength) const { return iOle2File->Read(iHandle, aPos, aDes, aLength); }

    //
    // Write methods
    //
    inline void WriteL(const TDesC8& aDes) const { iOle2File->WriteL(iHandle, aDes); }
    inline void WriteL(const TDesC8& aDes, const TOle2FilePosition aLength) const { iOle2File->WriteL(iHandle, aDes, aLength); }
    inline void WriteL(const TOle2FilePosition aPos, const TDesC8& aDes) const { iOle2File->WriteL(iHandle, aPos, aDes); }
    inline void WriteL(const TOle2FilePosition aPos, const TDesC8& aDes, const TOle2FilePosition aLength) const { iOle2File->WriteL(iHandle, aPos, aDes, aLength); }

    //
    // ReadOrdered methods
    //
    inline TInt ReadOrdered(TInt8& aByte) const { return iOle2File->ReadOrdered(iHandle, aByte); }
    inline TInt ReadOrdered(const TInt aPos, TInt8&  aByte) const { return iOle2File->ReadOrdered(iHandle, aPos, aByte); }
    inline TInt ReadOrdered(TInt16& aWord) const { return iOle2File->ReadOrdered(iHandle, aWord); }
    inline TInt ReadOrdered(const TInt aPos, TInt16& aWord) const { return iOle2File->ReadOrdered(iHandle, aPos, aWord); }
    inline TInt ReadOrdered(TInt32& aLong) const { return iOle2File->ReadOrdered(iHandle, aLong); }
    inline TInt ReadOrdered(const TInt aPos, TInt32& aLong) const { return iOle2File->ReadOrdered(iHandle, aPos, aLong); }

    //
    // WriteOrdered methods
    //
    inline void WriteOrderedL(const TInt8& aByte) const { iOle2File->WriteOrderedL(iHandle, aByte); }
    inline void WriteOrderedL(const TOle2FilePosition aPos, const TInt8& aByte) const { iOle2File->WriteOrderedL(iHandle, aPos, aByte); }
    inline void WriteOrderedL(const TInt16& aWord) const { iOle2File->WriteOrderedL(iHandle, aWord); }
    inline void WriteOrderedL(const TOle2FilePosition aPos, const TInt16& aWord) const { iOle2File->WriteOrderedL(iHandle, aPos, aWord); }
    inline void WriteOrderedL(const TInt32& aLong) const { iOle2File->WriteOrderedL(iHandle, aLong); }
    inline void WriteOrderedL(const TOle2FilePosition aPos, const TInt32& aLong) const { iOle2File->WriteOrderedL(iHandle, aPos, aLong); }

    //
    // MoveL method (added as a result of OR 301.121.111)
    //
    inline void MoveL(const TOle2FilePosition aDestPos, const TOle2FilePosition aSourcePos, const TOle2FilePosition aSize) { iOle2File->MoveL(iHandle, aDestPos, aSourcePos, aSize); }
    //
    // Position method OR 301.121.006
    //
    inline TOle2FilePosition Position() const { return iOle2File->Position(iHandle); }

    inline void Close() const { iOle2File->CloseStream( iHandle ); }

    //
    // OR 200 - Make Ole File visible
    //
    inline COle2File* const Ole2File( ) const { return iOle2File; }

private:
    COle2File         *iOle2File;
    TOle2StreamHandle  iHandle;

    __DECLARE_TEST;
};

#endif // !defined (__OLLOMAIN_H__)
