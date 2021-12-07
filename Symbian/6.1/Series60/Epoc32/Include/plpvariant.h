// PLPVARIANT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PLPVARIANT_H__
#define __PLPVARIANT_H__

#include <f32file.h>
#include <plpvar.h>

class PlpVariant
	{
public:
	IMPORT_C static void    Version(TVersion &aVersion);
	IMPORT_C static void	GetMachineIdL(TPlpVariantMachineId &aId);
	IMPORT_C static void	GetDriveIdL(TDriveNumber aDrive,TPlpVariantDriveId &aId);
	IMPORT_C static void	GetDriveAliasL(TDriveNumber aDrive,TPlpVariantDriveAlias &aAlias);
	IMPORT_C static TUint32 DriveStatusL(TDriveNumber aDrive);
	IMPORT_C static TBool   DriveLockedL(TDriveNumber aDrive);
	IMPORT_C static TBool   EnableLoadFromRam();
	IMPORT_C static HBufC*  GetPropertyLC(TUint32 Uid);
	IMPORT_C static void    SetPropertyL(TUint32 Uid,TDesC &des);
	IMPORT_C static TInt    MinimumDiskFreeThreshold();
	};

#endif __PLPVARIANT_H__
