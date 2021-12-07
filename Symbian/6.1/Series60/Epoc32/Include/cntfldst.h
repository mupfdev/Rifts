// CNTFLDST.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#if !defined(__CNTFLDST_H__)
#define __CNTFLDST_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif

#if !defined(__S32STD_H__)
#include <s32std.h>
#endif

#if !defined(__CNTDEF_H__)
#include <cntdef.h>
#endif
#define KTextStreamSeparator 0x00



class CStreamStore;

/**
 * Abstract base class for the different types of contact field data
 * storage.
 *
 * <code>CContactTextField</code>, <code>CContactStoreField</code>,
 * <code>CContactAgentField</code>, <code>CContactDateField</code> and
 * <code>CContactNumberField</code> are all derived from this class.A
 * pointer to the base class can be obtained by calling
 * <code>CContactItemField::Storage()</code>. Pointers to the derived
 * classes can be retrieved by calling
 * <code>CContactItemField::TextStorage()</code>,
 * <code>CContactItemField::StoreStorage()</code> etc.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactFieldStorage : public CBase
	{
public:
	/**
	  *
	  * Internalises the field data.
	  *
	  * @param     "RReadStream& aStream"
	  *            Stream from which the the contents of the field should
	  *            be internalised.
	  */
    virtual void InternalizeL( RReadStream& aStream)=0;
	/**
	  * Externalises the field data.
	  *
	  * @param     "RWriteStream& aStream"
	  *            Write stream to which the contents of the field should
	  *            be externalised.
	  */
    virtual void ExternalizeL(RWriteStream& aStream) const=0;
	/**
	  *
	  * Stores the field data.
	  *
	  * @param     "CStreamStore& aStore"
	  *            Reference to the stream store to which the field data
	  *            is written.
	  * @returns   "TStreamId"
	  *            The ID of the stream store.
	  */
	virtual TStreamId StoreL(CStreamStore& aStore) const=0;
	/**
	  *
	  * Restores the field data.
	  *
	  * @param     "CStreamStore& aStore"
	  *            Reference to the store from which the object is to be
	  *            restored.
	  * @param     "RReadStream& aStream"
	  *            Reference to the stream which should be passed to
	  *            <code>InternalizeL()</code>.
	  */
	virtual void RestoreL(CStreamStore& aStore,RReadStream& aStream)=0;
	/**
	  *
	  * Tests whether the field storage contains data.
	  *
	  * @returns   "TBool"
	  *            True if the field storage contains data, false if not.
	  */
	virtual TBool IsFull() const=0;
private:
	IMPORT_C virtual void CContactFieldStorage_Reserved1();
	TAny* CContactFieldStorage_Reserved;
	};

/**
 * Sets and gets the text stored in a contact item field.
 *
 * An object of this class can be retrieved using
 * <code>CContactItemField::TextStorage()</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactTextField : public CContactFieldStorage
	{
public:
	IMPORT_C ~CContactTextField();
public: 
	void InternalizeL(HBufC *aTextStream,TInt aTextFieldIndex);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
    void ExternalizeL(RWriteStream& aStream,TBool aIsInlineBlob,TInt aTextFieldIndex) const;
	TStreamId StoreL(CStreamStore& aStore) const;
	void RestoreL(CStreamStore& aStore,RReadStream& aStream);
	IMPORT_C void SetTextL(const TDesC& aText);
	IMPORT_C void SetText(HBufC *aHbuf);
	IMPORT_C void SetTextArray(MDesCArray* anArray);
	IMPORT_C TPtrC Text() const;
	TBool IsFull() const;
	IMPORT_C TPtrC StandardTextLC() const;
	IMPORT_C void SetStandardTextL(const TDesC& aText);
	IMPORT_C void SetStandardTextArray(MDesCArray* anArray);
private:
	HBufC *EncodeL(const TDesC& aText,TUid aConversion) const;
	IMPORT_C /*virtual*/ void CContactFieldStorage_Reserved1();
private:
	HBufC* iText;
	};

/**
 * Stores, sets and retrieves binary field datawhich is contained in an
 * 8-bit descriptor.
 *
 * An object of this class can be retrieved using
 * <code>CContactItemField::StoreStorage()</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactStoreField : public CContactFieldStorage
	{
public:
	~CContactStoreField();
	TStreamId StoreL(CStreamStore& aStore) const;
	void RestoreL(CStreamStore& aStore,RReadStream& aStream);
	IMPORT_C void SetThingL(const TDesC8& aDes);
	IMPORT_C void SetThingL(const HBufC8& aDes);
	IMPORT_C void SetThingL(const CBufBase* aBuf);
	IMPORT_C HBufC8* Thing() const; 
	void InternalizeL(RReadStream& aStream);
    void ExternalizeL(RWriteStream& aStream) const;
	TBool IsFull() const;
private:
	IMPORT_C /*virtual*/ void CContactFieldStorage_Reserved1();
private:
	HBufC8* iThing;
	};

/**
 * Storage for an agent ID.
 *
 * An agent is a field in a contact item which contains another person's
 * contact details. It corresponds to the agent property in the vCard
 * specification (version 2.1). The agent is identified by an agent ID (a
 * <code>TContactItemId</code>).An object of this class can be retrieved
 * using <code>CContactItemField::AgentStorage()</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactAgentField : public CContactFieldStorage
	{
public:
	TStreamId StoreL(CStreamStore& aStore) const;
	void RestoreL(CStreamStore& aStore,RReadStream& aStream);
	IMPORT_C void SetAgentId(TContactItemId aId);
	IMPORT_C TContactItemId Value() const;
	void InternalizeL( RReadStream& aStream);
    void ExternalizeL(RWriteStream& aStream) const;
	TBool IsFull() const;
private:
	IMPORT_C /*virtual*/ void CContactFieldStorage_Reserved1();
private:
	TContactItemId iAgentId;
	};

/**
 * Sets and gets the date/time value stored in a contact item field.
 *
 * An object of this class can be retrieved using
 * <code>CContactItemField::DateTimeStorage()</code>.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactDateField : public CContactFieldStorage
	{
public:
	CContactDateField();
	TStreamId StoreL(CStreamStore& aStore) const;
	void RestoreL(CStreamStore& aStore,RReadStream& aStream);
	IMPORT_C void SetTime(TTime atime);
	IMPORT_C void SetTime(TDateTime aDateTime);
	IMPORT_C TTime Time() const;
	void InternalizeL( RReadStream& aStream);
    void ExternalizeL(RWriteStream& aStream) const;
	TBool IsFull() const;
private:
	IMPORT_C /*virtual*/ void CContactFieldStorage_Reserved1();
private:
	TTime iTime;
	};

/**
 * An integer value stored in a contact item field.
 *
 * This class is not currently supported in the Contacts Model.
 *
 * @since 5.0
 * @lib "cntmodel.lib"
 */
class CContactNumberField : public CContactFieldStorage
    {
public:
	TStreamId StoreL(CStreamStore& aStore) const;
	void RestoreL(CStreamStore& aStore,RReadStream& aStream);
	IMPORT_C void SetNumber(TInt aNumber);
	IMPORT_C TInt Value() const;
	void InternalizeL( RReadStream& aStream);
    void ExternalizeL(RWriteStream& aStream) const;
	TBool IsFull() const;
private:
	IMPORT_C /*virtual*/ void CContactFieldStorage_Reserved1();
private:
    TInt iNumber;
    };

#endif
