// PLPVER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPVER_H__)
#define __PLPVER_H__

const TUint KPlpMajorVer = 1;
const TUint KPlpMinorVer = 0;

#ifndef __PLPVER__
const TUint KPlpBuildVer = 519;		// Explicit versioning.
#else
const TUint KPlpBuildVer = __PLPVER__;
#endif

const TUint8 KUnicodePlpVersion = 16;
/*
	RDG, changed unicode version from 8 to 16 so that old
	unicode machines running at version 8 won't connect to
	new builds of unicode PLP.

	Narrow machines won't connect to PLP above version 9 unless
	both ends are built as narrow.
*/
const TUint8 KEraPlpVersion = 6;
const TUint8 KMaxPlpVersion = 31;
const TUint8 KPrc16PlpVersion = 2;
const TUint8 KSiboPlpVersion = 3;

#endif



