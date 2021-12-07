// PLPSVRMSG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPSVRMSG_H__)
#define __PLPSVRMSG_H__

// #if !defined (__PLPSVR_H__)
// #include <plpsvr.h>
// #endif

/*
const TUint16 KRfOpen         =   0;
const TUint16 KRfClose        =   2;
const TUint16 KRfRead         =   4;
const TUint16 KRfDirRead      =   6;
const TUint16 KRfDeviceRead   =   8;
const TUint16 KRfWrite        =  10;
const TUint16 KRfSeek         =  12;
const TUint16 KRfFlush        =  14;
const TUint16 KRfSetEof       =  16;
const TUint16 KRfRename       =  18;
const TUint16 KRfDelete       =  20;
const TUint16 KRfInfo         =  22;
const TUint16 KRfStat         =  24;
const TUint16 KRfParse        =  26;
const TUint16 KRfMkDir        =  28;
const TUint16 KRfOpenUnique   =  30;
const TUint16 KRfStatusDevice =  32;
const TUint16 KRfPathTest	  =  34;
const TUint16 KRfStatusSystem =  36;
const TUint16 KRfChangeDir	  =  38;
const TUint16 KRfDate 	      =  40;
const TUint16 KRfResponse     =  42;
*/

enum TFileRequestType
    { 

	EReqPlpRfsQueryVersion = 0,
	EReqPlpRfsCloseServer = 0xff,

    EReqRfsrvOpen=EReqReserved, // 0x0f
	EReqOpenDir,                // 0x10
    EResponse,                  // 0x11
	EReqReadDir,                // 0x12
	EReqGetDriveList,           // 0x13
    EReqVolume,                 // 0x14
	EReqSetVolumeLabel,         // 0x15
	EReqOpenFile, 
	EReqTempFile, 
    EReqReadFile, 
	EReqWriteFile,              // 0x19
	EReqSeekFile,               // 0x1a
	EReqDelete, 
	EReqRemoteEntry,            // 0x1c
    EReqFlush, 
	EReqSetSize, 
	EReqRename,                 // 0x1f
	EReqMkDirAll,               // 0x20
	EReqRmDir, 
	EReqSetAtt,
    EReqAtt, 
	EReqSetModified,            // 0x24
	EReqModified, 
	EReqSetSessionPath, 
	EReqSessionPath, 
    EReqReadWriteFile, 
	EReqCreateFile,             // 0x29
	EReqReplaceFile,            // 0x2a
	EReqPathTest,
    EReqLock, 
	EReqUnLock, 
	EReqOpenDirUid,             // 46
	EReqDriveName, 
	EReqSetDriveName,
	EReqReplace, 
	EReqShortPath,              // 50
	EReqLongPath,               // 51
    };

// inline void SetStringZ(TPtrC8& aPtrC, const TText8* aString);

// #include <rf_base.inl>

#endif // __PLPSVRMSG_H__
