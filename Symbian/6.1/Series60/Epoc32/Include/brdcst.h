// BRDCST.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__BRDCST_H__)
#define __BRDCST_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

enum {EBrdGlobalDomainUid=0x10001468};

class RBrdBroadcastServerSession : public RSessionBase
	{
public:
	RBrdBroadcastServerSession();
	void ConstructL(TInt aMaximumNumberOfSimultaneousServerRequests, TBool aSimulateMemoryAllocationFailure);
	TVersion Version() const;
	void SendBroadcast(TUid aBroadcastUid, TUid aDomainUid);
	void ReceiveBroadcast(TUid aBroadcastUid, TUid aDomainUid, TRequestStatus& aRequestStatus);
	void CancelReceiveBroadcast(TUid aBroadcastUid, TUid aDomainUid);
	TInt NumberOfSessions() const;
private:
	TInt CreateSession(TInt aMaximumNumberOfSimultaneousServerRequests);
	static void StartServerL(TBool aSimulateMemoryAllocationFailure);
	};

class CBrdBroadcastServerSession : public CBase
	{
public:
	IMPORT_C static CBrdBroadcastServerSession* NewL(TInt aMaximumNumberOfSimultaneousServerRequests);
	IMPORT_C static CBrdBroadcastServerSession* NewL(TInt aMaximumNumberOfSimultaneousServerRequests, TBool aSimulateMemoryAllocationFailure); // setting aSimulateMemoryAllocationFailure to ETrue only has an effect in DEBUG builds of the server
	IMPORT_C static CBrdBroadcastServerSession* NewLC(TInt aMaximumNumberOfSimultaneousServerRequests);
	IMPORT_C static CBrdBroadcastServerSession* NewLC(TInt aMaximumNumberOfSimultaneousServerRequests, TBool aSimulateMemoryAllocationFailure); // setting aSimulateMemoryAllocationFailure to ETrue only has an effect in DEBUG builds of the server
	IMPORT_C virtual ~CBrdBroadcastServerSession();
	IMPORT_C TVersion Version() const;
	IMPORT_C void SendBroadcast(TUid aBroadcastUid, TUid aDomainUid);
	IMPORT_C void ReceiveBroadcast(TUid aBroadcastUid, TUid aDomainUid, TRequestStatus& aRequestStatus);
	IMPORT_C void CancelReceiveBroadcast(TUid aBroadcastUid, TUid aDomainUid);
	IMPORT_C TInt NumberOfSessions() const;
private:
	CBrdBroadcastServerSession();
	void ConstructL(TInt aMaximumNumberOfSimultaneousServerRequests, TBool aSimulateMemoryAllocationFailure);
private:
	RBrdBroadcastServerSession iBroadcastServerSession;
	};

class CBrdBroadcastServerSessionActiveWrapper : public CActive
	{
public:
	IMPORT_C ~CBrdBroadcastServerSessionActiveWrapper();
	IMPORT_C void ReceiveBroadcast();
protected:
	IMPORT_C CBrdBroadcastServerSessionActiveWrapper(TInt aPriority, CBrdBroadcastServerSession& aBroadcastServerSession, TUid aBroadcastUid, TUid aDomainUid);
	inline CBrdBroadcastServerSession& BroadcastServerSession() {return iBroadcastServerSession;}
	inline TUid BroadcastUid() {return iBroadcastUid;}
	inline TUid DomainUid() {return iDomainUid;}
private:
	// from CActive
	IMPORT_C virtual void DoCancel();
	IMPORT_C virtual void RunL();
	// new
	virtual void HandleBroadcastReceiptL()=0;
private:
	CBrdBroadcastServerSession& iBroadcastServerSession;
	TUid iBroadcastUid;
	TUid iDomainUid;
	TAny* iSpareForFutureUse;
	};

#endif

