// 
// DProvS.h
// Copyright (C) 1997-1998 Symbian Ltd. All rights reserved.
// 

//
// Created at: 31-Dec-98 9:52:34 AM
// Comments: Defines all the Data Provider plugin classes contained
// within the DPROV plugin DLL
// 


#if !defined(__DPROVS_H__)
#define __DPROVS_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__PI_H__)
#include "Pi.h"				// CPluginBase classes
#endif
#if !defined(__MDPROV_H__)
#include "MDProv.h"
#endif
#if !defined(__DPBASE_H__)
#include "DPBase.h"
#endif

// define an enumeration for the index numbers of the plugins
// available within this DLL
enum DProvPluginIndex
	{
	EDataPipeIndex = KDefaultIndex,
	EDeferredCompletionIndex
	} ;

// The count of the number of plugins defined for this DLL
#define KDProvPluginCount	EDeferredCompletionIndex		// Two only in this DLL so far CDataPipe and CDeferredCompletion

// Literals defined for the plugin information
// Firstly the version number of the data pipe plugin
const TInt KDataPipeMajorVN=1;
const TInt KDataPipeMinorVN=0;
const TInt KDataPipeBuildVN=0;

// Define the data and name strings for the data pipe plugin
_LIT(KDataPipeName,"CDataPipe||Comment : CDataPipe plugin ||Author : B.D.Evans.||Copyright © 1997-99 Symbian Ltd. All rights reserved.");
_LIT(KDataPipeData,"*");

// The version number of the deferred completion plugin
const TInt KDeferredCompletionMajorVN=1;
const TInt KDeferredCompletionMinorVN=0;
const TInt KDeferredCompletionBuildVN=0;

// Define the data and name strings for the deferred completion plugin
_LIT(KDeferredCompletionName,"CDeferredCompletion||Comment : CDeferredCompletion plugin ||Author : B.D.Evans.||Copyright © 1997-99 Symbian Ltd. All rights reserved.");
_LIT(KDeferredCompletionData,"*");

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// CDataPipe implements an MDataProvider interface allowing
// its user to call an MDataProviderObserver interface directly:
// This allows the piping of data direct from a data handler
// to a sub-document of the data handler, without ownership problems.
// (E.g. For Multi-part mime, or for byte code conversion)
// 
class CDataPipe : public CDataProvider
	{
// Methods
public:
	// Create an instance of a CDataPipe on the heap
	// Leaving if the instance cannot be fully initialised.
	static CDataPipe* NewL(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	// Create an instance of a CDataPipe on the heap
	// Leaving if the instance cannot be fully initialised.
	// Post-Condition : The returned pointer remains upon the CleanupStack.
	static CDataPipe* NewLC(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Default d'tor
	~CDataPipe();

// Virtual methods defined in CPluginActiveBase (See Pi.h).
	// Return the version number of the plugin
	TVersion Version() const;

	// Return a descriptor containing the 'name string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'name string' fails.
	HBufC* NameL() const;

	// Return a descriptor containing the 'data string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'data string' fails.
	HBufC* DataL() const;

	// Intercept the base class activate method to
	// ensure that a class instance can NEVER be added
	// to the scheduler, and activated.
	void Activate();

// MDataProvider methods
	// Initiate processing within this data provider
	void BeginL();

// Methods to pipe the data direct to the MDataProviderObserver
	// The request to construct a CDataHandler to process data of aDataType,
	// where aDataType is a string to match against some plugins declared data
	// handling ability.
	IMPORT_C virtual void SetDocumentTypeL(TDesC& aDataType);

	// Called by the client to request processing of the data
	// within the buffer
	IMPORT_C virtual void PipeL(HBufC8& aBuffer);

	// Called by the client to report its status to its observer.
	// Status may be a standard error code or an enumeration value of TPluginStatus
	// type.
	IMPORT_C virtual void SetStatus (TInt aStatusCode = KErrNone);

protected:
	// Respond to the completion status
	// and execute this active objects task.
	// Should never be called.
	void RunL();

private:
	// Standard plugin constructor
	// Input				: initialised references to a file session, and library handle
	//						also CDataPipe's DLL plugin index number.
	// Return				: nothing
	// Error Behaviour		: none, cannot fail.
	// Post Conditions		: constructed class with partial initialisation.
	CDataPipe(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Complete the initialisation of the plugin
	// May leave if any part of initialisation fails
	// Post-Condition : Fully initialised class when successful.
	void ConstructL();

// Attributes / Properties
private:
#ifdef _DEBUG
	void WriteContentsIntoFileL();	// Test a possible crash when writing data to a file on startup
#endif
	
#if defined _DEBUG
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
#endif

};  // CDataPipe

class CDeferredCompletion : public CDataProvider
// CDeferredCompletion provides an MDataProvider interface which has a simple
// functionality.
// BeginL schedules a completion status message for its next action when
// its RunL executes.
// Should an error occur during processing before the BeginL call is due
// PropagateError may be called to cancel the object and call the 
// MDataProviderObserver interface SetStatus method
// 
	{
// Methods
public:
	// Create an instance of a CDataPipe on the heap
	// Leaving if the instance cannot be fully initialised.
	static CDeferredCompletion* NewL(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	static CDeferredCompletion* NewLC(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	~CDeferredCompletion();

// from CPluginActiveBase
	// Return the version number of the plugin
	TVersion Version() const;

	// Return a descriptor containing the 'name string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'name string' fails.
	HBufC* NameL() const;

	// Return a descriptor containing the 'data string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'data string' fails.
	HBufC* DataL() const;

// MDataProvider methods
	// Initiate processing within this data provider
	IMPORT_C void BeginL();

	// CDeferredCompletion's error propagation method
	// Called by the client to ensure safe propagation of the error
	// to this data provider's observer.
	IMPORT_C void PropagateError(TInt aStatusCode);

protected:
	// Respond to the completion status
	// and execute this active objects task.
	// which is to send its observer the EPluginComplete status
	// message.
	// Will leave if any error occurs.
	void RunL();

private:
	// Standard plugin constructor
	// Input				: initialised references to a file session, and library handle
	//						also CDeferredCompletion's DLL plugin index number.
	// Return				: nothing
	// Error Behaviour		: none, cannot fail.
	// Post Conditions		: constructed class with partial initialisation.
	CDeferredCompletion(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Complete the initialisation of the plugin
	// May leave if any part of initialisation fails
	// Post-Condition : Fully initialised class when successful.
	void ConstructL();

// Attributes / Properties
private:
#if defined _DEBUG
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
#endif

};  // CDeferredCompletion

#endif    // __DPROVS_H__


