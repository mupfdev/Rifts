// CNTFIELD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CNTFIELD_H__)
#define __CNTFIELD_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

const TInt KNullFieldId=-1;
const TInt KHintIdMask=0xFFC00000;
const TInt KHintTypeMask=0x1FFFFF;
const TInt KHintAdditionalMask=0x200000;

//const TInt KIntContactFieldHint???=0x01;
const TInt KIntContactHintIsPhone=0x02;
const TInt KIntContactHintIsMsg=0x04;
const TInt KIntContactHintIsCompanyName=0x08;
const TInt KIntContactHintIsFamilyName=0x10;
const TInt KIntContactHintIsGivenName=0x20;
const TInt KIntContactHintIsAddress=0x40;
const TInt KIntContactHintIsAdditionalName=0x80;
const TInt KIntContactHintIsSuffixName=0x100;
const TInt KIntContactHintIsPrefixName=0x200;
const TInt KIntContactHintStorageInline=0x400;
const TInt KIntContactHintIsEmail=0x4000;

class RWriteStream;
class RReadStream;
class CContactFieldStorage;
class CContactTextField;
class CContactStoreField;
class CContactAgentField;
class CContactDateField;
class CContactNumberField;
class TFieldHeader;
class CContactItemField;
class CContactItemFieldDef;
class CContactItem;

/**
 * A contact item field's content type.
 *
 * The content type identifies the field's type and the vCard property
 * which the field maps to. It is owned by the field. Field types are
 * defined as UIDs in cntdef.h.The vCard mapping is optional. It should
 * be specified if the field types alone are not enough to identify the
 * mapping. The possible values for the vCard mapping are defined as UIDs
 * in cntdef.h.Each field is uniquely identified by the combination of
 * UIDs contained in the content type.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContentType : public CBase
    {
public:
    IMPORT_C ~CContentType();
	IMPORT_C static CContentType* NewL();
	IMPORT_C static CContentType* NewL(TFieldType aFieldType,TUid aMapping=KNullUid);
	IMPORT_C static CContentType* NewL(const CContentType &aContentType);
	IMPORT_C void SetMapping(TUid aMapping);
	IMPORT_C void AddFieldTypeL(TFieldType aFieldType);
	IMPORT_C void RemoveFieldType(TFieldType aFieldType);
    IMPORT_C TFieldType FieldType(TInt aIndex) const;
    IMPORT_C TInt FieldTypeCount() const;
    IMPORT_C TUid Mapping() const;
	IMPORT_C TBool ContainsFieldType(TFieldType aFieldType) const;
	IMPORT_C TBool SupportsMultipleLines() const;
	IMPORT_C TBool operator==(const CContentType &aType) const;
	IMPORT_C TBool IsEqualForSyncUpdate(const CContentType& aType) const;
	void Reset();
	void InternalizeAdditionalUidsL(TInt aCount,RReadStream& aStream);
private:
    CContentType();
	CContentType(TUid aMapping);
	void ConstructL();
	void CloneL(const CContentType &aContentType);
private:
    TUid iMapping;
	CArrayFix<TUid>* iFieldTypes;
    };

/**
 * A field in a contact item.
 *
 * Fields are stored in a field set (<code>CContactItemFieldSet</code>)
 * and the field set is owned by the contact item.The contact item field
 * stores the field data. The data may be text, a date/time value, or an
 * agent, as indicated by the storage type (<code>TStorageType</code>).
 * The storage type is also owned by the field. Note that numeric field
 * data is not supported. All numbers, for instance telephone or fax
 * numbers are stored in text fields in the contact database.Fields also
 * have a content type, attributes and a label. The label is a string
 * which identifies the field to a user e.g. First name, Last name.The
 * following attributes are supported: hidden the field is not displayed
 * if the view definition masks hidden fieldsdisabled the field cannot be
 * deleted from the original template and thus is marked as disabledread
 * only the field cannot be written tosynchronise used by Connectivity
 * applications; set by default for all contact item fieldsuser added the
 * field was added by the user and was not taken from the
 * templatetemplate indicates that the field is part of a template.
 * Template fields differ from other fields in that they are persisted
 * when they do not contain any data. This attribute was not present in
 * EPOC Release 5.speed dial the field contains a telephone number which
 * maps to one of the nine possible speed dial positions. This attribute
 * was not present in EPOC Releases 5 or 5.1.These attributes can be set
 * using member functions of this class, but they are normally set by
 * higher level classes, e.g. when setting a speed dial field,
 * <code>CContactDatabase</code> automatically sets the field's speed
 * dial attribute.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactItemField : public CBase
	{
private:
	friend class TFieldHeader;
	friend class CContactItemFieldSet;
	friend class CContactDatabase;
	friend class CContactTables;
	class THint
		{
	public:
		THint();
		THint(TInt aValue);
		TBool operator==(const THint& aHint) const;
		TBool operator!=(const THint& aHint) const;
		inline void SetHasAdditionalUids();
		inline void SetIsMatchAll();
		inline void SetIsPhone();
		inline void SetIsMsg();
		inline void SetIsCompanyName();
		inline void SetIsFamilyName();
		inline void SetIsGivenName();
		inline void SetIsAddress();
		inline void SetIsAdditionalName();
		inline void SetIsSuffixName();
		inline void SetIsPrefixName();
		inline void SetStorageIsInline();
		inline void SetIsEmail();
		inline TBool IsMatchAll() const;
		inline TBool IsDefault() const;
		inline TBool IsPhone() const;
		inline TBool IsMsg() const;
		inline TBool IsCompanyName() const;
		inline TBool IsFamilyName() const;
		inline TBool IsGivenName() const;
		inline TBool IsAddress() const;
		inline TBool IsAdditionalName() const;
		inline TBool IsSuffixName() const;
		inline TBool IsPrefixName() const;
		inline TBool IsStorageInline() const;
		inline TBool IsEmail() const;
		inline TBool Contains(const THint& aHint) const;
		TInt HintType() const;
		TInt FieldId() const;
		void SetFieldId(TInt aId);
		TBool HasAdditionalUids() const;
	public:
		TInt iHintValue;
		};
public:
	IMPORT_C static CContactItemField* NewLC();
	IMPORT_C static CContactItemField* NewL(TStorageType aType);
	IMPORT_C static CContactItemField* NewLC(TStorageType aType);
	IMPORT_C static CContactItemField* NewL(TStorageType aType, TFieldType aFieldType);
	IMPORT_C static CContactItemField* NewLC(TStorageType aType, TFieldType aFieldType);
	IMPORT_C static CContactItemField* NewL(const CContactItemField &aField);
	IMPORT_C static CContactItemField* NewLC(const CContactItemField &aField);
	IMPORT_C static CContactItemField* NewL(TStorageType aType, const CContentType &aContentType);
	IMPORT_C static CContactItemField* NewLC(TStorageType aType, const CContentType &aContentType);
	IMPORT_C ~CContactItemField();

	IMPORT_C TStorageType StorageType() const;
	IMPORT_C const CContentType &ContentType() const;
	inline TBool IsHidden() const;
	inline TBool IsReadOnly() const;
	inline TBool IsDisabled() const;
	inline TBool IsTemplate() const;
	inline TBool IsPrivate() const;
	inline TBool IsSpeedDial() const;
	inline TBool DoSynchronize() const;
	inline TBool OverRidesLabel() const;
	inline TBool HasExtraStream() const;
	inline TBool UsesTemplateTypes() const;
	inline TBool LabelUnspecified() const;
	inline TBool UserAddedField() const;
	IMPORT_C void SetHintType(TInt aType);
	IMPORT_C TPtrC Label() const;
	IMPORT_C void ResetStore();
	IMPORT_C CContactFieldStorage* Storage() const;
	IMPORT_C CContactTextField * TextStorage() const;
	IMPORT_C CContactStoreField * StoreStorage() const;
	IMPORT_C CContactAgentField * AgentStorage() const;
	IMPORT_C CContactDateField * DateTimeStorage() const;
	IMPORT_C CContactNumberField * NumberStorage() const;
	IMPORT_C void AddFieldTypeL(TFieldType aFieldType);
	IMPORT_C void RemoveFieldType(TFieldType aFieldType);
	IMPORT_C void SetMapping(TUid aMapping);
	IMPORT_C void SetHidden(TBool aHidden);
	IMPORT_C void SetReadOnly(TBool aReadOnly);
	IMPORT_C void SetSynchronize(TBool aSynchronize);
	IMPORT_C void SetDisabled(TBool aDisabled);
	IMPORT_C void SetLabelL(const TDesC& aLabel);
	IMPORT_C void SetLabel(HBufC* aLabel);
	IMPORT_C void SetUserAddedField(TBool aUserAddedField);
	IMPORT_C void SetTemplateField(TBool aTemplateField);
	IMPORT_C void SetPrivate(TBool aTemplateField);
	IMPORT_C void SetSpeedDial(TBool aSpeedDialField);
	IMPORT_C void SetId(TInt aId);
	IMPORT_C TInt Id() const;
	IMPORT_C TUint UserFlags() const;
	IMPORT_C void SetUserFlags(TUint aFlags);
	IMPORT_C static TBool IsValidLabel(const TDesC& aLabel,TInt& aInvalidPos);
	IMPORT_C TBool IsTemplateLabelField() const;
public:
	void Reset();
	void SetUsesTemplateTypes(TBool aUsesTemplateTypes);
	TInt TemplateFieldId() const;
	void SetDeleted(TBool aDeleted);
	inline TBool IsDeleted() const;
	void CopyStorageL(const CContactItemField &aField);
protected:
	void UsesTemplateData(TInt aTemplateFieldId);
private:
	void UsesTemplateLabel();
	void SetLabelUnspecified(TBool aUnspecified);
	const CContentType &TemplateContentType(const CContactItemFieldSet &aSystemTemplateFields) const;
	TFieldHeader StoreL(RWriteStream& aTextStream,CStreamStore& aBlobStore,TInt aTextFieldIndex);
	TStreamId StoreAdditionalUidsL(CStreamStore& aStore,TStreamId aId, CArrayFixFlat<TUid> *aAdditionalFields);
  	TStreamId StoreDataL(CStreamStore& aStore);

   	void RestoreL(CStreamStore& aStore,RReadStream& aStream);
	TStreamId RestoreFieldTypesL(RReadStream &aRootStream, const CContactItemFieldSet *aSystemTemplateFields);
    void RestoreDataL(CStreamStore& aStore,TStreamId aId);
	void RestoreTextL(HBufC *aTextStream,TInt aTextFieldIndex);
	
	TBool RestoreIfMatchL(RReadStream& aStream,TFieldType aFieldType, const CContactItemFieldSet *aSystemTemplateFields,HBufC *aTextStream,TInt aTextIndex);
	TBool RestoreIfMatchL(RReadStream& aStream,const CContactItemFieldDef *aFieldDef, const CContactItemFieldSet *aSystemTemplateFields,HBufC *aTextStream,TInt aTextIndex);
 	TStreamId RestoreHintL(CStreamStore& aStore,RReadStream& aStream);
	TBool AddFieldToHint(TFieldType aFieldType, CContactItemField::THint &aHint);
	void MapHintsToFieldTypes(THint aHint);
	CContactItemField();
	CContactItemField(TStorageType aType);
	void CloneL(const CContactItemField &aField);
	void ConstructStorageL();
private:
	enum {EUserMaskShift=4};
	enum // er5 hard coded enum most of which have been used but not documented ;o(
		{
		EHidden				=0x00000001,
		EReadOnly			=0x00000002,
		ESynchronize		=0x00000004,
		EDisabled			=0x00000008,
		/* 0x00000010,-> 0x00000080 are used for 
			the user defined attribs / categories like work /
			Personal / Other / None - used in er5 UI */
		EUserMask			=0x000000F0,
		ETemplateMask		=EUserMask|ESynchronize|EReadOnly|EHidden,
		EOverRidesLabel		=0x00000100,
		EUsesTemplateData	=0x00000200,
		EUserAddedField		=0x00000400,
		ETemplate			=0x00000800,
		/* 0x00001000,-> 0x0000F000 are used for 
			the storage type of the contact field */
		ELabelUnspecified	=0x40000000,
		EDeleted			=0x80000000
		};
	enum 
		// new extended enum to allow cntmodel to have
		// more attributes per field
		{
		EPrivate			=0x00000001,
		ESpeedDial			=0x00000002
		};

private:
	CContentType *iContentType;
	TStorageType iStorageType;
	HBufC* iLabel;
	TInt iId;
	TUint32 iAttributes;
	TUint32 iExtendedAttributes;
	CContactFieldStorage* iStorage;
	TInt iTemplateFieldId;
	};

/**
 * A field definition is an array of field types.
 *
 * Field definitions are used in the <code>CContactDatabase</code> find
 * functions to specify a subset of fields to search.The
 * <code>CContactItemFieldDef</code> class is derived from
 * <code>CArrayFixFlat<TUid></code> so all relevant functions can be
 * used, e.g. to add and remove elements. It adds no functions other than
 * a constructor.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactItemFieldDef : public CArrayFixFlat<TUid>
	{
public:
	/**
	  * The default C++ constructor is used to construct the
	  * <code>CContactItemFieldDef</code> object, with an array granularity of 8. */
	inline CContactItemFieldDef() : CArrayFixFlat<TUid>(8) {};
	};

class TContactFieldAtts
	{
public:
	inline TContactFieldAtts();
	void SetAttribs(TUint32 aAttribs);
	void SetExtendedAttribs(TUint32 aExtendedAttribs);
	void SetType(TStorageType aType);
	void SetCount(TInt aCount);
	void SetTemplateFieldId(TInt aId);
	TUint32 Attribs() const;
	TUint32 ExtendedAttribs() const;
	TStorageType Type() const;
	TInt Count() const;
	TInt TemplateFieldId() const;
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TUint32 iStorage;
	TUint32 iExtendedAttribs;
	};

class TFieldHeader
	{
public:
	inline TFieldHeader(TStreamId aId,TContactFieldAtts aAtts);
public:
	TStreamId iStreamId;
	TContactFieldAtts iAtts;
	};

inline TFieldHeader::TFieldHeader(TStreamId aId,TContactFieldAtts aAtts)
	{ iStreamId=aId; iAtts=aAtts; }

/**
 * Gets the field's hidden attribute.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if hidden attribute set,
 *            <code>EFalse</code> if not set.
 */
inline TBool CContactItemField::IsHidden() const
    { return iAttributes&EHidden; }
/**
 * Gets the field's read only attribute.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if read only attribute set,
 *            <code>EFalse</code> if not set.
 */
inline TBool CContactItemField::IsReadOnly() const
    { return iAttributes&EReadOnly; }
/**
 * Tests the field's disabled attribute.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if disabled attribute set,
 *            <code>EFalse</code> if disabled attribute not set.
 */
inline TBool CContactItemField::IsDisabled() const
	{ return iAttributes&EDisabled; }
/**
 * Tests whether the field is in a template, as set by
 * <code>SetTemplateField()</code>.
 *
 * @since     5.2
 * @returns   "TBool"
 *            <code>ETrue</code> if field is a template field.
 *            <code>EFalse</code> if not.
 */
inline TBool CContactItemField::IsTemplate() const
	{ return iAttributes&ETemplate; }
/**
 * Tests whether the field's private attribute is set.
 *
 * @since     5.2
 * @returns   "TBool"
 *            True if the field's private attribute is set, false if
 *            not.
 */
inline TBool CContactItemField::IsPrivate() const
	{ return iExtendedAttributes&EPrivate; }
/**
 * Tests whether the field is a speed dial field.
 *
 * @since     5.2
 * @returns   "TBool"
 *            True if the field is a speed dial field, false if not.
 */
inline TBool CContactItemField::IsSpeedDial() const
	{ return iExtendedAttributes&ESpeedDial; }
/**
 * Gets the status of the field's synchronise attribute.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if synchronise attribute set,
 *            <code>EFalse</code> if not set.
 */
inline TBool CContactItemField::DoSynchronize() const
    { return iAttributes&ESynchronize; }
inline TBool CContactItemField::IsDeleted() const
	{ return iAttributes&EDeleted; }

inline void CContactItemField::THint::SetHasAdditionalUids()
	{iHintValue|=KHintAdditionalMask;}
inline void CContactItemField::THint::SetIsPhone()
	{iHintValue|=KIntContactHintIsPhone;}
inline void CContactItemField::THint::SetIsMsg()
	{iHintValue|=KIntContactHintIsMsg;}
inline void CContactItemField::THint::SetIsCompanyName()
	{iHintValue|=KIntContactHintIsCompanyName;}
inline void CContactItemField::THint::SetIsFamilyName()
	{iHintValue|=KIntContactHintIsFamilyName;}
inline void CContactItemField::THint::SetIsGivenName()
	{iHintValue|=KIntContactHintIsGivenName;}
inline void CContactItemField::THint::SetIsAddress()
	{iHintValue|=KIntContactHintIsAddress;}
inline void CContactItemField::THint::SetIsAdditionalName()
	{iHintValue|=KIntContactHintIsAdditionalName;}
inline void CContactItemField::THint::SetIsSuffixName()
	{iHintValue|=KIntContactHintIsSuffixName;}
inline void CContactItemField::THint::SetIsPrefixName()
	{iHintValue|=KIntContactHintIsPrefixName;}
inline void CContactItemField::THint::SetStorageIsInline()
	{iHintValue|=KIntContactHintStorageInline;}
inline void CContactItemField::THint::SetIsEmail()
	{iHintValue|=KIntContactHintIsEmail;}
inline TBool CContactItemField::THint::IsPhone() const
	{return (iHintValue&KIntContactHintIsPhone);}
inline TBool CContactItemField::THint::IsMsg() const
	{return (iHintValue&KIntContactHintIsMsg);}
inline TBool CContactItemField::THint::IsCompanyName() const
	{return (iHintValue&KIntContactHintIsCompanyName);}
inline TBool CContactItemField::THint::IsFamilyName() const
	{return (iHintValue&KIntContactHintIsFamilyName);}
inline TBool CContactItemField::THint::IsGivenName() const
	{return (iHintValue&KIntContactHintIsGivenName);}
inline TBool CContactItemField::THint::IsAddress() const
	{return (iHintValue&KIntContactHintIsAddress);}
inline TBool CContactItemField::THint::IsAdditionalName() const
	{return (iHintValue&KIntContactHintIsAdditionalName);}
inline TBool CContactItemField::THint::IsSuffixName() const
	{return (iHintValue&KIntContactHintIsSuffixName);}
inline TBool CContactItemField::THint::IsPrefixName() const
	{return (iHintValue&KIntContactHintIsPrefixName);}
inline TBool CContactItemField::THint::IsStorageInline() const
	{return (iHintValue&KIntContactHintStorageInline);}
inline TBool CContactItemField::THint::IsEmail() const
	{return (iHintValue&KIntContactHintIsEmail);}
inline TBool CContactItemField::THint::Contains(const THint& aHint) const
	{return (iHintValue&aHint.iHintValue);}
/**
 * Tests whether the field's label (as set by <code>SetLabel()</code>)
 * overrides the label specified in the field's template.
 *
 * @returns   "TBool"
 *            True if the field's label overrides the label
 *            specified in the template; false if not.
 */
inline TBool CContactItemField::OverRidesLabel() const
	{return iAttributes&EOverRidesLabel;}
/**
 * Tests whether the field needs an extra stream to store information not
 * contained in the template.
 *
 * This is the case if the field's content type is not based on a
 * template, or if the field has a label which overrides the label
 * specified in the template.
 *
 * @returns   "TBool"
 *            True if the field uses an extra stream; false if not.
 */
inline TBool CContactItemField::HasExtraStream() const
	{return(!(iAttributes&EUsesTemplateData) || iAttributes&EOverRidesLabel);}
/**
 * Indicates whether or not the field's content type is based on a
 * template.
 *
 * @returns   "TBool"
 *            True if the field's content type is based on a
 *            template; false if not.
 */
inline TBool CContactItemField::UsesTemplateTypes() const
	{return iAttributes&EUsesTemplateData;}
/**
 * Tests whether the field's label has been set, either by a call to
 * <code>SetLabel()</code> or by inheriting a label specified in the
 * template.
 *
 * @returns   "TBool"
 *            True if the field's label has been set, false if not.
 */
inline TBool CContactItemField::LabelUnspecified() const
	{return iAttributes&ELabelUnspecified;}
/**
 * Tests the value of the user added field attribute.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the user added attribute is set,
 *            <code>EFalse</code> if not.
 */
inline TBool CContactItemField::UserAddedField() const
	{return iAttributes&EUserAddedField;}
#endif
