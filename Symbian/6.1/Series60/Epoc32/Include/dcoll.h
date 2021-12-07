// 
// DColl.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
// 
// Created at: 22-Dec-98 11:47:47 AM
// Comments: Defines the data collector class which acts as the binding
//			and controlling component for a data provider, data handler pair
// 


#if !defined(__DATACOLLECTOR_H__)
#define __DATACOLLECTOR_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__MDPROVOB_H__)
#include "MDProvOb.h"
#endif
#if !defined(__LOGDEF_H__)
#include "LogDef.h"
#endif

// Forward declaration definitions here
class MDataCollectorObserver;			// The observer interface for the CDataProvider
class CDataHandler;						// The base plugin data handler
class CDataProvider;					// The base plugin data provider
class CPluginOwner;						// The owning instance of a plugin
class CNode;							// The tree node

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// The CDataCollector acts as the glue connecting together CDataProvider 
// and CDataHandler plug-ins and providing a single point for their access
// to services from the WAP engine. 
// 
class CDataCollector : public CBase, public MDataProviderObserver
	{
// Methods
public:
	// Create a new CDataCollector on the heap, and
	// return a fully initialised class
	// Leaves on initialisation error
	// Requires a fully initialised CNode class reference
	// which it considers as the root of its data tree.
	IMPORT_C static CDataCollector* NewL(CNode& aTreeNode);

	// Create a new CDataCollector on the heap, and
	// return a fully initialised class
	// Leaves on initialisation error
	// Requires a fully initialised CNode class reference
	// The pointer returned remains on the CleanupStack
	IMPORT_C static CDataCollector* NewLC(CNode& aTreeNode);

	// Default d'tor
	IMPORT_C virtual ~CDataCollector();

	// Instance variable access methods
	// Return a reference to the root node for this data collector
	IMPORT_C virtual const CNode& Node(void) const;	

	// Cancel all data collection processing.
	// Return value is the status of the data collector, iDCStatus. (KErrCancel)
	// Note that the data collector is no longer guaranteed to be 
	// in a usable state after cancellation.
	IMPORT_C virtual TInt CancelCollection ();
	// Suspend all data collection processing
//#pragma message( __FILE__ "(75) : TODO : Fix the return codes here to be of type TPluginStatus")
	// Return value is the status of the data collector, iDCStatus. (EPluginSuspend)
	IMPORT_C virtual TInt SuspendCollection ();
	// Resume suspended data collection processing
	// Return value is the status of the data collector, iDCStatus. (EPluginProcessing)
	IMPORT_C virtual TInt ResumeCollection ();

	// Provide access to the current status of the data collection process. (iDCStatus).
	IMPORT_C virtual TInt CollectionStatus() const;

	// Provide access to the data provider owned by this data collector
	// Return a reference.
	IMPORT_C virtual CDataProvider& DataProvider(void) const;
	// Take ownership of the DataProvider plugin supplied as the parameter
	IMPORT_C virtual void SetDataProvider(CPluginOwner* aDataProvider);

	// Provide access to the data handler owned by this data collector
	// Return a reference.
	IMPORT_C virtual CDataHandler& DataHandler(void) const;
	// Take ownership of the data handler plugin supplied as the parameter
	IMPORT_C virtual void SetDataHandler(CPluginOwner* aDataHandler);

	// Provide access to the observer of this data collector
	// Return a reference.
	IMPORT_C virtual MDataCollectorObserver&  DataCollectorObserver () const;
	// Recieve a reference to the objct whic observes this data collector.
	IMPORT_C virtual void SetDataCollectorObserver (MDataCollectorObserver& aDataCollectorObserver);

	// Provide a status call for both the data provider, and the data handler, who
	// are children owned by this class.
	IMPORT_C virtual void OnChildStatus(CBase& aOriginator, CNode& aNode, TInt aStatus);

	// MDataProviderObserver methods
	// Recieve a reference to the data buffer which requires processing
	// For a data collector this donesn't really make much sense
	// unless special arrangements have been made.
	IMPORT_C virtual void ProcessDataL ( HBufC8& aBuffer );
	// Recieve a status message from the data provider through the observer
	// interface.
	IMPORT_C virtual void SetStatus (TInt aStatusCode = KErrNone);
	
	// The request to construct a CDataHandler to process data of aDataType
	// Once such a data handler is constructed this data collector will take
	// ownership of it, and transfer the data provider observer role to it also.
	IMPORT_C virtual void SetDocumentTypeL (TDesC& aDataType);

	// The request to construct a CDataHandler for aDataType with non default document encoding
	// Once such a data handler is constructed this data collector will take
	// ownership of it, and transfer the data provider observer role to it also.
	IMPORT_C virtual void SetDocumentTypeL (TDesC& aDataType, TDesC& aContentType);

	// The report of how many bytes of data is expected to be passed to
	// ProcessDataL, enabling %age reporting capabilities.
	IMPORT_C virtual void SetDataExpected(TInt aAmountExpected);

	// Set the URL that the DataProvider considers the base URL for
	// the current data.
	IMPORT_C virtual void SetBaseUrlL(TDesC* aBaseUrl);

private:
	// Default c'tor made explicit to avoid unintentional
	// conversion construction by the compiler
	explicit CDataCollector(CNode& aTreeNode);

	// Instance initialisation completion happens here
	// with a leave if initialisation cannot be completed
	// successfully.
	void ConstructL();

// Attributes / Properties
private:
	CPluginOwner* iDataProviderOwner;			// Required for plugin management
	CPluginOwner* iDataHandlerOwner;			// The plugin owners owns the child plugin instances
												// and this class owns the owners.
												// (See pi.h for the necessity of owner classes).

	MDataCollectorObserver* iObserver;			// The status message service provider of this instance
	CDataHandler* iDataHandler;					// The owned Data Handler. (obtained from iDataHandlerOwner)
	CDataProvider* iDataProvider;				// The owned Data Provider.(obtained from iDataProviderOwner)
	const CNode& iTreeNode;						// The root node for this data collector
	TInt iDCStatus;								// The overall status of this Data Collector
	TBool iCancelling;							// A re-entrancy protection flag

	__DECLARE_LOG;								// Declaration of the log server client

};  // CDataCollector

#endif    // __DATACOLLECTOR_H__
