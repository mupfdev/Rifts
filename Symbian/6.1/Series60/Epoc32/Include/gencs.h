// GENCS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


# if !defined(__GENCS_H__)
#define __GENCS_H__

const int KUidGenericCustomServerValue = 0x10001829;
const int KUidConnectivityGenericInterfaceValue = 0x1000182A;

enum TGenericServerCommand
	{
	EGcsCmdQueryVersion			= 0,
	EGcsCmdLoadInterface		= 1,
	EGcsCmdUnloadInterface		= 2,
	EGcsCmdCallService			= 3,
	EGcsCmdReset				= 4,
	EGcsCmdNone					= 254, // for internal use only
	EGcsCmdQuit					= 255
	};


const int KGenericServerMajVer	= 2;
const int KGenericServerMinVer	= 0;
const int KGenericServerBldVer	= 11; 
//const int KGenericServerBufferSize = 2048;
const int KGenericServerBufferSize = 20480;		// PETRAS 24.10.01

const int KEpocErrNone=0;
const int KEpocErrNotFound=(-1); 
const int KEpocErrGeneral=(-2);
const int KEpocErrCancel=(-3);
const int KEpocErrNoMemory=(-4);
const int KEpocErrNotSupported=(-5);
const int KEpocErrArgument=(-6);
const int KEpocErrTotalLossOfPrecision=(-7);
const int KEpocErrBadHandle=(-8);
const int KEpocErrOverflow=(-9);
const int KEpocErrUnderflow=(-10);
const int KEpocErrAlreadyExists=(-11);
const int KEpocErrPathNotFound=(-12);
const int KEpocErrDied=(-13);
const int KEpocErrInUse=(-14);
const int KEpocErrServerTerminated=(-15);
const int KEpocErrServerBusy=(-16);
const int KEpocErrCompletion=(-17);
const int KEpocErrNotReady=(-18);
const int KEpocErrUnknown=(-19);
const int KEpocErrCorrupt=(-20);
const int KEpocErrAccessDenied=(-21);
const int KEpocErrLocked=(-22);
const int KEpocErrWrite=(-23);
const int KEpocErrDisMounted=(-24);
const int KEpocErrEof=(-25);
const int KEpocErrDiskFull=(-26);
const int KEpocErrBadDriver=(-27);
const int KEpocErrBadName=(-28);
const int KEpocErrCommsLineFail=(-29);
const int KEpocErrCommsFrame=(-30);
const int KEpocErrCommsOverrun=(-31);
const int KEpocErrCommsParity=(-32);
const int KEpocErrTimedOut=(-33);
const int KEpocErrCouldNotConnect=(-34);
const int KEpocErrCouldNotDisconnect=(-35);
const int KEpocErrDisconnected=(-36);
const int KEpocErrBadLibraryEntryPoint=(-37);
const int KEpocErrBadDescriptor=(-38);
const int KEpocErrAbort=(-39);
const int KEpocErrTooBig=(-40);
const int KEpocErrDivideByZero=(-41);		
const int KEpocErrBadPower=(-42);
const int KEpocErrDirFull=(-43);

#endif
 