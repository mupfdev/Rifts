// MultiRead.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

// define the multiple resource file reader class
// for use in MultiRead1 and MultiRead2 examples

#ifndef __MultiRead_H
#define __MultiRead_H

class CMultipleResourceFileReader : public CBase
	{
public:
	// construct/destruct
	~CMultipleResourceFileReader();
	static CMultipleResourceFileReader* NewLC();
	// add resource file
	void AddResourceFileL(const TDesC& aName, TInt aVersion);
	HBufC8* AllocReadLC(TInt aResourceId);
private:
	// construct/destruct
	void ConstructL();
private:
	CArrayFixFlat<RResourceFile>* iResourceFiles;
	};

// construct/destruct

CMultipleResourceFileReader* CMultipleResourceFileReader::NewLC()
	{
	CMultipleResourceFileReader* self=new (ELeave) CMultipleResourceFileReader;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

void CMultipleResourceFileReader::ConstructL()
	{
	iResourceFiles=new (ELeave) CArrayFixFlat<RResourceFile> (2);
		// new array of resource files
		// typically two in an application, so use granularity 2
	}

CMultipleResourceFileReader::~CMultipleResourceFileReader()
	{
	if (iResourceFiles)
		{
		for (TInt i=0; i < iResourceFiles->Count(); i++)
			(*iResourceFiles)[i].Close(); // close each resource file
		delete iResourceFiles; // and destroy container
		}
	}

// manipulate resource files and resources

void CMultipleResourceFileReader::AddResourceFileL(const TDesC& aName, TInt aVersion)
	{
	_LIT(KAddingResourceFile,"Adding resource file %S, version %d: will be file %d\n");
	console->Printf(KAddingResourceFile,
			&aName, aVersion, iResourceFiles->Count()
			);
	RResourceFile file;
	file.OpenL(fsSession,aName); // open resource file
	TRAPD(error,file.ConfirmSignatureL(aVersion)); // confirm its signature
	if (error!=KErrNone)
		{
		file.Close();
		User::Leave(error);
		}
	TRAP(error,iResourceFiles->AppendL(file))
	if (error!=KErrNone)
		{
		file.Close();
		User::Leave(error);
		}
	return;
	}

HBufC8* CMultipleResourceFileReader::AllocReadLC(TInt aResourceId)
	{
	_LIT(KReadingResource,"Reading resource %08X\n");
	_LIT(KOwnedByFile,"   Owned by file %d\n");

	console->Printf(KReadingResource,aResourceId);
	for (TInt i=0; i < iResourceFiles->Count(); i++)
		{ // scan all resource files to find owner
		RResourceFile& file=(*iResourceFiles)[i]; // get resource file
		if (!file.OwnsResourceId(aResourceId))
			continue; // continue if not owner
		console->Printf(KOwnedByFile,i);
		return file.AllocReadLC(aResourceId);
				// return resource from owning file (if present)
		}
	User::Leave(KErrNotFound);
	return 0; // can never be executed, but keeps compiler happy
	}

#endif
