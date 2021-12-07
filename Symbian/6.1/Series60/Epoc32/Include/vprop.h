// VPROP.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
 
#ifndef __VPROP_H__
#define __VPROP_H__

#ifndef __E32BASE_H__
#include <e32base.h>
#endif

#ifndef __BADESCA_H__
#include <badesca.h>
#endif

#ifndef __S32STRM_H__
#include <s32strm.h>
#endif

#ifndef __VUID_H__
#include "vuid.h"
#endif

#ifndef __VTOKEN_H__
#include "vtoken.h"
#endif

#ifndef __VUTIL_H__
#include "vutil.h"
#endif

class CVersitParser;
class MVersitPlugIn;

//
// CParserParam
//

/**
 * A versit property parameter.
 *
 * It consists of a name and optionally a value, both in descriptor form.
 * A parser property (class <code>CParserProperty</code>) may own one or
 * more property parameters.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserParam : public CBase
	{
public:
	IMPORT_C static CParserParam* NewL(const TDesC8& aName,const TDesC8& aValue);
	IMPORT_C static CParserParam* NewL(const TDesC8& aName,const TDesC& aValue);
	IMPORT_C ~CParserParam();
	IMPORT_C void SetValueL(const TDesC8& aValue);
	IMPORT_C void SetValueL(HBufC8* aValue);
	IMPORT_C TInt ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TPtrC8 Name() const;
	IMPORT_C TPtrC8 Value() const;
	IMPORT_C HBufC* ValueL() const;
private:
	CParserParam(HBufC8* aName,HBufC8* aValue);
private:
	HBufC8* iParamName;
	HBufC8* iValue;
	};

//
// TVersitDateTime
//

/**
 * Versit date and time.
 *
 * This class is used throughout versit to represent the date and time.
 * It uses a <code>TDateTime</code> object to store the date/time value
 * and records whether this value is machine-local, vCard-local, or
 * universal time (UTC).
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class TVersitDateTime
	{
public:
	/** Time flags */
	enum TRelativeTime
		{
		EIsUTC,			/** Time is stored in UTC.*/
		EIsVCardLocal,	/** Time is local to the machine which originated a vCard.*/
		EIsMachineLocal,/** Time is local to the machine on which the code is running.*/
		EIsCorrect		/** Not currently used in versit.*/
		};
	IMPORT_C TVersitDateTime(const TDateTime& aDateTime,TRelativeTime aRelativeTime);

	enum TVersitDateTimeFlags {EExportTimeZoneDesignator=0x01};
	inline void SetFlag(TVersitDateTimeFlags aFlag) { iFlags |= aFlag; }
	inline TBool IsFlagSet(TVersitDateTimeFlags aFlag) const { return iFlags & aFlag; }
	inline void ClearFlag(TVersitDateTimeFlags aFlag) { iFlags &= ~aFlag; }
public:
	TDateTime iDateTime;
	TRelativeTime iRelativeTime;
private:
	TInt iFlags;
	};

//
// CParserPropertyValue
//
/**
 *
 * Abstract base class for all property values.
 *
 * Defines a pure virtual <code>ExternalizeL()</code> function which is
 * implemented by all concrete derived classes. The type of derived class
 * is returned by the <code>Uid()</code> function; the UID value is
 * specified on construction.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValue : public CBase
	{
public:	
	virtual void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt aLengthOutput)=0;
	IMPORT_C virtual TBool IsAsciiCharacterSetSufficient();
	IMPORT_C virtual void EncodeL(CBufBase* aTarget,const TDesC8& aSource,const TUid& aEncoding) const;
	IMPORT_C virtual TBool SupportsInterface(const TUid& /*aInterfaceUid*/) const;
	inline TUid Uid() const;
	inline void SetPlugIn(MVersitPlugIn* aPlugIn);
protected:
	IMPORT_C CParserPropertyValue(const TUid& aPropertyValueUid);
	IMPORT_C void FoldEncodeAndWriteValueToStreamL(RWriteStream& aStream, const TDesC& aValue
														,const Versit::TEncodingAndCharset& aEncodingCharset,TInt& aLengthOutput) const;
	IMPORT_C void FoldEncodeAndWriteValueToStreamL(RWriteStream& aStream, const CDesCArray* aValueArray
														,const Versit::TEncodingAndCharset& aEncodingCharset,TInt& aLengthOutput) const;
	IMPORT_C void FoldAndWriteValueToStreamL(RWriteStream& aStream, const TDesC& aValue
														,const Versit::TEncodingAndCharset& aEncodingCharset,TInt& aLengthOutput) const;
	IMPORT_C static void Append(TDes16& aTarget,TDesC8& aSource);
private:
	TUid iPropertyValueTypeUid;
	MVersitPlugIn* iPlugIn;
	};

//
// CParserTimePropertyValue
//

class CVersitDaylight;

class CParserTimePropertyValue : public CParserPropertyValue
	{
public:
	IMPORT_C virtual void ConvertAllDateTimesToUTCL(const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight)=0;
	IMPORT_C virtual void ConvertAllUTCDateTimesToMachineLocalL(const TTimeIntervalSeconds& aIncrement)=0;
public: //from CParserPropertyValue
	IMPORT_C virtual TBool SupportsInterface(const TUid& aInterfaceUid) const;
protected:
	IMPORT_C CParserTimePropertyValue(const TUid& aPropertyValueUid);
	IMPORT_C void ConvertDateTime(TDateTime* aDateTime,const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight);		
	IMPORT_C void EncodeVersitDateTimeL(TDes8& aBuf,const TVersitDateTime& aDateTime,TBool aEncodeTime=ETrue) const;
	IMPORT_C void EncodeTimePeriodL(TDes8& aBuf,const TTime& aTimePeriod) const;
	};

//
//  CParserPropertyValueHBufC
//
/**
 *
 * A property value which is stored using an <code>HBufC</code>.
 *
 * For example, a summary property value in a vCalendar entity might be
 * stored using this class.To find out the property value type, use
 * <code>Uid()</code> defined in the base class
 * <code>CParserPropertyValue</code>. A heap descriptor property value
 * UID has the value <code>KVersitPropertyHBufCUid</code>.The class
 * defines an <code>ExternalizeL()</code> function which has not been
 * documented. It is invoked by the parser's <code>ExternalizeL()</code>
 * function.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueHBufC : public CParserPropertyValue
	{	
public:
	IMPORT_C static CParserPropertyValueHBufC* NewL(const TDesC& aValue);
	IMPORT_C CParserPropertyValueHBufC(HBufC16* aValue);
	IMPORT_C ~CParserPropertyValueHBufC();
	IMPORT_C TPtrC Value() const;
	IMPORT_C HBufC* TakeValueOwnership();
public: // from CParserPropertyValue
	IMPORT_C TBool IsAsciiCharacterSetSufficient();
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt aLengthOutput);
private:
	CParserPropertyValueHBufC();
	void ConstructL(const TDesC& aValue);
protected:
	HBufC* iValue;
	};

//
//  CParserPropertyValueBinary
//
class CParserPropertyValueBinary : public CParserPropertyValue
	{
public:
	IMPORT_C static CParserPropertyValueBinary* NewL(const TDesC8& aValue);
	IMPORT_C static CParserPropertyValueBinary* NewLC(const TDesC8& aValue);
	inline CParserPropertyValueBinary(CBufSeg& aValue);
	IMPORT_C ~CParserPropertyValueBinary();
	IMPORT_C const CBufSeg* Value() const;	
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt /*aLengthOutput*/);
protected:
	inline CParserPropertyValueBinary();
	void ConstructL(const TDesC8& aValue);
protected:
	CBufSeg* iValue;
	};


//
//  CParserPropertyValueCDesCArray
//
/**
 * A property value stored in an array of descriptors.
 *
 * For instance, a postal address in a vCard might be stored using this
 * class.To find out the property value type, use <code>Uid()</code>
 * defined in the base class <code>CParserPropertyValue</code>. A
 * descriptor array property UID has the value
 * <code>KVersitPropertyCDesCArrayUid</code>.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueCDesCArray : public CParserPropertyValue
	{
public:
	IMPORT_C CParserPropertyValueCDesCArray(CDesCArray* aValue);
	IMPORT_C ~CParserPropertyValueCDesCArray();
	inline CDesCArray* Value() const;
	IMPORT_C TBool IsPresent(const TDesC& aValue) const;
public: // from CParserPropertyValue
	IMPORT_C TBool IsAsciiCharacterSetSufficient();
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt aLengthOutput);
protected:
	CDesCArray* iValue;
	};

//
// CParserPropertyValueTimeZone
//

class CParserPropertyValueTimeZone: public CParserPropertyValue
	{
public:
	static void EncodeTimeZone(TDes8& aBuf,TTimeIntervalSeconds iValue);
	IMPORT_C CParserPropertyValueTimeZone(TTimeIntervalSeconds aValue);
	inline TTimeIntervalSeconds Value() const;
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt /*aLengthOutput*/);
protected:
	TTimeIntervalSeconds iValue;
	};

//
// CVersitDaylight
//
/**
 * Daylight saving information.
 *
 * During part of the year, the time may need to be adjusted by a one
 * hour offset the daylight saving offset. This offset needs to be taken
 * into account when converting versit times
 * (<code>TVersitDateTime</code>s) between universal and local time. This
 * class stores information about the offset, including when it takes
 * effect and the standard time designations. An instance of this class
 * is owned by the <code>CParserPropertyValueDaylight</code> class.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitDaylight : public CBase
	{
public:
	IMPORT_C static CVersitDaylight* NewL(TBool aSavings, TTimeIntervalSeconds aOffset, TVersitDateTime* aStartTime, TVersitDateTime* aEndTime, const TDesC& aStandardDesignation, const TDesC& aDaylightDesignation);
	IMPORT_C ~CVersitDaylight();
private:
	CVersitDaylight(TBool aSavings, TTimeIntervalSeconds aOffset, TVersitDateTime* aStartTime, TVersitDateTime* aEndTime);
	void ConstructL(const TDesC& aStandardDesignation, const TDesC& aDaylightDesignation);
public:	
	TBool iSavings;
	TTimeIntervalSeconds iOffset;
	TVersitDateTime* iStartTime;
	TVersitDateTime* iEndTime;
	HBufC* iStandardDesignation;
	HBufC* iDaylightDesignation;
	};

//
// CParserPropertyValueDaylight
//
/**
 * A property value which contains the daylight savings rule for a
 * vCalendar.
 *
 * The property value is stored using an instance of the
 * <code>CVersitDaylight</code> class, which defines the specification
 * for daylight saving.To find out the property value type, use
 * <code>Uid()</code> defined in the base class
 * <code>CParserPropertyValue</code>. A daylight saving property UID has
 * the value <code>KVersitPropertyDaylightUid</code>.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueDaylight : public CParserTimePropertyValue
	{
public:
	IMPORT_C CParserPropertyValueDaylight(CVersitDaylight* aValue);
	IMPORT_C ~CParserPropertyValueDaylight();
	inline CVersitDaylight* Value() const;
public: // from CParserTimePropertyValue
	IMPORT_C void ConvertAllDateTimesToUTCL(const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight);
	IMPORT_C void ConvertAllUTCDateTimesToMachineLocalL(const TTimeIntervalSeconds& /*aIncrement*/);
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt aLengthOutput);
private:
	CVersitDaylight* iValue;
	};

//
//  CParserPropertyValueDateTime
//
/**
 * A date/time property value.
 *
 * The date/time value is contained in a <code>TVersitDateTime</code>
 * object. The member functions of class <code>TDateTime</code> may be
 * used to extract the date and time components from
 * <code>TVersitDateTime::iDateTime</code>.To find out the property value
 * type, use <code>Uid()</code> defined in the base class
 * <code>CParserPropertyValue</code>. A date/time property UID has the
 * value <code>KVersitPropertyDateTimeUid</code>.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueDateTime : public CParserTimePropertyValue
	{
public:
	IMPORT_C CParserPropertyValueDateTime(TVersitDateTime* aValue);
	IMPORT_C ~CParserPropertyValueDateTime();
	inline TVersitDateTime* Value() const;
public: // from CParserTimePropertyValue
	IMPORT_C void ConvertAllDateTimesToUTCL(const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight);
	IMPORT_C void ConvertAllUTCDateTimesToMachineLocalL(const TTimeIntervalSeconds& aIncrement);
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& /*aEncodingCharset*/,TInt /*aLengthOutput*/);
protected:
	TVersitDateTime* iValue;
	};

//
//  CParserPropertyValueDate
//
/**
 * A date property value.
 *
 * The date value is contained in a <code>TVersitDateTime</code> object.
 * The <code>Year()</code>, <code>Month()</code> and <code>Day()</code>
 * member functions of class <code>TDateTime</code> may be used to
 * extract the date components from
 * <code>TVersitDateTime::iDateTime</code>.To find out the property value
 * type, use <code>Uid()</code> defined in the base class
 * <code>CParserPropertyValue</code>. A date property UID has the value
 * <code>KVersitPropertyDateUid</code>.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueDate : public CParserTimePropertyValue
	{
public:
	IMPORT_C CParserPropertyValueDate(TVersitDateTime* aValue);
	IMPORT_C ~CParserPropertyValueDate();
	inline TVersitDateTime* Value() const;
public: // from CParserTimePropertyValue
	IMPORT_C void ConvertAllDateTimesToUTCL(const TTimeIntervalSeconds& /*aIncrement*/,const CVersitDaylight* /*aDaylight*/);
	IMPORT_C void ConvertAllUTCDateTimesToMachineLocalL(const TTimeIntervalSeconds& /*aIncrement*/);
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt /*aLengthOutput*/);
private:
	TVersitDateTime* iValue;
	};

//
//  CParserPropertyValueMultiDateTime
//
/**
 * A property value which consists of a list of date/time values.
 *
 * This can be externalised and converted between local time and
 * universal time. To find out the property value type, use
 * <code>Uid()</code> defined in the base class
 * <code>CParserPropertyValue</code>. A multiple date/time property value
 * UID has the value <code>KVersitPropertyMultiDateTimeUid</code>.The
 * class defines an <code>ExternalizeL()</code> function which has not
 * been documented. It is invoked by the parser's
 * <code>ExternalizeL()</code> function.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueMultiDateTime : public CParserTimePropertyValue
	{
public:
	IMPORT_C CParserPropertyValueMultiDateTime(CArrayPtr<TVersitDateTime>* aValue);
	IMPORT_C ~CParserPropertyValueMultiDateTime();
	inline CArrayPtr<TVersitDateTime>* Value() const;
public: // from CParserTimePropertyValue
	IMPORT_C void ConvertAllDateTimesToUTCL(const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight);
	IMPORT_C void ConvertAllUTCDateTimesToMachineLocalL(const TTimeIntervalSeconds& aIncrement);
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& /*aEncodingCharset*/,TInt aLengthOutput);
protected:
	CArrayPtr<TVersitDateTime>* iValue;
	};

//
//  CParserPropertyValueInt
//
/**
 *
 * A property value which is stored using a signed integer.
 *
 * For example, a priority property value in a vCalendar might be stored
 * using this class.To find out the property value type, use
 * <code>Uid()</code> defined in the base class
 * <code>CParserPropertyValue</code>. A signed integer property UID has
 * the value <code>KVersitPropertyIntUid</code>.The class defines an
 * <code>ExternalizeL()</code> function which has not been documented. It
 * is invoked by the parser's <code>ExternalizeL()</code> function.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueInt : public CParserPropertyValue
	{
public:
	IMPORT_C CParserPropertyValueInt(TInt aValue);
	inline TInt Value() const;
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt /*aLengthOutput*/);
protected:
	TInt iValue;
	};

//
//	CParserProperty
//

/**
 * A property in a vCard or vCalendar.
 *
 * Has a name, a value and, optionally, one or more parameters, which are
 * all initialised on construction. Grouped properties are supported see
 * the derived class, <code>CParserGroupedProperty</code>.Versit
 * properties have the general form:<code>Property Name (; Property
 * Parameter Name(=Property Parameter Value))* : Property
 * Value</code>where items in brackets are optional and * indicates that
 * the item may be repeatede.g. <code>TEL; HOME;
 * ENCODING=QUOTED-PRINTABLE; CHARSET=US-ASCII : 01234 567890</code>Here,
 * TEL is the property name, HOME, ENCODING and CHARSET are property
 * parameter names and QUOTED-PRINTABLE and US-ASCII are property
 * parameter values. The component following the colon is the property
 * value.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserProperty : public CBase
	{
public:
	IMPORT_C static					CParserProperty* NewL(CParserPropertyValue& aPropertyValue, const TDesC8& aName, CArrayPtr<CParserParam>* aArrayOfParams);
	IMPORT_C CParserProperty(CArrayPtr<CParserParam>* aArrayOfParams);
	IMPORT_C ~CParserProperty();
	IMPORT_C virtual void			ExternalizeL(RWriteStream& aStream, CVersitParser* aVersitParser = NULL);
	IMPORT_C CParserParam*			Param(const TDesC8& aParamName) const; // note params can only appear once
	IMPORT_C void					AddParamL(CParserParam* aParam);
	IMPORT_C void					DeleteParam(TDesC8& aParamName);
	IMPORT_C void					SetNameL(const TDesC8& aName);
	IMPORT_C virtual TBool			SupportsInterface(const TUid& /*aInterfaceUid*/) const;
	IMPORT_C TPtrC8					Name() const;
	inline void						SetValue(CParserPropertyValue* aPropertyValue);
	inline CParserPropertyValue*	Value() const;
	inline TUid						Uid() const;
	inline void						SetNameUid(TUid aUid);
	inline TUid						NameUid() const;
	inline void						SetParamArray(CArrayPtr<CParserParam>* aArrayOfParams);

protected:
	IMPORT_C CParserProperty(CParserPropertyValue& aPropertyValue, CArrayPtr<CParserParam>* aArrayOfParams);
	IMPORT_C static void			ConstructSelfL(CParserProperty& aSelf,const TDesC8& aName);

protected:
	CParserPropertyValue*			iPropertyValue;
	HBufC8*							iPropertyName;
	TUid							iPropertyNameUid;
	CArrayPtr<CParserParam>*		iArrayOfParams;

private:
	friend class CVersitParser;
	inline HBufC8*&					NameBuf();
	IMPORT_C virtual void			Reserved();
	};

#include "vprop.inl"

#endif
