// urlhnd.h
//
// Copyright (c) 1998/1999 Symbian Ltd.  All rights reserved. 
//

// Purpose:		Definition of CUrlHandler.
//
// Comments:	Base class for url handlers. CDataProvider derives from CPluginActiveBase, hence url handlers are 
//				active objects.
//
//				Urlhandlers are normally passed on to its customers encapsulated in a CPluginOwner object The C'tor cannot 
//				be changed as the object will be created by the plug-in components, and hence methods exist to intialise 
//				the necessary parameters. Therfore, CUrlHandler does not own any of its parameters other than the copy 
//				of the url in iUrl.
//

#if !defined(__URLHND_H__)
#define __URLHND_H__

// System includes
//
#include <mdptx.h>
#include <pi.h>
#include <urlbase.h>

// User includes
//
#include "dpbase.h"
#include "protom.h"

class CUrlHandler : public CDataProvider
	{
public:	// Methods

	// Sets the url that the url handler refers to. This method can leave as the Url object is being copied.
	//
	// In:
	// aUrl	- url to be refered to.
	//
	IMPORT_C void SetUrlL(const CUrl& aUrl);

	// Returns the url that this handler refers to.
	//	
	inline const CUrl& Url() const;

	// Sets the object from which the url handler may collect data to send for POST methods
	//
	// In:
	// aTransmissionData	- source of data to send
	//
	IMPORT_C void SetTransmissionData(MDataProviderTransmissionData& aTransmissionData);

	// Retrieves the object from which the url handler may collect data to send for POST methods
	//
	// Rtn: pointer to the object. Ownership is NOT transfered to the caller
	//
	IMPORT_C MDataProviderTransmissionData* TransmissionData();

	// Sets the protocol managers for this url handler plug-in.The protocol managers are used to share and 
	// manage resources needed by several url handlers of the same type.
	//
	// In:
	// aProtocolManager	- the scheme manager for this type of url handler
	//
	IMPORT_C void SetProtocolManager(CProtocolManager& aProtocolManager);

	// Retrieves the protocol/scheme manager for this type or url handler
	//
	// Rtn: returns the scheme manager. Ownership is NOT transfered to the caller
	//
	IMPORT_C CProtocolManager* ProtocolManager();

	// This may be used in the future allow the data handlers to communicate protocol specific params found in the 
	// content to the url handler. For instance, to execute protocol specific commands, e.g. HTTP Meta tags.
	//
	virtual void ProtocolCommandL()=0;
	
	// D'tor
	//
	IMPORT_C virtual ~CUrlHandler();

protected:	// Methods

	// C'tor - non allocating constrcution only
	//
	// In:
	// aFs			- file system handle. Note - not guaranteed to be connected
	// aLibrary		- handle to DLL in which this active plug-in was made
	// aIndex		- index for this (active) plug-in in this DLL
	// aPriority	- priority level for the active object
	//
	IMPORT_C CUrlHandler(RFs& aFs, const RLibrary& aLibrary, TInt aIndex, TInt aPriority);

protected:	// Attributes

	// Size of the data buffers.
	//
	TInt iSize;

	// Url that this url handler refers to. Owned by this class.
	//
	CUrl* iUrl;

	// Object from which the url handler may collect data to send in POST method. NOT owned by class.
	//
	MDataProviderTransmissionData*  iTransmissionData;

	// Scheme manager for the type of this url handler. NOT owned by class.
	//
	CProtocolManager* iProtocolManager;

private:	//Methods

	//	Reserved for future expansion. Reserves space in export table to maintain binary compatibility.
	//
	IMPORT_C virtual void CUrlHandler_Reserved1();

private:	// Attributes

	// Expansion data
	//
	TAny* iCUrlHandler_Reserved;
	};

inline const CUrl& CUrlHandler::Url() const
//
// Return iUrl
	{
	return *iUrl;
	}

#endif // __URLHND_H__
