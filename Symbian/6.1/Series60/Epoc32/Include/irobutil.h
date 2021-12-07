// IrObUtil.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#ifndef __IROBUTIL1__
#define __IROBUTIL1__


#include <e32std.h>

/*#include <Eikenv.h>
#include <eikcfdlg.h>	// FileSaveAs dlg
#include <eikfile.rsg>	// FileSaveAs dlg
#include <eikfsel.h>	// Folder selector class*/
#include <BAUTILS.H>	// NearestLanguageFile
#include <basched.h>
#include <coeutils.h>	// ConeUtils::FileExists
#include <apparc.h>		// CApaApplication::GenerateFileName
#include <apgcli.h>		// RApaLsSession   <-- data recognition.

#include <txtrich.h>	// Richtext
#include <utf.h>		// CharConv
#include <baclipb.h>	// Clipboard
// Ir
#include <obex.h>
// MS
#include <msvAPI.h>
#include <msvIDs.h>
#include <msvUIDs.h>
#include <msvSTD.hrh>






const TInt32 KUidMsgTypeIr			 =	0x100053A4;
///////////////////////////////////////////
// Class to allow an arbitrary number of filenames to be saves to a CMsvEntry
//
class CIrMtmFileNameExternaliser : public CBase
	{  
public:
	IMPORT_C	static	void ExternaliseAndCommit1FileNameL(CMsvEntry* aEntry, const TDesC16* aDes);
	IMPORT_C	static	void Internalise1FileNameL(CMsvEntry* aEntry, TDes16* aDes);
public:
	IMPORT_C	static  CIrMtmFileNameExternaliser* NewL(CMsvSession* aSession, TMsvId aId);
				CIrMtmFileNameExternaliser::~CIrMtmFileNameExternaliser();

				void InitialiseStoreL(TMsvId aId);
	IMPORT_C  	void ExternaliseFileNameL(const TDesC16* aFileName);
	IMPORT_C  	void CommitStoreL();
public:
	// Extract a list of filenames (added by shell) from the entry store.
	IMPORT_C	static   CDesC16Array* InternaliseFileNamesLC(CMsvStore& aMessageStore);
private:
	CIrMtmFileNameExternaliser(CMsvSession* aSession);
private:
	CMsvSession*		iSession;
	CMsvEntry*			iEntry;
	CMsvStore*			iMessageStore;
	RMsvWriteStream		iMessageWriteStream;
	TBool				iHaveCommitted;
	};

#endif // __IROBUTIL1__
