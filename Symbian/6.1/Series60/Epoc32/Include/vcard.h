// VCARD.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
 
#if !defined(__VCARD_H__)
#define __VCARD_H__

#if !defined(__VERSIT_H__)
#include <versit.h>
#endif

_LIT(KVersitTokenVCardVersionNo, "2.1");

//
// CParserVCard
//
/**
 * A vCard parser.
 *
 * In addition to the functions inherited from
 * <code>CVersitParser</code>, it provides support for property groups
 * and agents.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserVCard : public CVersitParser
	{
public:
	IMPORT_C static CParserVCard* NewL();
	IMPORT_C CArrayPtr<CParserProperty>* GroupOfPropertiesL(const TDesC8& aName) const;
public: //from CVersitParser
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream);
	IMPORT_C void ConvertAllPropertyDateTimesToMachineLocalL(const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight);
protected:
	IMPORT_C virtual CParserPropertyValue* MakePropertyValueAgentL(TPtr16 aValue);
	IMPORT_C CDesC8Array* GetGroupNamesL(TPtr8& aGroupsAndName);
protected: // from CVersitParser
	IMPORT_C void ParsePropertyL();
	IMPORT_C CParserPropertyValue* MakePropertyValueL(const TUid& aPropertyUid,HBufC16*& aValue);
public: //from CVersitParser
	IMPORT_C TUid RecognizeToken(const TDesC8& aToken) const;
	IMPORT_C void ConvertDateTimesToMachineLocalAndDeleteTZL();
private:
	CParserVCard();
private: // from CVersitParser
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	};

//
// CParserGroupedProperty
//
/**
 *
 * A grouped property.
 *
 * This is a vCard property which is a member of a property group. It
 * owns an array of descriptors, each of which identifies the name of a
 * group to which the property belongs (a grouped property can be a
 * member of more than one group).
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserGroupedProperty : public CParserProperty
	{
public:
	IMPORT_C static CParserGroupedProperty* NewL(CParserPropertyValue& aPropertyValue, const TDesC8& aName, CDesC8Array* aArrayOfGroups, CArrayPtr<CParserParam>* aArrayOfParams);
	IMPORT_C CParserGroupedProperty(CDesC8Array* aArrayOfGroups, CArrayPtr<CParserParam>* aArrayOfParams);
	IMPORT_C ~CParserGroupedProperty();
	IMPORT_C TBool Group(const TDesC8& aGroup) const;
	inline void SetGroups(CDesC8Array* aArrayOfGroups);
	inline const CDesC8Array* Groups();
public: //from CParserProperty
	IMPORT_C TBool SupportsInterface(const TUid& aInterfaceUid) const;
	IMPORT_C void ExternalizeL(RWriteStream& aStream, CVersitParser* aVersitParser = NULL);
protected:
	CParserGroupedProperty(CParserPropertyValue& aPropertyValue, CDesC8Array* aArrayOfGroups, CArrayPtr<CParserParam>* aArrayOfParams);
private: //from CParserProperty
	IMPORT_C virtual void Reserved();
protected:
	CDesC8Array* iArrayOfGroups;
	};

//
// CParserPropertyValueAgent
//
/**
 * An agent property value.
 *
 * An agent property contains information about a person who is not the
 * main subject of the vCard. It is implemented as a vCard nested within
 * another vCard. To find out the property value type, use
 * <code>Uid()</code> defined in the base class
 * <code>CParserPropertyValue</code>. An agent property UID has the value
 * <code>KVCardPropertyAgentUid</code>.The class defines an
 * <code>ExternalizeL()</code> function which has not been documented. It
 * is invoked by the parser's <code>ExternalizeL()</code> function.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueAgent : public CParserPropertyValue
	{
public:
	IMPORT_C CParserPropertyValueAgent(CParserVCard* aValue);
	IMPORT_C ~CParserPropertyValueAgent();
	inline CParserVCard* Value() const;

public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& /*aEncodingCharset*/,TInt /*aLengthOutput*/);
protected:
	CParserVCard* iValue;
private:
	};

#include "vcard.inl"

#endif
