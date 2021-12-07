// E32WINS.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32WINS_H__
#define __E32WINS_H__

#include <E32STD.H>

enum TEmulatorFlip {EEmulatorFlipRestore,EEmulatorFlipInvert,EEmulatorFlipLeft,EEmulatorFlipRight};

// flip the emulator window
IMPORT_C TInt EmulatorFlip(TEmulatorFlip aEmulatorFlip);

const TUint KEmulGray2=		0x00000001;
const TUint KEmulGray4=		0x00000002;
const TUint KEmulGray16=	0x00000004;
const TUint KEmulGray256=	0x00000008;
const TUint KEmulColor16=	0x00000010;
const TUint KEmulColor256=	0x00000020;
const TUint KEmulColor4K=	0x00000040;
const TUint KEmulColor64K=	0x00000080;
const TUint KEmulColor16M=	0x00000100;

IMPORT_C void EmulatorColorDepth(TUint& aDepths);

// used by F32
IMPORT_C TPtrC EmulatorDataPath();
IMPORT_C TInt MapEmulatedFileName(TDes& aBuffer,const TDesC& aFileName);

// <SYMBIAN>
extern const TInt KMaxEnvLength;

IMPORT_C TInt SetEnvironment(const TDesC& aEnvVar, const TDesC& aEnvValue);
IMPORT_C TInt GetEnvironment(const TDesC& aEnvVar, TDes& aEnvValue);

IMPORT_C TChar MMCDriveLetter();
IMPORT_C TInt  MMCDriveNumber();
IMPORT_C TInt  MMCPassword   (TInt aNum, TMediaPassword& aPassword);
IMPORT_C TInt  SetMMCPassword(TInt aNum, const TMediaPassword& aPasswd);
// </SYMBIAN>



#endif

