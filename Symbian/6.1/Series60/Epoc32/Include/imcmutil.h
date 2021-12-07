// IMCMUTIL.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved. 
// 

// Client MTM utilities for POP3, SMTP and IMAP4 protocols

#if !defined (__IMCMUTIL_H__)
#define __IMCMUTIL_H__

#if !defined (__MSVFTEXT_H__)
#include <msvftext.h>
#endif

#if !defined (__MIUTHDR_H__)
#include "miuthdr.h"
#endif

#if !defined (__MIUTDEF_H__)
#include "miutdef.h"
#endif

#ifdef __WINS__
_LIT(KMsvAutoSendExe, "c:\\system\\programs\\Autosend.dll");
const TInt KAutoSendMinHeapSize=0x1000;
const TInt KAutoSendMaxHeapSize=0x10000;
#elif __EPOC32__
_LIT(KMsvAutoSendExe, "Autosend.exe");
const TUid KMsvAutoSendExeUid = {0x1000A402}; //268477442
#endif

class CClientMtmRegistry;
class CImClientMTMUtils : public CBase
	{
public:
	IMPORT_C static CImClientMTMUtils* NewL();
	IMPORT_C ~CImClientMTMUtils();

	IMPORT_C void FindL(const TDesC& aTextToFind, CRichText& aRichText, CImHeader& aHeader, TMsvPartList aPartList, TMsvPartList& rReturnList);
	IMPORT_C TMsvPartList FindInHeaderL(const TDesC& aTextToFind, CImHeader& aHeader, TMsvPartList aPartList);
	IMPORT_C TMsvPartList FindInBodyL(const TDesC& aTextToFind, CRichText& aRichText, TMsvPartList aPartList);
private:
	void ConstructL();
	TBool FindInMessagePartRecipientL(const TDesC& aTextToFind,TMsvPartList aPartList,CDesCArray& aRecipients);

private:
	CMsvFindText* iFindText;
	};

class CImEmailAutoSend : public CActive
	{
public:
	static CImEmailAutoSend* NewL(CMsvSession& aSession,TMsvId aServiceId);
	static CImEmailAutoSend* NewLC(CMsvSession& aSession,TMsvId aServiceId);
	~CImEmailAutoSend();
	void SendOnNextConnectionL();
	TMsvId Service();
	void ChangeService(TMsvId aServiceId);
private:
	CImEmailAutoSend(CMsvSession& aSession,TMsvId aServiceId);
	void ConstructL();
	void RunL();
	void DoCancel();
	void LoadSMTPClientMtmL();
	void Reset();
private:
	CMsvSession& iSession;
	CClientMtmRegistry*	iClientRegistry;
	CBaseMtm* iBaseMtm;
	CMsvOperation* iOperation;
	CMsvEntrySelection* iSelection;
	TMsvId iServiceId;
	};

#endif 
