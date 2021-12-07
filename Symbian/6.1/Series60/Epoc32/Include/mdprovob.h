// 
// MDProvOb.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
//

// 
// Created at: 22-Dec-98 10:54:39 AM
// Comments: Definition of the data provider observer abstract class
//			It is anticipated that this class will be used as a mixin for
//			those objects which wish to provide services for an MDataProvider
//			plugin.
// 


#if !defined(__MDPROVOB_H__)
#define __MDPROVOB_H__

#if !defined(__APMSTD_H__)
#include <ApmStd.h>
#endif

class MDataProviderObserver
// MDataProviderObserver provides a virtual interface for any class to observe
// any MDataProvider, and provide data receiving services. 
// 
	{
// Methods
public:
	// Called by the data provider to request processing of the data
	// within the buffer
	virtual void ProcessDataL ( HBufC8& aBuffer ) = 0;

	// Called by the data provider to report its status to its observer.
	// Status may be a standard error code or an enumeration value of TPluginStatus
	// type.
	virtual void SetStatus (TInt aStatusCode = KErrNone) = 0;

	// The request to construct a CDataHandler to process data of aDataType,
	// where aDataType is a string to match against some plugins declared data
	// handling ability.
	virtual void SetDocumentTypeL (TDesC& aDataType) = 0;

	// The request to construct a CDataHandler for aDataType with non default document encoding
	// where aDataType is a string to match against some plugins declared data
	// handling ability.
	virtual void SetDocumentTypeL (TDesC& aDataType, TDesC& aContentType) = 0;

	// The report of how many bytes of data is expected to be passed to
	// ProcessDataL, enabling %age reporting capabilities.
	virtual void SetDataExpected(TInt aAmountExpected) = 0;

	// Set the URL that the DataProvider considers the base URL for
	// the current data.
	virtual void SetBaseUrlL(TDesC* aBaseUrl) = 0;

private:
	// Reserved for future expansion
	IMPORT_C virtual void MDataProviderObserverReserved1();	
	IMPORT_C virtual void MDataProviderObserverReserved1() const;
	};  // MDataProviderObserver

#endif    // __MDPROVOB_H__
