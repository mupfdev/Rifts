// 
// DHand.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
// 
// Revision 1.001 By: Brian Evans : brian-evans@symbian.com At 3:53:22 PM on 07-Sep-99

//
// Created at: 22-Dec-98 10:24:24 AM
// Comments: Defines the base class for all Data Handling plugins
// 


#if !defined(__DHAND_H__)
#define __DHAND_H__

#if !defined (__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined (__E32STD_H__)
#include <e32std.h>
#endif
#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined (__APMSTD_H__)
#include <ApmStd.h>
#endif
#if !defined (__LOGDEF_H__)
#include "LogDef.h"		// Logging macro definitions
#endif

#if !defined (__PI_H__)
#include "PI.h"			// The CPluginBase class definition
#endif
#if !defined (__MDPROVOB_H__)
#include "MDProvOb.h"	// The MDataProviderObserver mixin class definition
#endif
#if !defined (__DCOLLOB_H__)
#include "DCollOb.h"	// The MDataCollectorObserver class definition
#endif

// Forward declaration definitions here
class CNode;
class CDTD;
class CDataCollector;

// Define the UID for a Data Handling plugin which can be returned by a plugin manager
#if defined(_UNICODE)
const TUid KUidWAPDataHandlingPlugin = {0x100041e1};	// Unicode version
#else
const TUid KUidWAPDataHandlingPlugin = {0x100041e0};	// Non-unicode version
#endif

////////////////////////////////////////////////////////////////////////////////////////
// 
// CSubDoc maintains a pairing of CDataCollector objects
// with it's last known status report, for a CDataHandler derived object. 
// It is intended to be used by a data handler to provide consistent
// behavior when requiring the services of another data handler to
// deal with a sub-part of its data. (i.e. a sub-document).
// e.g. Image fetching, byte code translation, etc.
// Note : Where a data collector has been passed to the
// WapEngine in a FetchSubDocumentL() call, it is important
// that the SetFetchSubDocumentFlag() method is called.
//
class CSubDoc : public CBase
	{
// Methods
public:
	// Create an instance of a CSubDoc on the heap
	// Leaving if the instance cannot be fully initialised.
	// Take ownership of the Data collector.
	IMPORT_C static CSubDoc* NewL(CDataCollector* aDataCollector);
	// Default d'tor
	virtual ~CSubDoc();
	
	// Allow access to the status of the sub-document, and by implication
	// the current state of the CDataCollector.
	IMPORT_C const TInt Status() const;

	// Set the status of the SubDocument.
	// intended to be used by the base CDataHandler class only,
	// and so not exported.
	void SetStatus(TInt aStatus);

	// Return a reference to the contained data collector
	IMPORT_C CDataCollector& DataCollector() const;	

	// Check if this was used for a FetchSubDocumentL() call
	IMPORT_C TBool FetchSubDocFlag() const;

	// Set the FetchSubDocumentL() flag
	IMPORT_C void  SetFetchSubDocumentFlag();

private:
	// The default c'tor, made explicit to prevent unintended conversion
	// instantiation by the compiler
	explicit CSubDoc(CDataCollector* aDataCollector);

	// Copy constructor private to prevent unintended usage by the compiler
	explicit CSubDoc(CSubDoc& aSubDoc);

	// Completes the initialisation of the object instance
	// leaving if initialisation cannot be completed successfully.
	void ConstructL();
	
	// Assignment made private to prevent unintended usage by the compiler
	CSubDoc& operator = (CSubDoc& aSubDoc);

// Attributes / Properties
private:
	// The instance of CDataCollector which represents the sub-document
	CDataCollector* iDataCollector;				
	// The last known status of this sub-document
	TInt iSubDocStatus;

	// A flag indicating if this sub-document
	// was used as a WapEngine::FetchSubDocumentL() parameter.
	// This affects the status filtering behaviour of the data handler,
	// within its OnChildStatus() method.
	TBool iSubDocFetchItem;

#if defined _DEBUG
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
#endif

};  // CSubDoc


//////////////////////////////////////////////////////////////////////////////////////////////////
//
// CDataHandler forms an abstract base class for all the DataHandling plug-ins.
// some generic functionality is provided to enable the construction of derived classes to be
// simpler.
// 
class CDataHandler : public CPluginBase, public MDataProviderObserver, public MDataCollectorObserver
	{
	// Methods
public:
	// Default d'tor
	IMPORT_C virtual ~CDataHandler();

	// Instance variable access methods
	// Provide access to the data collector which owns this data handler
	IMPORT_C virtual const CDataCollector& DataCollector(void) const;
	// Set the owning instance of the data collector.
	// Input : a fully initialised instance of CDataCollector 
	// Post-Condition : iDataCollector is set as the pointer to aDataCollector.
	IMPORT_C virtual void SetDataCollector(const CDataCollector& aDataCollector);

	// Provide access to the tree node which this data handler considers as its root node.
	IMPORT_C virtual const CNode& Node(void) const;    
	// Set this data handlers root tree node
	// Input : a fully initialised instance of CNode.
	// Post-Condition : iTreeNode is set as the pointer to aNode.
	IMPORT_C virtual void SetNode(const CNode& aNode);

	// Provide access to the DTD instance that provides validation for this data handler
	IMPORT_C virtual const CDTD& Dtd(void) const;    
	// Set the DTD instance which will provide validation for this data handler
	// Input : a fully initialised instance of CDTD 
	// Post-Condition : iDtd is set as the pointer to aDtd.
	IMPORT_C virtual void SetDtd(const CDTD& aDtd);

	// Provide access to the descriptor for this data handlers content encoding
	IMPORT_C virtual const HBufC* ContentEncoding(void) const;
	// Set the descriptor for this data handlers content encoding
	// Input : a descriptor which contains the encoding type
	//			of the data to be processed by this data handler. 
	IMPORT_C virtual void SetContentEncodingL(TDesC& aEncoding);

	// Report the count of bytes already received from the data provider.
	IMPORT_C virtual TInt DataReceived() const;

	// Report the %age of data processing already completed.
	// Pre-Condition : SetDataExpected must have been provided
	//					with the number of bytes which the document
	//					will contain. Where the data expected is unknown
	//					this method will always return 0
	IMPORT_C virtual TInt PercentProcessed() const;

	// Suspend/Resume processing
	// Suspend this data collector and all its sub-documents
	IMPORT_C virtual TInt Suspend();
	// Resume this data handlers processing including sub-document processing
	IMPORT_C virtual TInt Resume();

	// Cancels the current data handling process, and cascades the cancel to its sub-documents
	// Input				: Nothing.
	// Return				: The status of the Cancel, -ve value for error, or KerrNone.
	// Post Conditions		: processing has been terminated, and cannot be restarted.
	// 
	IMPORT_C virtual void Cancel();

	// MDataCollectorObserver methods :
	// Method for sub-documents to report their status.
	// Note that the data handler is effectively acting as a Wap Engine proxy here.
	// Input : The data collector which is reporting the status, the tree node which
	//			is considered as the root for that data collector, and the status value,
	//			which is either a standard error condition, (i.e. < 0),
	//			a percentage complete value, ( 0 > aStatus < 100), OR
	//			a TPluginStatus value.
	// Post-Condition : iStatus is changed to incorporate the status report of the
	//					sub-document and this data handlers new status has been reported to
	//					this data handlers observer.
	// Note : The sub-document's status report will be passed directly on to this
	//			data handler's observer IF the CSubDoc::FetchSubDocFlag() method
	//			returns ETrue, before the updated status is reported.
	IMPORT_C virtual void OnChildStatus(const CDataCollector& aChild, CNode& aNode, TInt aStatus);

	// MDataProviderObserver methods :
	// Data recieving method, called by the data provider to request data processing.
	// Post-Condition : The buffer has been processed.
	// Input : An reference to a fully initialised buffer of binary data 
	//			of the correct type to process.
	// Note : The type of data expected was resolved during the creation of this data handler
	//			via the CreatePlugin methods.
	IMPORT_C virtual void ProcessDataL ( HBufC8& aBuffer ) = 0;

	// Status reciever method, called by the DataProvider to report its status.
	// Input : A status code which is either a standard error condition, (i.e. < 0),
	//			a percentage complete value, ( 0 > aStatus < 100), OR
	//			a TPluginStatus value 
	IMPORT_C virtual void SetStatus (TInt aStatusCode = KErrNone );

	// The request to construct a CDataHandler for aDataType
	// This request when recieved by the data handler is usually an error,
	// being intended for a CDataCollector to provoke the construction
	// of a data handler to process data of the type reported,
	// unless some special arrangements have been made.
	// Input : A descriptor containing a 'data string' to match against a plugins
	//			reported 'data string' via CPluginBase::Data(). 
	IMPORT_C virtual void SetDocumentTypeL (TDesC& aDataType);

	// The request to construct a CDataHandler for aDataType with non default document encoding
	// This request when recieved by the data handler is usually an error,
	// being intended for a CDataCollector to provoke the construction
	// of a data handler to process data of the type reported,
	// unless some special arrangements have been made.
	// Input : A descriptor containing a 'data string' to match against a plugins
	//			reported 'data string' via CPluginBase::Data(), together with a
	//			descriptor containing the expected encoding of the data to be processed. 
	IMPORT_C virtual void SetDocumentTypeL (TDesC& aDataType, TDesC& aContentType);

	// The report of how many bytes of data is expected to be passed to
	// ProcessDataL, enabling %age reporting capabilities.
	IMPORT_C virtual void SetDataExpected(TInt aAmountExpected);

	// Set the URL that the DataProvider considers the base URL for
	// the current data.
	IMPORT_C virtual void SetBaseUrlL(TDesC* aBaseUrl);

	// Uses the input dtd node to perform validation upon its completed document tree
	// Input				: The root node of the DTD tree to use for the validation process.
	// Return				: The final status of the Validation, -ve value for error, or KerrNone, to indicate a valid document tree.
	// Error Behaviour		: returns the error value.
	// Pre Condition		: The data handler has not completed all data processing, and a complete data tree is available.
	// Post Conditions		: The data handler has not changed state.
	// 
	IMPORT_C virtual TInt ValidateL(CNode& aDtdRootNode);
	
protected:
	// The default c'tor
	// Standard plugin constructor
	// Input				: initialised references to a file session, and library handle
	//						also CDataHandler's DLL plugin index number.
	// Return				: nothing
	// Error Behaviour		: none, cannot fail.
	// Post Conditions		: constructed class with partial initialisation.
	IMPORT_C CDataHandler(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Called by the data handler when the data provider reports its 
	// processing as complete, to tidy up, and complete all its processing.
	// Post-Condition : data processing is complete.
	IMPORT_C virtual void CommitL();

	// Creates a sub document for the data handler
	// Input				: Initialised pointer to a CDataCollector to use for the
	//						  sub-document, and a boolean indicating if this data handler has
	//						  been, or will be used for a sub-document fetch call to the wap engine.
	// Return				: 0 or +ve error for the index of the sub-document in the iSubDocuments array,
	//						  or a -ve value for error.
	// Error Behaviour		: returns the error value.
	// Post Conditions		: constructed CSubDoc class placed upon the iSubDocument array.
	// 
	IMPORT_C TInt CreateSubDocument(CDataCollector* aDataCollector, TBool aUsedForSubDocFetch = EFalse);


private:
	// Reserved for future expansion
	IMPORT_C virtual void CDataHandler_Reserved1();		
	IMPORT_C virtual void CDataHandler_Reserved1() const;		

#if defined _DEBUG
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
#endif

// Attributes / Properties
protected:
	CNode* iTreeNode;							// The root node for this data handler.
	CDTD* iDtd;									// The validation DTD for this data handler.
	CDataCollector* iDataCollector;				// The owning instance of CDataCollector
	TInt iAmountReceived;						// The number of bytes recieved from the Data Provider
	TInt iAmountExpected;						// The number of bytes expected from the Data Provider
	RPointerArray<CSubDoc> iSubDocuments;		// The contained sub-documents
	HBufC* iEncoding;							// The documents encoding : MAY BE NULL

	TAny*	iCDataHandler_Reserved;							// Reserved for future expansion

	};  // CDataHandler

#endif    // __DHAND_H__
