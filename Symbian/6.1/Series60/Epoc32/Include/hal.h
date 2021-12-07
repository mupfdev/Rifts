// HAL.H
//
// Copyright (c) 1995-2000 Symbian Ltd.  All rights reserved.
//
#ifndef __HAL_H__
#define __HAL_H__

#include <e32def.h>
#include <hal_data.h>

/**
 * Get and set miscellaneous device-specific information and state
 *
 * @public
 * @lib hal
 * @since 6.0
 */
class HAL : public HALData
	{
public:
	enum TEntryProperty
		{
		EEntryValid=0x1,
		EEntryDynamic=0x2,
		};

	struct SEntry
		{
		TInt iProperties;
		TInt iValue;
		};
public:
	IMPORT_C static TInt Get(TAttribute anAttribute, TInt& aValue);
	IMPORT_C static TInt Set(TAttribute anAttribute, TInt aValue);
	IMPORT_C static TInt GetAll(TInt& aNumEntries, SEntry*& aData);
	};

#endif
