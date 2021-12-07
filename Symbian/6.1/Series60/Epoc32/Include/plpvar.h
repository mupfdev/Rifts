// PLPVAR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PLPVAR_H__
#define __PLPVAR_H__

#include <e32std.h>

const TInt KMaxPlpVariantMachineIdLength = 0x80;
const TInt KMaxPlpVariantDriveIdLength = 0x80;
const TInt KMaxPlpVariantDriveAliasLength = 0x80;
typedef TBuf<KMaxPlpVariantMachineIdLength> TPlpVariantMachineId;	
typedef TBuf<KMaxPlpVariantDriveIdLength> TPlpVariantDriveId;		
typedef TBuf<KMaxPlpVariantDriveAliasLength> TPlpVariantDriveAlias;	

#endif __PLPVAR_H__
