// EIKDOC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKDOC_H__)
#define __EIKDOC_H__

#include <apparc.h>
#include <savenotf.h>

class CEikAppUi;
class CEikApplication;
class CApaWindowGroupName;

class CEikDocument : public CApaDocument
	{
public: // new functions
	virtual CEikAppUi* CreateAppUiL()=0;
	IMPORT_C virtual CFileStore* OpenFileL(TBool aDoOpen,const TDesC& aFilename,RFs& aFs);
	IMPORT_C void PrepareToEditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly);
	IMPORT_C void PrepareToEditL();
	IMPORT_C void SetAppFileMode(TUint aMode);
	IMPORT_C TUint AppFileMode() const;
	IMPORT_C virtual void UpdateTaskNameL(CApaWindowGroupName* aWgName);
	IMPORT_C const TApaAppCaption& AppCaption() const;
	IMPORT_C void SetChanged(TBool aHasChanged);
	IMPORT_C void SetEditStoreL(CStreamStore* aStore);
	inline CStreamStore* EditStore() const;
	IMPORT_C ~CEikDocument();
	IMPORT_C virtual void SaveL(MSaveObserver::TSaveType aSaveType);
public: // from CApaDocument
	IMPORT_C void NewDocumentL();
	IMPORT_C CFileStore* CreateFileStoreLC(RFs& aFs,const TDesC& aFileName);
	IMPORT_C void EditL(MApaEmbeddedDocObserver* aObserver,TBool aReadOnly=EFalse);
	IMPORT_C void PrintL(const CStreamStore& aSourceStore);
	IMPORT_C void SaveL();
	IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aStreamDic) const;
	IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aStreamDic);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TBool IsEmpty() const;
	IMPORT_C TBool HasChanged() const;
protected:
	IMPORT_C CEikDocument(CEikApplication& aApp);
private:
	void NullAppUi();
	// reserved functions from CApaDocument
	IMPORT_C virtual void Reserved_1();
	IMPORT_C virtual void Reserved_2();
protected:
	CEikAppUi* iAppUi;
	CStreamStore* iEditStore;
private:
	TBool iChanged;
	TUint iAppFileMode;
	//
	friend class CEikAppUi;
	};

#define iEikProcess ((CEikProcess*)Process())
#define iEikApplication ((CEikApplication*)Application())
#define KDefaultIconicDoorSize TSize(500,500)

//
// inlines
//

inline CStreamStore* CEikDocument::EditStore() const
	{ return(iEditStore); }

#endif

