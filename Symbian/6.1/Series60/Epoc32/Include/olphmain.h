/* ===========================================================================
 * 
 * Copyright        :   Infomatrix Ltd, 19999
 *
 * Program          :   OLE2 Library
 *
 * Identification   :   Physical Classes as identified in [OLE2_SDS]
 *
 * SDS Ref          :   [OLE2_SDS]
 *
 * Filename         :   $Workfile$, $Revision: 1.3 $
 *
 * Author           :   Chris Goldsmith
 *
 * History          :   
 *
 * $Log: olphmain.h,v $
 * Revision 1.3  2001/12/04 14:06:41  BijalShah
 * Symbian_00108 changes included and tested at Intuwave Ltd.
 *
 * Revision 1.33  1999/12/13 12:18:54  chrisg
 * OR 301.121.141: Fixed Stream Concatenations
 * OR 301.121.140: Exported Copy Constructor for COle2StreamPackage
 *
 * Revision 1.32  1999-11-10 09:40:07+00  chrisg
 * OR 301.121.111: Updated to include a MoveL method for moving
 * data around within a BigBlock. Also added a copy constructor
 * for COle2StreamPackage.
 *
 * Revision 1.31  1999/10/25 14:59:24  chrisg
 * OR 301.121.072: Fixed a warning in compilation for gcc
 *
 * Revision 1.30  1999-10-25 14:24:08+01  chrisg
 * OR 301.121.071: Updated to make property sets work with Cacheing in teh Writers
 *
 * Revision 1.29  1999-10-22 17:45:02+01  chrisg
 * <>
 *
 * Revision 1.28  1999-10-22 17:19:20+01  chrisg
 * OR 301.121.070: Updated to provide cacheing for the writers
 *
 * Revision 1.27  1999-10-15 09:42:26+01  chrisg
 * OR 301.121.051: Updated return type of WriteL and WriteOrderedL methods
 * to be void, thus simplifying a lot of the Excel Writer code
 *
 * Revision 1.26  1999-10-07 15:20:33+01  chrisg
 * OR 301.121.035 Removed uncalled functions COle2File::OpenStreamL(name,handle)
 * and COle2PropertySet::(startblock).
 *
 * Also removed __TEST_INVARIANT from inline functions
 *
 * Revision 1.25  1999-09-30 14:32:41+01  chrisg
 * Updates to make build with the UNICODE TARGET compiler
 *
 * Revision 1.24  1999-09-27 13:32:41+01  chrisg
 * Removed TABS
 *
 * Revision 1.23  1999/09/24 14:37:45  chrisg
 * CHanged to enable Cacheing for the OLE2 Readers
 *
 * Revision 1.22  1999/09/21 17:06:41  chrisg
 * Updates for UNICODE
 *
 * Revision 1.21  1999-09-17 09:45:23+01  chrisg
 * Changed the position methods to return a reference
 *
 * Revision 1.20  1999-09-16 18:06:12+01  chrisg
 * Updated to make it compile
 *
 * Revision 1.19  1999-09-16 17:39:45+01  chrisg
 * Updated algorithm for stepping through PS chain, and added relevant
 * trace points to code
 *
 * Revision 1.18  1999-09-15 16:16:32+01  chrisg
 * Changed as per Steffi's review
 *
 * Revision 1.18  1999-09-15 12:02:43+01  chrisg
 * Updated the Write methods to use TDesC8& instead of TDes8&
 *
 * Revision 1.17  1999/09/14 13:58:34  chrisg
 * Updated for second phase, including writers, and reading small blocks
 *
 * Revision 1.16  1999-09-07 10:54:22+01  chrisg
 * Changed Position methods to be const
 *
 * Revision 1.15  1999-09-07 10:45:00+01  chrisg
 * Added Position() method as per OR 301.121.006
 *
 * Revision 1.14  1999/09/07 09:10:24  chrisg
 * Removed TABS
 *
 * Revision 1.13  1999-09-03 11:23:39+01  stefania
 * typo
 *
 * Revision 1.12  1999-09-03 11:15:42+01  stefania
 * typo
 *
 * Revision 1.11  1999/09/03 10:10:13  stefania
 * Removed ENDIAN_CONV macros
 *
 * Revision 1.10  1999-09-03 10:29:45+01  stefania
 * Added OLE2_INVALID_FILE_POSITION
 *
 * Revision 1.9  1999-09-03 09:45:25+01  stefania
 * Added ENDIAN_CONV inline functions.
 *
 * Revision 1.8  1999-09-02 15:04:08+01  stefania
 * Chain of Read() and ReadOrdered() functions now simplified.
 *
 * Revision 1.6  1999/09/01 15:31:21  chrisg
 * Added ReadOrdered() methods for eight bit integers
 *
 * Revision 1.5  1999-08-27 15:22:08+01  eds
 * Completed Component Testing.
 *
 * Revision 1.4  1999/08/23 15:38:52  eds
 * Reads names of all streams from docfile.
 *
 * Revision 1.3  1999-08-17 12:01:55+01  chrisg
 * Updated for new partitioning of property set and root chain functionality
 *
 * Revision 1.2  1999-08-16 17:22:30+01  chrisg
 * Updated to make compile and Link
 *
 * Revision 1.1  1999-08-11 16:48:42+01  chrisg
 * Initial revision
 *
 *
 * ---------------------------------------------------------------------------
 */
 
#if !defined (__OLPHMAIN_H__)
#define __OLPHMAIN_H__

// User includes
#include "cosyincs.h"
#include "oledefs.h"

// Classes referenced
class MOleFileMediator;

extern GLDEF_C void Panic(TInt);
//
// Mixin class for Ole2Chains, this allows us to reference
// Big and Small Block Chains transparently
//
class MOle2Chain
{
public:    // methods
    virtual ~MOle2Chain() {}

    //
    // Read methods
    //
    virtual TInt Read(      TDes8& aDes,
                      const TInt   aLength)=0;
    virtual TInt Read(const TInt   aPos,
                            TDes8& aDes,
                      const TInt   aLength)=0;
    //
    // Write methods
    //
    virtual void WriteL(const TDesC8& aDes,
                        const TInt    aLength)=0;
    virtual void WriteL(const TInt    aPos,
                        const TDesC8& aDes,
                        const TInt    aLength)=0;

    virtual void ConcatenateL(const TOle2BlockNumber aBlockNumber)=0;
    
    // OR 301.121.111
    virtual void MoveL(const TOle2FilePosition aDestPos,
                       const TOle2FilePosition aSourcePos,
                       const TOle2FilePosition aSize)=0;

    virtual TOle2FilePosition& Position() =0; // OR 301.121.006

    virtual TOle2FilePosition Size() const = 0;
};

class COle2BigBlockDepot;
//
// COle2BigBlockChain is a non-compound class, as it does not
// construct or destruct any of its own member data.
// iBigBlockDeopt is passed into the constructor and remains
// the proprerty of COle2File, which must perform the destruction
//
// Cacheing is enabled for BigBlockChains, this also assists Small
// Block Chains, as they use big block chains for their depots, and
// their base unit -- Good Eh?
//
class COle2BigBlockChain: public CBase, public MOle2Chain
{
public:    // methods
    // copy constructor, not implemented to prevent accidental use
    COle2BigBlockChain(COle2BigBlockChain&);
    // constructor
    COle2BigBlockChain(COle2BigBlockDepot *aBigBlockDepot,
                       MOleFileMediator& aFile,
                       TOle2BlockNumber    aStartOfChain,
                       TOle2FilePosition   aSizeOfStream = 0x7fffffff);
    ~COle2BigBlockChain();

    //
    // Read methods
    //
    TInt Read(      TDes8& aDes, 
              const TInt   aLength);
    TInt Read(const TInt   aPos,
                    TDes8& aDes,
              const TInt   aLength);
    //
    // Write methods
    //
    void WriteL(const TDesC8& aDes, 
                const TInt    aLength);
    void WriteL(const TInt    aPos,
                const TDesC8& aDes,
                const TInt    aLength);

    void   ConcatenateL(const TOle2BlockNumber aBlockNumber);
    
    // OR 301.121.111
    void MoveL(const TOle2FilePosition aDestPos,
               const TOle2FilePosition aSourcePos,
               const TOle2FilePosition aSize);

    TOle2FilePosition& Position()  { return iIndex; } // OR 301.121.006
    TOle2FilePosition  Size() const { return iSizeOfStream; }

protected: // methods
    TOle2FilePosition 
         CreateFilePositionL(const TOle2FilePosition aLogicalPos);
    TOle2FilePosition 
         GetFilePosition    (const TOle2FilePosition aLogicalPos);

protected: // data - This is normally bad, but in this instance justifyable
    MOleFileMediator& iFile;          // The file
    COle2BigBlockDepot  *iBigBlockDepot; // Big Block Depot

private:   // data
    TOle2BlockNumber       iStartOfChain;  // The First Physical Block in the chain
    TOle2BlockNumber       iCurrentBlock;  // The Current Logical Block in the chain
    TOle2BlockNumber       iPhysicalBlock; // The Current Physical Block in the chain
    TOle2FilePosition      iIndex;         // The logical read/write index
    TOle2FilePosition      iSizeOfStream;

    TBuf8<OLE2_BIG_BLOCK_SIZE> iCache;// Cacheing for blocks in chains

    TBool                      iCacheModified;
    __DECLARE_TEST;
};

class COle2SmallBlockDepot;
//
// COle2SamllBlockChain is a non-compound class, as it does not
// construct or destruct any of its own member data.
// iBigBlockDeopt is passed into the constructor and remains
// the proprerty of COle2File, which must perform the destruction
//
class COle2SmallBlockChain: public CBase, public MOle2Chain
{
public:  // methods
    // copy constructor, not implemented to prevent accidental use
    COle2SmallBlockChain(COle2SmallBlockChain&);
    // constructor
    COle2SmallBlockChain(COle2SmallBlockDepot *aSmallBlockDepot,
                         COle2BigBlockChain   *aSmallBlocks,
                         TOle2BlockNumber      aStartOfChain,
                         TOle2FilePosition     aSizeOfStream);

    //
    // Read methods
    //
    TInt Read(      TDes8& aDes, 
              const TInt   aLength);
    TInt Read(const TInt   aPos,
                    TDes8& aDes,
              const TInt   aLength);
    //
    // Write methods, these are only here because of the Mixin class
    // they are not implemented in this version
    //
    void WriteL(const TDesC8& /* aDes */, 
                const TInt    /* aLength */) 
        { Panic(KOle2ErrNotImplemented); }
    void WriteL(const TInt    /* aPos */,
                const TDesC8& /* aDes */,
                const TInt    /* aLength */)
        { Panic(KOle2ErrNotImplemented); }

    void   ConcatenateL(const TOle2BlockNumber /* aBlockNumber */)
        { Panic(KOle2ErrNotImplemented); }
    
    // OR 301.121.111
    void MoveL(const TOle2FilePosition /* aDestPos */,
               const TOle2FilePosition /* aSourcePos */,
               const TOle2FilePosition /* aSize */)
        { Panic(KOle2ErrNotImplemented); }

    TOle2FilePosition& Position() 
        { return iIndex; } // OR 301.121.006
    TOle2FilePosition  Size() const
        { return iSizeOfStream; }

private: // methods
    TOle2FilePosition GetFilePosition(const TOle2FilePosition aLogicalPos)const;

private: // data
    TOle2BlockNumber       iStartOfChain;    // The First Block in the chain
    TOle2FilePosition      iIndex;           // The logical read/write index
    COle2SmallBlockDepot  *iSmallBlockDepot; // Small Block Depot
    COle2BigBlockChain    *iSmallBlocks;     // The Chain
    TOle2FilePosition      iSizeOfStream;

    __DECLARE_TEST;
};

//
// Class for accessing information in the BigBlockDepot
// This class is non-compound, and so does not require
// 2 phase construction
//
class COle2BigBlockDepot: public CBase
{
public:  // methods
    // copy constructor, not implemented to prevent accidental use
    COle2BigBlockDepot(COle2BigBlockDepot&);
    // constructor
    COle2BigBlockDepot(MOleFileMediator& aFile, TOle2BlockNumber aNumBigBlockDepotBlocks);

    TOle2BlockNumber NextBlock(const TOle2BlockNumber aBlock);
    TOle2BlockNumber AddBlockL(const TOle2BlockNumber aBlock);
    void SetBlockNumberL(const TOle2BlockNumber aPhysicalBlockToSet,
                         const TOle2BlockNumber aNewValue);
    void CreateNewBlockL(TOle2BlockNumber aBlockNumber);

private: // methods
    TOle2BlockNumber GetBigBlockDepotBlock(TOle2BlockNumber aBlockNumber);
    void AddBigBlockDepotBlockL(TOle2BlockNumber aBlockNumber);

private: // data
    TOle2BlockNumber iNumBigBlockDepotBlocks;
    MOleFileMediator& iFile;

    __DECLARE_TEST;
};

//
// Class for accessing information in the SamllBlockDepot
// This class is non-compound, and so does not require
// 2 phase construction
//
class COle2SmallBlockDepot: public CBase
{
public:  // methods
    // copy constructor, not implemented to prevent accidental use
    COle2SmallBlockDepot(COle2SmallBlockDepot&);
    // constructor
    COle2SmallBlockDepot(COle2BigBlockChain *aDepotChain)
              :iDepotChain(aDepotChain) {}

    TOle2BlockNumber NextBlock(const TOle2BlockNumber aBlock);

private: // data
    COle2BigBlockChain *iDepotChain;

    __DECLARE_TEST;
};

class COle2PsMap; // A new class for handling the order of property sets
//
// Class for providing access to the root chain
// This class is compound, and so requires 2 phase construction.
//
// Also please note, that from version 1.19 of this file
// the PropertySet interface is a logical property set, which is
// mapped to a physical property set by COle2PsMap
//
class COle2RootChain: public COle2BigBlockChain
{
public: // methods
    static COle2RootChain *NewL(COle2BigBlockDepot *aBigBlockDepot,
                                MOleFileMediator& aFile,
                                TOle2BlockNumber    aStartOfChain);
    ~COle2RootChain();

    // Translates a property set index into a physical file position
    TOle2FilePosition GetPropertySet(const TOle2PsNumber aPropertySetIndex);
    TOle2FilePosition NewPropertySetL(void);
    TOle2PsNumber     NumberOfPses(void) const;
    void              RemovePs(const TOle2PsNumber aPropertySetIndex);
    TOle2PsNumber     GetPhysicalPs(const TOle2PsNumber aPropertySetIndex);

private: // methods
    // copy constructor, not implemented to prevent accidental use
    COle2RootChain(COle2RootChain&);
    // constructor
    COle2RootChain(COle2BigBlockDepot *aBigBlockDepot,
                   MOleFileMediator& aFile,
                   TOle2BlockNumber    aStartOfChain):
                   COle2BigBlockChain(aBigBlockDepot,
                                      aFile,
                                      aStartOfChain) {}
    void ConstructL();

private: //data
    COle2PsMap        *iPsMap;
};

//
// Class for providing access to a property set
// This class is non-compound, and so does not require
// 2 phase construction
//
class COle2PropertySet: public CBase
{
public: // methods
    static COle2PropertySet *NewL(      COle2RootChain    *aRootChain,
                                  const TOle2FilePosition aFilePosition);
    static COle2PropertySet *NewL(      COle2RootChain    *aRootChain,
                                  const TOle2FilePosition aFilePosition,
                                  const TOle2StreamName&  aStreamName,
                                  const TOle2StreamType   aStreamType
                                                          = EOle2FileStream);

    void              StreamNameL(TOle2StreamName& aStreamName);
    TOle2StreamType   StreamTypeL();
    TOle2FilePosition StreamSizeL();
    TOle2BlockNumber  StartBlockL();

    void SetStreamSizeL(TOle2FilePosition aStreamSize);

private: // methods
    // copy constructor, not implemented to prevent accidental use
    COle2PropertySet(const COle2PropertySet&); 
    // constructor
    COle2PropertySet(      COle2RootChain    *aRootChain,
                     const TOle2FilePosition aFilePosition):
                     iRootChain(aRootChain),iFilePosition(aFilePosition) {}
    void ConstructL(const TOle2StreamName&  aStreamName,
                    const TOle2StreamType   aStreamType);

    void SetStreamNameL(const TOle2StreamName& aStreamName);
    void SetStreamTypeL(      TOle2StreamType  aStreamType);

private: // data
    COle2RootChain     *iRootChain;
    TOle2FilePosition   iFilePosition;

    __DECLARE_TEST;
};

class COle2PsMap : public CBase
{
public:
    COle2PsMap();
    TInt AddPsToMap(const TOle2PsNumber aLogicalPs,
                    const TOle2PsNumber aPhysicalPs);

    TBool         PsInMap(const TOle2PsNumber aPhysicalPs) const;
    TOle2PsNumber GetPs(const TOle2PsNumber  aLogicalPs) const;
    TOle2PsNumber NumberOfPses() const
        { return iNumberOfPses; }
    void          RemovePs(const TOle2PsNumber aLogicalPs);
private:
    TOle2PsNumber     iPsMap[OLE2_MAX_NUMBER_OF_PSES];
    TOle2PsNumber     iNumberOfPses;

    __DECLARE_TEST;
};

#endif // !defined (__OLPHMAIN_H__)
