//  BIOUUIDS.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
//  Contains the TUid defines for the Bio Messaging 

#if !defined(__BIOUTILS_H__)
#define __BIOUTILS_H__

// forward declarations
class TUid;

const TUid KUidSmartMessageParserDll    = { 0x10001251};

const TInt KBIOMessageBaseError				= -10000;
const TInt KBIOMessageNotFound				= KBIOMessageBaseError;
const TInt KBIOMessageSvrMtmNotInactive		= KBIOMessageBaseError-1;
const TInt KBIOMessageNoParserCreated		= KBIOMessageBaseError-2;   
const TInt KBIOMessageParserDllStillInUse	= KBIOMessageBaseError-3;      

const TUid KUidMsvNbsEditor={0x10001264};

//  New BIO Messaging TUids

const TUid KUidMsvBIODataStream			= {0x10005268}; // stream used for storing parsed data

//  BIO Mtm components
const TUid KUidBIOMessageTypeMtm		= {0x10001262};
const TUid KUidBIOMessageClientMtmDll	= {0x1000125A}; //previously NBSC, now BIOC
const TUid KUidBIOMessageServerMtmDll	= {0x1000125C}; //previously NBSS, now BIOS
const TUid KUidBIOMessageUiLayerMtmDll	= {0x10001265}; //previously NBUM, now BIUM

const TUid KUidBIOMessageViewerApp		= {0x10001264}; //previously NBED,now BIED

#endif //__BIOUTILS_H__
