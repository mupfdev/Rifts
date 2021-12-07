// GSMUSTOR.H
//
// Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
//


/**
 *
 * @file gsmustor.h  This file contains the header file of the CSmsSARStore.
 *
 */

#if !defined (__GSMUSTOR_H__)
#define __GSMUSTOR_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__S32STD_H__)
#include <s32std.h>
#endif

#include "etools.h"


const TInt KSARStoreUidValue=0x1000089d;
const TUid KSARStoreUid={KSARStoreUidValue};  //  Used for second uid of SAR stores


class RFs;
class CFileStore;
class RReadStream;
class RWriteStream;

class TSAREntry
	{
public:
	enum
		{
		ESmsSAREntryDescriptionLength=32
		};
public:
	IMPORT_C TSAREntry();
	inline TInt Reference() const;
	inline void SetReference(TInt aReference);
	inline TInt Total() const;
	inline void SetTotal(TInt aTotal);
	inline TInt Count() const;
	inline void SetCount(TInt aCount);
	inline TBool IsComplete() const;
	inline TInt Data1() const;
	inline void SetData1(TInt aData);
	inline TInt Data2() const;
	inline void SetData2(TInt aData);
	inline TInt Data3() const;
	inline void SetData3(TInt aData);
	inline TInt Data4() const;
	inline void SetData4(TInt aData);
	inline TPtrC Description1() const;
	inline void SetDescription1(const TDesC& aDescription);
	inline TPtrC Description2() const;
	inline void SetDescription2(const TDesC& aDescription);
	inline const TTime& Time() const;
	inline void SetTime(const TTime& aTime);

	inline TStreamId DataStreamId() const;
	inline void SetDataStreamId(TStreamId aStreamId);

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
	inline TBool IsDeleted() const;
	inline void SetIsDeleted(TBool aIsDeleted);
	inline TBool IsAdded() const; 
	inline void SetIsAdded(TBool aIsAdded); 

private:
	enum TSAREntryFlags
		{
		ESAREntryIsDeleted=0x01,
		ESAREntryIsAdded=0x02
		};
private:
	TInt iReference;  
	TInt iTotal;
	TInt iCount;
	TInt iData1;
	TInt iData2;
	TInt iData3;
	TInt iData4;
	TBuf<ESmsSAREntryDescriptionLength> iDescription1;  
	TBuf<ESmsSAREntryDescriptionLength> iDescription2;  
	TTime iTime;
	TStreamId iDataStreamId;
	TInt iFlags;  //  Not externalized
	friend class CSARStore; 
	};

class CSARStore : public CBase
	{
public:
	IMPORT_C void OpenL(const TDesC& aFullName,TUid aThirdUid);
	IMPORT_C void Close();
	IMPORT_C void CompactL();

	IMPORT_C const CArrayFix<TSAREntry>& Entries() const;
	IMPORT_C void PurgeL(const TTimeIntervalMinutes& aTimeIntervalMinutes,TBool aPurgeIncompleteOnly);
	IMPORT_C void PurgeL(TInt aKSegmentationLifetimeMultiplier,TBool aPurgeIncompleteOnly);
	IMPORT_C void DeleteEntryL(TInt aIndex);

	IMPORT_C void OpenFileLC();
	IMPORT_C void CloseFile();
	void DoCloseFile();

protected:
	IMPORT_C CSARStore(RFs& aFs);
	IMPORT_C ~CSARStore();

	IMPORT_C CFileStore& FileStore();
	IMPORT_C const CFileStore& FileStore() const;

	IMPORT_C void AddEntryL(const TSAREntry& aEntry);  //  Adds entry 
	IMPORT_C void ChangeEntryL(TInt aIndex,const TSAREntry& aNewEntry);  

	IMPORT_C TStreamId ExtraStreamId() const;
	IMPORT_C void SetExtraStreamIdL(TStreamId aExtraStreamId);

private:
	void DoOpenLC(const TDesC& aFullName,TUid aThirdUid);
	void DoDeleteEntryL(TInt aIndex);  //  Deletes stream but doesn't call iFileStore->CommitL()
	void InternalizeEntryArrayL(); 
	void ExternalizeEntryArrayL(); 
	void DoExternalizeEntryArrayL(); 
	void DoCommitAndCompactL();

private:
	enum
		{
		KNumStoreCommitsBeforeCompaction=16
		};

protected:
	RFs& iFs; ///< file server
private:
	CLASSNAMEDECL(CSARStore);
	CFileStore* iFileStore;
	CArrayFixFlat<TSAREntry> iEntryArray;
	TStreamId iExtraStreamId;  //  Used for any other data that needs persisting
	TInt iCommitCount;
	TPtrC iFullName;   ///< holds the name of the File Store
	TUid iThirdUid;
	};

#include "gsmustor.inl"

#endif // !defined __GSMUSTOR_H__

