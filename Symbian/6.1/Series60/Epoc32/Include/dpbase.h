// 
// DPBase.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
// 

//
// Created at: 31-Dec-98 9:52:34 AM
// Comments: Defines the abstract base class for all WAP Data Providing plugin classes
// 


#if !defined(__DPBASE_H__)
#define __DPBASE_H__

#if !defined (__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined (__E32STD_H__)
#include <e32std.h>
#endif
#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined (__PI_H__)
#include "PI.h"			// The CPluginBase class definition
#endif
#if !defined (__MDPROVOB_H__)
#include "MDProvOb.h"	// The MDataProviderObserver mixin class definition
#endif
#if !defined (__MDPROV_H__)
#include "MDProv.h"		// The MDataProvider mixin class definition
#endif

// Provide a UID constant which identifies a CDataProvider plugin.
#if defined(_UNICODE)
const TUid KUidWAPDataProviderPlugin = {0x100041D7};
#else
const TUid KUidWAPDataProviderPlugin = {0x100041D6};
#endif

class CDataProvider : public CPluginActiveBase, public MDataProvider
// CDataProvider provides an abstract base class for all WAP Data Providing classes
// 
	{
// Methods
public:
	// Default d'tor
	IMPORT_C virtual ~CDataProvider();

	// MDataProvider derived methods
	// Set the observer for the data provider
	IMPORT_C virtual void SetDataProviderObserver(const MDataProviderObserver& aUrlObserver);
	// Provide access to the observer for this data provider instance
	IMPORT_C virtual MDataProviderObserver& DataProviderObserver();

	// Suspend all processing activity in this data provider
	IMPORT_C virtual void SuspendL();
	// Resume all suspended processing activity in this data provider
	IMPORT_C virtual void ResumeL();

protected:
	// Default c'tor
	IMPORT_C CDataProvider(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

private:
	// Reserved for future expansion
	IMPORT_C virtual void CDataProvider_Reserved1();
	IMPORT_C virtual void CDataProvider_Reserved1() const;

// Attributes / Properties
protected:
	// The observer of this instance of the data provider
	MDataProviderObserver* iDataProviderObserver;

#if defined _DEBUG
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
#endif
private:
	TAny* iCDataProvider_Reserved;								// Reserved for future expansion
	};  // CDataProvider

#endif    // __DPBASE_H__


