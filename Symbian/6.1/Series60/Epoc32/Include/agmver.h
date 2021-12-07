// AGMVER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMVER_H__
#define __AGMVER_H__

#include <e32std.h>

class RReadStream;
class RWriteStream;

class TAgnVersion : public TVersion
	{
public:
	inline TAgnVersion(TVersion aVersion) : TVersion(aVersion) {};
	inline TAgnVersion() {};
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;	
	};

#endif