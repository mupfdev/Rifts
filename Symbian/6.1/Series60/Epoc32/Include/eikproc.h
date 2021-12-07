// EIKPROC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKPROC_H__)
#define __EIKPROC_H__

#if !defined(__APPARC_H__)
#include <apparc.h>
#endif

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

class CFileStore;
class CEikDocument;
class CApaAppFinder;

class CEikProcess : public CApaProcess
	{
public:
	enum TLastUsedFile
		{
		ELastOpenFile,
		ELastCreatedFile
		};
public:
	static CEikProcess* NewL(const RFs& aFs);
	IMPORT_C TPtrC CommandTailEnd() const;
	IMPORT_C TFileName MainDocFolder() const;
	IMPORT_C void SetLastUsedFileL(TLastUsedFile aType,const TDesC& aFileName) const;
	IMPORT_C TFileName LastUsedFileL(TLastUsedFile aType) const;
	IMPORT_C void SetMainStore(CFileStore* aMainStore);
	IMPORT_C CFileStore* MainStore() const;
	IMPORT_C void AppFromDocL(TDes& aLibraryName,const TDesC& aDocumentName) const;
	IMPORT_C void SaveToDirectFileStoreL(CEikDocument* aDoc,const TFileName* aNewFileName=NULL);
	IMPORT_C void SaveToDirectFileStoreL(CEikDocument* aDoc,const TFileName* aNewFileName,TBool aReopen,TFileName* aTempFile=NULL);
	IMPORT_C ~CEikProcess();
private:
	CEikProcess(const RFs& aFs,CApaAppFinder& aAppFinder);
	void GetLibraryNameL(TDes& aLibraryName,const CFileStore& aDocStore,const CStreamDictionary& aStreamDic) const;
	void OpenNewFileL(const TFileName* aNewFileName,const TParse& aNewFilePath);
	CDictionaryStore* OpenMainAppIniFileLC() const;
private:
	TPtrC iCommandTailEnd;
	CFileStore* iMainStore;
	};

#endif
