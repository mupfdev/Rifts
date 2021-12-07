// DBWRITER.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
#ifndef __DBWRITER_H__
#define __DBWRITER_H__

#include <d32dbms.h>
#include <e32std.h>
#include <s32file.h>
#include <bautils.h>
#include <txtrich.h>
#include <txtfmlyr.h>
#include <txtmrtsr.h>
#include <gdi.h>

// User includes
#include "hlpconstants.h"

// Db writer constants
const TInt KTopicTblTopicTitle = 1;
const TInt KTopicTblCategoryTitle = 2;
const TInt KTopicTblTopicText = 3;
const TInt KTopicTblTopicMarkup = 4;
const TInt KTopicTblSynonym = 5;
const TInt KTopicTblTopicId = 6;
const TInt KTopicTblCategoryUID = 7;

const TInt KIndexTblIndex = 1;
const TInt KIndexTblIndexId = 2;

const TInt KTopicIndexTblTopicId = 1;
const TInt KTopicIndexTblIndexId = 2;
const TInt KTopicIndexTblCategoryUID = 3;
const TInt KTopicIndexTblTopicTitle = 4;

const TInt KContextTblContext = 1;
const TInt KContextTblTopicId = 2;

const TInt KImageTblImageId = 1;
const TInt KImageTblImage = 2;

// DML statements used in creating the database tables and indices
_LIT(KHlpDMLTopicTable,			"CREATE TABLE Topic (TopicTitle CHAR(120), Category CHAR(120), TopicText LONG VARCHAR, TopicMarkup LONG VARBINARY, Synonym CHAR(200), TopicId UNSIGNED INTEGER, CategoryUID UNSIGNED INTEGER)");

// IndexeId's are unique on a per-helpfile basis, ie. all indexId's in one help file are unique.
_LIT(KHlpDMLIndexTable,			"CREATE TABLE Index (Index CHAR(120), IndexId UNSIGNED INTEGER)");

// TopicId's are unique within a helpfile but not across a help file
_LIT(KHlpDMLTopicIndexTable,	"CREATE TABLE TopicIndex (TopicId UNSIGNED INTEGER, IndexId UNSIGNED INTEGER, CategoryUID UNSIGNED INTEGER, TopicTitle CHAR(120))");

_LIT(KHlpDMLContextTable,		"CREATE TABLE Context (Context CHAR(30), TopicId UNSIGNED INTEGER)");
_LIT(KHlpDMLImageTable,			"CREATE TABLE Image (ImageId UNSIGNED INTEGER, Image LONG VARBINARY)");

_LIT(KHlpDMLTopicTableIdx,		"CREATE UNIQUE INDEX TopicIdx ON Topic (TopicId)");
_LIT(KHlpDMLIndexTableIdx,		"CREATE UNIQUE INDEX IndexIdx ON Index (IndexId)");
_LIT(KHlpDMLTopicIndexTableIdx, "CREATE UNIQUE INDEX TopicIndexIdx ON TopicIndex (IndexId, TopicId)");
_LIT(KHlpDMLContextTableIdx,	"CREATE UNIQUE INDEX ContextIdx ON Context (Context)");
_LIT(KHlpDMLImageTableIdx,		"CREATE UNIQUE INDEX ImageIdx ON Image (ImageId)");

// DDL statements used in opening tables for writing
_LIT(KHlpSQLTopicTable,			"SELECT * FROM Topic");
_LIT(KHlpSQLIndexTable,			"SELECT * FROM Index");
_LIT(KHlpSQLTopicIndexTable,	"SELECT * FROM TopicIndex");
_LIT(KHlpSQLContextTable,		"SELECT * FROM Context");
_LIT(KHlpSQLImageTable,			"SELECT * FROM Image");

// enum for selecting a table for writing to
enum
	{
	ETopicTable,
	EIndexTable,
	ETopicIndexTable,
	EContextTable,
	EImageTable
	};


class CHlpTable;

// CHlpDbWriter class: creates the store and the database, and provides the interface to write to the file
class CHlpDbWriter : public CBase
	{
public:
	IMPORT_C	~CHlpDbWriter();
	IMPORT_C	static CHlpDbWriter* NewL(RFs& aFs);
	IMPORT_C	static CHlpDbWriter* NewLC(RFs& aFs);
public:
	IMPORT_C	void CreateFileL(const TDesC& aFileName);
	IMPORT_C	void CreateDatabaseL();
	IMPORT_C	void CompressDatabaseL();
	IMPORT_C	void SetDatabaseUidL(TUid& aUid);
	IMPORT_C	void CloseFileL();
public:
	IMPORT_C	void AddBitmapL(TInt aBitmapId);
	IMPORT_C	TBool IsBitmapStored(TInt aBitmapId) const;
	IMPORT_C	TInt BitmapCount() const;
	IMPORT_C	TInt BitmapIdForIndex(TInt aIndex) const;
public:
	IMPORT_C	void BeginTransaction();
	IMPORT_C	void CommitTransaction();
public:
	IMPORT_C	CHlpTable* TopicTable();
	IMPORT_C	CHlpTable* IndexTable();
	IMPORT_C	CHlpTable* TopicIndexTable();
	IMPORT_C	CHlpTable* ContextTable();
	IMPORT_C	CHlpTable* ImageTable();
	IMPORT_C	void SetUidL(TUid aUid);
private:
	void DoCreateDatabaseL();
	CHlpTable* DoOpenTableL(TInt aTable);
	void DoOpenTablesL();
	void StoreUidsL();
	void StoreStreamDictionaryL();
private:
	CHlpDbWriter(RFs& aFs);
	void ConstructL();
private:
	RFs& iFs;
	TFileName iFileName;

	RDbStoreDatabase iDatabase;
	CArrayFixFlat<TUid>* iUids;
	CArrayPtrFlat<CHlpTable>* iTables;
	CArrayFixFlat<TUid>* iImagesAlreadyStored;

	CPermanentFileStore* iStore;
	CStreamDictionary* iDictionary;
	};

class THlpStoreResolver : public MRichTextStoreResolver
	{
public:
	virtual const CStreamStore& StreamStoreL(TInt aPos) const;
	CStreamStore* iStore;
	};

// CHlpRowSet class: abstract class for accessing database tables
class CHlpRowSet : public CBase
	{
public:
	CHlpRowSet(RDbView* aView);
	IMPORT_C	virtual ~CHlpRowSet();
	IMPORT_C	TBool AtRow();
	IMPORT_C	TBool AtBeginning();	
	IMPORT_C	TBool AtEnd();
	IMPORT_C	TBool FirstL();
	IMPORT_C	TBool LastL();
	IMPORT_C	TInt  CountL();
public:
	IMPORT_C	void NextL();
	IMPORT_C	void PreviousL();
public:
	IMPORT_C	TDbColNo MapColNameToColNo(const TDbCol& aCol);
	IMPORT_C	TDbColNo MapColNameToColNo(const TDesC& aName);
	IMPORT_C	CDbColSet* ColSet();

	IMPORT_C	RDbView* View();
private:
	RDbView* iView;
	};

// CHlpView class: concrete class used for accessing database tables (for test code)
class CHlpView : public CHlpRowSet
	{
public:
	IMPORT_C	static CHlpView* NewL(RDbView* aView);
	IMPORT_C	static CHlpView* NewLC(RDbView* aView);
	~CHlpView();
public:
	inline void SetPictureFactory(MPictureFactory* aPictureFactory) {iPictureFactory=aPictureFactory;};
public:
	IMPORT_C	void GetTextL(TDbColNo aCol, TDes& aText);
	IMPORT_C	void GetRichTextL(TDbColNo aTextCol, TDbColNo aMarkupCol, CRichText& aRichText);
	IMPORT_C	void GetValL(TDbColNo aCol, TUint32& aValue);
	IMPORT_C	void GetL();
private:
	void GetMarkupL(CRichText& aRichText, TDbColNo aMarkupCol);
private:
	CHlpView(RDbView* aView);
	void ConstructL();
private:
	THlpStoreResolver iStoreResolver;
	MPictureFactory *iPictureFactory;
	TBool iHasRows;
	};

// CHlpTable class: concrete class used for writing to database tables
class CHlpTable : public CHlpRowSet
	{
public:
	IMPORT_C	static CHlpTable* NewL(RDbView* aView);
	IMPORT_C	static CHlpTable* NewLC(RDbView* aView);
	~CHlpTable();
public:
	IMPORT_C	void InsertL();
	IMPORT_C	void PutL();
public:
	IMPORT_C	void SetColL(TDbColNo aCol, const TDesC& aText);
	IMPORT_C	void SetColL(TDbColNo aTextCol, TDbColNo aMarkupCol, CRichText& aRichText);
	IMPORT_C	void SetColL(TDbColNo aTextCol, CRichText& aRichText);
	IMPORT_C	void SetColL(TDbColNo aCol, TUint32 aValue);
	IMPORT_C	void SetColL(TDbColNo aCol, const CFbsBitmap& aBitmap);
private:
	void SetMarkupL(CRichText& aRichText, TDbColNo aMarkupCol);
	void SetLongTextL(const TDesC& aText, TDbColNo aLongTextCol);
private:
	CHlpTable(RDbView* aView); 
	void ConstructL();
	};

#endif
