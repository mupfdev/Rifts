// CNTITEM.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CNTITEM_H__)
#define __CNTITEM_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__CNTDEF_H__)
#include <cntdef.h>
#endif

#if !defined(__CNTFIELD_H__)
#include <cntfield.h>
#endif

#include <cntdb.h>

const TInt KUidStringLength =244;
#define KUidStringSeparator '-'
class CContactItemField;
#define KContactMaxFieldNumber 32
class CContactItemViewDef;
class CContactItem;

const TInt KContactFieldSetSearchAll=-1;
/**
 * A contact item's field set.
 *
 * The field set owns an array of contact item fields
 * (<code>CContactItemField</code>s). The field set is owned by a contact
 * item, and can be retrieved using
 * <code>CContactItem::CardFields()</code>. Use functions provided by
 * class <code>CContactItem</code> to add and remove fields to/from the
 * field set.A field set can contain more than one field of the same
 * type, but this is not advisable as it may cause problems when
 * synchronising the contacts database.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactItemFieldSet : public CBase
	{
	friend class CContactItemField;
	friend class CContactDatabase;
	friend class CContactTables;
public:
	IMPORT_C static CContactItemFieldSet* NewL();
	IMPORT_C static CContactItemFieldSet* NewLC();
	IMPORT_C ~CContactItemFieldSet();
	inline const CContactItemField& operator[](TInt aIndex) const;
	inline CContactItemField& operator[](TInt aIndex);
	inline TInt Find(TFieldType aFieldType) const; // will only find the first such occurence
	inline TInt Find(TFieldType aFieldType,TUid aMapping) const;
	IMPORT_C TInt FindNext(TFieldType aFieldType,TInt aStartPos=KContactFieldSetSearchAll) const;
	IMPORT_C TInt FindNext(TFieldType aFieldType,TUid aMapping,TInt aStartPos=KContactFieldSetSearchAll) const;
	inline TInt Count() const;
	inline void Reset();
	IMPORT_C void UpdateFieldL(const CContactItemField& aField, TInt aMatchCount);
	IMPORT_C void UpdateFieldSyncL(const CContactItemField& aField, TInt aMatchCount);
	IMPORT_C CContactItemFieldSet& AddL(CContactItemField& aField);
	IMPORT_C void Remove(TInt aIndex);
	IMPORT_C void InsertL(TInt aIndex,CContactItemField& aField);
	IMPORT_C void Move(TInt aFrom, TInt aTo);
	IMPORT_C TStreamId StoreL(CStreamStore& aStore,RWriteStream& aTextStream,CStreamStore& aBlobStore);
	TStreamId StoreL(CStreamStore& aStore,RWriteStream& aTextStream,CStreamStore& aBlobStore,CContactTables* aTables);
	IMPORT_C void RestoreL(CStreamStore& aStore, TStreamId anId,CStreamStore* aBlobStore,const CContactItemViewDef& aViewDef,RReadStream& aReadStream);
private:
	CContactItemFieldSet();
	void ConstructL();
	void SetFieldId(CContactItemField& aField);
	const CContactItemField* FindById(TInt aId) const;
	TStreamId StoreL(CStreamStore& aStore,const CContactItem* aTemplate,RWriteStream& aStream,CStreamStore& aBlobStore,CContactTables* aTables);
	void RestoreL(CStreamStore& aStore, TStreamId anId, CStreamStore* aBlobStore,const CContactItemViewDef& aViewDef,const CContactItem* aTemplate,RReadStream& aReadStream,CContactTables* aContactsTable);
	void RestoreAndAddTemplateL(CStreamStore& aStore, TStreamId aId,CStreamStore* aBlobStore,const CContactItemViewDef& aViewDef,const CContactItem* aTemplate, RReadStream& aReadStream,CContactTables* aContactsTable);
	TInt MatchTemplateField(const CContentType& aContentType,TUint aUserFlags,TBool &aExactMatch) const;
	static HBufC* LoadTextStreamLC(RReadStream& aStream);
private:
	CArrayPtr<CContactItemField>* iFields;
	};

class CContactDatabase;
/**
 * The abstract base class for contact cards, templates and groups.
 *
 * All contact items are identified by a contact ID,
 * (<code>TContactItemId</code>), have a last modified date and time and
 * own one or more fields (the field set). Contact items also have an
 * access count and attributes (e.g. hidden). Note that fields in a
 * contact item also have attributes. Attribute values specified in the
 * contact item override those in the contained fields. The access count
 * is a record of the number of objects referencing a contact item. A
 * contact item cannot be fully deleted until its access count is zero.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactItem : public CBase
	{
	friend class CContactCardTemplate;
	friend class CContactItemPlusGroup;
	friend class CContactCard;
	friend class CContactTemplate;
	friend class CContactGroup;
	friend class CContactOwnCard;
	friend class CVCardToContactsAppConverter;
	friend class CContactTables;//lpd
public:
	IMPORT_C ~CContactItem();
	virtual TUid Type() const=0;
	IMPORT_C TContactItemId Id() const;
	IMPORT_C TContactItemId TemplateRefId() const;
	IMPORT_C TTime LastModified() const;
	IMPORT_C void SetLastModified(const TTime& aLastModified);
	IMPORT_C void AddFieldL(CContactItemField& aField);
	IMPORT_C void RemoveField(TInt aFieldPos);
	IMPORT_C void InsertFieldL(CContactItemField& aField,TInt aFieldPos);
	IMPORT_C CContactItemFieldSet& CardFields() const;
	IMPORT_C void SetHidden(TBool aHidden);
	IMPORT_C void SetSystem(TBool aSystem);    	
	IMPORT_C TBool IsHidden();
	IMPORT_C TBool IsSystem();    	
	IMPORT_C void UpdateFieldSet(CContactItemFieldSet* aNewFieldSet);
	IMPORT_C void SetDeleted(TBool aDeleted);
	IMPORT_C TBool IsDeleted() const;
	IMPORT_C void SetTemplateRefId(TContactItemId aUid);
	TContactItemId Agent();
	inline TBool IsDeletable();
	inline void IncAccessCount();
	inline void DecAccessCount();
	inline TInt AccessCount() const;
	IMPORT_C void SetUidStringL(TDesC& aString);
	IMPORT_C TPtrC UidStringL(TInt64 aMachineUniqueId) const;
	inline TPtrC Guid();
public:
	enum { ESystem=0x01, EHidden=0x02, ECompressedGuid=0x04, EDeleted=0x08 };
protected:
private:
	CContactItem();
	void ConstructL();
	void ConstructL(const CContactItem *aTemplate);
	void MakeUidStringL(TInt64 aMachineUniqueId);
	void SetHasCompressedGuid(TBool aCompressed);
	TBool GuidIsCompressed() const;
private:
	CContactItemFieldSet* iFieldSet;
	TUint32 iAttributes;
	TContactItemId iId;
	TContactItemId iTemplateRefId;
	TTime iLastModified;
	TTime iCreationDate;
	TUint32 iAccessCount;
	HBufC* iGuid;
	friend class CContactDatabase;
	};

/**
 * Abstract base class for <code>CContactGroup</code>,
 * <code>CContactCard</code> and <code>CContactOwnCard</code>.
 *
 * Exists to avoid duplication of group functionality in its three
 * derived classes.
 *
 * @since 5.2
 * @lib "cntmodel.lib"
 */
class CContactItemPlusGroup : public CContactItem
	{
public:
	IMPORT_C const CContactIdArray* GroupsJoined() const;
	IMPORT_C CContactIdArray* GroupsJoinedLC() const;
protected:
	CContactItemPlusGroup();
	IMPORT_C ~CContactItemPlusGroup();
private:
	CContactIdArray* iGroups;
	friend class CContactDatabase;
	};

/**
 * Contact group.
 *
 * A contact group is a contact item which holds a set of associated
 * contact item IDs. The members of the group may be contact cards, own
 * cards, or even other groups. The group has a label which identifies
 * the group to users, e.g. "family", or "colleagues". The type of a
 * contact group is <code>KUidContactGroup</code>, as returned by
 * <code>Type()</code>.Objects of this class are constructed using
 * <code>CContactDatabase::CreateContactGroupL()</code> or
 * <code>CreateContactGroupLC()</code>. These functions create the group,
 * optionally with a label, add it to the database, and return a pointer
 * to it.To create an association between a card and a group, use
 * <code>CContactDatabase::AddContactToGroupL()</code> and to remove the
 * association, use <code>RemoveContactFromGroupL()</code>. To find out
 * which groups a card belongs to, use
 * <code>CContactCard::GroupsJoinedLC()</code> or
 * <code>CContactOwnCard::GroupsJoinedLC()</code>.The function
 * <code>CContactDatabase::GetGroupIdListL()</code> may be used to
 * retrieve a list of IDs for all groups in the database.
 *
 * @since 5.2
 * @lib "cntmodel.lib"
 */
class CContactGroup : public CContactItemPlusGroup
	{
public:
	IMPORT_C static CContactGroup* NewL();
	IMPORT_C static CContactGroup* NewLC();
	IMPORT_C ~CContactGroup();
public: // from CContactItem
	IMPORT_C TUid Type() const;
public:
	// default sorted item array is ascending
	IMPORT_C CContactIdArray* ItemsContainedLC() const;
	IMPORT_C const CContactIdArray* ItemsContained() const;
	IMPORT_C TBool IsSystem() const;
	IMPORT_C void SetSystem(TBool aSystem);
	IMPORT_C TBool ContainsItem(TContactItemId aContactId);
	IMPORT_C void SetGroupLabelL(const TDesC& aLabel);
	IMPORT_C TPtrC GetGroupLabelL();
	IMPORT_C TBool HasItemLabelField();
	IMPORT_C CContactIdArray* GroupsJoinedLC() const;
// 
	IMPORT_C void ReservedFunction1();
	IMPORT_C void ReservedFunction2();
private:
	CContactGroup();
private:
	CContactIdArray* iItems;
	friend class CContactDatabase;
	};

class CContactCardTemplate : public CContactItem
	{
	friend class CContactDatabase;
	friend class CContactTables;
public:
	IMPORT_C void SetTemplateLabelL(const TDesC& aLabel);
	IMPORT_C TPtrC GetTemplateLabelL();
protected:
	IMPORT_C static CContactCardTemplate* NewL();
	IMPORT_C static CContactCardTemplate* NewLC();
	IMPORT_C static CContactCardTemplate* NewL(const CContactItem *aTemplate);
	IMPORT_C static CContactCardTemplate* NewLC(const CContactItem *aTemplate);
	IMPORT_C TBool HasItemLabelField();
// 
	IMPORT_C void ReservedFunction1();
	IMPORT_C void ReservedFunction2();

protected: // from CContactItem
	IMPORT_C TUid Type() const;
private:
	CContactCardTemplate();
	};

/**
 * A contact card.
 *
 * Implements the pure virtual <code>Type()</code> function defined in
 * class <code>CContactItem</code>. Contact cards may optionally be
 * constructed from a template.Note: In EPOC Releases 5.0 and 5.1, this
 * class was derived from <code>CContactItem</code>, rather than from
 * <code>CContactItemPlusGroup</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactCard : public CContactItemPlusGroup
	{
public:
	IMPORT_C ~CContactCard();
	IMPORT_C static CContactCard* NewL();
	IMPORT_C static CContactCard* NewLC();
	IMPORT_C static CContactCard* NewL(const CContactItem *aTemplate);
	IMPORT_C static CContactCard* NewLC(const CContactItem *aTemplate);
public: // from CContactItem
	IMPORT_C TUid Type() const;
public:
	IMPORT_C CContactIdArray* GroupsJoinedLC() const;
private:
	CContactCard();
private:
	friend class CContactDatabase;
	};

/**
 * Own card.
 *
 * An own card is a contact card which contains information about the
 * device's owner. This can be sent to another compatible electronic
 * device as a vCard. The contact database recognises a single own card
 * referred to as the current own card; its ID is returned by
 * <code>CContactDatabase::OwnCardId()</code>. Like a contact card, an
 * own card can be a member of one or more contact card groups. The own
 * card type is identified by a UID of <code>KUidContactOwnCard</code>,
 * as returned by <code>Type()</code>.Own cards can be constructed using
 * either <code>CContactDatabase::CreateOwnCardLC()</code> or
 * <code>CreateOwnCardL()</code>. These functions create an own card,
 * based on the system template, add it to the database, set it as the
 * database's current own card and return a pointer to it. To change the
 * database's current own card, use
 * <code>CContactDatabase::SetOwnCardL()</code>.
 *
 * @since 5.2
 * @lib "cntmodel.lib"
 */
class CContactOwnCard : public CContactItemPlusGroup
	{
public:
	IMPORT_C ~CContactOwnCard();
	IMPORT_C static CContactOwnCard* NewL();
	IMPORT_C static CContactOwnCard* NewLC();
	IMPORT_C static CContactOwnCard* NewL(const CContactItem *aTemplate);
	IMPORT_C static CContactOwnCard* NewLC(const CContactItem *aTemplate);
public: // from CContactItem
	IMPORT_C TUid Type() const;
public:
	IMPORT_C CContactIdArray* GroupsJoinedLC() const;
private:
	CContactOwnCard();
private:
	friend class CContactDatabase;
	};

/**
 * A template is a contact item which is used to seed the initial field
 * set for other contact items.
 *
 * In EPOC Release 5, only a single contact item template was supported
 * the system template. Its ID is returned by
 * <code>CContactDatabase::TemplateId()</code>. After EPOC Release 5,
 * support for multiple non-system (i.e. user-defined) templates was
 * added. They are implemented by the <code>CContactCardTemplate</code>
 * class. After EPOC Release 5, <code>CContactCardTemplate</code> should
 * be used in preference to <code>CContactTemplate</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactTemplate : public CContactItem
	{
public:
	IMPORT_C static CContactTemplate* NewL();
	IMPORT_C static CContactTemplate* NewLC();
	IMPORT_C static CContactTemplate* NewL(const CContactItem *aTemplate);
	IMPORT_C static CContactTemplate* NewLC(const CContactItem *aTemplate);
public: // from CContactItem
	IMPORT_C TUid Type() const;
private:
	CContactTemplate();
	};

//
// class ContactGuid
//

/**
 * Globally unique identifier enquiry.
 *
 * Each contact item has a unique identifier, stored as a descriptor. It
 * is referred to as the "UID string". It is a combination of the unique
 * identifier of the database in which the contact item was created, the
 * contact item ID and the date/time of the contact item's creation. This
 * class provides a single static exported function to enquire whether an
 * item was created in a specified database.
 *
 * @since 5.1
 * @lib "cntmodel.lib"
 */
class ContactGuid
	{
public:
	IMPORT_C static TContactItemId IsLocalContactUidString(const TDesC& aString, TInt64 aMachineUniqueId);
	static TBool GetCreationDate(TDes& aString, TInt64 aMachineUniqueId);
	static HBufC* CreateGuidLC(const TDesC& aCreationDate,TContactItemId aId, TInt64 aMachineUniqueId);
	static HBufC* CreateGuidLC(const TTime& aCreationDate,TContactItemId aId, TInt64 aMachineUniqueId);
	static HBufC* CreateGuidLC(TContactItemId aId, TInt64 aMachineUniqueId);
	};

inline const CContactItemField& CContactItemFieldSet::operator[](TInt aIndex) const
	{ return *(*iFields)[aIndex]; }
inline CContactItemField& CContactItemFieldSet::operator[](TInt aIndex)
	{ return *(*iFields)[aIndex]; }
/**
 * Finds the first field in the field set with the specified field type.
 *
 * @param     "TFieldType aFieldType"
 *            The field type of interest.
 * @returns   "TInt"
 *            If found, the index of the field within the field set,
 *            or <code>KErrNotFound</code> if not found.
 */
inline TInt CContactItemFieldSet::Find(TFieldType aFieldType) const
	{ return FindNext(aFieldType,KContactFieldSetSearchAll); }
inline TInt CContactItemFieldSet::Find(TFieldType aFieldType,TUid aMapping) const
	{ return FindNext(aFieldType,aMapping,KContactFieldSetSearchAll); }
/**
 * Retrieves the number of fields in the field set.
 *
 * @returns   "TInt"
 *            The number of fields in the field set.
 */
inline TInt CContactItemFieldSet::Count() const
	{ return iFields->Count(); }
/** Deletes all fields in the field set.*/
inline void CContactItemFieldSet::Reset()
	{ iFields->ResetAndDestroy(); }
/**
 * Tests whether the contact item is deletable.
 *
 * This is true if the contact item's access count is zero.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if deletable, <code>EFalse</code>
 *            if not deletable.
 */
inline TBool CContactItem::IsDeletable()
	{return (iAccessCount == 0);}
/** Increments the contact item's access count. */
inline void CContactItem::IncAccessCount()
	{iAccessCount++;}
/** Decrements the contact item's access count. */
inline void CContactItem::DecAccessCount()
	{if(iAccessCount) iAccessCount--;}
/**
 * Gets the contact item's access count.
 *
 * @returns   "TInt"
 *            The contact item's access count.
 */
inline TInt CContactItem::AccessCount() const
	{return(iAccessCount);}

/** 
 * Accessor function for Contact Guid. 
 * This is used to cache contact items that are added during a sync.
 */
inline TPtrC CContactItem::Guid() { return iGuid ? *iGuid : KNullDesC(); }

#endif
