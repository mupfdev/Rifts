// HLPMODEL.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
#ifndef __HLPMODEL_H
#define __HLPMODEL_H

// System includes
#include <e32std.h>
#include <badesca.h>	// For MDesCArray
#include <txtmrtsr.h>	// For MRichTextStoreResolver
#include <gdi.h>		// For MPictureFactory
#include <d32dbms.h>

// Help model includes
#include <hlpconstants.h>

// Classes referenced
class CRichText;
class CHlpDatabase;
class CHlpFileEntry;
class CHlpSQLSearch;
class TCoeHelpContext;
class CParaFormatLayer;
class CCharFormatLayer;

// Typedefs
typedef CArrayPtrFlat<CHlpDatabase> CHlpDatabases;
typedef CArrayPtrFlat<CHlpFileEntry> CHlpFileList;


//
// Client API to handle messages from the Help Model
//
class MHlpModelObserver
	{
public: // TInt aEvent should be a named enum
	virtual void HandleModelEventL(TInt aEvent) = 0;
	};

//
// Internal API to handle events reported by the search engine
//
class MHlpDbObserver
	{
public: // TInt aEvent should be a named enum
	virtual void HandleDbEventL(TInt aEvent) = 0;
	};

//
// Search types (these should be named, but I can't break SC. Inherited from previous
// author of help model).
//
enum
	{
	EIndexList,
	ECategoryList,
	ETopicListForCategory,
	ETopicListForCategoryUID,
	EContextSearch,
	EIndexSearch,
	EQuickSearch,
	EFullTextSearch,
	ETopicIdSearch
	};

//
// Search progress responses (this should be scoped as members of MHlpModelObserver
// and should also be named, but I can't break SC. Inherited from previous
// author of help model).
//
enum
	{
	ENoRecordsFound,
	ESearchInProgress,
	ESearchComplete
	};

//
// Search progress responses (ditto for naming and scoping)
//
enum
	{
	ECategoryListAvailable,		// Category list
	ECategoryListNoneFound,
	ESearchListAvailable,		// Text searches
	ESearchListNoneFound,
	ETopicListAvailable,		// Category expansion
	ETopicListNoneFound,
	EIndexListAvailable,		// Index list
	EIndexListNoneFound,
	EIndexSearchListAvailable,	// Topic list from index phrase
	EIndexSearchListNoneFound,
	ETopicAvailable,			// Topic text
	ETopicNotFound,
	EModelSearchInProgress,
	EHlpSearchCancelled
	};



///////////////////////////////////////////////////////////////////////////////////////
// ----> CHlpItem - representing an individual item in the help file
///////////////////////////////////////////////////////////////////////////////////////
class CHlpItem : public CBase
	{
public:
	static CHlpItem* NewL(const TDesC& aTitle, TUint32 aId, TUid aCategoryId, TUid aHelpFileUid);
	static CHlpItem* NewLC(const TDesC& aTitle, TUint32 aId, TUid aCategoryId, TUid aHelpFileUid);
	static CHlpItem* NewLC(const TDesC& aTitle, TUint32 aId, TUid aHelpFileUid);
	IMPORT_C ~CHlpItem();

public: // Access
	inline TUid CategoryUid() const { return iCategoryUid; }
	inline TUid HelpFileUid() const { return iHelpFileUid; }
	inline TUint32 Id() const { return iId; }
	inline const TDesC& Title() const { return *iTitle; }

public: // These should not be public, but I can't break SC (these were inherited from
		// the previous author.
	HBufC* iTitle;
	TUint32 iId;

private:
	friend class CHlpList; // Needed for searching
	CHlpItem(TUint32 aId);
	CHlpItem(TUint32 aId, TUid aHelpFileUid);
	CHlpItem(TUint32 aId, TUid aCategoryId, TUid aHelpFileUid);
	void ConstructL(const TDesC& aTitle);

private: // Meta data required for correct restoration of topics
	TUid iCategoryUid;
	TUid iHelpFileUid;
	};



///////////////////////////////////////////////////////////////////////////////////////
// ----> MHlpTitleArray 
///////////////////////////////////////////////////////////////////////////////////////
class MHlpTitleArray : public MDesCArray
	{
public:
	virtual TUint32 At(TInt aIndex) const = 0;
	};



///////////////////////////////////////////////////////////////////////////////////////
// ----> CHlpList 
///////////////////////////////////////////////////////////////////////////////////////
class CHlpList : public CBase, public MHlpTitleArray
	{
public: // Static construct / destruct
	IMPORT_C static CHlpList* NewL();
	IMPORT_C static CHlpList* NewLC();
	IMPORT_C ~CHlpList();

public: // From MDesCArray
	IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;

public:
	// 'At' returns topic Id, but this function is next to useless because you can't
	// uniquely identify a help topic by topic id alone. You need to know 3 things:-
	// a) topic id, 2) category id, 3) help file uid. This information is all
	// encapsulated in CHlpItem so help app authors should use 'Item' instead.
	IMPORT_C TUint32 At(TInt aIndex) const;
	IMPORT_C CHlpItem* Item(TInt aIndex) const;
	IMPORT_C TInt Find(TUint32 aId);
	IMPORT_C void Reset();
	IMPORT_C void AppendL(CHlpItem* aItem);
 
	void MoveL(CHlpList& aDestinationList);

private: // 2nd phase constructor
	void ConstructL();

private:
	// This is the array of help items that were located as a result of
	// performing a search.
	CArrayPtrFlat<CHlpItem>* iList;
	};



///////////////////////////////////////////////////////////////////////////////////////
// ----> CHlpTopic 
///////////////////////////////////////////////////////////////////////////////////////
class CHlpTopic : public CBase
	{
public:
	IMPORT_C static CHlpTopic* NewL();
	IMPORT_C static CHlpTopic* NewLC();
	IMPORT_C ~CHlpTopic();

public: 
	// This function will not behave as expected in the case where it is used to 
	// restore rich text that includes pictures. Instead, only the text and markup
	// will be restored. Help App authors should use 'CHlpModel::LoadTopic' instead.
	// I can't remove this as it would break S&BC.
	IMPORT_C void RestoreL(RDbView* aView);
	
	IMPORT_C CRichText* TopicText();
	IMPORT_C TDesC& TopicTitle();
	IMPORT_C TDesC& Category();

	inline CParaFormatLayer* ParaFormatLayer() const { return iGlobalParaFormatLayer; }
	inline CCharFormatLayer* CharFormatLayer() const { return iGlobalCharFormatLayer; }

private:
	void ConstructL();

private:
	friend class CHlpModel;

	TUint32 iTopicId;
	TBuf<KMaxTitleColumn> iTopicTitle;
	TBuf<KMaxTitleColumn> iCategory;

	CRichText* iTopicText;
	CParaFormatLayer* iGlobalParaFormatLayer;  
	CCharFormatLayer* iGlobalCharFormatLayer; 
	};




///////////////////////////////////////////////////////////////////////////////////////
// ----> CHlpModel 
///////////////////////////////////////////////////////////////////////////////////////
class CHlpModel : public CBase, public MHlpDbObserver, public MPictureFactory, public MRichTextStoreResolver
	{
public: // Construct / destruct
	IMPORT_C static CHlpModel* NewL(RFs& aFs, MHlpModelObserver* aObserver);
	IMPORT_C static CHlpModel* NewLC(RFs& aFs, MHlpModelObserver* aObserver);
	IMPORT_C ~CHlpModel();

public:	// Opens all the help files in \System\Help
	IMPORT_C void OpenL();
	IMPORT_C void CloseL();

public: // Opens specific help files
	IMPORT_C void OpenFileL(const TDesC& aFileName);
	IMPORT_C void CloseFileL(const TDesC& aFileName);

public: // Specialized searching
	IMPORT_C void ContextSearchL(TCoeHelpContext& aContext);
	IMPORT_C void CategoryUIDSearchL(TUid aCategoryUID);
	IMPORT_C void TopicSearchL(const CHlpItem& aHelpItem);
	IMPORT_C void IndexSearchL(const CHlpItem& aHelpItem);

		// Generic searching
	IMPORT_C void SearchL(TInt aType, TUint32 aId);
	IMPORT_C void SearchL(TInt aType, HBufC* aCriterion=NULL);
	IMPORT_C void SearchL(TInt aType, const TDesC& aCriterion);

public: // Cancel EFullTextSearch types - will return KErrArgument if not the correct type
	IMPORT_C TInt CancelSearch();

public: // Assumes that the search has already been performed and that the view is valid
	IMPORT_C void LoadTopicL(CRichText& aRichText, TDes& aTitle);
	IMPORT_C void LoadTopicL(CRichText& aRichText);
	IMPORT_C void LoadTopicL(CHlpTopic* aTopic);
	IMPORT_C void LoadListL(CHlpList* aList);
	IMPORT_C void CategoryListL(CDesCArray* aList);

public: // FROM MPictureFactory
	void NewPictureL(TPictureHeader& aHdr,const CStreamStore& aDeferredPictureStore) const;

public: // FROM MRichTextStoreResolver
	IMPORT_C const CStreamStore& StreamStoreL(TInt aPos) const;

public:
	// Check to see if any of the databases have matching meta data
	IMPORT_C TInt MatchUidL(TUid aUid);

	// Replace the current observer with another
	IMPORT_C void SetObserver(MHlpModelObserver* aObserver);

private: // Internal search API
	void DoSearchL(TInt aType, const TDesC& aCriterion);
	void DoNextSearchL();
	void ResetReadyForSearch();
	void ResetViews();
	void SetCriterionL(const TDesC& aCriterion);

private: // Event management
	void HandleDbEventL(TInt aEvent);
	void ReportEventToObserverL(TInt aEvent);

private: // Misc internal functions
	inline CHlpDatabase* CurrentDatabase() const;
	inline TInt DatabaseCount() const;
	inline void SetSearchType(TInt aSearchType);
	inline TInt CurrentSearchType() const;
	RDbView* CurrentView() const;
	TBool DiskPresent(TInt aDrive) const;
	CHlpFileList* BuildListForDriveLC(TDriveUnit aDrive, RFs& aFsSession) const;

private:
	CHlpModel(RFs& aFs, MHlpModelObserver& aObserver);
	void ConstructL();

private: // Member data
	RFs& iFsSession;
	
	// This is required in order to restore rich text pictures from the database
	CStreamStore* iCurrentRichTextStore;
	
	// Creates our SQL string based upon the search type and criteria
	CHlpSQLSearch* iSearch;

	// An array of all the help files currently available
	CHlpDatabases* iDatabases;

	// Receives help model notifications as various actions are performed
	MHlpModelObserver* iObserver;

	// Were any matching results found for this search
	TBool iFound;

	// What was being searched for
	HBufC* iCriterion;

	// What type of search was being performed
	TInt iSearchType;

	// Which database are we currently searching
	TInt iCurrentDb;

	// Transient category Uid used when creating category lists
	TUid iTransientCategoryUid;
 	
	// The results of a search
	CHlpList* iResultsList;
	};





///////////////////////////////////////////////////////////////////////////////////////
// ----> CHlpModel (inlines)
///////////////////////////////////////////////////////////////////////////////////////
inline TInt CHlpModel::DatabaseCount() const
	{
	return iDatabases->Count();
	}
inline void CHlpModel::SetSearchType(TInt aSearchType)
	{
	iSearchType = aSearchType;
	}
inline CHlpDatabase* CHlpModel::CurrentDatabase() const
	{
	return iDatabases->At(iCurrentDb);
	}
inline TInt CHlpModel::CurrentSearchType() const
	{
	return iSearchType;
	}



#endif

