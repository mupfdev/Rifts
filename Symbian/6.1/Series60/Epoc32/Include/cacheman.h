// CACHEMAN.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//

#if !defined (__CACHEMAN_H__)
#define __CACHEMAN_H__

#include <mentact.h>
#include <msvstd.h>
#include <msvapi.h>

_LIT(KMiutWildCard, "*.*");

class CImFinder : public CMsgActive
	{
public:
	IMPORT_C void FindFirstL(TMsvId aRootEntry, TRequestStatus &aStatus);
	IMPORT_C ~CImFinder();
	IMPORT_C virtual void FindNextL(TRequestStatus &aStatus);
	void FindFirstL(const CMsvEntrySelection& aInitialSelection, TRequestStatus &aStatus);

	class CImEntryStack : public CBase
		{
	public:
		static CImEntryStack* NewL();
		~CImEntryStack();
		inline void PushL(TMsvId aId);
		inline TMsvId PopL();
		inline TBool Empty() const;
		inline void Reset();

	private:
		void ConstructL();

		CMsvEntrySelection* iFolders;
		};

protected:
	void ConstructL();
	CImFinder(CMsvEntry& aEntry);

private:
	void DoRunL();

	virtual void AddChildEntriesL() = 0;
	virtual TBool IsRequiredEntryType(TUid aEntryType) const = 0;

protected:
	CImEntryStack* iEntryStack;
	CMsvEntry& iCurrentEntry;

private:
	enum TImmfState
		{
		EImmfEntryFound,
		EImmfFindingEntry,
		EImmfNothingFound
		};

	TImmfState iState;
	};


class CImMessageFinder : public CImFinder
	{
public:
	IMPORT_C static CImMessageFinder* NewL(CMsvEntry& aEntry);
	IMPORT_C static CImMessageFinder* NewLC(CMsvEntry& aEntry);
	
protected:
	virtual void AddChildEntriesL();
	virtual TBool IsRequiredEntryType(TUid aEntryType) const;

	CImMessageFinder(CMsvEntry& aEntry);
	};


class CImEntryFinder : public CImFinder
	{
public:
	IMPORT_C static CImEntryFinder* NewL(CMsvEntry& aEntry);
	IMPORT_C static CImEntryFinder* NewLC(CMsvEntry& aEntry);
	
protected:
	virtual void AddChildEntriesL();
	virtual TBool IsRequiredEntryType(TUid aEntryType) const;

	CImEntryFinder(CMsvEntry& aEntry);
	};


class CImMessageCounter : public CImFinder
	{
public:
	IMPORT_C static CImMessageCounter* NewL(CMsvEntry& aEntry);
	IMPORT_C static CImMessageCounter* NewLC(CMsvEntry& aEntry);
	IMPORT_C TInt Count();
	
protected:
	virtual void AddChildEntriesL();
	virtual TBool IsRequiredEntryType(TUid aEntryType) const;

	CImMessageCounter(CMsvEntry& aEntry);

private:
	TInt iCount;
	};


class CImPruneMessage : public CMsgActive
	{
public:
	IMPORT_C static CImPruneMessage* NewL(CMsvEntry& aEntry, RFs& aFs);
	IMPORT_C static CImPruneMessage* NewLC(CMsvEntry& aEntry, RFs& aFs);

	IMPORT_C void StartL(TMsvId aMessageEntry, TRequestStatus &aStatus);
	~CImPruneMessage();
	
private:
	CImPruneMessage(CMsvEntry& aEntry, RFs& aFs);
	void ConstructL();
	void DoRunL();
	void DoComplete(TInt& );
	void DoCancel();
	void PruneEntryL();

private:
	enum TImPruningState
		{
		EImPruneUpdatingEntry,
		EImPruneUpdatingFirstEntry,
		EImPruneFindingEntry
		};

	TImPruningState iState;

	CMsvEntry& iCurrentEntry;
	RFs& iFs;
	CImEntryFinder* iEntryFinder;
	CFileMan* iFileManager;
	TMsvId iRootEntryId;
	CMsvOperation* iChangeOperation;
	};

struct TImCacheManagerProgress
	{
public:
	TInt iTotalMessages;
	TInt iMessagesProcessed;
	};

class CImCacheManager : public CMsvOperation
	{
public:
	IMPORT_C void StartL(TMsvId aRootEntry, TRequestStatus &aStatus);
	IMPORT_C void StartL(const CMsvEntrySelection& aSelection, TRequestStatus &aStatus);
	IMPORT_C ~CImCacheManager();
	IMPORT_C const TDesC8& ProgressL();
	IMPORT_C void DoCancel();

protected:
	IMPORT_C void ConstructL();
	IMPORT_C CImCacheManager(CMsvSession& aSession, TRequestStatus& aObserverRequestStatus);

	IMPORT_C void RunL();

private:
	// Override this function to filter the currently selected message (iCurrentEntry).
	// Return TRUE if the current entry is to be pruned.
	virtual TBool Filter() const = 0;

	void DoRunL();

	// Remove the store from the currently selected entry
	inline void PruneMessageL();
	
protected:
	CMsvEntry* iCurrentEntry;

private:
	CMsvSession& iSession;
	CImMessageFinder* iMessageFinder;
	CImMessageCounter* iMessageCounter;
	CMsvOperation* iDeleteOperation;

	TImCacheManagerProgress iProgress;
	TRequestStatus* iReport;

	enum TImcmState
		{
		EImcmLookingForMessage,
		EImcmPruningMessages,
		EImcmCountingMessages,
		EImcmSkippingPrune
		};

	TMsvId iRootEntry;
	TImcmState iState;
	TPckgBuf<TImCacheManagerProgress> iProgressBuf;

	CMsvEntrySelection* iMessagesToPrune;
	};

#endif