// CDBSTORE.INL
//
// CStoreableOverrideSettings class inline functions
//
// Written by Ann, August 1998
// Copyright (C) Symbian Ltd

#ifndef __CDBSTORE_INL__
#define __CDBSTORE_INL__

#include <cdbstore.h>

inline CBufStore* CStoreableOverrideSettings::GetStore() const
	{
	return iStore;
	}

#endif

