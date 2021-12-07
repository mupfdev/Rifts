//
// Pi.h
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//
// Revision 1.003 By: Brian Evans : brian-evans@symbian.com At 6:33:11 PM on 09-Sep-99
//						Updated the informative comments for T2 compliance.
//
// Revision 1.002 By: Brian Evans : brian-evans@symbian.com At 9:18:24 AM on 09-Aug-99
//

//
// Comments :	Definition of the abstract plugin base classes, CPluginBase, and CPluginActiveBase. 
//			Also definition of the abstract CPluginManager class,
//			and the concrete owner classes CPluginOwner, and CPluginManagerOwner
//
// Required plugin DLL methods and ordinal numbers : 
// THIS MUST BE ADHERED TO BY ALL PLUGIN DLL'S
// AND IS FIXED WITHIN THE FREEZE FILE (.DEF).
// #1 CreatePluginManagerL
// #2 CreatePluginL
// #3 CreateActivePluginL
//
// Known Gotcha's :
// When you create an object whose code lies within the plugin DLL
// you have to be aware that the system may potentially unload the DLL whilst
// an object is being used.
// The EPOC OS however, holds a count of how many times the DLL has been opened,
// and so we can exploit this behavior by holding an open handle to the library
// with each object we create, closing the handle when the object is destroyed.
// This is the purpose of the 'owner' classes.
// So for each object within the class supply an owner to the caller which holds the
// functional class, and a handle to the library it resides in.
// On destruction of the owner close the library as the very last call in the destructor.
// WARNING : DO NOT PERFORM ANY PROCESSING AFTER THE CLOSE LIBRARY CALL, THE DLL WHICH
// CONTAINS THE OWNER CODE MAY BE UNLOADED WHILST YOU ARE PROCESSING, IF YOU HAVE CLOSED
// THE LAST OPEN HANDLE ON THAT DLL!!!.
//
// CPluginManager creation:
// Call the static method CreatePluginManagerL(), DLL ordinal #1. 
// Supplying an RFs, and a reference to an RLibrary.
//
// Each time you create a CPluginManager, you have to load an RLibrary, and the most
// efficient thing would be to assign this library to the CPluginManagerOwner, but an RLibrary can't
// be copied, so it will be the RLibrary member in CPluginManagerOwner. 
// Effectively this means that the DLL's function CreatePluginManagerL(), fixed as ordinal #1,
// can't create a CPluginManagerOwner, and therefore will return a CPluginManager* instead.
// The best way of creating a CPluginManager, then, seems to do it within the 
// CPluginManagerOwner::ConstructL
//

// Plugin creation:
// Call the member methods CPluginManager::CreatePluginL(), 
// or CPluginManager::CreateActivePluginL().
// Otherwise call the static member methods CPluginBase::CreatePluginOwner(),
// or CPluginActiveBase::CreatePluginOwner().
//
// It seems reasonable to provide the CPluginManager with a function to create new plugins.
// This function must return a CPluginOwner, as it will be called by clients.
// The DLL's function CreatePluginL(), fixed as ordinal #2, will provide a plugin object derived from CBase.
// The CPluginManager::CreatePluginL method will call this #2 function and return a CPluginOwner* to its
// caller.
// The DLL's function CreateActivePluginL(), fixed as ordinal #3 function will provide a plugin object 
// derived from CActive. The CPluginManager::CreatePluginActiveL function
// will call this #3 function and again return a CPluginOwner* to its caller
//
// Note that the static methods CPluginBase::CreatePluginOwnerL(),
// and CPluginActiveBase::CreatePluginOwnerL().
// provide more general searching capabilities using a TMatchParams structure to define a search
// for a specific plugin, or class of plugin using the general plugin type UID, and a set of match
// conditions.
//

// Uids:
// Uids passed as arguments to methods such as CPluginBase::CreatePluginOwnerL, 
// refer to the type of plugin expected / required.
// This plugin type UID is the one defined for the DLL's plugin manager to return,
// identifying the type of plugin which the DLL contains. when the plugin manager
// is requested to return the data descriptor for plugin index 0.
// i.e. CPluginManager::DataL(0).
//
// Do not confuse the plugin type UID with the UID's defined for the plugin DLL itself.
// Plugin DLL's will be defined with the following UID constant triplet.
// 1. KDynamicLibraryUidValue.
// 2. KPluginDllUidValue.
// 3. Specific DLL UID.  (Varies with the DLL & MUST be unique across the system).
//

#if !defined (__PI_H__)
#define __PI_H__

#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined (__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__WAPDEB_H__)
#include "WapDeb.h"
#endif

#if !defined(__LOGDEF_H__)
#include "LogDef.h"
#endif

const TInt KDefaultIndex = 1;				// The DLL index value for the first plugin in a plugin DLL

// Required plugin DLL method ordinal numbers
const TInt KCreatePluginManagerMethod = 1;	// #1 CreatePluginManagerL
const TInt KCreatePluginMethod = 2;			// #2 CreatePluginL
const TInt KCreateActivePluginMethod = 3;	// #3 CreateActivePluginL

// Forward declarations of the owner and client.
class CPluginOwner;
class CPluginServerClient;

// Define a return type for a plugin's unique id for clarity.
typedef TInt TPluginUniqueId;

///////////////////////////////////////////////////////////////////////////////////////////////
//
// A simple class to hold the plugin match characteristics, to be used
// during plugin searching. 
// i.e. The version number, name, and data descriptor of the plugin.
// A match may be performed upon any or all of the characteristics,
// singly or in any combination.
//
// The partial match flag indicates that a match is valid on the first part of 
// the plugin's reported string where; 
//	The 'first part' of the string is defined as the characters which form the start
//	of the plugin's reported string to the first occurance of the '||' character pair,
//	or the string's end.
//
// The wildcard match flag indicates that a match is valid on the first part of 
// the plugin's reported string where;
//	The 'first part' of the string is defined as the characters which form the start
//	of the plugin's reported string to the first occurance of the '||' character pair,
//	or the string's end.
// And
//	Wildcard characters are ‘*’ and ‘?’, where ‘*’ matches zero or more consecutive
//	occurrences of any character and ‘?’ matches a single occurrence of any character.
//	Wildcards are only applicable to the plugin's reported string.
//	The match string is ALWAYS a literal.
//
// The extended match flag indicates that a match is valid on each section
// for a match to the first part of the plugin's reported string where;
//	A 'section' of the string is defined as the characters which form the start
//	of the plugin's reported string to the first occurance of the '||' character pair,
//	or the string's end;
// OR 
//	The characters from a '||' character pair in the plugin's reported string to
//	the next occurance of the '||' character pair, or the string's end
//
// Any combination of flags is acceptable.
//
// WARNING : This structure DOES NOT own the instance pointer variables, 
// and so WILL NOT delete them.
//
class TMatchParams
	{
public:
	// Default d'tor
	IMPORT_C TMatchParams();

	// Instance variable Accessors
	// Provide access to the plugin 'data string'
	// match descriptor
	IMPORT_C const TPtrC DataType() const;

	// Set the plugin 'data string' match descriptor
	// Post-Condition : iDataType equals aDataType.
	IMPORT_C void SetDataType(const TPtrC& aDataType);

	// Provide access to the plugin 'name string'
	// match descriptor
	IMPORT_C const TPtrC Name() const;

	// Set the plugin 'name string' match descriptor
	// Post-Condition : iName equals aName.
	IMPORT_C void SetName(const TPtrC& aName);

	// Provide access to the plugin version number
	// match variable
	IMPORT_C const TVersion* Version() const;

	// Set the plugin version number match variable
	// Post-Condition : iVersion equals aVersion.
	IMPORT_C void SetVersion(TVersion* aVersion);

	// Check if 'partial' matching is allowed
	IMPORT_C TBool IsPartialMatch() const;
	// Set/Clear the 'partial' match flag
	// Post-Condition : iPartialMatch equals aPartialMatch.
	IMPORT_C void SetPartialMatch(TBool aPartialMatch);

	// Check if 'wildcard' matching is allowed
	IMPORT_C TBool IsWildcardMatch() const;
	// Set/Clear the 'wildcard' match flag
	// Post-Condition : iWildcardMatch equals aWildcardMatch.
	IMPORT_C void SetWildcardMatch(TBool aWildcardMatch);

	// Check if 'extended' matching is allowed
	IMPORT_C TBool IsExtendedMatch() const;
	// Set/Clear the 'extended' match flag
	// Post-Condition : iExtendedMatch equals aExtendedMatch.
	IMPORT_C void SetExtendedMatch(TBool aExtendedMatch);

private:
	TPtrC iDataType;		// The plugin 'data string' match descriptor.
	TPtrC iName;			// The plugin 'name string' match descriptor.
	TVersion* iVersion;		// The plugin version number match variable.
	TBool iPartialMatch;	// The flag to show if 'partial' matching is enabled
	TBool iWildcardMatch;	// The flag to show if 'wildcard' matching is enabled
	TBool iExtendedMatch;	// The flag to show if 'extended' matching is enabled
	};

///////////////////////////////////////////////////////////////////////////////////////////////
//
// CPluginBase is an abstract base class for all CBase derived plugins.
// It provides access and negotiation with the plugin server 
// for the creation of specified types of plugins, with particular 
// characteristics.
// Additionally it can supply its version number, name, and data descriptor
//

class CPluginBase : public CBase
	{
public:
	// The default c'tor
	// Input				: initialised references to a file session, and library handle
	//						also Its DLL plugin index number.
	// Return				: nothing
	// Error Behaviour		: none, cannot fail.
	// Post Conditions		: constructed base class with partial initialisation.
	IMPORT_C CPluginBase(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);
	IMPORT_C virtual ~CPluginBase();
	
	// Information providing accessors
	// For derivation of other plugins (see The SDK -> Dynamic Link Libraries.html : Virtual function tables)
	// Return the version number of the plugin
	IMPORT_C virtual TVersion Version() const = 0;

	// Return a descriptor containing the 'name string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'name string' fails.
	IMPORT_C virtual HBufC* NameL() const = 0;

	// Return a descriptor containing the 'data string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'data string' fails.
	IMPORT_C virtual HBufC* DataL() const = 0;

	// Returns the DLL index number of this plugin.
	IMPORT_C TInt Index() const;					//  Cannot inline with EXPORTED functions for Binary compatability.

	// Plugin Loader methods
	//	Search the available Plugins for a match to the match parameters
	//	Return a pointer to the CPluginOwner of the created plugin.
	//  Input : a UID identifying the type of plugin required,
	//			and an initialised TMatchParams instance specifying the search parameters.
	//	The caller is responsible for deletion of the CPluginOwner.
	//  May leave if creation/initialisation of the 'plugin owner' fails.
	IMPORT_C static CPluginOwner* CreatePluginOwnerL (const TUid& aPluginUid, const TMatchParams& aMatchParams);

	// Provide an overload for clients who have an existing Plugin Server client
	IMPORT_C static CPluginOwner* CreatePluginOwnerL (const TUid& aPluginUid, const TMatchParams& aMatchParams, CPluginServerClient* iPiServer);

	//	Respond to the request that we can handle this type
	//	Returning the unique id of the plugin
	//  If we do not find a specific handler reply KErrNotFound.
	//	May leave if creation/initialisation of intermediate objects
	//	required for processing fails.
	//  Input : a UID identifying the type of plugin required, and a type descriptor
	//			to match against a plugins declared 'data string'. 
	IMPORT_C static TPluginUniqueId CanHandleL (const TUid& aPluginUid, const TDesC& aDataType);

	// Provide an overload for clients who have an existing Plugin Server client
	IMPORT_C static TPluginUniqueId CanHandleL (const TUid& aPluginUid, const TDesC& aDataType, CPluginServerClient* iPiServer);

	//	Build an array of the data returned by a plugin
	//  with a single entry for each of the known plugins
	//  The caller is responsible for deletion of this array.
	//  Input : a UID identifying the type of plugin required.
	//	May leave if creation/initialisation of the array fails.
	//	NULL may be returned if no plugins are available.
	IMPORT_C static CDesCArray* KnownHandledTypesL (const TUid& aPluginUid);

	// Provide an overload for clients who have an existing Plugin Server client
	IMPORT_C static CDesCArray* KnownHandledTypesL (const TUid& aPluginUid, CPluginServerClient* iPiServer);


protected:	// Accessors
	IMPORT_C const TFileName FileName() const;		// Provide the filename of the DLL this plugin resides in
	IMPORT_C RFs& FsSession() const;				// Provide the reference to the open file session of its owner

private:
	// A Helper method for plugin searching
	//  Input : a UID identifying the type of plugin required, a type descriptor
	//			to match against a plugins declared 'data string', and a valid
	//			pointer to an initialised plugin server client instance.
	//	Return : The unique identifier of the 'best match' plugin, or KErrNotFound
	//			The method may leave on unexpected errors.
	static TPluginUniqueId CanHandleL (const TUid& aPluginUid, const TMatchParams& aMatchParams, CPluginServerClient* iPiServer);

	// Reserved for future expansion
	IMPORT_C virtual void Reserved1();		
	IMPORT_C virtual void Reserved1() const;		

protected:
	RFs& iFs;						// A reference to its owners file session

	__DECLARE_LOG;					// Declare the CLogClient pointer

private:
	const RLibrary& iLibrary;		// A reference to the RLibrary of its owner
	const TInt iIndex;				// Its DLL plugin index number
	TAny* iReserved;				// Reserved for future expansion
	};

// Define the function prototype for the plugin DLL ordinal #2 call 'CreatePluginL'
typedef CPluginBase* (*TPluginFactoryFunction)(RFs&,const RLibrary&,TInt aIndex);

///////////////////////////////////////////////////////////////////////////////////////////////
//
// CPluginActiveBase is an abstract base class for all CActive derived plugins.
// It provides access and negotiation with the plugin server 
// for the creation of specified types of plugins, with particular 
// characteristics.
// Additionally it can supply its version number, name, and data descriptor
//

class CPluginActiveBase : public CActive
	{
public:
	// The default c'tor
	// Input				: initialised references to a file session, and library handle
	//						Its DLL plugin index number, and the priority to initially run at.
	// Return				: nothing
	// Error Behaviour		: none, cannot fail.
	// Post Conditions		: constructed base class with partial initialisation.
	IMPORT_C CPluginActiveBase(RFs& aFs, const RLibrary& aLibrary, TInt aIndex, TInt aPriority = EPriorityStandard);
	
	// Default d'tor
	// IMPORT_C Required for derivation from this class (see The SDK -> Dynamic Link Libraries.html : Virtual function tables)
	IMPORT_C virtual ~CPluginActiveBase();
	
	// Information
	// Return the version number of the plugin
	IMPORT_C virtual TVersion Version() const = 0;	// For derivation of other plugins ( The SDK -> Dynamic Link Libraries.html : Virtual function tables)

	// Return a descriptor containing the 'name string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'name string' fails.
	IMPORT_C virtual HBufC* NameL() const = 0;

	// Return a descriptor containing the 'data string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'data string' fails.
	IMPORT_C virtual HBufC* DataL() const = 0;

	// Returns the DLL index number of this plugin.
	IMPORT_C TInt Index() const;					// Cannot inline with EXPORTED functions for Binary compatability.

	// Plugin Loader methods
	//	Search the available Plugins for a match to the match parameters
	//	Return a pointer to the CPluginOwner of the created plugin.
	//  Input : a UID identifying the type of plugin required,
	//			and an initialised TMatchParams instance specifying the search parameters.
	//	The caller is responsible for deletion of the CPluginOwner.
	//  May leave if creation/initialisation of the 'plugin owner' fails.
	IMPORT_C static CPluginOwner* CreatePluginOwnerL (const TUid& aPluginUid, const TMatchParams& aMatchParams);

	// Provide an overload for clients who have an existing Plugin Server client
	IMPORT_C static CPluginOwner* CreatePluginOwnerL (const TUid& aPluginUid, const TMatchParams& aMatchParams, CPluginServerClient* iPiServer);

	//	Respond to the request that we can handle this type
	//	Returning the unique id of the plugin
	//  If we do not find a specific handler reply KErrNotFound.
	//	May leave if creation/initialisation of intermediate objects
	//	required for processing fails.
	//  Input : a UID identifying the type of plugin required, and a type descriptor
	//			to match against a plugins declared 'data string'. 
	IMPORT_C static TPluginUniqueId CanHandleL (const TUid& aPluginUid, const TDesC& aDataType);

	// Provide an overload for clients who have an existing Plugin Server client
	IMPORT_C static TPluginUniqueId CanHandleL (const TUid& aPluginUid, const TDesC& aDataType, CPluginServerClient* iPiServer);

	//	Build an array of the data returned by a plugin
	//  with a single entry for each of the known plugins
	//  The caller is responsible for deletion of this array.
	//  Input : a UID identifying the type of plugin required.
	//	May leave if creation/initialisation of the array fails.
	//	NULL may be returned if no plugins are available.
	IMPORT_C static CDesCArray* KnownHandledTypesL (const TUid& aPluginUid);

	// Provide an overload for clients who have an existing Plugin Server client
	IMPORT_C static CDesCArray* KnownHandledTypesL (const TUid& aPluginUid, CPluginServerClient* iPiServer);

	// Methods inherited from CActive
	// Add this instance to the active scheduler
	// if necessary, and activate it.
	IMPORT_C virtual void Activate();

	// Bug report EDNSTAR-4HPNYH fix
	// Provide a cancel signalling method
	// to allow cancellation of the active plugin
	// from within its RunL when the CActive::Cancel()
	// call will not work
	IMPORT_C virtual void RequestCancel();


protected:	// Accessors
	// Allow correct cleanup of this object
	// when the active object is cancelled.
	IMPORT_C virtual void DoCancel();

	IMPORT_C const TFileName FileName() const;		// Provide the filename of the DLL this plugin resides in
	IMPORT_C RFs& FsSession() const;				// Provide the reference to the open file session of its owner

private:
	// A Helper method for plugin searching
	//  Input : a UID identifying the type of plugin required, a type descriptor
	//			to match against a plugins declared 'data string', and a valid
	//			pointer to an initialised plugin server client instance.
	//	Return : The unique identifier of the 'best match' plugin, or KErrNotFound
	//			The method may leave on unexpected errors.
	static TPluginUniqueId CanHandleL (const TUid& aPluginUid, const TMatchParams& aMatchParams, CPluginServerClient* iPiServer);

	// Reserved for future expansion
	IMPORT_C virtual void Reserved1();		
	IMPORT_C virtual void Reserved1() const;		

protected:
	RFs& iFs;						// A reference to its owners file session
	TBool iCancelRequested;			// The flag for cancellation request : Bug report EDNSTAR-4HPNYH fix

	__DECLARE_LOG;					// Declare the CLogClient pointer

private:
	const RLibrary& iLibrary;		// A reference to the RLibrary of its owner
	const TInt iIndex;				// Its DLL plugin index number
	TBool iAdded;					// A flag indicating if this object has been
									// attached to the CActiveScheduler
	TAny* iReserved;				// Reserved for future expansion
	};

// Define the function prototype for the plugin DLL ordinal #3 call 'CreateActivePluginL'
typedef CPluginActiveBase* (*TPluginActiveFactoryFunction)(RFs&,const RLibrary&,TInt aIndex);

///////////////////////////////////////////////////////////////////////////////////////////////
// Derivation of this concrete class is forbidden
// A container class for the plugin instance
// Which exploits the EPOC OS reference counting behaviour to
// ensure that the DLL it resides in is not unloaded until
// full cleanup has been accomplished.
//
class CPluginOwner : public CBase
	{
	friend class CPluginManager;

public:
	// Note that these next 2 methods are mutually exclusive.
	// A plugin owner can only own a single plugin.
	IMPORT_C CPluginBase& Plugin() const;						// Supply the owned plugin
	IMPORT_C CPluginActiveBase& ActivePlugin() const;			// Supply the owned active plugin
	
	// Default d'tor
	~CPluginOwner();											// Non-virtual ok : no derivation

	// Allow access to the DLL library reference
	IMPORT_C const RLibrary& Library() const;

private:
	// Default c'tor allows construction by CPluginManager only
	CPluginOwner();

	// Complete the initialisation
	// of this instance.
	// Will leave if initialisation is not completed successfully.
	// Input : a TFileName reference containing the name of the DLL
	//			which holds the executable code of the owned plugin.
	//			and a TUid for the third UID of the DLL
	//		Note that the first UID will be KDynamicLibraryUidValue
	//			 and the second KPluginDllUidValue
	void ConstructL(const RLibrary& aLibrary);

	// Create a plugin owner on the heap
	// returning a fully initialised instance.
	// May leave if initialisation cannot be completed.
	static CPluginOwner* NewL(const RLibrary& aLibrary);// To be called by CPluginManager::CreatePluginL only

	// Set the owned plugin.
	// These methods panic if a plugin is owned already.
	void SetPlugin(CPluginBase* aPlugin);						// To be called by CPluginManager::CreatePluginL only
	void SetPlugin(CPluginActiveBase* aPlugin);					// To be called by CPluginManager::CreatePluginL only

private:
	CPluginBase* iPlugin;										// The owned plugin
	CPluginActiveBase* iActivePlugin;							// OR the owned active plugin (Mutually exclusive).
	RLibrary iLibrary;											// The plugin DLL handle to hold open. 
																// Contains the executable code for the owned plugin,
																// and this owner!

	__DECLARE_LOG;												// Declaration of Log server client. 

	};

///////////////////////////////////////////////////////////////////////////////////////////////
// Abstract class for use by a plugin DLL to manage all the plugins contained therein.
class CPluginManager : public CBase
	{
public:
	// Default c'tor
	// Input				: initialised references to a file session, and library handle
	// Error Behaviour		: none, cannot fail.
	// Post Conditions		: constructed class with iFs set to point at aFs
	//							and iLibrary set to point at aLibrary.
	IMPORT_C CPluginManager(RFs& aFs,const RLibrary& aLibrary);
	IMPORT_C virtual ~CPluginManager();						 // IMPORT_C Required for derivation from this class

	// Create a fully initialised plugin owner on the heap
	// which contains a fully initialised plugin instance corresponding
	// to the plugin identified by the plugin DLL index number
	// provided.
	// Will leave if there is an error when constructing these objects.
	IMPORT_C CPluginOwner* CreatePluginL(TInt aIndex) const; 

	// Create a fully initialised plugin owner on the heap
	// which contains a fully initialised active plugin instance corresponding
	// to the plugin identified by the plugin DLL index number
	// provided.
	// Will leave if there is an error when constructing these objects.
	IMPORT_C CPluginOwner* CreatePluginActiveL(TInt aIndex) const; 

	// State how many plugins are contained within this DLL
	virtual TInt Count() const =0;

	// Return the version number of the plugin identified by
	// the plugin DLL index, or the plugin manager if the index value is 0
	virtual TVersion Version(TInt aIndex) const =0;

	// Return a descriptor containing the 'name string'
	// for the plugin identified by the plugin DLL index, 
	// or the plugin manager if the index value is 0.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'name string' fails.
	virtual HBufC* NameL(TInt aIndex) const =0;

	// Return a descriptor containing the 'data string'
	// for the plugin identified by the plugin DLL index, 
	// or the plugin manager if the index value is 0.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'data string' fails.
	// NOTE : The 'data string' for the plugin manager identifies the 
	// plugin type UID for the plugins contained within the managed DLL.
	virtual HBufC* DataL(TInt aIndex) const =0;


protected:
	IMPORT_C RFs& FsSession() const;		// Allow access to this plugin managers file session

private:
	// Reserved for future expansion
	IMPORT_C virtual void Reserved1();		
	IMPORT_C virtual void Reserved1() const;		

protected:
	__DECLARE_LOG;							// Declaration of Log server client.

private:
	const RLibrary& iLibrary;				// A reference to the RLibrary of its owner
	RFs& iFs;								// A reference to the RFs of its owner
	TAny* iReserved;						// Reserved for future expansion					
	};

// Define the function prototype for the plugin DLL ordinal #1 call 'CreatePluginManagerL'
typedef CPluginManager* (*TPluginManagerFactoryFunction)(RFs& aFs,RLibrary& aLibrary);

///////////////////////////////////////////////////////////////////////////////////////////////
// Derivation of this concrete class forbidden
// A container class for the plugin manager instance
// Which exploits the EPOC OS reference counting behaviour to
// ensure that the DLL it resides in is not unloaded until
// full cleanup has been accomplished.
//

class CPluginManagerOwner : public CBase
	{
public:
	// Construct an instance of CPluginManager owner upon the heap.
	// Input : a TFileName reference containing the name of the DLL
	//			which holds the executable code of the owned plugin manager,
	//			a reference to an initialised file session.
	//			and a TUid for the third UID of the DLL
	//		Note that the first UID will be KDynamicLibraryUidValue
	//			 and the second KPluginDllUidValue
	// Returns : A fully initialised plugin manager owner, containing a fully
	//			initialised plugin manager.
	// This method will leave if it cannot fully initialise.
	IMPORT_C static CPluginManagerOwner* NewL(RFs& aFs, const TFileName& aPluginDllName, const TUid* aDllUid = NULL);

	// Default d'tor
	// Non-virtual ok : no derivation
	~CPluginManagerOwner();

	IMPORT_C CPluginManager& PluginManager() const;

private:
	// Default c'tor
	// explicit to prevent instantiation through implicit conversion of the parameter
	explicit CPluginManagerOwner(RFs& aFs);	

	// Complete the initialisation of the plugin manager owner
	// including the allocation of a new plugin manager.
	// Leave on any error.
	// Input : a TFileName reference containing the name of the DLL
	//			which holds the executable code of the owned plugin manager
	// Post-Condition : A fully initialised instance of CPluginManager is
	// held in the iPluginManager pointer
	void ConstructL(const TFileName& aPluginDllName);

	// Complete the initialisation of the plugin manager owner
	// including the allocation of a new plugin manager.
	// Leave on any error.
	// Input : a TFileName reference containing the name of the DLL
	//			which holds the executable code of the owned plugin manager
	//			and a TUid for the third UID of the DLL
	//		Note that the first UID will be KDynamicLibraryUidValue
	//			 and the second KPluginDllUidValue
	// Post-Condition : A fully initialised instance of CPluginManager is
	// held in the iPluginManager pointer
	void ConstructL(const TFileName& aPluginDllName, const TUid* aUid);

private:
	RFs& iFs;								// The file session to use
	CPluginManager* iPluginManager;			// the owned plugin manager
	RLibrary iLibrary;						// Contains the executable code for the owned plugin manager,
											// and this owner!

	__DECLARE_LOG;							// Declaration of Log server client.

	};

#endif //__PI_H__