// MTMUIBAS.H
//
// Copyright (C) Symbian Ltd 1998
//

#if !defined(__MTMUIBAS_H__)
#define __MTMUIBAS_H__

#if !defined(__MSVSTD_H__)
#include <MSVSTD.H>
#endif
#if !defined(__MTCLBASE_H__)
#include <mtclbase.h>
#endif

// Forward references
class CMsvSession;
class CMsvOperation;
class CCoeEnv;

///////////////////////////////////
// CBaseMtmUi - MTMUi base API   //
///////////////////////////////////
class CBaseMtmUi : public CBase
	{
public:
	//  --- enums ---
	enum {EProgressStringMaxLen=255};
	//
	// --- Set up functionality ---
	IMPORT_C void SetPreferences(TUint aFlags);
	IMPORT_C TUint Preferences() const;
	//
	// --- Destruction ---
	IMPORT_C virtual ~CBaseMtmUi();
	//
	// --- Accessor functions ---
	inline TUid Type() const;
	inline CBaseMtm& BaseMtm() const;
	//
	// --- Functions NOT dependent on the current context ---
	IMPORT_C virtual CMsvOperation* CreateL(const TMsvEntry& aEntry, CMsvEntry& aParent, TRequestStatus& aStatus);
	//
	// --- Functions dependent on the current context ---
	virtual CMsvOperation* OpenL(TRequestStatus& aStatus) = 0; 
	virtual CMsvOperation* CloseL(TRequestStatus& aStatus) = 0;
	virtual CMsvOperation* EditL(TRequestStatus& aStatus) = 0;// Launches editor/settings dialog as appropriate  
	virtual CMsvOperation* ViewL(TRequestStatus& aStatus) = 0;// Launches viewer/settings dialog as appropriate  
	//
	// --- Actions upon message selections ---
	// --- Selections must be in same folder and all of the correct MTM type ---
	// --- Context may change after calling these functions ---
	virtual CMsvOperation* OpenL(TRequestStatus& aStatus, const CMsvEntrySelection& aSelection) = 0; 
	virtual CMsvOperation* CloseL(TRequestStatus& aStatus, const CMsvEntrySelection& aSelection) = 0;
	virtual CMsvOperation* EditL(TRequestStatus& aStatus, const CMsvEntrySelection& aSelection) = 0;// Launches editor/settings dialog as appropriate  
	virtual CMsvOperation* ViewL(TRequestStatus& aStatus, const CMsvEntrySelection& aSelection) = 0;// Launches viewer/settings dialog as appropriate  
	virtual CMsvOperation* CancelL(TRequestStatus& aStatus, const CMsvEntrySelection& aSelection) = 0;
	//
	// --- Deletion ---
	// --- Deletes entries from the current context, which must be a folder or service of the relevant MTM ---
	IMPORT_C virtual CMsvOperation* DeleteFromL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);//Deletes selection from current context
	// --- Un-deletes entries from the current context, which must be a folder or service of the relevant MTM ---
	IMPORT_C virtual CMsvOperation* UnDeleteFromL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);//Un-deletes selection from current context
	// --- Deletes service, which need not be the current context ---
	IMPORT_C virtual CMsvOperation* DeleteServiceL(const TMsvEntry& aService, TRequestStatus& aStatus); // default implementation simply delegates to the server
	//
	// --- Message responding ---
	virtual CMsvOperation* ReplyL(TMsvId aDestination, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus) = 0;
	virtual CMsvOperation* ForwardL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus) = 0;
	//
	// --- Copy and move functions ---
	// --- Context should be set to folder or entry of this MTM ---
	// --- Default implementations imply call the relevant CMsvEntry functions ---
	IMPORT_C virtual CMsvOperation* CopyToL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);// Context should be MTM folder/service to copy to
	IMPORT_C virtual CMsvOperation* MoveToL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus);// Context should be MTM folder/service to move to
	IMPORT_C virtual CMsvOperation* CopyFromL(const CMsvEntrySelection& aSelection, TMsvId aTargetId, TRequestStatus& aStatus);// Context should be MTM folder/service to copy from
	IMPORT_C virtual CMsvOperation* MoveFromL(const CMsvEntrySelection& aSelection, TMsvId aTargetId, TRequestStatus& aStatus);// Context should be MTM folder/service to move from
	//
	// --- Interpret transfer progress ---
	IMPORT_C virtual TInt DisplayProgressSummary(const TDesC8& aProgress) const;// Used for display operation summary (usually completed operations). Default implementation returns KErrNotSupported. 
	IMPORT_C virtual TInt GetProgress(const TDesC8& aProgress, TBuf<EProgressStringMaxLen>& aReturnString, TInt& aTotalEntryCount, TInt& aEntriesDone,
		TInt& aCurrentEntrySize, TInt& aCurrentBytesTrans) const;// Default implementation returns KErrNotSupported
	//	
	// --- RTTI functions ---
	IMPORT_C virtual TInt QueryCapability(TUid aCapability, TInt& aResponse);
	IMPORT_C virtual void InvokeSyncFunctionL(TInt aFunctionId, const CMsvEntrySelection& aSelection, TDes8& aParameter);
	IMPORT_C virtual CMsvOperation* InvokeAsyncFunctionL(TInt aFunctionId, const CMsvEntrySelection& aSelection, TRequestStatus& aCompletionStatus, 
		TDes8& aParameter);

protected:
	// --- Construction ---
	IMPORT_C CBaseMtmUi(CBaseMtm& aBaseMtm, CRegisteredMtmDll& aRegisteredMtmDll);
	IMPORT_C virtual void ConstructL();
	virtual void GetResourceFileName(TFileName& aFileName) const = 0;
	//
	// --- Utility functions ---
	IMPORT_C CMsvSession& Session() const;

protected:
	// --- Data ---
	CBaseMtm&			iBaseMtm;
	CCoeEnv*			iCoeEnv;
	TUint				iFlags;

private:
	// --- Data ---
	CRegisteredMtmDll&	iRegisteredMtmDll;
	TInt				iResourceFileOffset;
	};

#include "mtmuibas.inl"

#endif // __MTMUIBAS_H__
