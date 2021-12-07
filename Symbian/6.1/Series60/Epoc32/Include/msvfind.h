// MSVFIND.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVFIND_H__)
#define __MSVFIND_H__

#if !defined(__MSVAPI_H__)
#include "msvapi.h"
#endif

#if !defined __MTCLBASE_H__
#include "mtclbase.h"
#endif

#if !defined(__MTMDEF_H__)
#include "mtmdef.h"
#endif

//**********************************
// TMsvFindResult
//**********************************
//
// Contains the result of a find operation for a particular entry
//

class TMsvFindResult
	{
public:
	IMPORT_C TMsvFindResult();
	IMPORT_C TMsvFindResult(TMsvPartList aPartList, TMsvId aId);
	//
public:
	TMsvPartList iPartList;
	TMsvId iId;
	};

//**********************************
// CMsvFindResultSelection
//**********************************
//
// A list of find operation results with an accessor to find  
// the position for a particular entry
//

class CMsvFindResultSelection : public CArrayFixFlat<TMsvFindResult>
	{
public:
	IMPORT_C CMsvFindResultSelection();
	//
public:
	IMPORT_C CMsvFindResultSelection* CopyL()  const;
	IMPORT_C CMsvFindResultSelection* CopyLC() const;
	IMPORT_C TInt Find(TMsvId aId) const;
	};

//**********************************
// TMsvFindOperationProgress
//**********************************
//
// Find operation progress
//

class TMsvFindOperationProgress
	{
public:
	IMPORT_C TMsvFindOperationProgress();
	//
public:
	TInt iError;
	TInt iCompleted;
	TInt iRemaining;
	TMsvId iCurrentId;
	};

class CClientMtmRegistry;
class CMsvChildMessages;

//**********************************
// CMsvFindOperation
//**********************************
//
// The find operation. Created by calling the relevant static function
// The results for all of these are added to the CMsvFindResultSelection which
// can be accessed via the accessor function GetFindResult
//

class CMsvFindOperation : public CMsvOperation
	{
public:
	IMPORT_C static CMsvFindOperation* FindInChildrenL(CMsvSession& aSession, const TDesC& aTextToFind, TMsvId aParentId, TMsvPartList aPartList, TRequestStatus& aObserverRequestStatus);
	IMPORT_C static CMsvFindOperation* FindInSelectionL(CMsvSession& aSession, const TDesC& aTextToFind, const CMsvEntrySelection& aSelection, TMsvPartList aPartList, TRequestStatus& aObserverRequestStatus);
	IMPORT_C ~CMsvFindOperation();
	//
	IMPORT_C const TDesC8& ProgressL();
	IMPORT_C const TDesC8& FinalProgress();
	//
	inline const CMsvFindResultSelection& GetFindResult() const;
	//
protected:
	IMPORT_C CMsvFindOperation(CMsvSession& aSession, const TDesC& aTextToFind, TMsvPartList aPartList, TRequestStatus& aObserverRequestStatus);
	IMPORT_C void ConstructFindInChildrenL(TMsvId aId);
	IMPORT_C void ConstructFindInSelectionL(const CMsvEntrySelection& aSelection);
	//
private:
	void ConstructL();
	//
	IMPORT_C void DoCancel();
	IMPORT_C void RunL();
	//
	void DoRunL();
	void FindL();
	void Complete(TInt aStatus);
	void StartL();
	//
	virtual TBool IsValid(const TMsvEntry& aEntry) const;
	//
private:
	enum { EMsvFindingText, EMsvExpandingFolders } iState;
	TBuf<KMsvMaxFindTextLength> iTextToFind;
	TMsvPartList iPartList;
	CMsvFindResultSelection* iFindResultSel;
	TPckgBuf<TMsvFindOperationProgress> iProgress;
	CMsvEntrySelection* iSelection;
	CClientMtmRegistry* iClientRegistry;
	CArrayPtrFlat<CBaseMtm>* iMtmArray;
	CMsvChildMessages* iChildMessages;
	TMsvId iCurrentId;
	TMsvEntry iEntry;
	};

#include "msvfind.inl"

#endif

