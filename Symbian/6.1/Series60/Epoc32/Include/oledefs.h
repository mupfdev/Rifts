// OLEDEFS.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#ifndef __OLEDEFS_H__
#define __OLEDEFS_H__

// User includes
#include <e32std.h>

// Literal constants
_LIT8(KOleFileMagicMarker, "\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1");

// Typedefs
typedef TInt32 TOle2BlockNumber;
typedef TDes16 TOle2StreamName;
typedef TInt32 TOle2FilePosition;
typedef TInt32 TOle2PsNumber;

// Enumerations
enum TOle2StreamType
{ 
    EOle2InvalidStream   = -1,
    EOle2DirectoryStream = 0x01, 
    EOle2FileStream      = 0x02, 
    EOle2RootStream      = 0x05
};

// Definitions
#define OLE2_INVALID_PS_NUMBER      -1

#define OLE2_BIG_BLOCK_SIZE         0x200 // 512 bytes in every big block
#define OLE2_SMALL_BLOCK_SIZE       0x040 // 64 bytes in every big block
#define OLE2_BLOCK_NUMBER_SIZE      4     // Each big block number is 4 bytes
#define OLE2_BLOCKS_PER_DEPOT_BLOCK (OLE2_BIG_BLOCK_SIZE/OLE2_BLOCK_NUMBER_SIZE)

#define OLE2_INVALID_BLOCK          ((TOle2BlockNumber)0xffffffff)
#define OLE2_RESERVED_BLOCK         ((TOle2BlockNumber)0xffffffff)
#define OLE2_END_OF_CHAIN           ((TOle2BlockNumber)0xfffffffe)
#define OLE2_SPECIAL_BLOCK          ((TOle2BlockNumber)0xfffffffd)

#define OLE2_MAX_NUMBER_OF_PSES     0x20  // A suitably arbitrary number
#define OLE2_INVALID_PS             ((TOle2FilePosition)0xffffffff)
#define OLE2_INVALID_FILEPOS        -1

#define OLE2_NUM_BIG_BLOCK_DEPOT_BLOCKS_OFFSET 0x002C

#define OLE2_PS_NAME_DATA_SIZE          0x40
#define OLE2_STREAM_STORAGE_BLOCK_SIZE  0x80
#define OLE2_STREAM_NAME_LENGTH_OFFSET  0x40

#define OLE2_PS_TYPE_OFFSET             0x42
#define OLE2_PS_TYPE_SIZE               0x02
#define OLE2_PS_SIZE_OFFSET             0x78

#define OLE2_PS_NUMBER_SIZE             0x04

#define OLE2_PS_PREV_PS_OFFSET          0x44
#define OLE2_PS_NEXT_PS_OFFSET          0x48
#define OLE2_PS_DIR_PS_OFFSET           0x4C

#define OLE2_PS_START_BLOCK_OFFSET      0x74

#define OLE2_PS_SIZE_SIZE               0x04
#define OLE2_PS_START_BLOCK_SIZE        0x04

#define OLE2_ID_FPOS                         0x0000
#define OLE2_NUM_BIG_BLOCK_DEPOT_BLOCKS_FPOS 0x002C
#define OLE2_ROOT_BIG_BLOCK_INDEX_FPOS       0x0030
#define OLE2_SMALL_BLOCK_DEPOT_INDEX_FPOS    0x003C
#define OLE2_WRITE_BLOCK_SIZE                0x80
#define OLE2_MIN_BIG_BLOCK_SIZE              0x1000

//ENDIANESS CONVERSION FUNCTIONS
extern inline void EndianConv(TInt8& aByte, const TDesC8& aBuff)
{  aByte = aBuff[0]; }

extern inline void EndianConv(TInt16& aWord, const TDesC8& aBuff)
{  aWord = STATIC_CAST( TInt16, ((aBuff[1]<<8) | (aBuff[0])) ); }

extern inline void EndianConv(TInt32& aLong, const TDesC8& aBuff)
{  aLong = ((aBuff[3]<<24) | (aBuff[2]<<16) | (aBuff[1]<<8) | (aBuff[0])); }

extern inline void EndianConv(TOle2StreamType& aType, const TDesC8& aBuff)
{ TInt16 i; EndianConv(i,aBuff); aType = STATIC_CAST(TOle2StreamType, i); }

extern inline void SetEndianVal(TDes8& aBuff, const TInt32 aLong)
{
   aBuff.SetLength(4);
   aBuff[3] = STATIC_CAST(TUint8,((aLong>>24)&0x000000ff));
   aBuff[2] = STATIC_CAST(TUint8,((aLong>>16)&0x000000ff));
   aBuff[1] = STATIC_CAST(TUint8,((aLong>>8 )&0x000000ff));
   aBuff[0] = STATIC_CAST(TUint8,((aLong    )&0x000000ff));
}

extern inline void SetEndianVal(TDes8& aBuff, const TInt16 aWord)
{
   aBuff.SetLength(2);
   aBuff[1] = STATIC_CAST(TUint8,((aWord>>8 )&0x000000ff));
   aBuff[0] = STATIC_CAST(TUint8,((aWord    )&0x000000ff));
}

extern inline void SetEndianVal(TDes8& aBuff, const TInt8 aByte)
{
   aBuff.SetLength(1);
   aBuff[0] = STATIC_CAST(TUint8,((aByte    )&0x000000ff));
}

extern inline void SetEndianVal(TDes8& aBuff, TOle2StreamType aType)
{ TInt16 i=STATIC_CAST(TInt16,aType); SetEndianVal(aBuff, i); }

//invalid position for Ole streams 
//Anything less or equal to this is invalid
#define OLE2_INVALID_FILE_POSITION -1


// Convert PhysicalBlock to PhysicalPosition. NB: Blocks start at -1
#define OLE2_PHYS_BLOCK_TO_PHYS_POS(blk)  OLE2_BIG_BLOCK_SIZE*((blk)+1)
#define OLE2_SMALL_BLOCK_TO_PHYS_POS(blk) OLE2_SMALL_BLOCK_SIZE*((blk))

// BigBlockDirectoryBlock index in file
#define OLE2_BIG_BLOCK_DEPOT_BLOCKS(blk) 0x004C + ((blk)*OLE2_BLOCK_NUMBER_SIZE)

// Check for a valid property set number
#define OLE2_VALID_PS(ps)                ((ps) >= 0)

// Check for a valid block number
#define OLE2_VALID_BLOCK(blk)            ((blk) >= 0)

// Check for a valid File Position
#define OLE2_VALID_FILEPOS(fp)           ((fp) >= 0)


#endif