// D32DBMS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
#if !defined(__D32DBMS_H__)
#define __D32DBMS_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#ifndef __S32STD_H__
#include <s32std.h>
#endif

// other classes referenced
class RFs;
class CDbObject;
class CDbRowConstraint;
class CDbCursor;
class CDbDatabase;
class CDbIncremental;
class CDbNotifier;
class TDbColumn;
class TDbColumnC;

// classes defined
class TDbCol;
class CDbColSet;
class TDbColSetIter;
class TDbKeyCol;
class CDbKey;
class TDbBookmark;
class TDbQuery;
class RDbHandleBase;
template<class T> class RDbHandle;
class RDbRowConstraint;
class RDbRowSet;
class RDbColReadStream;
class RDbColWriteStream;
class TDbWindow;
class RDbView;
template<class T> class TUnion;
class TDbLookupKey;
class TDbSeekKey;
template<TInt S> class TDbSeekMultiKey;
class RDbTable;
class CDbNames;
class RDbDatabase;
class RDbIncremental;
class RDbUpdate;
class RDbNotifier;
class RDbs;
class RDbNamedDatabase;
class RDbStoreDatabase;

//

const TInt KDbMaxName=0x40;
const TInt KDbMaxColName=KDbMaxName;
typedef TBuf<KDbMaxName> TDbName;
typedef TBufC<KDbMaxName> TDbNameC;
typedef TBuf<KDbMaxColName> TDbColName;
typedef TBufC<KDbMaxColName> TDbColNameC;

typedef TInt TDbColNo;
const TDbColNo KDbNullColNo=0;

const TInt KDbUndefinedCount=-1;
const TInt KDbUndefinedLength=-1;
const TInt KDbDefaultTextColLength=50;

enum TDbColType
	{
	EDbColBit,
	EDbColInt8,EDbColUint8,
	EDbColInt16,EDbColUint16,
	EDbColInt32,EDbColUint32,
	EDbColInt64,
	EDbColReal32,EDbColReal64,
	EDbColDateTime,
	EDbColText8,EDbColText16,
	EDbColBinary,
	EDbColLongText8,EDbColLongText16,
	EDbColLongBinary,
	EDbColText=EDbColText16,
	EDbColLongText=EDbColLongText16
	};

enum TDbTextComparison {EDbCompareNormal,EDbCompareFolded,EDbCompareCollated};

class TDbCol
	{
	friend class CDbColSet;
public:
	enum {ENotNull=0x01,EAutoIncrement=0x02};
public:
	inline TDbCol() {}
	IMPORT_C TDbCol(const TDesC& aName,TDbColType aType);
	IMPORT_C TDbCol(const TDesC& aName,TDbColType aType,TInt aMaxLength);
	static inline TBool IsLong(TDbColType aType);
private:
	inline TDbCol(const TDesC& aName);
public:
	TDbColType iType;
	TInt iMaxLength;
	TUint iAttributes;
	TDbColNameC iName;
	};
class CDbColSet : public CBase
	{
	friend class TDbColSetIter;
public:
	IMPORT_C CDbColSet();
	IMPORT_C static CDbColSet* NewL();
	IMPORT_C static CDbColSet* NewLC();
	IMPORT_C ~CDbColSet();
	inline const TDbCol& operator[](TDbColNo aCol) const;
	IMPORT_C const TDbCol* Col(const TDesC& aColName) const;
	IMPORT_C TDbColNo ColNo(const TDesC& aColName) const;
	inline TInt Count() const;
	inline void Clear();
	IMPORT_C CDbColSet& AddL(const TDbCol& aCol);
	IMPORT_C void Remove(const TDesC& aColName);
private:
	CArrayPakFlat<TDbCol> iColumns;
	};
class TDbColSetIter
	{
public:
	IMPORT_C TDbColSetIter(const CDbColSet& aColSet);
	inline operator TAny* () const;
	inline const TDbCol& operator*() const;
	inline const TDbCol* operator->() const;
	IMPORT_C TDbColSetIter& operator++();
	inline TDbColSetIter operator++(TInt);
	inline TDbColNo Col() const;
private:
	const TDbCol* iColumn;
	TInt iIndex;
	const CArrayPakFlat<TDbCol>* iArray;
	};

class TDbKeyCol
	{
public:
	enum TOrder {EAsc,EDesc};
public:
	inline TDbKeyCol() {}
	IMPORT_C TDbKeyCol(const TDesC& aName,TOrder anOrder=EAsc);
	IMPORT_C TDbKeyCol(const TDesC& aName,TInt aLength,TOrder anOrder=EAsc);
public:
	TOrder iOrder;
	TInt iLength;
	TDbColNameC iName;
	};
class CDbKey : public CBase
	{
public:
	enum {EUnique=0x01,EPrimary=0x02};
public:
	IMPORT_C CDbKey();
	IMPORT_C static CDbKey* NewL();
	IMPORT_C static CDbKey* NewLC();
	IMPORT_C ~CDbKey();
	IMPORT_C CDbKey& AddL(const TDbKeyCol& aKeyCol);
	IMPORT_C void Remove(const TDesC& aColName);
	IMPORT_C void Clear();
	inline TInt Count() const;
	inline const TDbKeyCol& operator[](TInt aCol) const;
	inline void MakeUnique();
	inline TBool IsUnique() const;
	inline void SetComparison(TDbTextComparison aComparison);
	inline TDbTextComparison Comparison() const;
	inline void MakePrimary();
	inline TBool IsPrimary() const;
private:
	CArrayPakFlat<TDbKeyCol> iKeys;
	TDbTextComparison iComparison;
	TInt iAttributes;
	};

class TDbBookmark
	{
	friend class RDbRowSet;
public:
	struct TMark
		{
		enum {ESize=8};
		TUint32 iMark[ESize];
		};
private:
	TMark iMark;
	};

class TDbQuery
	{
public:
	inline TDbQuery(const TDesC& aQuery,TDbTextComparison aComparison=EDbCompareNormal);
	inline const TDesC& Query() const;
	inline TDbTextComparison Comparison() const;
private:
	const TDesC& iQuery;
	TDbTextComparison iComparison;
	};

class RDbHandleBase
	{
public:
	inline RDbHandleBase();
	void Close();
protected:
	inline void Set(CDbObject* aObject);
	CDbObject& Object() const;
protected:
	CDbObject* iObject;
	};

template <class T>
class RDbHandle : public RDbHandleBase
	{
public:
	inline T* operator=(T* aT);
	inline T* operator->() const;
	inline T& operator*() const;
	inline T* operator()() const;
	};

class RDbRowConstraint
	{
	friend class RDbRowSet;
public:
	IMPORT_C TInt Open(const RDbRowSet& aView,TDbQuery aCriteria);
	IMPORT_C void Close();
private:
	RDbHandle<CDbRowConstraint> iConstraint;
	};

class RDbRowSet
	{
	friend class RDbRowConstraint;
	friend class RDbColReadStream;
	friend class RDbColWriteStream;
public:
	enum TPosition {EFirst,ENext,EPrevious,ELast,EBeginning,EEnd};
	enum TAccess {EUpdatable,EReadOnly,EInsertOnly};
	enum TDirection {EForwards,EBackwards};
	enum TAccuracy {EEnsure,EQuick};
public:
	IMPORT_C void Close();
	IMPORT_C void Reset();
//
	IMPORT_C CDbColSet* ColSetL() const;
	IMPORT_C TInt ColCount() const;
	IMPORT_C TDbColType ColType(TDbColNo aCol) const;
	IMPORT_C TDbCol ColDef(TDbColNo aCol) const;
//
	IMPORT_C TBool AtRow() const;
	IMPORT_C TBool AtBeginning() const;
	IMPORT_C TBool AtEnd() const;
//
	IMPORT_C TInt CountL(TAccuracy anAccuracy=EEnsure) const;
	IMPORT_C TBool IsEmptyL() const;
//
	IMPORT_C TBool GotoL(TPosition aPosition);
	inline void BeginningL();
	inline void EndL();
	inline TBool FirstL();
	inline TBool LastL();
	inline TBool NextL();
	inline TBool PreviousL();
//
	IMPORT_C TDbBookmark Bookmark() const;
	IMPORT_C void GotoL(const TDbBookmark& aMark);
//
	IMPORT_C TBool MatchL(const RDbRowConstraint& aConstraint);
	IMPORT_C TInt FindL(TDirection aDirection,TDbQuery aCriteria);
//
	IMPORT_C void GetL();
	IMPORT_C void InsertL();
	IMPORT_C void InsertCopyL();
	IMPORT_C void UpdateL();
	IMPORT_C void PutL();
	IMPORT_C void Cancel();
	IMPORT_C void DeleteL();
//
	inline TBool IsColNull(TDbColNo aCol) const;
	IMPORT_C TInt ColSize(TDbColNo aCol) const;
	IMPORT_C TInt ColLength(TDbColNo aCol) const;
//
	IMPORT_C TInt8 ColInt8(TDbColNo aCol) const;
	IMPORT_C TInt16 ColInt16(TDbColNo aCol) const;
	IMPORT_C TInt32 ColInt32(TDbColNo aCol) const;
	IMPORT_C TInt64 ColInt64(TDbColNo aCol) const;
	inline TInt ColInt(TDbColNo aCol) const;
	IMPORT_C TUint8 ColUint8(TDbColNo aCol) const;
	IMPORT_C TUint16 ColUint16(TDbColNo aCol) const;
	IMPORT_C TUint32 ColUint32(TDbColNo aCol) const;
	inline TUint ColUint(TDbColNo aCol) const;
	IMPORT_C TReal32 ColReal32(TDbColNo aCol) const;
	IMPORT_C TReal64 ColReal64(TDbColNo aCol) const;
	inline TReal ColReal(TDbColNo aCol) const;
	IMPORT_C TTime ColTime(TDbColNo aCol) const;
	IMPORT_C TPtrC8 ColDes8(TDbColNo aCol) const;
	IMPORT_C TPtrC16 ColDes16(TDbColNo aCol) const;
	IMPORT_C TPtrC ColDes(TDbColNo aCol) const;
//
	IMPORT_C void SetColNullL(TDbColNo aCol);
	inline void SetColL(TDbColNo aCol,TInt aValue);
	IMPORT_C void SetColL(TDbColNo aCol,TInt32 aValue);
	IMPORT_C void SetColL(TDbColNo aCol,TInt64 aValue);
	inline void SetColL(TDbColNo aCol,TUint aValue);
	IMPORT_C void SetColL(TDbColNo aCol,TUint32 aValue);
	IMPORT_C void SetColL(TDbColNo aCol,TReal32 aValue);
	IMPORT_C void SetColL(TDbColNo aCol,TReal64 aValue);
	IMPORT_C void SetColL(TDbColNo aCol,TTime aValue);
	IMPORT_C void SetColL(TDbColNo aCol,const TDesC8& aValue);
	IMPORT_C void SetColL(TDbColNo aCol,const TDesC16& aValue);
private:
	inline MStreamBuf* ColSourceL(TDbColNo aCol) const;
	inline MStreamBuf* ColSinkL(TDbColNo aCol);
	CDbCursor& CheckCol(TDbColNo aCol) const;
	TDbColumnC ColumnC(TDbColNo aCol,TDbColType aType) const;
	TDbColumn Column(TDbColNo aCol,TDbColType aType);
protected:
	RDbHandle<CDbCursor> iCursor;
	};

class RDbColReadStream : public RReadStream
	{
public:
	IMPORT_C void OpenL(const RDbRowSet& aView,TDbColNo aCol);
	IMPORT_C void OpenLC(const RDbRowSet& aView,TDbColNo aCol);
	};
class RDbColWriteStream : public RWriteStream
	{
public:
	inline RDbColWriteStream() {}
	inline RDbColWriteStream(const MExternalizer<TStreamRef> &anExternalizer);
	IMPORT_C void OpenL(RDbRowSet& aView,TDbColNo aCol);
	IMPORT_C void OpenLC(RDbRowSet& aView,TDbColNo aCol);
	};

class TDbWindow
	{
public:
	enum TUnlimited {EUnlimited=KMaxTInt};
	enum {ENone=0};
public:
	inline TDbWindow();
	inline TDbWindow(TUnlimited);
	IMPORT_C TDbWindow(TInt aForeSlots,TInt aRearSlots);
	inline TInt Size() const;
	inline TInt PreferredPos() const;
private:
	TInt iSize;
	TInt iPreferredPos;
	};
#if defined(__NO_CLASS_CONSTS__)
#define KDbUnlimitedWindow TDbWindow(TDbWindow::EUnlimited)
#else
const TDbWindow KDbUnlimitedWindow=TDbWindow(TDbWindow::EUnlimited);
#endif

class RDbView : public RDbRowSet
	{
public:
	IMPORT_C TInt Prepare(RDbDatabase& aDatabase,const TDbQuery& aQuery,TAccess anAccess=EUpdatable);
	IMPORT_C TInt Prepare(RDbDatabase& aDatabase,const TDbQuery& aQuery,const TDbWindow& aWindow);
	IMPORT_C TInt Prepare(RDbDatabase& aDatabase,const TDbQuery& aQuery,const TDbWindow& aWindow,TAccess anAccess);
	IMPORT_C TInt EvaluateAll();
	IMPORT_C TInt Evaluate();
	IMPORT_C void Evaluate(TRequestStatus& aStatus);
	IMPORT_C TBool Unevaluated() const;
	};

template <class T>
class TUnion			// implementation class
	{
public:
	inline operator const T&() const;
	inline const T& operator()() const;
	inline T& operator()();
	inline void Set(const T& aT);
private:
	TUint8 iRep[sizeof(T)];
	};
class TDbLookupKey		// implementation class
	{
public:
	struct SColumn
		{
		union
			{
			TInt32 iInt32;
			TUint32 iUint32;
			TUnion<TInt64> iInt64;
			TReal32 iReal32;
			TReal64 iReal64;
			TUnion<TTime> iTime;
			struct {const TText8* iPtr;TInt iLength;} iDes8;
			struct {const TText16* iPtr;TInt iLength;} iDes16;
			};
		TDbColType iType;
		};
public:
	inline TDbLookupKey();
	inline TInt Count() const;
	inline const SColumn* First() const;
	void Add(TInt aKey);
	void Add(TUint aKey);
	void Add(TInt64 aKey);
	void Add(TReal32 aKey);
	void Add(TReal64 aKey);
	void Add(TTime aKey);
	void Add(const TDesC8& aKey);
	void Add(const TDesC16& aKey);
private:
	SColumn& NextKey();
private:
	TInt iCount;
	SColumn iKey[1];	// at least one
	};

class TDbSeekKey
	{
	friend class RDbTable;
public:
	inline TDbSeekKey();
	inline TDbSeekKey(TInt aKey);
	inline TDbSeekKey(TUint aKey);
	inline TDbSeekKey(TInt64 aKey);
	inline TDbSeekKey(TReal32 aKey);
	inline TDbSeekKey(TReal64 aKey);
	inline TDbSeekKey(TTime aKey);
	inline TDbSeekKey(const TDesC8& aKey);
	inline TDbSeekKey(const TDesC16& aKey);
	IMPORT_C TDbSeekKey& Add(TInt aKey);
	IMPORT_C TDbSeekKey& Add(TUint aKey);
	IMPORT_C TDbSeekKey& Add(TInt64 aKey);
	IMPORT_C TDbSeekKey& Add(TReal32 aKey);
	IMPORT_C TDbSeekKey& Add(TReal64 aKey);
	IMPORT_C TDbSeekKey& Add(TTime aKey);
	IMPORT_C TDbSeekKey& Add(const TDesC8& aKey);
	IMPORT_C TDbSeekKey& Add(const TDesC16& aKey);
private:
	TDbLookupKey& Check();
protected:
	inline TDbSeekKey(TInt aKeys,TInt);
private:
	TInt iMaxKeys;
	TDbLookupKey iKey;
	};
template<TInt S>
class TDbSeekMultiKey : public TDbSeekKey
	{
public:
	inline TDbSeekMultiKey();
private:
	TDbLookupKey::SColumn iExtraKeys[S-1];
	};

class RDbTable : public RDbRowSet
	{
public:
	enum TComparison {ELessThan,ELessEqual,EEqualTo,EGreaterEqual,EGreaterThan};
public:
	IMPORT_C TInt Open(RDbDatabase& aDatabase,const TDesC& aName,TAccess anAccess=EUpdatable);
	inline TInt SetIndex(const TDesC& anIndex);
	inline TInt SetNoIndex();
	IMPORT_C TBool SeekL(const TDbSeekKey& aKey,TComparison aComparison=EEqualTo);
private:
	IMPORT_C TInt SetIndex(const TDesC* anIndex);
	};

class CDbNames : public CBase
	{
private:
	inline CDbNames();
public:
	static CDbNames* NewLC();
	~CDbNames();
	inline TInt Count() const;
	inline const TDesC& operator[](TInt anIndex) const;
	IMPORT_C void AddL(const TDesC& aName);
private:
	CArrayPakFlat<TDbNameC> iList;
	};
typedef CDbNames CDbTableNames,CDbIndexNames;

class RDbDatabase
	{
	friend RDbView;
	friend RDbTable;
	friend RDbIncremental;
	friend RDbUpdate;
	friend RDbNotifier;
public:
	struct TSize {TInt iSize;TInt iUsage;};
public:
	IMPORT_C void Close();
	IMPORT_C TInt Destroy();
//
	IMPORT_C TBool IsDamaged() const;
	IMPORT_C TInt Recover();
//
	IMPORT_C TInt UpdateStats();
	IMPORT_C TSize Size() const;
	IMPORT_C TInt Compact();
//
	IMPORT_C TInt ChangeSecurity(CSecurityDecryptBase* aKey,CSecurityEncryptBase* aNewKey);
//
	IMPORT_C TInt Begin();
	IMPORT_C TInt Commit();
	IMPORT_C void Rollback();
	IMPORT_C TBool InTransaction() const;
//
	inline TInt CreateTable(const TDesC& aName,const CDbColSet& aDef);
	inline TInt CreateTable(const TDesC& aName,const CDbColSet& aDef,const CDbKey& aPrimaryKey);
	IMPORT_C TInt DropTable(const TDesC& aName);
	IMPORT_C TInt AlterTable(const TDesC& aName,const CDbColSet& aNewDef);
	IMPORT_C TInt CreateIndex(const TDesC& aName,const TDesC& aTable,const CDbKey& aKey);
 	IMPORT_C TInt DropIndex(const TDesC& aName,const TDesC& aTable);
//
	IMPORT_C TInt Execute(const TDesC& aSql,TDbTextComparison aComparison=EDbCompareNormal);
//
	IMPORT_C CDbTableNames* TableNamesL() const;
	IMPORT_C CDbColSet* ColSetL(const TDesC& aName) const;
	IMPORT_C CDbIndexNames* IndexNamesL(const TDesC& aTable) const;
	IMPORT_C CDbKey* KeyL(const TDesC& aName,const TDesC& aTable) const;
private:
	IMPORT_C TInt CreateTable(const TDesC& aName,const CDbColSet& aColSet,const CDbKey* aPrimaryKey);
protected:
	RDbHandle<CDbDatabase> iDatabase;
	};

class RDbIncremental
	{
public:
	IMPORT_C void Close();
	IMPORT_C TInt Next(TInt& aStep);
	IMPORT_C void Next(TPckgBuf<TInt>& aStep,TRequestStatus& aStatus);
//
	IMPORT_C TInt Recover(RDbDatabase& aDatabase,TInt& aStep);
	IMPORT_C TInt Compact(RDbDatabase& aDatabase,TInt& aStep);
	IMPORT_C TInt DropTable(RDbDatabase& aDatabase,const TDesC& aTable,TInt& aStep);
	IMPORT_C TInt AlterTable(RDbDatabase& aDatabase,const TDesC& aTable,const CDbColSet& aNewDef,TInt& aStep);
	IMPORT_C TInt CreateIndex(RDbDatabase& aDatabase,const TDesC& aName,const TDesC& aTable,const CDbKey& aKey,TInt& aStep);
	IMPORT_C TInt DropIndex(RDbDatabase& aDatabase,const TDesC& aName,const TDesC& aTable,TInt& aStep);
	inline TInt Execute(RDbDatabase& aDatabase,const TDesC& aSql,TInt& aStep);
	IMPORT_C TInt Execute(RDbDatabase& aDatabase,const TDesC& aSql,TDbTextComparison aComparison,TInt& aStep);
	IMPORT_C TInt UpdateStats(RDbDatabase& aDatabase,TInt& aStep);
private:
	RDbHandle<CDbIncremental> iState;
	};

class RDbUpdate
	{
public:
	IMPORT_C TInt Execute(RDbDatabase& aDatabase,const TDesC& aSql,TDbTextComparison aComparison=EDbCompareNormal);
	IMPORT_C void Close();
//
	IMPORT_C TInt Next();
	IMPORT_C void Next(TRequestStatus& aStatus);
	IMPORT_C TInt RowCount() const;
private:
	RDbHandle<CDbIncremental> iUpdate;
	TPckgBuf<TInt> iRows;
	};

class RDbNotifier
	{
public:
	enum TEvent {EClose,EUnlock,ECommit,ERollback,ERecover};
public:
	IMPORT_C TInt Open(RDbDatabase& aDatabase);
	IMPORT_C void Close();
//
	IMPORT_C void NotifyUnlock(TRequestStatus& aStatus);
	IMPORT_C void NotifyChange(TRequestStatus& aStatus);
	IMPORT_C void Cancel();
private:
	RDbHandle<CDbNotifier> iNotifier;
	};

// Client-server databases

class RDbs : public RSessionBase
	{
public:
	IMPORT_C static TVersion Version();
	IMPORT_C TInt Connect();
//
	IMPORT_C void ResourceMark();
	IMPORT_C void ResourceCheck();
	IMPORT_C TInt ResourceCount();
	IMPORT_C void SetHeapFailure(RHeap::TAllocFail aType,TInt aRate);
private:
	TInt DoConnect();
	TInt SessionMessage(TInt aFunction);
	};

// Generic database implementation

class RDbNamedDatabase : public RDbDatabase
	{
public:
	enum TAccess {EReadWrite,EReadOnly};
public:
	IMPORT_C TInt Create(RFs& aFs,const TDesC& aDatabase,const TDesC& aFormat=TPtrC(),CSecurityEncryptBase* aKey=0);
	IMPORT_C TInt Replace(RFs& aFs,const TDesC& aDatabase,const TDesC& aFormat=TPtrC(),CSecurityEncryptBase* aKey=0);
//
	IMPORT_C TInt Open(RFs& aFs,const TDesC& aDatabase,const TDesC& aFormat=TPtrC(),CSecurityDecryptBase* aKey=0,TAccess aMode=EReadWrite);
	IMPORT_C TInt Open(RDbs& aDbs,const TDesC& aDatabase,const TDesC& aFormat=TPtrC(),CSecurityDecryptBase* aKey=0);
	};

// DBMS Store database implementation

const TInt KDbStoreMaxColumnLength=255;

class RDbStoreDatabase : public RDbDatabase
	{
public:
	IMPORT_C TStreamId CreateL(CStreamStore* aStore);
	IMPORT_C void OpenL(CStreamStore* aStore,TStreamId anId);
//
	IMPORT_C TStreamId CreateL(CStreamStore* aStore,CSecurityEncryptBase* aKey);
	IMPORT_C void OpenL(CStreamStore* aStore,TStreamId anId,CSecurityDecryptBase* aKey);
//
	IMPORT_C static void CompressL(CStreamStore& aStore,TStreamId aId);
	IMPORT_C static void DecompressL(CStreamStore& aStore,TStreamId aId);
	};

#include <d32dbms.inl>
#endif
