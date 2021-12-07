// E32ROM.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32ROM_H__
#define __E32ROM_H__
#include <e32std.h>
//
const TUint KRomHeaderSize=0x100;
//
typedef TUint32 TLinAddr;
//
class TRomHeader
	{
public:
	TUint8 iJump[128];
	TVersion iVersion;
	TInt64 iTime;
	TLinAddr iRomBase;
	TUint32 iRomSize;
	TLinAddr iRomRootDirectoryList;
	TLinAddr iKernDataAddress;
	TLinAddr iKernStackAddress;
	TLinAddr iPrimaryFile;
	TLinAddr iSecondaryFile;
	TUint iCheckSum;
	TInt64 iLanguage;
	TUint32 iHardware;
	TSize iScreenSize;
	TInt iScreenBitsPerPixel;
	TLinAddr iRomSectionHeader;
	TInt iTotalSvDataSize;
	TLinAddr iVariantFile;
	TLinAddr iExtensionFile;
	TLinAddr iRelocInfo;
	TUint32  iTraceMask;  // The kernel tracemask
	TLinAddr iUserDataAddress;	// non-MMU stuff
	TInt iTotalUserDataSize;	// non-MMU stuff
	TUint32 iPad[32-25]; // sizeof(TRomHeader)=256
	};

class TRootDirInfo
	{
public:
	TUint iHardwareVariant;
	TLinAddr iAddressLin;
	};

class TRomRootDirectoryList
	{
public:
	TInt iNumRootDirs;
	TRootDirInfo iRootDir[1];
	};

class TRomSectionHeader
	{
public:
	TVersion iVersion;
	TTime iTime;
	TInt64 iLanguage;
	TUint iCheckSum;
	};
//
class TRomEntry
	{
public:
	TInt iSize;
	TUint32 iAddressLin;
	TUint8 iAtt;
	TUint8 iNameLength;
	TUint8 iName[2];
	};
const TInt KRomEntrySize=(sizeof(TRomEntry)-2);
//
class TRomDir
	{
public:
	TInt iSize;
	TRomEntry iEntry;
	};
//
// Header of ROM image files under the new scheme. (dlls & exes)
//	
class TRomImageHeader
	{
public:
	TUint32	iUid1;
	TUint32	iUid2;
	TUint32	iUid3;
	TUint32	iCheck;
	TUint iEntryPoint;
	TUint iCodeAddress;
	TUint iDataAddress;
	TInt iCodeSize;
	TInt iTextSize;
	TInt iDataSize;
	TInt iBssSize;
	TInt iHeapSizeMin;
	TInt iHeapSizeMax;
	TInt iStackSize;
	TDllRefTable* iDllRefTable;
	TInt iExportDirCount;
	TUint iExportDir;
	TUint iCheckSumCode;
	TUint iCheckSumData;
	TVersion iVersion;
	TUint iFlags;
	TProcessPriority iPriority;
	TUint iDataBssLinearBase;
	TLinAddr iNextExtension;
	TUint iHardwareVariant;
	};	
//
// Header for extension ROMs
// Equivalent to TRomHeader
//
class TExtensionRomHeader
	{	
public:
	TVersion iVersion;
	TInt64 iTime;
	TLinAddr iRomBase;
	TUint32 iRomSize;
	TLinAddr iRomRootDirectoryList;
	TUint iCheckSum;
	//
	TVersion iKernelVersion;
	TInt64 iKernelTime;
	TUint iKernelCheckSum;
	TUint32 iPad[32-11]; // sizeof(TExtensionRomHeader)=128
	};
//
#endif

