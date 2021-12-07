// APPARC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APPARC_H__
#define __APPARC_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__GDI_H__)
#include <gdi.h>
#endif
#if !defined(__APADEF_H__)
#include <apadef.h>
#endif
#if !defined(__APAID_H__)
#include <apaid.h>
#endif

// classes defined:
class CApaApplication;
class CApaDocument;
class CApaProcess;
class MApaEmbeddedDocObserver;
//
// classes referenced:
class CApaDll;
class RReadStream;
class RWriteStream;
class CFileStore;
class CPersistentStore;
class CStreamDictionary;
class CDictionaryStore;
class CApaAppInfoFileReader;
class TApaDllInfo;
//

/// TApaLastUsedEntry

class TApaLastUsedEntry
	{
public:
	IMPORT_C TApaLastUsedEntry(TFileName aFileName, TUid aAppUid);
	IMPORT_C TApaLastUsedEntry();
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
public:
	TFileName iFileName;
	TUid iAppUid;
	};


// CApaRecentFile

class CApaRecentFile
	{
public:
	IMPORT_C static void AddLastUsedEntryL(RFs& aFs, const TDesC& aFileName, TUid aAppUid);
	IMPORT_C static TApaLastUsedEntry GetRecentFileL(RFs& aFs, TUid aAppUid, TInt aIndex);
	IMPORT_C static CArrayFixFlat<TApaLastUsedEntry>* GetRecentFileListL(RFs& aFs, TUid aAppUid);
	};

// CApaApplication

class CApaApplication : public CBase
// base class for applications; allows creation of documents & file stores + display of app icon and name.
	{
public:
	virtual void PreDocConstructL()=0; // call once before creating document
	virtual CApaDocument* CreateDocumentL(CApaProcess* aProcess)=0;
	virtual TUid AppDllUid()const=0;
	//
	// utility functions
	IMPORT_C static TInt GenerateFileName(RFs& aFs,TFileName& aRootName);
	IMPORT_C CDictionaryStore* OpenIniFileL(RFs& aFs)const;
	IMPORT_C CApaAppInfoFileReader* OpenAppInfoFileL()const;
	virtual CDictionaryStore* OpenIniFileLC(RFs& aFs)const=0;
	virtual CApaAppInfoFileReader* OpenAppInfoFileLC()const=0;
	//
	// enquiry functions
	IMPORT_C virtual TFileName AppFullName()const; // returns the full path and name of the app
	virtual void Capability(TDes8& aInfo)const=0;
	//
	// accessor function
	IMPORT_C TFileName DllName()const;
private:
	// Reserved virtual functions...
	IMPORT_C virtual void Reserved_1();
private:
	CApaDll* iApaDll;  // the CApaDll that owns me
	TInt iSpare;
	friend class CApaDll;
	friend class CApaProcess;
	};


class CApaDocument : public CBase
// base class for documents; allows insertion of glass doors.
	{
public:
	class TCapability
		{
	public:
		IMPORT_C TCapability();
		//
		inline TBool CanDrawGlass()const;
		inline TBool CanPrint()const;
		//
		inline void SetCanDrawGlass();
		inline void SetCanPrint();
		//
	private:
		enum {
			ECanDrawGlass	=0x01,
			ECanPrint		=0x02
			};
	private:
		TUint iCapability;
		};
	//
public:
	// document instantiation functions
	virtual void NewDocumentL()=0; // builds a new embedded or main document without loading from a store (may create the content from eg code or a template file).
	virtual CFileStore* CreateFileStoreLC(RFs& aFs,const TDesC& aFileName)=0; // creates a file for a document and stores itself to that store (store should be put on cleanup stack).
	//
	// interaction functions
	IMPORT_C virtual CPicture* GlassPictureL(); // Does nothing by default, override to return handle to glass picture.
	virtual void EditL(MApaEmbeddedDocObserver* aContainer,TBool aReadOnly=EFalse)=0; // Edit the document in the context of the container's environment. If aContainer is null, edit as the main document
	virtual void PrintL(const CStreamStore& aSourceStore)=0; // default print parameters, assume print context supplied by environment
	//
	// persistence functions
	virtual void SaveL()=0; // save the doc to the file in the custody of iAppProcess. This fn should be called by any "Save" menu option. store->Commit() should be called within it.
	virtual void StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic) const=0; // store to aStore, lodging the headstream in aStreamDic
	virtual void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic)=0; // restore from aStore using aStreamDic
	inline virtual void DetachFromStoreL(CPicture::TDetach /*aDegree*/=CPicture::EDetachFull) {} // supply an implementation if you support deferred loading or embedding
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream)const;
	//
	// enquiry functions
	virtual TBool IsEmpty()const=0; // return ETrue if the document is empty
	IMPORT_C virtual void ValidatePasswordL()const; // return EFalse if there *is* a password *and* the user doesn't get it right, ETrue otherwise (ie they get it right or there isn't one). Returns ETrue by default
	IMPORT_C virtual TCapability Capability()const; // returns "cant do anything" by default
	inline CApaApplication* Application()const;
	inline CApaProcess* Process()const;
	virtual TBool HasChanged()const =0;
	//
	IMPORT_C virtual ~CApaDocument();
protected:
	IMPORT_C CApaDocument(CApaApplication& aApp,CApaProcess& aProcess);
private:
	// Reserved virtual functions...
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
protected:
	MApaEmbeddedDocObserver* iContainer; // null unless this is an embedded object currently being edited
private:
	CApaApplication* iApplication; // the doc's associated application
	CApaProcess* iApaProcess;
	TInt iSpare;
	};


class CApaProcess : public CBase
// Maintains a list of documents and all the potentially shared resources used by documents (including DLL files).
	{
public:
	IMPORT_C static CApaProcess* NewL(const RFs& aFs,CApaAppFinder& aAppFinder);
	IMPORT_C void ResetL();
	//
	// static utility functions
	IMPORT_C static CStreamDictionary* ReadRootStreamLC(RFs& aFs,CFileStore*& aStore,const TDesC& aDocFullFileName,TUint aFileMode); // opens aDocFileName as aStore and returns the stream dictionary contained in its root stream on the cleanup stack
	IMPORT_C static void WriteRootStreamL(CPersistentStore& aStore,CStreamDictionary& aStreamDic,const CApaApplication& aApp);
	IMPORT_C static void WriteRootStreamL(CPersistentStore& aStore,CStreamDictionary& aStreamDic,const TApaAppIdentifier& aAppId);
	IMPORT_C static TApaAppIdentifier ReadAppIdentifierL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic);
	IMPORT_C static void WriteAppIdentifierL(CStreamStore& aStore,CStreamDictionary& aStreamDic,const TApaAppIdentifier& aAppId);
	//
	// document management
	IMPORT_C CApaDocument* AddNewDocumentL(const TDesC& aDllFileName,TUid aDllUid=KNullUid); // Create and add a new (possibly embedded) document of the specified application. Creates a new CApaApplication if this is the first document of that type to be added to the application
	IMPORT_C CApaDocument* OpenNewDocumentL(CFileStore*& aStore,CStreamDictionary*& aStreamDic,const TDesC& aDocFullFileName,TUint aFileMode); // Open a file and restore the contained document
	IMPORT_C void DestroyDocument(CApaDocument* aDoc); // Removes a doc (identified by the object) from the list and destroys it. Also removes the app and closes the AppDll if appropriate.
	//
	// setter functions
	IMPORT_C void SetMainDocument(CApaDocument* aDocument);
	IMPORT_C void SetMainDocFileName(const TDesC& aMainDocFileName); // panics if the descriptor is too long
	//
	// accessor functions
	IMPORT_C TPtrC MainDocFileName()const;
	inline RFs& FsSession()const;
	inline CApaDocument* MainDocument()const;
	inline TPtrC TempFilePath()const;
	inline CApaAppFinder* AppFinder()const;
	//
	IMPORT_C ~CApaProcess();
protected:
	IMPORT_C CApaProcess(const RFs& aFs,CApaAppFinder& aAppFinder);
	IMPORT_C void ConstructL();
public:
	static TInt IdleRemoveApplications(TAny* aThis);
	void RemoveMarkedApplications();
private:
	CApaDll* AddAppDllL(const TDesC& aDllFileName,TUid aUid=KNullUid); // searches storage media for a dll with the correct name & uid, creates one and adds it to the array
	void RemoveAppDll(CApaDll* aDll);
	CApaDocument* CreateDocL(CApaDll* aApp);
	CApaDll* FindAppInListL(const TDesC& aAppFileName,TUid aUid)const; // returns NULL if not in list
	void DeleteAllDocs();
	void MarkApplicationForRemoval(CApaApplication* aApp);
private:
	CArrayFixFlat<TApaDllInfo>* iAppList; // array of apps in use
	CArrayFixFlat<CApaDocument*>* iDocList; // array of documents (1 main + n embedded)
	CApaDocument* iMainDoc;
	TFileName* iMainDocFileName;
	CApaAppFinder* iAppFinder;
	RFs iFsSession; // file server session for doc store
	CIdle* iApplicationRemover;
	};


class MApaEmbeddedDocObserver
	{
public:
	enum TExitMode {
		EKeepChanges,
		ERevertToSaved,
		ENoChanges,
		EEmpty
		};
public:
	virtual void NotifyExit(TExitMode aMode)=0; // called on completion of editing of an embedded document
	};


//// inlines ////

inline CApaApplication* CApaDocument::Application()const
	{ return iApplication; }

inline CApaProcess* CApaDocument::Process()const
	{ return iApaProcess; }

inline TBool CApaDocument::TCapability::CanDrawGlass()const
	{ return iCapability&ECanDrawGlass; }

inline TBool CApaDocument::TCapability::CanPrint()const
	{ return iCapability&ECanPrint; }

inline void CApaDocument::TCapability::SetCanDrawGlass()
	{ iCapability = iCapability|ECanDrawGlass; }

inline void CApaDocument::TCapability::SetCanPrint()
	{ iCapability = iCapability|ECanPrint; }

inline TPtrC CApaProcess::TempFilePath()const 
	{ return iAppFinder->TempPath(); }

inline RFs& CApaProcess::FsSession()const
	{ return (RFs&)iFsSession; }

inline CApaDocument* CApaProcess::MainDocument()const
	{ return iMainDoc; }

inline CApaAppFinder* CApaProcess::AppFinder()const 
	{ return iAppFinder; }

#endif
