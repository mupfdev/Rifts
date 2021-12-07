// CDBOVER.INL
//
// CCommDbOverrideSettings inline functions
//
// Written by Ann, July 1998
// Copyright (C) Symbian Ltd 1998

#if !defined(__CDBOVER_INL__)
#define __CDBOVER_INL__

#include <cdbover.h>
#include <commdb.h>

inline CCommDbOverrideSettings::TParamList CCommDbOverrideSettings::PartialFull() const
	{
	return iPartialFull;
	}

inline TCommDbDatabaseType CCommDbOverrideSettings::DatabaseType() const
	{
	return iDb->Type();
	}

#endif

