// CNTDB.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
#ifndef __CNTDB_H__
#define __CNTDB_H__

// System includes
#include <e32base.h>
#include <d32dbms.h>
#include <cntdef.h>
#include <cntdbobs.h>
#include <s32file.h>
#include <badesca.h>
#include <versit.h>
#include <collate.h>

// Classes referenced
class RFs;
class RFile;
class CBufStore;
class CCnaConverterList;
//
class CCntFilter;
class CFoundMatches;
class CTextFieldMinimal;
class CContentType;
class CContactGroup;
class CContactItem;
class CContactItemField;
class CContactItemFieldSet;
class CContactItemFieldDef;
class CContactItemPlusGroup;
class CContactDateField;
class CContactDatabase;
class CContactSrvSession;
class CPrivConverter;
class CContactPhoneParser;
class CPrivItemTableColSet;
class CPrivFindViewColSet;
class CPrivateChangeNotifier;
class CPrivateChangeEventNotifier;
class CCntIdleSorter;
class CSortArray;

// Constants
const TInt KMaxContactTextSeperator=4;
const TInt KTextFieldMinimalLength=64;

const TInt KMajorVersion=1;
const TInt KMinorVersion=0;
const TInt KBuildNumber=40;



//
// Classes used for compact 
//

class MContactUiCompactObserver
	{
public:
	virtual void Step(TInt aStep)=0;
	virtual void HandleError(TInt aError)=0;
	};

class MContactUiActive
	{
public:
	virtual void Cancel()=0;
	virtual void SetObserver(MContactUiCompactObserver *aObserver)=0;
	virtual TInt StepsTogo() const=0;
	virtual TInt Step()=0;
	virtual TInt Error() const=0;
private:
	IMPORT_C virtual void MContactUiActive_Reserved1();
	};

class CContactActiveBase : public CBase, public MContactUiActive
	{
public:
	~CContactActiveBase();
	void SetObserver(MContactUiCompactObserver *aObserver);
	void Cancel();
	TInt StepsTogo() const;
	TInt Step();
	TInt Error() const;
protected:
	void ConstructL();
	static TInt CompactCallBack(TAny *aThis);
protected:
	MContactUiCompactObserver *iObserver;
	RDbIncremental iDbInc;
	CIdle *iIdle;
	TInt iStep;
	TInt iError;
	};

class CContactActiveCompress : public CContactActiveBase
	{
public:
	void ConstructL(RDbNamedDatabase &aDataBase);
	};

class CContactActiveRecover : public CContactActiveBase
	{
public:
	void ConstructL(RDbNamedDatabase &aDataBase);
	};



/**
 * An item within a text definition.
 *
 * A <code>TContactTextDefItem</code> has a field type and an optional
 * separator string with a maximum length of 4 characters. See also class
 * <code>CContactTextDef</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class TContactTextDefItem
	{
public:
	IMPORT_C TContactTextDefItem();
	IMPORT_C TContactTextDefItem(TFieldType aFieldType);
	IMPORT_C TContactTextDefItem(TFieldType aFieldType, const TDesC &aSeperator);
public:
	TFieldType iFieldType;
	TBuf<KMaxContactTextSeperator> iSeperator;
	};

/**
 * Defines a way of grouping together fields to form a string which
 * represents a contact item.
 *
 * A text definition is an array of text definition items
 * (<code>TContactTextDefItem</code>s).An example of a function which
 * uses a text definition to build up a string from a contact item is
 * <code>CContactDatabase::ReadContactTextDefL()</code>. When creating
 * the string, this function searches the item for fields whose type
 * matches one of the fields specified in the text definition. The
 * contents of the first matching field of each type found in the item
 * are read into the string. These strings may be separated using a field
 * separator, which is also specified in the text definition. A separator
 * is not appended to the last field used to make up the string it is
 * only inserted when there is a following non-empty field.In addition to
 * this, the text definition may also contain a fallback field type. This
 * is used when none of a contact item's fields specified in the text
 * definition contain any text. If the item's fallback field contains no
 * text either, or if the fallback field type's value is
 * <code>KUidContactFieldNone</code>, the text is read from the first
 * non-empty field in the item.A contact database can have a default text
 * definition which is set using
 * <code>CContactDatabase::SetTextDefinitionL()</code>. This may be
 * overriden using the variants of
 * <code>CContactDatabase::ReadContactTextDefL()</code> which take a
 * <code>CContactTextDef*</code> argument.<code>CContactTextDef</code> is
 * derived from <code>CArrayFixFlat<TContactTextDefItem></code>, so all
 * relevant functions can be used, e.g. to add and remove elements.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactTextDef : public CArrayFixFlat<TContactTextDefItem>
	{
	friend class CContactDatabase;
	friend class CContactTables;
public:
	CContactTextDef();
	IMPORT_C static CContactTextDef* NewL();
	IMPORT_C static CContactTextDef* NewLC();
	IMPORT_C void SetFallbackField(TFieldType iFieldType);
	IMPORT_C TFieldType FallbackField() const;
	IMPORT_C const TBool ExactMatchOnly();
	IMPORT_C void SetExactMatchOnly(TBool aExactMatchOnly);
private:
	TFieldType iFallbackFieldType;
	TBool iExactMatchOnly;//Default to EFalse cause ReadInTextDef to only match the chosen fields and not attempt a matchall
	};

/**
 * A view definition for a contact item.
 *
 * When reading or opening a contact item using the
 * <code>CContactDatabase</code> class, a view definition may be
 * specified to indicate which field data should be retrieved. See for
 * instance <code>CContactDatabase::ReadContactL()</code>.A view
 * definition for a contact item contains an array of field types, a use
 * (<code>CContactItemViewDef::TUse</code>) and a mode
 * (<code>CContactItemViewDef::TMode</code>). The use indicates whether
 * the field types contained in the view definition should be included in
 * or excluded from the view. The mode indicates whether fields with the
 * hidden attribute should be included or excluded.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactItemViewDef : public CBase
	{
public:
	/** Include or exclude specified fields. */
	enum TUse 
			{ 
			EIncludeFields, /** Include specified fields in the view.*/
			EMaskFields		/** Exclude specified fields from the view.*/
			};	
	/** Include or exclude hidden fields.*/
	enum TMode 
			{ 
			EIncludeHiddenFields,	/** Include hidden fields in the view.*/
			EMaskHiddenFields		/** Exclude hidden fields from the view.*/
			};
public:
	IMPORT_C static CContactItemViewDef* NewL(TUse aUse, TMode aMode);
	IMPORT_C static CContactItemViewDef* NewLC(TUse aUse, TMode aMode);
    inline TUid operator[](TInt aIndex) const;
    IMPORT_C TInt Find(const CContentType &aContentType) const;
    IMPORT_C TInt Find(TFieldType aFieldType) const;
    inline TInt Count() const;
    inline void Reset();
	IMPORT_C void AddL(TFieldType aFieldType);
	IMPORT_C void Remove(TFieldType aFieldType);
	IMPORT_C void Remove(TInt aIndex);
	inline TUse Use() const;
	inline void SetUse(TUse aUse);
	inline TMode Mode() const;
	inline void SetMode(TMode aMode);
	IMPORT_C TBool Contains(const CContactItem& aItem);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;	
	IMPORT_C TBool MatchesAll() const;
private:
	CContactItemViewDef(TUse aUse,TMode aMode);
private:
    CArrayFixFlat<TUid> iFieldTypes;
	TUse iUse;
	TMode iMode;
	};

/**
 * The view definition specifies a subset of fields to be loaded when
 * reading a contact item.
 *
 * A default view definition is owned by the contact database. It is set
 * using <code>CContactDatabase::SetViewDefinitionL()</code> and is used
 * in calls to <code>CContactDatabase::ReadContactL()</code>,
 * <code>ReadContactLC()</code> and <code>ReadContactAndAgentL()</code>
 * when no view definition is specified.The view definition owns the item
 * view definition (see the <code>CContactItemViewDef</code> class),
 * which stores the view definition's field types, use and mode.The
 * following functions prototyped in class <code>CContactViewDef</code>
 * have not been implemented: <code>Groups()</code>, <code>AddL()</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactViewDef : public CBase
	{
public:
	IMPORT_C static CContactViewDef* NewL();
	IMPORT_C static CContactViewDef* NewLC();
	IMPORT_C static CContactViewDef* NewL(CContactItemViewDef* aItemDef);
	IMPORT_C static CContactViewDef* NewLC(CContactItemViewDef* aItemDef);
	IMPORT_C ~CContactViewDef();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C CContactItemViewDef& ItemDef() const;
	IMPORT_C CContactIdArray& Groups() const;
	inline void AddL(TFieldType aFieldType);
private:
	CContactViewDef();
	void ConstructL(CContactItemViewDef* aItemDef);
private:
	CContactItemViewDef* iItemDef;
//	CContactIdArray* iGroupIds; // unused for now
	};

/**
 * Iterates through the sorted contact items in a contact database.
 *
 * A value of <code>KNullContactId</code> is returned by the iterator if
 * a requested contact item cannot be found.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class TContactIter
	{
public:
	IMPORT_C TContactIter(CContactDatabase &aDatabase);
	IMPORT_C TContactItemId FirstL();
	IMPORT_C TContactItemId NextL();
	IMPORT_C TContactItemId PreviousL();
	IMPORT_C TContactItemId LastL();
	IMPORT_C void GotoL(TContactItemId aContactId);
	IMPORT_C void Reset();
private:
	void GotoIndexL(TInt aPos);
private:
	CContactDatabase &iDatabase;
	TContactItemId iCursorId;
	};

/**
 * Specifies the mixin protocol for an asynchronous find observer.
 *
 * An object which implements this protocol is passed to the asynchronous
 * find functions defined in class <code>CContactDatabase</code>,
 * (<code>FindAsyncL()</code> and <code>FindInTextDefAsyncL()</code>).
 * The observer would typically notify the user of the progress of the
 * operation.
 *
 * @since 5.0
 * @lib ""
 */
class MIdleFindObserver
	{
public:
	/**
	  *
	  * Asynchronous find observer callback.
	  *
	  * If an observer is supplied to
	  * <code>CContactDatabase::FindAsyncL()</code> or
	  * <code>FindInTextDefAsyncL()</code>, this callback function is called
	  * by <code>CIdle::RunL()</code> when nothing of a higher priority can be
	  * scheduled. It is called for every 16 items searched to give the
	  * application a chance to update its search status. The implementation
	  * of this function might typically test for and handle errors and
	  * retrieve information about the progress of the search. This
	  * information may be retrieved using functions provided by the
	  * <code>CIdleFinder</code> class.
	  *
	  */
	virtual void IdleFindCallback()=0;
	};

struct SFindInTextDefWordParser
	{
public:
	/**
	  * Initialises the search string and the word array to the values
	  * specified.
	  *
	  * @since     5.0
	  * @param     "const TDesC *aSearchString"
	  *            Pointer to the input string to be parsed.
	  * @param     "CDesCArray *aWordArray"
	  *            Pointer to the array to which words parsed from the
	  *            input string should be added.
	  */
	inline SFindInTextDefWordParser(const TDesC *aSearchString, CDesCArray *aWordArray) : iSearchString(aSearchString), iWordArray(aWordArray) {};
public:
	const TDesC *iSearchString;
	CDesCArray *iWordArray;
	};


/**
 * Gives information about the progress of an asynchronous contact
 * database search, and can be used to get the results of the search.
 *
 * An instance of this class is returned by calls to
 * <code>CContactDatabase::FindAsyncL()</code> and
 * <code>CContactDatabase::FindInTextDefAsyncL()</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CIdleFinder : public CIdle
	{
public:
	~CIdleFinder();
	IMPORT_C TBool IsComplete() const;
	IMPORT_C CContactIdArray *TakeContactIds();
	IMPORT_C TInt Error() const;
private:
	friend class CContactDatabase;
	static CIdleFinder *NewL(CContactDatabase &aContactDatabase, const TDesC& aText, const CContactItemFieldDef *aFieldDef, MIdleFindObserver *aObserver);
	static CIdleFinder *NewL(CContactDatabase &aContactDatabase, const MDesCArray* aFindWords,const CContactTextDef* aTextDef, MIdleFindObserver *aObserver, const TCallBack &aWordParserCallback);
	void DoCancel();
	void Start();
	static TInt CallbackL(TAny *aSelf);
	TInt doFindL();
	void ConstructL(const TDesC *aText, const MDesCArray* aFindWords, const TCallBack *aWordParserCallback);
	TBool ScanForMatch(const TDesC &aFieldText,const TDesC &aFindText, CFoundMatches *aFoundMatches) const;
	TBool CheckFindL(const CContactItemFieldSet *aFieldSet);
	TBool CheckFindL(RDbView& aView);
	CIdleFinder(CContactDatabase &aContactDatabase, const CContactItemFieldDef *aFieldDef, const CContactTextDef* aTextDef, MIdleFindObserver *aObserver);
	void doConstructFindViewsL();
	void doAppendFieldsToSearchStringL(TInt aFieldDef,TInt aNoFields,HBufC* aOrderFields);
	TInt ApproximateSizeOfSearchString();
private:
enum TAsyncFindState
		{
		EFindInBlobFinished				=0x00000001,
		EFindInIdentityFinished			=0x00000002,
		EFindInEmailFinished			=0x00000004,
		EFindInTextDefFinished			=0x00000008
		};
private:
	class TIdentityTableColSet
	{
	public:
		TDbColNo iParentIdColNo;
		TDbColNo iFirstNameColNo;
		TDbColNo iLastNameColNo;
		TDbColNo iCompanyNameColNo;
		TDbColNo iIdentityTypeColNo;
		TDbColNo iIdentityAttsColNo;
	};
private:
	CContactDatabase *iContactDatabase;
	CContactIdArray *iIdsFound;
	TBool iOwnsIds;
	CDesCArray* iFindWords;
	CDesCArray* iFindWords2;
	HBufC *iText;
	HBufC *iOriginalText;//without *..*
	const CContactItemFieldDef* iFieldDef;
	const CContactTextDef* iTextDef;
	MIdleFindObserver *iObserver;
	TInt iError;
	TCallBack iWordParserCallback;
	TInt iFindFlags;
	TInt iNoIdentitySearchColumns;
	TInt iFindState;
	//Async Find views
	RDbView iEmailFindView;
	RDbView iIdentityFindView;
	//identity Table Columns
	TIdentityTableColSet iIdentityTableCols;
	};

/**
 * Base class used in the derivation of <code>CContactDatabase</code>.
 *
 * It has no user accessible functions.
 *
 * @since 5.0
 * @lib ""
 */
class MContactDbPrivObserver
	{
public:
	virtual void HandleDatabaseEventL(RDbNotifier::TEvent)=0;
	virtual void HandleDatabaseEventL(const TContactDbObserverEvent &aEvent)=0;
	};


class MContactSortObserver
	{
public:
	virtual void HandleSortEventL(TInt aContactsSorted, TInt aContactsTotal)=0;
	};


/**
 * A database of contact items.
 *
 * Contact items can be added to and removed from the database and items
 * in the database can be opened or read. To edit an item, the item must
 * first be opened. Changes to the item can then be committed to the
 * database using <code>CommitContactL()</code>. Committing can only take
 * place to an open item. Reading an item provides read only access to
 * it.When deleting a contact item, note that each item has an access
 * count. The item cannot be fully deleted unless its access count is
 * zero. This is to prevent contact items which have been synchronised
 * with a PC scheduler application for example from being deleted. Also,
 * if the item is a template, it cannot be deleted if other items are
 * based on it.More than one contact database can exist on an EPOC
 * device, but there is always a single default contact database. The
 * default database is the database which is loaded by default when the
 * Contacts application starts up. Its filename is contacts.cdb. The
 * default database can be moved between drives, but must always be
 * stored in the \system\data\ folder.The <code>CContactDatabase</code>
 * class implements searching and sorting. It also provides separate
 * phone number matching functions. Phone number matching provides a high
 * speed method of indexing and looking up phone numbers. This is
 * primarily intended for looking up caller IDs on incoming calls. Before
 * looking up phone numbers, the index must be created. This only needs
 * to be done once, when the contact database is opened. From then on,
 * the index is automatically maintained by the database server. Index
 * creation is started by a call to <code>InitLoadPhoneMatchesL()</code>.
 * Then it is updated using calls to <code>LoadPhoneMatchesL()</code>.The
 * database owns speed dial information. This is a mapping between a
 * single digit integer and a telephone number. There may be up to 9
 * speed dial telephone numbers; each of them belongs to a contact item
 * in the database if a contact item is deleted, its speed dial mapping
 * is removed.The following functions defined in class
 * <code>CContactDatabase</code> are not currently supported. If called,
 * they leave with <code>KErrNotSupported</code>.<code>ReplacePrefL()</c-
 * ode><code>ReadPrefL()</code><code>CreatePrefL()</code>
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactDatabase : public CBase, public MContactDbPrivObserver
	{
	friend class TContactIter;
	friend class CContactActiveRecover;
	friend class CIdleFinder;
	friend class CCntIdleSorter;
	friend class CContactLocalView;
	friend class CContactTables;
public:
	class TSortPref
		{
	public:
		enum TOrder {EAsc,EDesc};
	public:
		inline TSortPref();
		inline TSortPref(TFieldType aFieldType,TOrder aOrder=EAsc);
		void ExternalizeL(RWriteStream& aStream) const;
		void InternalizeL(RReadStream& aStream);
	public:
		TOrder iOrder;
		TFieldType iFieldType;
		};
	enum TOptions 
  		{
  		EDefault=0x0,
		EIncludeX =0x01,
  		ETTFormat =0x02,
		EExcludeUid=0x04,
		EDecreaseAccessCount=0x08,
		EImportSingleContact=0x10,
		EIncreaseAccessCount=0x20,
		ELocalTime=0x40
  		};
	enum TThreadAccess {ESingleThread,EMultiThread};
	enum TSortDataSource
		{
		ENoOrder,
		EUsesIdentityTableOnly,
		EUsesAllTables
		};
public:
	IMPORT_C static CContactDatabase* OpenL(TThreadAccess aAccess=ESingleThread);
	IMPORT_C static CContactDatabase* OpenL(const TDesC& aFileName,TThreadAccess aAccess=ESingleThread);
	IMPORT_C static CContactDatabase* CreateL(TThreadAccess aAccess=ESingleThread);
	IMPORT_C static CContactDatabase* CreateL(const TDesC& aFileName,TThreadAccess aAccess=ESingleThread);
	IMPORT_C static CContactDatabase* ReplaceL(TThreadAccess aAccess=ESingleThread);
	IMPORT_C static CContactDatabase* ReplaceL(const TDesC& aFileName,TThreadAccess aAccess=ESingleThread);
	IMPORT_C static TBool DatabaseDrive(TDriveUnit &aDriveUnit);
	IMPORT_C static TBool FindContactFile(TDes &aFileName);
	inline static TInt NullUidValue();
	IMPORT_C static void SetDatabaseDriveL(TDriveUnit aDriveUnit, TBool aCopy=ETrue);
	IMPORT_C static void GetDefaultNameL(TDes &aDes);
	IMPORT_C static void DeleteDefaultFileL();
	IMPORT_C ~CContactDatabase();

	IMPORT_C void SetViewDefinitionL(CContactViewDef* aView);
	IMPORT_C void SetTextDefinitionL(CContactTextDef* aView);
	IMPORT_C const CContactTextDef* TextDefinition() const;
	IMPORT_C TInt CountL();
	IMPORT_C void SetDbViewContactType(const TUid aUid);
	IMPORT_C TUid GetDbViewContactType() const;

	
	IMPORT_C TContactItemId AddNewContactL(CContactItem& aContact);
		
	IMPORT_C CContactItem* CreateContactGroupL(TBool aInTransaction=EFalse);
	IMPORT_C CContactItem* CreateContactGroupLC(TBool aInTransaction=EFalse);
	IMPORT_C CContactItem* CreateContactGroupL(const TDesC& aGroupLabel,TBool aInTransaction=EFalse);
	IMPORT_C CContactItem* CreateContactGroupLC(const TDesC& aGroupLabel,TBool aInTransaction=EFalse);
	IMPORT_C CContactItem* CreateContactCardTemplateL(const TDesC& aTemplateLabel,TBool aInTransaction=EFalse);
	IMPORT_C CContactItem* CreateContactCardTemplateLC(const TDesC& aTemplateLabel,TBool aInTransaction=EFalse);
	IMPORT_C CContactItem* CreateContactCardTemplateL(const CContactItem* aTemplate,const TDesC& aTemplateLabel,TBool aInTransaction=EFalse);
	IMPORT_C CContactItem* CreateContactCardTemplateLC(const CContactItem* aTemplate,const TDesC& aTemplateLabel,TBool aInTransaction=EFalse);
//
	IMPORT_C CContactIdArray* GetCardTemplateIdListL() const;
	IMPORT_C CContactIdArray* GetGroupIdListL() const;
	IMPORT_C void AddContactToGroupL(TContactItemId aItemId, TContactItemId aGroupId);
	IMPORT_C void AddContactToGroupL(CContactItem& aItem, CContactItem& aGroup);
	IMPORT_C void AddContactToGroupL(TContactItemId aItemId, TContactItemId aGroupId,TBool aInTransaction);
	IMPORT_C void RemoveContactFromGroupL(CContactItem& aItem, CContactItem& aGroup);
	IMPORT_C void RemoveContactFromGroupL(TContactItemId aItemId, TContactItemId aGroupId);
	inline TInt GroupCount() const;
	inline TInt TemplateCount() const;

	// speed dial functions
	IMPORT_C void SetFieldAsSpeedDialL(CContactItem& aItem, TInt aFieldId, TInt aSpeedDialPosition);
	IMPORT_C TContactItemId GetSpeedDialFieldL(TInt aSpeedDialPosition, TDes& aPhoneNumber);
	IMPORT_C void RemoveSpeedDialFieldL(TContactItemId aContactId, TInt aSpeedDialPosition);

	// reading contacts from the db
	IMPORT_C CContactItem* ReadMinimalContactL(TContactItemId aContactId);
	IMPORT_C CContactItem* ReadMinimalContactLC(TContactItemId aContactId);
	IMPORT_C CContactItem* ReadContactL(TContactItemId aContactId);
	IMPORT_C CArrayPtr<CContactItem>* ReadContactAndAgentL(TContactItemId aContactId);
	IMPORT_C CContactItem* ReadContactL(TContactItemId aContactId,const CContactItemViewDef& aViewDef);
	IMPORT_C CContactItem* ReadContactLC(TContactItemId aContactId);
	IMPORT_C CContactItem* ReadContactLC(TContactItemId aContactId,const CContactItemViewDef& aViewDef);
	IMPORT_C void ReadContactTextDefL(const CContactItem &aItem, TDes &aResult);
	IMPORT_C void ReadContactTextDefL(const CContactItem &aItem, TDes &aResult,CContactTextDef* aTextDef);
	IMPORT_C void ReadContactTextDefL(TContactItemId aContactId, TDes &aResult);
	IMPORT_C void ReadContactTextDefL(TContactItemId aContactId, TDes &aResult,CContactTextDef* aTextDef);
	IMPORT_C CContactItem* OpenContactL(TContactItemId aContactId);
	IMPORT_C CContactItem* OpenContactL(TContactItemId aContactId,const CContactItemViewDef& aViewDef);
	IMPORT_C CContactItem* OpenContactLX(TContactItemId aContactId);
	IMPORT_C CContactItem* OpenContactLX(TContactItemId aContactId,const CContactItemViewDef& aViewDef);
	IMPORT_C void CloseContactL(TContactItemId aContactId);
	IMPORT_C void CommitContactL(const CContactItem& aContact);
	IMPORT_C void DeleteContactL(TContactItemId aContactId);
	IMPORT_C void DeleteContactsL(const CContactIdArray& aContactIds);
  	IMPORT_C CArrayPtr<CContactItem>* ImportContactsL(const TUid& aFormat,RReadStream& aReadStream,TBool& aImportSuccessful,TInt aOption);
  	IMPORT_C void ExportSelectedContactsL(const TUid& aFormat,const CContactIdArray& aSelectedContactIds,RWriteStream& aWriteStream,TInt aOption,TBool aExportPrivateFields=ETrue);
	IMPORT_C void ExportSelectedContactsL(const TUid& aFormat,const CContactIdArray& aSelectedContactIds,RWriteStream& aWriteStream,TInt aOption,const Versit::TVersitCharSet aCharSet, TBool aExportPrivateFields=ETrue);
	IMPORT_C void CompactL();

	IMPORT_C CContactIdArray* FindLC(const TDesC& aText,const CContactItemFieldDef *aFieldDef);
	IMPORT_C CIdleFinder* FindAsyncL(const TDesC& aText,const CContactItemFieldDef *aFieldDef, MIdleFindObserver *aObserver);
	IMPORT_C CContactIdArray* FindInTextDefLC(const MDesCArray& aFindWords, const TCallBack &aWordParserCallback);
	IMPORT_C CContactIdArray* FindInTextDefLC(const MDesCArray& aFindWords,CContactTextDef* aTextDef, const TCallBack &aWordParserCallback);
	IMPORT_C CIdleFinder* FindInTextDefAsyncL(const MDesCArray& aFindWords, MIdleFindObserver *aObserver, const TCallBack &aWordParserCallback);
	IMPORT_C CIdleFinder* FindInTextDefAsyncL(const MDesCArray& aFindWords,const CContactTextDef* aTextDef, MIdleFindObserver *aObserver, const TCallBack &aWordParserCallback);
	IMPORT_C CContactIdArray* SortArrayL(const CContactIdArray* aIdArray, const CArrayFix<TSortPref>* aSortOrder);
	IMPORT_C CContactIdArray* SortArrayLC(const CContactIdArray* aIdArray, const CArrayFix<TSortPref>* aSortOrder);
	IMPORT_C void SortByTypeL(CArrayFix<TSortPref>* aSortOrder);
	IMPORT_C void SortL(CArrayFix<TSortPref>* aSortOrder);
	IMPORT_C void SortAsyncL(CArrayFix<TSortPref>* aSortOrder, TRequestStatus& aStatus);
	IMPORT_C void CancelAsyncSort();
	IMPORT_C void SortAsyncL(CArrayFix<TSortPref>* aSortOrder, TRequestStatus& aStatus, MContactSortObserver& aObserver);

  	IMPORT_C TPtrC FileUid();
	IMPORT_C CContactActiveCompress* CreateCompressorLC();
	IMPORT_C CContactActiveRecover* CreateRecoverLC();
	IMPORT_C void RecoverL();
	IMPORT_C TBool IsDamaged() const;
	IMPORT_C TBool CompressRequired();
	IMPORT_C void CloseTables();
	IMPORT_C void OpenTablesL();
	IMPORT_C static CContactDatabase* LockServerConnectL(const TDesC& aFileName);

	//New Phone Matching function, takes a number as a TDesc& and will match from the right of the string
	//by the the number defined
	IMPORT_C CContactIdArray* MatchPhoneNumberL(const TDesC& aNumber, TInt aMatchLengthFromRight);


	IMPORT_C const CContactIdArray* SortedItemsL();
	IMPORT_C TContactItemId TemplateId() const;
	IMPORT_C CContactItem* CreateOwnCardLC();
	IMPORT_C CContactItem* CreateOwnCardL();
	IMPORT_C TContactItemId OwnCardId() const;
	IMPORT_C void SetOwnCardL(const CContactItem& aContact);

//	Preferred Template
	IMPORT_C TContactItemId PrefTemplateId() const;
	IMPORT_C void SetPrefTemplateL(const CContactItem& aContact);

//	Current item
	IMPORT_C void SetCurrentItem(const TContactItemId aContactId);
	IMPORT_C const TContactItemId GetCurrentItem() const;

//	Connectivity
	IMPORT_C void SetDateFormatTextL(const TDesC& aFormat);
	IMPORT_C void FilterDatabaseL(CCntFilter& aFilter);
	IMPORT_C CContactIdArray* ContactsChangedSinceL(const TTime& aTime);
	IMPORT_C TContactSyncId SetLastSyncDateL(const TTime& aSyncDate);
	IMPORT_C void SetLastSyncDateL(TContactSyncId aSyncId, const TTime& aSyncDate);
	IMPORT_C void GetLastSyncDateL(TContactSyncId aSyncId, TTime& aSyncDate);

	IMPORT_C TInt FileSize() const;
	IMPORT_C TUint ConnectionId() const;
	IMPORT_C const CContentType &TemplateContentType(const CContactItemField &aField) const;
	IMPORT_C TVersion Version() const;
	IMPORT_C TInt64 MachineId() const;
	void UnlockLastLockedContact();

public: // Deprecated interfaces
	IMPORT_C TInt InitLoadPhoneMatchesL();
	IMPORT_C TInt LoadPhoneMatchesL();
	IMPORT_C CContactIdArray* PhoneMatchListL(const TDesC& aNumber) const;
	IMPORT_C CContactIdArray* MatchPhoneNumberL(TInt aPhoneNumber);
	IMPORT_C void ReplacePrefL(TInt anId);
	IMPORT_C void ReadPrefL(TInt32 anId);
	IMPORT_C TInt32 CreatePrefL();
	IMPORT_C void CompressL();

public:	// For test code only
	IMPORT_C void DamageDatabaseL(TInt aSecretCode);	// Don't use this, you don't really want to damage your database do you?
	IMPORT_C void OverrideMachineUniqueId(TInt64 aMachineUniqueId);
	IMPORT_C TInt CntServerResourceCount();
	IMPORT_C void SetCntServerHeapFailure(RHeap::TAllocFail aType,TInt aRate);
	IMPORT_C TInt BlobSizeL(TContactItemId aContactId);
	IMPORT_C CContactIdArray* DeletedContactsLC();
	IMPORT_C void ResetServerSpeedDialsL();

public:	// For cnt server only
	IMPORT_C void HandleDatabaseEventL(const TContactDbObserverEvent &aEvent);
	IMPORT_C static TInt TextToPhoneMatchNumber(const TDesC& aText, TInt& aNumDigits, TInt aPhoneMatchLength=7);
	//
	IMPORT_C TInt GetCurrentDatabase(TDes& aDatabase) const;
	IMPORT_C TInt SetCurrentDatabase(const TDesC& aDatabase) const;

	IMPORT_C void StoreSortOrderL();
	IMPORT_C void RestoreSortOrderL();
	IMPORT_C const CArrayFix<TSortPref>* SortOrder() const;
	//Contact Hint Field Access

	enum TContactViewFilter
		{
		EUnfiltered	=0x00000000,
		EMailable	=0x00000001,
		ESmsable	=0x00000002,
		ELandLine	=0x00000004,
		EFaxable	=0x00000008,
		EPhonable   =0x00000010,
		EWork		=0x00000020,
		EHome		=0x00000040
		};

	IMPORT_C TBool ContactMatchesHintFieldL(TInt aBitWiseFilter,TContactItemId aContactId);		
public: // for vCard converter only
	IMPORT_C void DatabaseBeginLC(TBool aIsInTransaction);
	IMPORT_C void DatabaseCommitLP(TBool aIsInTransaction);
  	IMPORT_C CContactItem *UpdateContactLC(TContactItemId aContactId,CContactItem* aNewContact);
	IMPORT_C TContactItemId doAddNewContactL(CContactItem& aContact,TBool aIsTemplate,TBool aIsInTransaction);
	IMPORT_C void doCommitContactL(const CContactItem& aContact,TBool aIsInTransaction, TBool aSendChangedEvent);
	IMPORT_C TContactItemId ContactIdByGuidL(const TDesC& aGuid);
	IMPORT_C void doDeleteContactL(TContactItemId aContactId, TBool aIsInTransaction, TBool aSendChangedEvent, TBool aDecAccessCount=EFalse);
	IMPORT_C CContactItemViewDef* AllFieldsView();
public: // For Symbian use only
	IMPORT_C void DatabaseBeginL(TBool aIsInTransaction);
	IMPORT_C void DatabaseCommitL(TBool aIsInTransaction);
	IMPORT_C void DatabaseRollback();
	IMPORT_C void SetSortedItemsList(CContactIdArray* aSortedItems, CArrayFix<TSortPref>* aSortOrder);
private:
	CContactItem* doCreateContactGroupLC(const TDesC* aGroupLabel,TBool aInTransaction);
	void CreateGroupRecordL(TContactItemId aGroupId);
	CContactIdArray *ReadGroupIdsLC(TContactItemId aGroupId);
	void WriteGroupIdsLC(const CContactIdArray *aGroupArray);
	//
	void RestoreGroupMembersL(CContactItem& aGroup);
	void RestoreGroupMembershipL(CContactItemPlusGroup& aGroup);
	void doDeleteGroupMemberL(TContactItemId aGroupId,TContactItemId aItemId, TBool aIsInTransaction);
	void AddLabelFieldToItemL(CContactItem& aGroup);
	void AddToTemplateListL(const TContactItemId aNewTemplateId);
	void AddToGroupListL(const TContactItemId aNewGroupId);
	TInt FieldTypeCount(const CContactItemFieldSet& aSystemTemplateFields, const CContactItemFieldSet& aFieldSet, TInt aStartIndex, const CContactItemField& aField) const;
	void RestoreTemplateFieldsL(CContactItem& aContact,const CContactItemFieldSet& aTemplateFields, const CContactItemViewDef& aViewDef);
	void ClearTemplateFieldContent(CContactItem& aNewTemplate);
	void DeleteFindView();
	TBool CheckType(TUid aUid);
	TBool CheckType(TUid aUid) const;
	void DeleteContactCardTemplateL(CContactItem* aTemplate);
	void DeleteContactGroupL(CContactItem* aGroup);
	void IncTemplateRefL(TContactItemId aTemplateRefId);
	void DecTemplateRefL(TContactItemId aTemplateRefId);
	void SetFieldsAsTemplate(CContactItem& aContact);
	void PersistOwnCardIdL(const TContactItemId aOwnCardId);
	void PersistPrefTemplateIdL();
	void PersistPreferenceIdL(const TDesC& aColumn, const TContactItemId aId);
	void PersistGroupIdsL();
	void PersistCardTemplateIdsL();
	void PersistPhoneNumberMatchingL(const CContactItemFieldSet& aFieldSet, TContactItemId aContactId);
	void doDeletePhoneMatchingNumbersL(TContactItemId aContactId);
	TInt NumRetries() const;
	void ItemTableUpdateWithRetryL();
	void ItemTableInsertWithRetryL();
	void ItemTableDeleteWithRetryL();
	friend class CContactChangeNotifier;
	static void CleanupDatabaseRollback(TAny *aDatabase);
	void StartLockServerL(const TDesC& aFileName,TThreadAccess aAccess);
	TBool CheckSortError(TInt aError);
	void AddObserverL(MContactDbObserver *aChangeNotifier);
	void RemoveObserver(const MContactDbObserver *aChangeNotifier);
	void LockRecordLC(TContactItemId aContactId);
	void UnlockRecord(TContactItemId aContactId);
	void CreatePrefInternalL();
	TBool ReadPrefInternalL();
	void CancelSystemTemplate();
	CContactItem* SystemTemplateL() const;
	CContactItem* ContactTemplateL(TContactItemId aId) const;
	CContactItem* GetCachedTemplateL(TContactItemId aId);
	void RemoveFromCache(TContactItemId aId);
	void DeleteCacheEntry(TInt aIndex);
	void DeleteAllMembershipL(const CContactItemPlusGroup *aContact);
	static TInt64 GenerateMachineUniqueID();
	TInt32 CreatePhoneMatchNumberL(const TDesC &aText,TInt aMatchLength,TInt &aNumDigits);
	static TInt32 PadOutPhoneMatchNumber(TInt32& aPhoneNumber,TInt aPadOutLength);
	static void AppendMatchingNumberSetL(RArray<TInt>& aArray, const CContactItemFieldSet& aFieldSet, TFieldType aFieldType);

public:
	static void CleanupTableCancel(TAny *aTable);
	typedef TBuf<KTextFieldMinimalLength> TTextFieldMinimal;
	enum TDirection {EAsc,EDesc};
private:
	CContactDatabase();
	static void ConnectFsLC(RFs &aFs);
	void doOpenL(const TDesC& aFileName,TThreadAccess aAccess);
	void doCreateL(const TDesC& aFileName, TBool aReplace,TThreadAccess aAccess);
	void doDeleteContactsL(const CContactIdArray& aContactIds, TBool &aCommited);
	void CreateTemplateAndPrefsL();
	void WriteTemplateIdsColL(TDbColNo aColNo,CContactIdArray* aIdArray);
	void ReadTemplateIdsColL(TDbColNo aColNo);
	void WriteStoreToColL(CBufStore* aBufStore,TStreamId aStreamId,TInt aColNo);
	void WriteBlobColL(const CContactItem& aContact,TDbColNo aHeaderColNo,TDbColNo aBlobColNo,const CContactItem* aTemplate,TDbColNo aTextColNo);
	void HandleRetryError(TInt aErr,TInt &aAttemptsLeft, TBool aRetryNotFound);
	void BlobOpenWithRetryL(RDbColReadStream &aBlob, TDbColNo aColNo);
	void ReadBlobColL(CContactItem& aContact,TDbColNo aHeaderColNo,TDbColNo aBlobColNo,const CContactItemViewDef& aViewDef,const CContactItem* aTemplate,TDbColNo aTextColNo);
// GROUP id list writing to the db
	void WriteIdsColL(TDbColNo aColNo,CContactIdArray* aIdArray);
	void ReadIdsColL(TDbColNo aColNo);
//
	TInt DoGotoL(TContactItemId aContactId);
	TInt NextExistingL(TInt aIndex);
	TInt PreviousExistingL(TInt aIndex);
	inline void __DbgDbmsResourceMark();
	inline void __DbgDbmsResourceCheck();
	void static GetFieldText(const CContactItemField& aField, CContactDatabase::TTextFieldMinimal &aText);
	TInt static FieldText(const CContactItemFieldSet& aFieldSet,TFieldType aFieldType, CContactDatabase::TTextFieldMinimal &aText, TInt aStartPosition);
	void static NonZeroFieldText(const CContactItemFieldSet& aFieldSet,TFieldType aFieldType, CContactDatabase::TTextFieldMinimal &aText);
	void GetTextFieldInfoL(TFieldType aFieldType, CContactDatabase::TTextFieldMinimal &aText);
	CContactIdArray* doSortLC(const CArrayFix<TSortPref>* aSortOrder, const CContactIdArray* aIdArray);
	void ReSortL(CArrayFix<TSortPref>* aSortOrder);
	void SortWithoutOrderL(CContactIdArray* aArray);
	void SortDuplicatesL(const CArrayFix<TSortPref>& aSortOrder,CSortArray& aList,TInt aPos);
	void SortDuplicatesL(const CArrayFix<TSortPref>& aSortOrder,CSortArray& aList,
								TInt aIndex,TInt aStartPos,TInt aEndPos);
	void InsertInSortArray(const CContactItem& aContact);
	void MoveInSortArray(const CContactItem& aContact);
	void RemoveFromSortArray(TContactItemId aContactId);
	void InsertInSortArrayL(const CContactItem& aContact);
	void MoveInSortArrayL(const CContactItem& aContact);
	TInt NewSortIndexL(const CContactItemFieldSet& aFieldSet,TInt aStartPos,TInt aEndPos);
	TInt CompareSortFieldsL(const CContactItemFieldSet& aFieldSet);
	TInt ContactPosL(TContactItemId aContactId);
	void SendEventToAllObservers(TContactDbObserverEventType aEventType);
	void SendEventToAllObservers(const TContactDbObserverEvent &aEvent);
	HBufC* GuidLC(const CContactItem& aContact,TBool& aCompressed);
// MContactDbPrivObserver
	void HandleDatabaseEventL(RDbNotifier::TEvent aEvent);
#if defined(_DEBUG)
	static void WriteLogToFileL();
	static void GetLogFileLC(RFs& aFs,RFile& aFile);
#endif

private: // Speed Dials
	void AddSpeedDialAttribsToContactL(CContactItem& aItem,TInt aFieldId,TInt aSpeedDialPosition);
	void RemoveSpeedDialAttribsFromContactL(TContactItemId aItemId, TInt aSpeedDialPosition);
	static TUid SpeedDialFieldUidFromSpeedDialPosition(TInt aSpeedDialPosition);
	static const TDesC& DateFormatForLocale();
	TBool doFindL(CContactIdArray *aIdsFound, const TDesC& aText,const CContactItemFieldDef *aFieldDef);
	TBool doFindInTextDefL(CIdleFinder *iIdleFinder);
	void SendChangeEvent(TContactDbObserverEventType aType, TContactItemId aId);
	void PrepAddEvent(TUid aType, TContactItemId aUid);
	void PrepChangeEvent(TUid aType, TContactItemId aUid);
	void PrepDeleteEvent(TUid aType, TContactItemId aUid);

//LPD DBMS Improvements
private:
enum TFindFieldFlags
		{
		EFindInAllFields				=0x00000001,
		EFindFirstName					=0x00000002,
		EFindLastName					=0x00000004,
		EFindCompanyName				=0x00000008,
		EFindInEmailTableOnly			=0x00000010,
		EFindInAnyIdentityField			=0x00000020	
		};
private:
	void doCreatePhoneNumbersTableL();
	void doCreateContactIdentityTableL();
	void doCreateEmailTableL();
	void doDeleteRowsInRelatedTablesL(TContactItemId aContactId);
	void ConstructTableUsageFlagsFromSortOrderL(TInt& aFlags);
	//Async Searching
	void CreateIterativeFindViewL(const TDesC& aSearchCondition,RDbView& aView);
	TBool PerformFindIterationL(CContactIdArray *aIdsFound,const TDesC& aText,RDbView& aView,CIdleFinder::TIdentityTableColSet aIdenityTableCols, TInt aFieldsToSearch);
	TBool PerformEmailFindIterationL(CContactIdArray *aIdsFound,RDbView& aView);
	TBool PerformTextDefFindIterationL(CIdleFinder* aIdleFinder, CContactIdArray *aIdsFound,RDbView& aView);
	TBool ContactHintColumnMatchesFilter(TInt aHintField, TInt aFilter);
	static void StripOutNonDigitCharsL(TDes& aText);
private:
	friend class RContactRemoteView;
	RDbNamedDatabase iDatabase;
	RDbs iDbsSession;
	CContactSrvSession* iContactSrvSession;
	CPrivateChangeNotifier* iChangeNotifier;
	CPrivateChangeEventNotifier* iChangeEventNotifier;
//
	TContactItemId iLastLockedContact;
	TContactItemId iTemplateId;
	TContactItemId iOwnCardId;
	TContactItemId iPrefTemplateId;
	CContactIdArray* iCardTemplateIds;
	CContactIdArray* iGroupIds;
	CArrayPtrFlat<CContactItem> iTemplateCache;
//
	CContactTables* iItemTable;
	RDbTable iGroupTable;
	RDbTable iGroupTableByGroup;
	RDbTable iPrefTable;
	RDbTable iPhoneTable;
	RDbTable iSyncTable;
//
	HBufC* iDateFormatText;
	CArrayFix<TSortPref>* iSortOrder;
	CArrayPtrFlat<MContactDbObserver>* iObservers;
	CContactTextDef* iTextDef;
	CContactIdArray* iSortedItems;
	CContactViewDef* iView;
	TUid iDbViewContactType; // used to select which contact type to sort / search on
	CContactItemViewDef* iAllFieldsView;
	TBuf<40> iUidString;
	CIdle* iIdleFinder;
	TBool iTablesOpen;
	CContactItem* iSystemTemplate;
	TInt iFileLayoutVersion;
	CPrivFindViewColSet* iFindView;
	TInt64 iMachineUniqueId;
	CPrivConverter* iConv;
	TCollationMethod iCollateMethod; // used for sorting contacts
	RFs iFsSession;
	CCntIdleSorter* iIdleSorter;
	CContactPhoneParser* iPhoneNumParser;
	};



/**
 * Receives events reporting changes to a contact database.
 *
 * After the change notifier has been created using <code>NewL()</code>,
 * it notifies the specified observer whenever a change takes place to
 * the database.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactChangeNotifier : public CBase
	{
public:
	IMPORT_C ~CContactChangeNotifier();
	IMPORT_C static CContactChangeNotifier* NewL(CContactDatabase& aDatabase, MContactDbObserver *aObserver);
private:													
	CContactChangeNotifier(CContactDatabase& aDatabase, MContactDbObserver *aObserver);
	void ConstructL();
private:
	CContactDatabase &iDatabase;		
	MContactDbObserver* iObserver;
	};

class CContactConverter : public CBase
	{
public:
	virtual CArrayPtr<CContactItem>*  ImportL(CContactDatabase& aDb,RReadStream& aReadStream,TBool& aImportSuccessful,TInt aOptions,TBool aImportSingle)=0;
	virtual void ExportL(CContactDatabase& aDb,const CContactIdArray& aSelectedContactIds,RWriteStream& aWriteStream,TInt aOptions,const Versit::TVersitCharSet aCharSet,TBool aExportPrivateFields, TInt aCommitNumber=10)=0;
	};

class CContactPhoneNumberParser : public CBase
	{
public:
	virtual void ExtractRawNumber(const TDesC& aTextualNumber, TDes& aRawNumber)=0;
	};


inline TInt CContactDatabase::TemplateCount() const
	{ return iCardTemplateIds->Count(); }
inline TInt CContactDatabase::GroupCount() const 
	{ return iGroupIds->Count(); }
inline TInt CContactDatabase::NullUidValue()
	{ return KNullContactId; }
inline TUid CContactItemViewDef::operator[](TInt aIndex) const
    { return iFieldTypes[aIndex]; }
/**
 * Gets the number of field types in the view definition.
 *
 * @returns   "TInt"
 *            The number of field types in the view definition.
 */
inline TInt CContactItemViewDef::Count() const
    { return iFieldTypes.Count(); }
/**
 * Deletes all field types from the view definition's field type array.
 */
inline void CContactItemViewDef::Reset()
    { iFieldTypes.Reset(); }
/**
 * Gets the view definition's use.
 *
 * @returns   "TUse"
 *            The current <code>TUse</code> setting.
 */
inline CContactItemViewDef::TUse CContactItemViewDef::Use() const
	{ return iUse; }
/**
 * Sets the view definition's use.
 *
 * @param     "TUse aUse"
 *            The new <code>TUse</code> setting.
 */
inline void CContactItemViewDef::SetUse(CContactItemViewDef::TUse aUse)
	{ iUse=aUse; }
inline CContactItemViewDef::TMode CContactItemViewDef::Mode() const
	{ return iMode; }
/**
 * Sets the view definition's mode.
 *
 * @param     "TMode aMode"
 *            The new <code>TMode</code> setting.
 */
inline void CContactItemViewDef::SetMode(CContactItemViewDef::TMode aMode)
	{ iMode=aMode; }

/**
 * Constructs a <code>TSortPref</code> object.
 *
 * The order is initialised to <code>EAsc</code> and the field type to
 * <code>KNullUid</code>.
 *
 */
inline CContactDatabase::TSortPref::TSortPref()
	: iOrder(EAsc), iFieldType(KNullUid)
	{}
inline CContactDatabase::TSortPref::TSortPref(TFieldType aFieldType,TOrder aOrder)
	: iOrder(aOrder), iFieldType(aFieldType)
	{}





#endif
