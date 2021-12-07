//
// btsdp.h
//
// Copyright (c) 2000-2001 Symbian Ltd.  All rights reserved.
//

#ifndef BTSDP_H
#define BTSDP_H

#include <e32base.h>
#include <bttypes.h>

static const TUid KUidServiceSDP			= {0x100095FA};

typedef TUint16 TSdpAttributeID;

// Universal Attributes
static const TSdpAttributeID KSdpAttrIdServiceRecordHandle = 0x0000;
static const TSdpAttributeID KSdpAttrIdServiceClassIDList = 0x0001;
static const TSdpAttributeID KSdpAttrIdServiceRecordState = 0x0002;
static const TSdpAttributeID KSdpAttrIdServiceID = 0x0003;
static const TSdpAttributeID KSdpAttrIdProtocolDescriptorList = 0x0004;
static const TSdpAttributeID KSdpAttrIdBrowseGroupList = 0x0005;
static const TSdpAttributeID KSdpAttrIdLanguageBaseAttributeIDList = 0x0006;
static const TSdpAttributeID KSdpAttrIdServiceInfoTimeToLive = 0x0007;
static const TSdpAttributeID KSdpAttrIdServiceAvailability = 0x0008;
static const TSdpAttributeID KSdpAttrIdBluetoothProfileDescriptorList = 0x0009;
static const TSdpAttributeID KSdpAttrIdDocumentationURL = 0x000A;
static const TSdpAttributeID KSdpAttrIdClientExecutableURL = 0x000B;
static const TSdpAttributeID KSdpAttrIdIconURL = 0x000C;

// Language specific attributes
static const TSdpAttributeID KSdpAttrIdBasePrimaryLanguage = 0x0100;
static const TInt KSdpAttrIdOffsetServiceName = 0x0000; // + Language offset
static const TInt KSdpAttrIdOffsetServiceDescription = 0x0001; // + Language offset
static const TInt KSdpAttrIdOffsetProviderName = 0x0002; // + Language offset

// SDP server specific attributes
static const TSdpAttributeID KSdpAttrIdSdpServerVersionNumberList = 0x0200;
static const TSdpAttributeID KSdpAttrIdSdpServerServiceDatabaseState = 0x0201;
static const TSdpAttributeID KSdpAttrIdSdpServerGroupID = 0x0200;

/************************************************************************/
//
//   SDP database server API
//
/************************************************************************/

typedef TPckgBuf<TSdpAttributeID> TSdpAttributeIDPckgBuf;
typedef TUint32 TSdpServRecordHandle;
typedef TPckgBuf<TSdpServRecordHandle> TSdpServRecordHandlePckgBuf;

/**
   The main session class.
   Used to create subsessions to database functionality.
**/
class RSdp : public RSessionBase
	{
public:
	IMPORT_C RSdp();
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	IMPORT_C void ResourceCountMarkStart();
	IMPORT_C void ResourceCountMarkEnd();
	IMPORT_C TInt ResourceCount();
	};

/**
   Subsession base class.
   Contains basic subssession functionality.

   @private
**/
class RSdpSubSession : public RSubSessionBase
	{
public:
	IMPORT_C virtual TInt Open(RSdp& aSession) = 0;
	IMPORT_C virtual void Close() = 0;
	};



class CSdpAttrValueDES;
class CSdpAttrValue;

/**
   API for creating, modifying and deleting service record.
   
   Allow service records to be added and deleted, and arbitrary
   attributes to be added, updated and deleted from these records.
**/
class RSdpDatabase : public RSdpSubSession
	{
public:
	IMPORT_C RSdpDatabase();
	IMPORT_C TInt Open(RSdp& aSession);
	IMPORT_C void Close();
	IMPORT_C void CreateServiceRecordL(const TUUID& aUUID, TSdpServRecordHandle& aHandle);
	IMPORT_C void CreateServiceRecordL(CSdpAttrValueDES& aUUIDList, TSdpServRecordHandle& aHandle);
	IMPORT_C void UpdateAttributeL(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, CSdpAttrValue& aAttrValue);
	IMPORT_C void UpdateAttributeL(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, TUint aUintValue);
	IMPORT_C void UpdateAttributeL(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, const TDesC16& aDesCValue);
	IMPORT_C void UpdateAttributeL(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, const TDesC8& aDesCValue);
	IMPORT_C void DeleteAttributeL(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID);
	IMPORT_C void DeleteRecordL(TSdpServRecordHandle aHandle);
private:
	HBufC8* iBuffer; //used for synchronous requests (could have been local)
	};


/**
   Interface class from the element parser.

   The member functions of this interface are called by the
   CElementParser class whenever it decodes an element of a specific
   type.
**/
class MSdpElementBuilder
	{
public:
	IMPORT_C virtual MSdpElementBuilder* BuildUnknownL(TUint8 aType, TUint8 aSizeDesc, const TDesC8& aData);
	IMPORT_C virtual MSdpElementBuilder* BuildNilL();
	IMPORT_C virtual MSdpElementBuilder* BuildUintL(const TDesC8& aUint);
	IMPORT_C virtual MSdpElementBuilder* BuildIntL(const TDesC8& aInt);
	IMPORT_C virtual MSdpElementBuilder* BuildUUIDL(const TUUID& aUUID);
 	IMPORT_C virtual MSdpElementBuilder* BuildBooleanL(TBool aBool);
	IMPORT_C virtual MSdpElementBuilder* BuildStringL(const TDesC8& aString);
	IMPORT_C virtual MSdpElementBuilder* BuildDESL();  // Must not return NULL
	IMPORT_C virtual MSdpElementBuilder* BuildDEAL();  // ditto
	IMPORT_C virtual MSdpElementBuilder* StartListL(); // ditto
	IMPORT_C virtual MSdpElementBuilder* EndListL();
	IMPORT_C virtual MSdpElementBuilder* BuildURLL(const TDesC8& aURL);
	};

enum TSdpElementType
	{
	ETypeNil		=  0,
	ETypeUint		=  1,
	ETypeInt		=  2,
	ETypeUUID		=  3,
	ETypeString		=  4,
	ETypeBoolean	=  5,
	ETypeDES		=  6,
	ETypeDEA		=  7,
	ETypeURL		=  8,
	ETypeEncoded	= 32,	// Outside SDP reserved range
	};

class MSdpAttributeValueVisitor;

/**
   Base class for all SDP values in the database.

   Derived classes from this are used as the values for SDP service
   record attributes.  They can also be built using the parser to
   decode elements.
**/
class CSdpAttrValue : public CBase
	{
public:
	CSdpAttrValue();
	virtual ~CSdpAttrValue();
	virtual TSdpElementType Type() const=0;
	virtual TUint DataSize() const=0;

	// getter interface
	virtual TUint Uint() const;
	virtual TInt Int() const;
	virtual TBool DoesIntFit() const;
	virtual TInt Bool() const;
	virtual const TUUID &UUID() const;
	virtual const TPtrC8 Des() const;

	virtual void AcceptVisitorL(MSdpAttributeValueVisitor& aVisitor);
	};

/**
   This is a list of attr-values => can build its constituents.

   Used for DataElementSequences and DataElementAlternative
**/
class CSdpAttrValueList : public CSdpAttrValue, public MSdpElementBuilder
	{
public:
	IMPORT_C virtual ~CSdpAttrValueList();
	IMPORT_C virtual void AcceptVisitorL(MSdpAttributeValueVisitor& aVisitor);
	IMPORT_C virtual TUint DataSize() const;
	IMPORT_C void AppendValueL(CSdpAttrValue* aValue);

	// MSdpElementBuilder interface
	IMPORT_C virtual MSdpElementBuilder* BuildUnknownL(TUint8 aType, TUint8 aSizeDesc, const TDesC8& aData);
	IMPORT_C virtual MSdpElementBuilder* BuildNilL();
	IMPORT_C virtual MSdpElementBuilder* BuildUintL(const TDesC8& aUint);
	IMPORT_C virtual MSdpElementBuilder* BuildIntL(const TDesC8& aInt);
	IMPORT_C virtual MSdpElementBuilder* BuildUUIDL(const TUUID& aUUID);
	IMPORT_C virtual MSdpElementBuilder* BuildBooleanL(TBool aBool);
	IMPORT_C virtual MSdpElementBuilder* BuildStringL(const TDesC8& aString);
	IMPORT_C virtual MSdpElementBuilder* BuildDESL();
	IMPORT_C virtual MSdpElementBuilder* BuildDEAL();
	IMPORT_C virtual MSdpElementBuilder* StartListL();
	IMPORT_C virtual MSdpElementBuilder* EndListL();
	IMPORT_C virtual MSdpElementBuilder* BuildURLL(const TDesC8& aString);
	IMPORT_C virtual MSdpElementBuilder* BuildEncodedL(const TDesC8& aString);

protected:
	CSdpAttrValueList(MSdpElementBuilder *aBuilder);
	void ConstructL();

private:
	MSdpElementBuilder *iParent;

protected:
	CArrayPtr<CSdpAttrValue> *iList;
	};


/**
   Represents a Nil element value.

   There are no accessors for this type, for obvious reasons.
**/
class CSdpAttrValueNil : public CSdpAttrValue
	{
public:
	IMPORT_C static CSdpAttrValueNil *NewNilL();
	virtual ~CSdpAttrValueNil();
	virtual TSdpElementType Type() const;
	virtual TUint DataSize() const;
private:
	CSdpAttrValueNil();
private:
	};

static const TInt KSdpMaxUintSize = 16;

/**
   Represents a unsigned integer value of an attribute.

   The uint can be up to 128 bits in size.
**/
class CSdpAttrValueUint : public CSdpAttrValue
	{
public:
	IMPORT_C static CSdpAttrValueUint* NewUintL(const TDesC8 &aUint);
	virtual ~CSdpAttrValueUint();
	virtual TSdpElementType Type() const;
	virtual TUint DataSize() const;
	TUint Uint() const;
	virtual TBool DoesIntFit() const;
	virtual const TPtrC8 Des() const;
private:
	CSdpAttrValueUint(const TDesC8 & aUint);
private:
	TBuf8<KSdpMaxUintSize> iUint;
	};

static const TInt KMaxIntSize  = 16;

/**
   Represents a integer value of an attribute.

   The int can be up to 128 bits in size.
**/
class CSdpAttrValueInt : public CSdpAttrValue
	{
public:
	IMPORT_C static CSdpAttrValueInt* NewIntL(const TDesC8 &aInt);
	virtual ~CSdpAttrValueInt();
	virtual TSdpElementType Type() const;
	virtual TUint DataSize() const;
	virtual TInt Int() const;
	virtual TBool DoesIntFit() const;
	virtual const TPtrC8 Des() const;
private:
	CSdpAttrValueInt(const TDesC8 & aInt);
private:
	TBuf8<KMaxIntSize> iInt;
	};


/**
   Represents a UUID value of an attribute.

   The UUID can be up to 128 bits in size.
**/
class CSdpAttrValueUUID : public CSdpAttrValue
	{
public:
	IMPORT_C static CSdpAttrValueUUID* NewUUIDL(const TUUID& aUUID);
	virtual ~CSdpAttrValueUUID();
	virtual TSdpElementType Type() const;
	virtual TUint DataSize() const;
	// getters
	virtual const TUUID &UUID() const;
	virtual const TPtrC8 Des() const;
private:
	CSdpAttrValueUUID(const TUUID& aUUID);
private:
	TUUID iUUID;
	};

/**
   Represents a string value of an attribute.

   The encoding of the string is up to the user.  The interpretation
   of the encoding is enabled using facilities in SDP.
**/
class CSdpAttrValueString : public CSdpAttrValue
	{
public:
	IMPORT_C static CSdpAttrValueString* NewStringL(const TDesC8& aString);
	virtual ~CSdpAttrValueString();
	virtual TSdpElementType Type() const;
	virtual TUint DataSize() const;
	virtual const TPtrC8 Des() const;
private:
	CSdpAttrValueString();
	void ConstructL(const TDesC8& aString);
private:
	HBufC8 *iBuffer;
	};

/**
   Represents a boolean value of an attribute.

**/
class CSdpAttrValueBoolean : public CSdpAttrValue
	{
public:
	IMPORT_C static CSdpAttrValueBoolean *NewBoolL(TBool aBool);
	virtual ~CSdpAttrValueBoolean();
	virtual TSdpElementType Type() const;
	virtual TUint DataSize() const;
	virtual TBool Bool() const;
private:
	CSdpAttrValueBoolean(TBool aBool);
private:
	TBool iBool;
	};

/**
   Represents a data element sequence value of an attribute.

   A DES can contain other values within it, including other
   sequences.  This enables arbitrary tree structures to be created.
**/

class CSdpAttrValueDES : public CSdpAttrValueList
	{
public:
	IMPORT_C static CSdpAttrValueDES* NewDESL(MSdpElementBuilder* aBuilder);
	virtual TSdpElementType Type() const;
private:
	CSdpAttrValueDES(MSdpElementBuilder *aBuilder);
	};

/**
   Represents a data element alternative value of an attribute.

   A DEA can contain other values within it, including other
   sequences.  This enables arbitrary tree structures to be created.
**/
class CSdpAttrValueDEA : public CSdpAttrValueList
	{
public:
	IMPORT_C static CSdpAttrValueDEA* NewDEAL(MSdpElementBuilder* aBuilder);
	virtual TSdpElementType Type() const;
private:
	CSdpAttrValueDEA(MSdpElementBuilder *aBuilder);
	};

/**
   Represents a URL value of an attribute.

**/
class CSdpAttrValueURL : public CSdpAttrValue
	{
public:
	IMPORT_C static CSdpAttrValueURL* NewURLL(const TDesC8& aString);
	virtual ~CSdpAttrValueURL();
	virtual TSdpElementType Type() const;
	virtual const TPtrC8 Des() const;
	virtual TUint DataSize() const;
private:
	CSdpAttrValueURL();
	void ConstructL(const TDesC8& aString);
private:
	HBufC8 *iBuffer;
	};

class MSdpAttributeValueVisitor
	{
public:
    virtual void VisitAttributeValueL(CSdpAttrValue &aValue, TSdpElementType aType)=0;
    virtual void StartListL(CSdpAttrValueList &aList)=0;
    virtual void EndListL()=0;
	};

template<class T>
class TSdpIntBuf : public TBufC8<sizeof(T)>
	{
public:
	inline TSdpIntBuf(const T& aRef);
	};

TEMPLATE_SPECIALIZATION class TSdpIntBuf<TUint32> : public TSdpIntBuf<TUint>
	{
public:
	inline TSdpIntBuf(const TUint32& aRef);
	};

TEMPLATE_SPECIALIZATION class TSdpIntBuf<TUint16> : public TSdpIntBuf<TUint>
	{
public:
	inline TSdpIntBuf(const TUint16& aRef);
	};

class SdpUtil
	{
public:
	IMPORT_C static TUint GetUint(const TDesC8& aData);
	IMPORT_C static void PutUint(TUint8* aPtr, TInt64 aInt, TInt aNumberOfBytes);
	};

//*************************************************************
//
//  SDP Agent client API
//
//*************************************************************


/**
	Mixin class to be implemented by the user. The functions herein will be 
	called for the user of CSdpAgent when responses are received from the 
	remote SDP Server.
**/
class MSdpAgentNotifier
	{
public:
	virtual void NextRecordRequestComplete(TInt aError, TSdpServRecordHandle aHandle, TInt aTotalRecordsCount) = 0;
	virtual void AttributeRequestResult(TSdpServRecordHandle aHandle, TSdpAttributeID aAttrID, CSdpAttrValue* aAttrValue) = 0;
	virtual void AttributeRequestComplete(TSdpServRecordHandle, TInt aError) = 0;
	};

class CSdpAgentEng;
class CSdpSearchPattern;
class CSdpAttrIdMatchList;

/**
	Class for making SDP requests from a remote SDP server.
	To make SDP requests, construct a CSdpAgent using the Bluettoth address of 
	the remote device to query. Call SetRecordFilterL to specify the UUIDs to 
	be searched for. Then make calls to NextRecordRequestL() and one of the 
	overloads of AttributeRequestL to retrieve information from the remote 
	device.
**/
class CSdpAgent : public CBase
	{
public:
	IMPORT_C static CSdpAgent* NewL(MSdpAgentNotifier& aNotifier, const TBTDevAddr& aDevAddr);
	IMPORT_C static CSdpAgent* NewLC(MSdpAgentNotifier& aNotifier, const TBTDevAddr& aDevAddr);
	IMPORT_C ~CSdpAgent();
	IMPORT_C void SetRecordFilterL(const CSdpSearchPattern& aUUIDFilter);
	IMPORT_C void SetAttributePredictorListL(const CSdpAttrIdMatchList& aMatchList);
	IMPORT_C void NextRecordRequestL();

	IMPORT_C void AttributeRequestL(TSdpServRecordHandle aHandle, 
								   TSdpAttributeID aAttrID);
	IMPORT_C void AttributeRequestL(TSdpServRecordHandle aHandle, 
								   const CSdpAttrIdMatchList& aMatchList);
	IMPORT_C void AttributeRequestL(MSdpElementBuilder* aBuilder,
		                           TSdpServRecordHandle aHandle, 
								   TSdpAttributeID aAttrID);
	IMPORT_C void AttributeRequestL(MSdpElementBuilder* aBuilder,
		                           TSdpServRecordHandle aHandle, 
								   const CSdpAttrIdMatchList& aMatchList);
	IMPORT_C void Cancel();

private:
	CSdpAgent();
	void ConstructL(MSdpAgentNotifier& aNotifier, TBTDevAddr aDevAddr);


private:
	CSdpAgentEng* iAgentEngine;
	};


/**
	SDP UUID search pattern.
	Holds a list of UUIDs which will be matched in SDP Service Search Requests.
**/
class CSdpSearchPattern : public CBase, public MSdpElementBuilder
	{
public:
	IMPORT_C static CSdpSearchPattern* NewL();
	IMPORT_C void ConstructL();
	IMPORT_C ~CSdpSearchPattern();
	IMPORT_C TInt AddL(const TUUID& aUUID);
	IMPORT_C TInt Remove(const TUUID& aUUID);
	IMPORT_C TInt Find(const TUUID& aUUID, TInt &aPos) const;
	IMPORT_C TInt Count() const;
	IMPORT_C const TUUID At(TInt anIndex) const;
	IMPORT_C void Reset();
	inline TBool IsEmpty();

	
private:
	CSdpSearchPattern();

private:
	// Implementation of Mbuilder interface
	MSdpElementBuilder* BuildUUIDL(const TUUID& aUUID);
	MSdpElementBuilder* BuildDESL();
	MSdpElementBuilder* StartListL();
	MSdpElementBuilder* EndListL();
private:
	CArrayFixFlat<TUUID>* iUUIDArray;
	};

struct TAttrRange
	{
public:
	TAttrRange() {};
	TAttrRange(TSdpAttributeID aAttrId) : iStart(aAttrId), iEnd(aAttrId) {}
	TAttrRange(TSdpAttributeID aStart, TSdpAttributeID aEnd) : iStart(aStart), iEnd(aEnd) {ASSERT(iStart <= iEnd);}
	inline TBool IsInRange(TSdpAttributeID aAttrId) const;
	inline TBool IsContiguousWith(TSdpAttributeID aAttrId) const;
	inline TBool IsContiguousWith(TAttrRange aRange) const;

public:
	TSdpAttributeID iStart;
	TSdpAttributeID iEnd;
	};

#define KAttrRangeAll TAttrRange(0, KMaxTUint16)

class CSdpServRecord;
class CElementEncoder;
class MAttributeMatchHandler;

/**
	SDP Attribute ID Match list.
	Holds a list of Attribute IDs to be retrieved from a remote device in an 
	Service Attribute Request.
	Set in terms of ranges of attributes, each one specified through a 
	TAttrRange.
**/
class CSdpAttrIdMatchList : public CBase, public MSdpElementBuilder
	{
public:
	IMPORT_C static CSdpAttrIdMatchList* NewL();
	IMPORT_C static CSdpAttrIdMatchList* NewL(const CSdpAttrIdMatchList& aAttrMatchList);
	IMPORT_C ~CSdpAttrIdMatchList();
	IMPORT_C void AddL(TAttrRange aRange);
	IMPORT_C void RemoveL(TAttrRange aRange);
	TInt Find(TSdpAttributeID aAttrId, TInt &aPos) const;
	IMPORT_C TBool InMatchList(TSdpAttributeID aAttrId, TInt &aPos) const;
	inline TBool InMatchList(TSdpAttributeID aAttrId) const;
	inline TInt Count() const;

	void FindAttributesL(CSdpServRecord &aRec, MAttributeMatchHandler &aHandler) const;
    IMPORT_C TUint EncodeL(CElementEncoder& aEncoder) const;

private:
	// Implementation of MSdpElementBuilder interface
	MSdpElementBuilder* BuildUintL(const TDesC8& aUint);
	MSdpElementBuilder* BuildDESL();
	MSdpElementBuilder* StartListL();
	MSdpElementBuilder* EndListL();

private:
	CSdpAttrIdMatchList();
	CArrayFix<TAttrRange>* iList;

	__DECLARE_TEST;
	};


// interface via NetDB
// includes parser and builder to use it


const static TInt KSdpErrorBase = -6400;
const static TInt KErrSdpAlreadyBound = KSdpErrorBase;
const static TInt KErrSdpPeerError = KSdpErrorBase-1;
const static TInt KErrSdpClientNotConnected = KSdpErrorBase-2;
const static TInt KErrSdpUnsupportedVersion = KSdpErrorBase-3;
const static TInt KErrSdpBadRecordHandle = KSdpErrorBase-4;
const static TInt KErrSdpBadContinuationState = KSdpErrorBase-5;
const static TInt KErrSdpServerRejectedRequest = KSdpErrorBase-6;
const static TInt KErrSdpBadRequestBufferLength = KSdpErrorBase-7;
const static TInt KErrSdpBadResultBufferLength = KSdpErrorBase-8;
const static TInt KErrSdpBadUUIDLength = KSdpErrorBase-9;
const static TInt KErrSdpBadResultData = KSdpErrorBase-10;
const static TInt KErrSdpDatabaseFull = KSdpErrorBase-11;


template <class T> class CSdpStackFix;

/**
   Parser for element encoded SDP values.

   Parses an input buffer, calling a MSdpElementBuilder each time an element is
   decoded.  This parser can parse incrementally, and be fed new data
   as it arrives.
**/
class CElementParser : public CBase
	{
public:
class CLinearBuf : public CBase
	{
public:
	static CLinearBuf* NewLC(TInt aExpandSize);
	~CLinearBuf();
	void AppendL(const TDesC8& aData);
	const TPtrC8 Ptr() const;
	void Consume(TInt aLength);
	TInt Size() const;

private:
	CLinearBuf();
	void ConstructL(TInt aExpandSize);

	CBufFlat* iBuf;
	TInt iStartOffset;
	};

public:
	IMPORT_C static CElementParser* NewL(MSdpElementBuilder* aBuilder);
	IMPORT_C ~CElementParser();
	IMPORT_C TInt ParseElementsL(const TDesC8& aData);
	IMPORT_C TBool BufferedParseL(const TDesC8& aData);
	IMPORT_C void Reset();
	IMPORT_C void Reset(MSdpElementBuilder* aBuilder);
	void SetBuilder(MSdpElementBuilder* aBuilder);
	MSdpElementBuilder* Builder();

private:
	void ConstructL();
	CElementParser(MSdpElementBuilder* aBuilder);
	static TBool IsComposite(TUint8 aType);
	void CloseListsL();

	MSdpElementBuilder* iBuilder;
	CSdpStackFix<TInt>* iListStack;
	CLinearBuf* iRemainderBuf;
	};


#include <btsdp.inl>

#endif
