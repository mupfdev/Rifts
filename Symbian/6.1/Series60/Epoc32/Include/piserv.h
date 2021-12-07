// 
// PiServ.h
// Copyright (C) 1998-1998 Symbian Ltd. All rights reserved.
//

// 
// Comments: The Plugin Server is the administration module for handling all
//			registration of plugin modules which may be loaded via an application.
//			It provides the facilities for DLL's containing plugins to register
//			their contents, and it also provides negotiation to identify the 
//			correct plugin to load in response to an applications request for a service.
// 
//			Client side of the plugin server
//			a prospective client of the plugin server creates
//			a CPluginServerClient object to handle the negotiation with the server.
//
//			This CPluginServerClient object can provide access to an iterator
//			through the plugins of a particular type. and access
//			to the plugin factory.
//			It also provides methods to create a plugin of a particular
//			type with certain characteristics.
// 

#if !defined(__PISERV_H__)
#define __PISERV_H__


#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__E32TEST_H__)
#include <e32test.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined (__APMSTD_H__)
#include <ApmStd.h>
#endif

#include "PicManOb.h"
#include "LogDef.h"

// Forward declaration
class TMatchParams;			// Plugin searching structure
class CPluginBase;			// Passive plugin base class
class CPluginActiveBase;	// Active plugin base class
class CPluginOwner;			// A plugins owner class which wraps the plugin
class CPluginManager;		// A plugin DLL manager class
class CPluginManagerOwner;	// A plugin manager wrapper

class CPluginCacheItem;		// The plugins cached information structure class
class CPluginFactory;		// The plugin construction class

typedef TInt TPluginUniqueId;		// The plugins id unique within the Plugin server
typedef TInt TIteratorIndex;		// The current iterator position, used for navigation.

#if defined(_UNICODE)
const TInt32 KPluginDllUidValue=0x100041DB;
const TInt32 KWAPApplicationUidValue=0x100041D9;
#else
const TInt32 KPluginDllUidValue=0x100041DA;
const TInt32 KWAPApplicationUidValue=0x100041D8;
#endif

// Use a structure that can be copied across IPC
// To hold the values for a plugin's control info
struct TIPCControl
	{
	TInt	iId;			// Plugin id
	TInt	iLocalIndex;	// plugin's index in DLL
	TInt	iFilenameIndex; // map index for plugin's DLL filename within the plugin registry DB
	TBool	iEnabled;		// Flag for enabled/Disabled status
	};

/////////////////////////////////////////////////////////////////////////////// 
// CPluginActiveObserver is the active object class supporting the
// notification messages, it is owned by a CPluginFactory which it notifies
// when its RunL method is called. Its TRequestStatus is passed to
// the plugin server when requesting asynchronous notifications. 
// (See CPluginFactory::NotifyOnChange())
// A derived class could be used to provide different notification behaviour,
// and installed via the CPluginServerClient class.
//
class CPluginActiveObserver : public CActive
	{
public:
	IMPORT_C static CPluginActiveObserver* NewL(CPluginFactory& aFactory, TPriority aPriority = EPriorityHigh);
	IMPORT_C virtual ~CPluginActiveObserver();

	// Launching behaviour : Setting the object active on the scheduler, awaiting completion.
	IMPORT_C void Activate();

protected:
	// CActive methods
	IMPORT_C void DoCancel();
	IMPORT_C void RunL();

protected:
	// Default c'tor
	IMPORT_C CPluginActiveObserver(CPluginFactory& aFactory, TPriority aPriority);
	
	// Completes the initialisation of this base object,
	// and MUST be called by any derived class to fully instantiate it's base.
	IMPORT_C void BaseConstructL();
	
private:
	CPluginFactory& iFactory;	// Reference to the owning factory
	};

/////////////////////////////////////////////////////////////////////////////// 
// RPluginSession maintains the Client side session with 
// the CSPluginServer. It is entirely owned and used by CPluginFactory.
//
class RPluginSession : public RSessionBase		// For the Client side session 
    {
	friend class CPluginFactory;				// To allow access to the protected SendRecieve methods
public:
    TInt Connect();								//	Connect with the plugin server

    static TVersion Version();					// Give the current version number of the Plugin client side.

private:
	__DECLARE_LOG;								// Declare the CLogClient pointer
	};

/////////////////////////////////////////////////////////////////////////////// 
//
// CPluginFactory is the class that provides the communication of the
// client requests to the plugin server, including the packing / unpacking of
// any parameters passing accross the process boundary
// It is created, and owned by a CPluginServerClient for a client,
// and cannot be created directly
//  WARNING : Derivation from this class is neither anticipated, nor recommended!
//
class CPluginFactory : public CBase
	{
	friend class CPluginServerClient;			// The owner of the factory
	friend class CPluginActiveObserver;			// our notification object
public:
	// Close the plugin server connection.
	IMPORT_C void Close();

	// Count of total cached plugins
	IMPORT_C TInt PluginCount() const;

	// Notification message initiation and cancellation
	// Request Notification for this CPluginFactory of any changes 
	// to the Plugins available, so that it may update its information.
	// (Uses the iForceRefresh flag)
	// Returns KErrNone of the error code
	IMPORT_C TInt NotifyOnChange();
	// Request Notification via the supplied plugin observer of any changes 
	// to the Plugins available, so that it may update its information.
	// (Uses the iForceRefresh flag)
	// Returns KErrNone of the error code
	IMPORT_C TInt NotifyOnChange(CPluginActiveObserver* aPluginObserver);
	// Cancel any requests for change notifications.
	IMPORT_C void NotifyOnChangeCancel();
	
	// Notification callback from the CPluginActiveObserver
	// indicating how the plugin registry has changed. 
	// (aStatus wraps a TPluginChange enumeration)
	void PluginChanged(TRequestStatus& aStatus);

	// Plugin Item information retrieval
	// Obtain the version descriptor of the plugin identified by the unique id
	// NOTE the caller assumes ownership of the returned 'version string'.
	IMPORT_C HBufC* VersionL(TPluginUniqueId aPluginId);
	// Obtain the 'name string' of the plugin identified by the unique id
	// NOTE the caller assumes ownership of the returned 'name string'.
	IMPORT_C HBufC* NameL(TPluginUniqueId aPluginId);
	//Obtain the 'data string' of the plugin identified by the unique id
	// NOTE the caller assumes ownership of the returned 'data string'.
	IMPORT_C HBufC* DataL(TPluginUniqueId aPluginId);

	// Cached item information extraction in a list for all plugins matching the plugin UID
	IMPORT_C RPointerArray<CPluginCacheItem>* GetPluginListL(const TUid& aPluginInterface);

	// Accessable routine from the E32Dll method to allow
	// clearance of the TLS stored lists
	static void FreeTLSPluginLists(TAny* aList);

	// Exported method to allow clearance of the TLS stored lists
	IMPORT_C void ClearCache();

private:
	// Construct the class instance upon the heap.
	// return a fully initialised CPluginFactory
	// or Leave on any error.
	static CPluginFactory* NewL();					// Can only be created by a CPluginServerClient
	// Default d'tor NON-Virtual
	~CPluginFactory();								// Destruction likewise

	// Default c'tor
	CPluginFactory();

	// Complete the initialisation of the class here
	// Leave on any error.
	void ConstructL();

	// Create a connection to the plugin server
	// where necessary.
	// Leave if an attempted connection fails.
	void ConnectL();

	// Helper methods
	// A DLL is loaded from the file identified by the path to enable a
	// CPluginManagerOwner to be created
	CPluginManagerOwner* LoadDllL(TDesC& aPluginPath);

	// Obtain information about the plugin identified by the unique id
	void RefreshPluginInfoL(TPluginUniqueId aPluginId);

	// Return the cached information about the item identified by the unique id
	//	NOTE : Ownership of the CPluginCacheItem passes to the caller
	CPluginCacheItem* GetPluginInfoL(TPluginUniqueId aPluginId);
	
	// Create a plugin identified by the unique id
	//	NOTE : Ownership of the CPluginOwner passes to the caller
	CPluginOwner* CreatePluginL(TPluginUniqueId aPluginId, TBool aActive = EFalse);
	// Create an active plugin identified by the unique id
	//	NOTE : Ownership of the CPluginOwner passes to the caller
	CPluginOwner* CreatePluginActiveL(TPluginUniqueId aPluginId);

	// Return true if the plugin identified by the unique id is enabled.
	TBool GetEnabled(TPluginUniqueId aPluginId);
	// Set/Clear the enabled flag for the plugin specified by the unique id.
	void SetEnabled(TPluginUniqueId aPluginId, TBool aEnabled);
	// Delete the plugin specified by the unique id.
	void DeletePlugin(TPluginUniqueId aPluginId);

	// Helper method for Plugin construction
	CPluginOwner* BuildThePluginOwnerL(TDesC& aDllFilename, TInt aPluginDllIndex, TBool aActive);

	// Plugin factory optimisations
	CPluginOwner* CreatePluginFromCacheL(const TUid& aPluginUid, const TMatchParams& aMatchParams);
	CPluginOwner* LoadCachedPluginL(TPluginUniqueId aPluginId);
	void AddToPluginCacheL(const TUid& aPluginUid, const TMatchParams& aMatchParams, TPluginUniqueId aPluginId);
	void AddToPluginCacheL(TPluginUniqueId aPluginId, TBool aActive, HBufC* aDllFilename, TInt aPluginDllIndex);

private:

	CPluginCacheItem* iPluginInfo;					// The plugin item's retrieved information
													// An optimisation for the version, name and data calls
	RPluginSession* iPluginConnection;				// The plugin server session
	RFs iFs;										// The file server session
	CPluginActiveObserver* iPluginObserver;			// The active object for notification messages
	TBool iConnected;								// A flag to indicate if the server connection is open
	TInt iPluginsRegistered;						// The number of plugins registered by the server
	TBool iForceRefresh;							// A flag indicating that the iPluginInfo is stale

	// Optimisation lists
	struct COptimisationList
		{
		RPointerArray<CPluginCacheItem>* iCachedList;
		TUid iCachedListUid;
		};
	// The mapping of the plugin unique id to its load data
	class CPluginMapItem : public CBase
		{
	public:
		CPluginMapItem();		// c'tor
		~CPluginMapItem();		// d'tor

		TPluginUniqueId iId;
		TBool iActive;
		TInt iPluginDllIndex;
		TUid iUid;
		HBufC* iDllFilename;
		HBufC* iName;
		HBufC* iData;
		};
	struct _dllTlsStorage
		{
		RPointerArray<CPluginMapItem>* iPluginMapping;
		RPointerArray<COptimisationList>* iCachedLists;
		};
	struct _dllTlsStorage* iTls;
	TFileName iPreviousFileName;
	CPluginManagerOwner* iPreviousPimo;

	__DECLARE_LOG;									// Declare the CLogClient pointer

#if defined _DEBUG
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
													// Called by the standard macro __TEST_INVARIANT
#endif
	};	// CPluginFactory

class CPluginIterator : public CBase
// CPluginIterator handles the retrieval of information
// from a set of plugins identified by a UID and some match parameters
// It is created, and owned by a CPluginServerClient for a client,
// and it cannot be created directly.
// Iteration returns the iterator position, for navigation.
// Use the Id() method to obtain the plugin's unique id required
// for the Plugin Server creation calls.
// 
	{
	friend class CPluginServerClient;

// Methods
public:
	IMPORT_C virtual ~CPluginIterator();

// Item count and navigation
	IMPORT_C TInt Count() const;
	IMPORT_C TIteratorIndex First();							// Returns the index position of the first iterator item, (usually 0)
	IMPORT_C TIteratorIndex Next(TIteratorIndex aCurrentIndex); // Takes the current index position, and returns the index position of this iterator item
	IMPORT_C TIteratorIndex Last();								// Returns the index position of the first iterator item, (usually count - 1)
	IMPORT_C TIteratorIndex BestMatch();						// Returns the current index position of the best plugin match

	// Current item information retrieval
	// NOTE : Ownership of the returned descriptor passes to the caller
	IMPORT_C HBufC* VersionL() const;	// The version number of the iterator's current plugin
	// NOTE : Ownership of the returned descriptor passes to the caller
	IMPORT_C HBufC* NameL() const;		// The Name descriptor of the iterator's current plugin
	// NOTE : Ownership of the returned descriptor passes to the caller
	IMPORT_C HBufC* DataL() const;		// The Data descriptor of the iterator's current plugin
	IMPORT_C TPluginUniqueId Id();		// Returns the unique Plugin id of the current iterator item.

private:

	class TIterationItem
	// Holds a pair of integers to indicate the unique id of a plugin
	// together with the confidence of its match
	//
		{
	public:
		TInt iConfidence;		// Match confidence
		TPluginUniqueId iId;	// Plugin id
		};

	// Create an instance of the iterator upon the heap which iterates
	// All plugins with the specified UID.
	// Leave upon any error.
	static CPluginIterator* NewL(const TUid& aPluginUid, CPluginServerClient& aPlugin);
	// Create an instance of the iterator upon the heap which iterates
	// All plugins with the specified UID, and match parameters.
	// Leave upon any error.
	static CPluginIterator* NewL(const TUid& aPluginUid, CPluginServerClient& aPlugin, const TMatchParams& aMatchParams);

	// Default c'tor made explicit to avoid unintentional
	// conversion construction by the compiler
	explicit CPluginIterator(CPluginServerClient& aPlugin);

	// Complete the initialisation of the iterator instance
	// Leave on any error.
	void ConstructL(const TUid& aPluginUid, const TMatchParams& aMatchParams);

	// Specialist matching helpers
	// A descriptor match tester that checks the first section of aPluginString
	// for a match to the first part of the aMatchString
	// The 'first section' of the string is defined as the characters which form the start
	// of the string to the first occurance of the '||' character pair,
	// or the string's end. 
	TBool DoMatch(const TDesC& aPluginStr, const TDesC& aMatchStr);
	TBool PartialMatch(const TDesC& aPluginStr, const TDesC& aMatchStr);
	TBool WildcardMatch(const TDesC& aPluginStr, const TDesC& aMatchStr);
	TBool ExtendedMatch(const TDesC& aPluginStr, const TDesC& aMatchStr);

	// Fill the iterator with TIterationItems based upon the UID
	void PopulateL(const TUid& aPluginUid);
	// Fill the iterator with TIterationItems based upon the UID and match parameters
	void PopulateL(const TUid& aPluginUid, const TMatchParams& aMatchParams);

// Attributes / Properties
private:
	TInt iCount;							// The number of items in the set
	TIteratorIndex iCurrentIndex;			// The current item
	CPluginServerClient& iPlugin;			// The owning CPluginServerClient instance
	CArrayFixFlat<TIterationItem> iIndexes;	// The mapping of the current index to the plugin unique id/confidence level

	__DECLARE_LOG;							// Declare the CLogClient pointer

#if defined _DEBUG
	void __DbgTestInvariant() const;		// Debug method definition to allow class invariant testing
#endif
	};  // CCPluginIterator


class CPluginServerClient : public CBase
//
//	CPluginServerClient provides the top level of the client side of the plugin server
//	It provides access to an iterator for plugin searching,
//	and also some access functions to obtain information, create, 
//  enable/disable a plugin from it's known unique id.
//  WARNING : Derivation from this class is not anticipated, nor recommended!
//
	{
	friend class CPluginIterator;		

public:
	IMPORT_C static CPluginServerClient* NewL();
	IMPORT_C ~CPluginServerClient();

	// Plugin construction
	IMPORT_C CPluginOwner* CreatePluginL(TPluginUniqueId aPluginId) const;
	IMPORT_C CPluginOwner* CreatePluginActiveL(TPluginUniqueId aPluginId) const;


	// Plugin control
	// Return true if the plugin identified by the uique id is enabled
	IMPORT_C TBool GetEnabled(TPluginUniqueId aPluginId) const;
	// Enable or disable a plugin. 
	// The input parameter is a unique id referring to the required plugin.
	IMPORT_C void SetEnabled(TPluginUniqueId aPluginId, TBool aEnabled) const;	
	// Delete a plugin from the registry.
	// The input parameter is a unique id referring to the required plugin.
	IMPORT_C void DeletePlugin(TPluginUniqueId aPluginId) const;

	// Information retrieval via unique plugin id
	IMPORT_C CPluginCacheItem& GetPluginInfoL(TPluginUniqueId aPluginId);
	
	// Provide a plugin iterator instance
	IMPORT_C CPluginIterator& PluginIteratorL(const TUid& aPluginUid);
	IMPORT_C CPluginIterator& PluginIteratorL(const TUid& aPluginUid, const TMatchParams& aMatchParams);

	// Allow access to the factory by reference
	IMPORT_C CPluginFactory& PluginFactory();

	// Local Optimisations
	CPluginOwner* CreatePluginFromCacheL(const TUid& aPluginUid, const TMatchParams& aMatchParams);
	void AddToPluginCacheL(const TUid& aPluginUid, const TMatchParams& aMatchParams, TPluginUniqueId aPluginId);

private:
	// Private constructor, guaranteed to complete.
	// Called from NewL
	CPluginServerClient();

	// Complete the initialisation of this instance
	// Leave if there is any error.
	void ConstructL();

private:
	CPluginFactory* iPluginFactory;		// The factory to provide the plugin server connection
	CPluginIterator* iIterator;			// The plugin iterator

	__DECLARE_LOG;						// Declare the CLogClient pointer

#if defined _DEBUG
	void __DbgTestInvariant() const;				// Debug method definition to allow class invariant testing
#endif
	};

#endif // __PISERV_H__
