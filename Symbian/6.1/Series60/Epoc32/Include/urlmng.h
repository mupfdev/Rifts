// urlmng.h
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

// Purpose:		Definition of CUrlMng class.
//
// Comments:	The Url Manager creates and owns the protocol managers, and uses them just to create the 
//				url handlers. It associates protocol managers with schemes.
//

#if !defined(__URLMNG_H__)
#define __URLMNG_H__

// System includes
//
#include <e32base.h>
#include <pi.h>
#include <mdptx.h>
#include <urlbase.h>

// User includes
//
#include "protom.h"

// Static data used by this class
//

// Uid's used by url plugins must derive from this.
#if defined(_UNICODE)
const TUid KUidUrlPlugins = {0x100041D7};
#else
const TUid KUidUrlPlugins = {0x100041D6};
#endif

// Enum for panic codes used in this class
enum EUrlMngPanic
	{
	EBadPointer
	};

// Forward class declarations
//
class CSchemeDesc;

class CUrlMng : public CBase
	{

public:	// Methods

	// Factory c'tor.
	//
	// Rtn: pointer to created url manager object. Ownership transfered to caller.
	//
	IMPORT_C static CUrlMng* NewL();

	// Creates the url handler plugin to deal with a given scheme and method. Specifically this method deals with 
	// GET methods. Returns the handler via the plug-in owner class.
	//
	// In:
	// aUrl								- url to instansiate the url handler with
	// aMethod							- method for the handler's transaction
	// aWmlFetchFlags					- flag associated with the fetch.
	//
	// Rtn: Pointer to plug-in owner class, encapsulating the url handler. Ownership is tranfered to caller.
	//
	IMPORT_C CPluginOwner* CreateUrlHandlerL(const CUrl& aUrl, const TDesC& aMethod, TInt aWmlFetchFlags);

	// Creates the url handler plugin to deal with a given scheme and method. Specifically this method deals with 
	// POST methods, requiring a object from which to collect the data to be posted. Returns the handler via the 
	// plug-in owner class.
	//
	// In:
	// aUrl				- url to instansiate the url handler with
	// aMethod			- method for the handler's transaction
	// aDptd			- object that the url handler will use collect the data for transmission.
	// aWmlFetchFlags					- flag associated with the fetch.
	//
	// Rtn: Pointer to plug-in owner class, encapsulating the url handler. Ownership is tranfered to caller.
	//
	IMPORT_C CPluginOwner* CreateUrlHandlerL(const CUrl& aUrl, const TDesC& aMethod,
											MDataProviderTransmissionData& aDptd, TInt aWmlFetchFlags);
	
	// Disconnects the file systems in each scheme managers in iSchemeDescArray. Specific
	// protocols may be able to accept the 'aForciblyDisconnect' flag if there is an
	// underlying network service that has to be terminated.
	//
	IMPORT_C void Disconnect(TBool aForciblyDisconnect = EFalse);
	
	// Cancels the connection startup
	IMPORT_C virtual void CancelConnect();

	// Provides the mechanism to set and get the scheme/protocol managers. (This is for future possible use - not 
	// expected to be used for WAP 1.1)
	//
	// In:
	// aScheme	- descriptor of scheme in question.
	//
	IMPORT_C CPluginOwner* SchemeManager(const TDesC& aScheme);

	// D'tor
	//
	IMPORT_C ~CUrlMng();

private:	// Methods

	// C'tor - does non-allocating construction.
	//
	CUrlMng();

	// Second phase construction. All allocations are done here.
	//
	void ConstructL();

	// Finds the CSchemeDesc in iSchemeDescArray whose scheme matches aScheme.
	//
	// In:
	// aScheme	- the sought scheme.
	//
	// Rtn: returns pointer to CSchemeDesc object if match found, else NULL. Ownership NOT transfered to caller.
	//
	CSchemeDesc* FindSchemeDesc(const TDesC& aScheme);
	
	// Creates a new entry in iSchemeDescArray, linking aScheme with aManager. The class now takes ownership fo aManager.
	//
	// In:
	// aScheme	- the scheme handled by the scheme manager.
	// aManager	- the manager for the scheme in aScheme. Ownersip transfered to class.
	//
	void SetSchemeManagerL(const TDesC& aScheme, CPluginOwner* aManager);
	
	// Creates a protocol/scheme manager for the scheme in aUrl. The array of known scheme managers is searched for a 
	// suitable manager. If one not found, a suitable manager is created and added to the array.
	// 
	// In:
	// aUrl	- the url for which the scheme manager is required.
	//
	// Rtn: a reference to the appropriate scheme manager. Ownership is NOT transfered.
	//
	CProtocolManager& CreateProtocolManagerL(const CUrl& aUrl);

private: // Attributes

	// Array of schemes and their managers. Owened by class.
	//
	CArrayPtrFlat<CSchemeDesc>* iSchemeDescArray;

	};

#endif // __URLMNG_H__
