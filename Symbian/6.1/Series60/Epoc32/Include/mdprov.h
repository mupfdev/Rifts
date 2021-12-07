// 
// MDProv.h
// Copyright (C) 1997-1999 Symbian Ltd. All rights reserved.
//

// 
// Created at: 08-Jun-99 10:54:39 AM
// Comments: The definition of the abstract mixin class that all data provider plugins 
//			classes derive from.
// 


#if !defined(__MDPROV_H__)
#define __MDPROV_H__

#if !defined(__MDPROVOB_H__)
#include "MDProvOb.h"				// Definition of the observer abstract class
#endif

class MDataProvider
//
// Interface base for all data providers
//
	{
public:
	// Set the observer for the data provider
	IMPORT_C virtual void SetDataProviderObserver(const MDataProviderObserver& aUrlObserver) = 0;
	// Provide access to the observer for this data provider instance
	IMPORT_C virtual MDataProviderObserver& DataProviderObserver() = 0;

	// Suspend all processing within this data provider
	IMPORT_C virtual void SuspendL()=0;
	// Resume all suspended processing within this data provider
	IMPORT_C virtual void ResumeL()=0;
	// Initiate processing within this data provider
	IMPORT_C virtual void BeginL()=0;

private:
	// Reserved for future expansion
	IMPORT_C virtual void MDataProviderReserved1();
	IMPORT_C virtual void MDataProviderReserved1() const;
	};

#endif
