// protom.h
//
// Copyright (c) 1998/1999 Symbian Ltd.  All rights reserved. 
//

// Purpose:		Definition of abstract class CProtocolManager
//
// Comments:	This is the interface class for scheme managers. Used by the Url manager to create 
//				active plug-ins to deal with a given scheme and method.

#if !defined(__PROTOM_H__)
#define __PROTOM_H__

// System includes
//
#include <e32base.h>
#include <pi.h>

// Forward class definitions
//
class CUrl;
class MDataProviderTransmissionData;

class CProtocolManager : public CPluginBase
	{
public:	// Methods

	// Creates the url handler plugin to deal with a given scheme and method. Specifically this interface deals with 
	// POST methods, requiring a object from which to collect the data to be posted. Returns the handler via the 
	// plug-in owner class.
	//
	// In:
	// aUrl				- url to instansiate the url handler with
	// aMethod			- method for the handler's transaction
	// aTd				- object that the url handler will use collect the data for transmission.
	// aWmlFetchFlags	- flag for fetch information; eg reload.
	//
	// Rtn: Pointer to plug-in owner class, encapsulating the url handler. Ownership is tranfered to caller.
	//
	virtual CPluginOwner* CreateUrlHandlerL(const CUrl& aUrl, const TDesC& aMethod, 
											MDataProviderTransmissionData& aTd, TInt aWmlFetchFlags)=0;

	// Creates the url handler plugin to deal with a given scheme and method. Specifically this interface deals with 
	// GET methods. Returns the handler via the plug-in owner class.
	//
	// In:
	// aUrl				- url to instansiate the url handler with
	// aMethod			- method for the handler's transaction
	// aWmlFetchFlags	- flag for fetch information; eg reload.
	//
	// Rtn: Pointer to plug-in owner class, encapsulating the url handler. Ownership is tranfered to caller.
	//
	virtual CPluginOwner* CreateUrlHandlerL(const CUrl& aUrl, const TDesC& aMethod, TInt aWmlFetchFlags)=0;
	
	// Disconnects the file server session.  Specific protocols may be able to accept
	// the 'aForciblyDisconnect' flag if there is an underlying network service that has
	// to be terminated.
	//
	virtual void Disconnect(TBool aForciblyDisconnect = EFalse)=0;

	// Cancels the connection startup
	virtual void CancelConnect()=0;

protected:	// Methods

	// Default c'tor - does non-allocating construction of class.
	//
	// In:
	// aFs		- file system handle. Note - not guaranteed to be connected
	// aLibrary	- handle to DLL in which this plug-in was made
	// aIndex	- index for this plug-in in this DLL.
	//
	IMPORT_C CProtocolManager(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
private:	// Methods

	//	Reserved for future expansion. Reserves space in export table to maintain binary compatibility.
	//
	IMPORT_C virtual void CProtocolManager_Reserved1();
	};

#endif // __PROTOM_H__
