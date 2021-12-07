// VPROP.INL
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

//
// CParserPropertyValue
//
/**
 * Returns the property value's UID.
 *
 * This UID identifies the property value's type and is specified on
 * construction. The values are defined in vuid.h.
 *
 * @returns   " TUid "
 *            The property value's UID.
 */
inline TUid CParserPropertyValue::Uid() const
	{return iPropertyValueTypeUid;}

inline void CParserPropertyValue::SetPlugIn(MVersitPlugIn* aPlugIn)
	{iPlugIn=aPlugIn;}

//
//  CParserPropertyValueCDesCArray
//
/**
 * Constructs a binary value
 *
 * Sets the property values UID to
 * <code>KVersitPropertyBinaryUid</code>.
 *
 */
inline CParserPropertyValueBinary::CParserPropertyValueBinary() :CParserPropertyValue(TUid::Uid(KVersitPropertyBinaryUid))
	{}

/**
 * Constructs a binary value with a 
 * <code>aValue</code>.
 *
 * Sets the property value to <code>aValue</code>, value UID  to
 * <code>KVersitPropertyBinaryUid</code> and .
 *
 */
inline CParserPropertyValueBinary::CParserPropertyValueBinary(CBufSeg& aValue) :CParserPropertyValue(TUid::Uid(KVersitPropertyBinaryUid)), iValue(&aValue)
	{}

//
//  CParserPropertyValueCDesCArray
//
/**
 * Gets the property value.
 *
 * @returns   " CDesCArray* "
 *            Pointer to the array of descriptors owned by the
 *            property value object.
 */
inline CDesCArray* CParserPropertyValueCDesCArray::Value() const
	{return iValue;}

//
// CParserPropertyValueTimeZone
//
/**
 * Gets the property value.
 *
 * @returns   " TTimeIntervalSeconds "
 *            Value in interval seconds 
 */
inline TTimeIntervalSeconds CParserPropertyValueTimeZone::Value() const
	{return iValue;}

//
// CParserPropertyValueDaylight
//
/**
 * Gets the daylight saving property value.
 *
 * @returns   " CVersitDaylight* "
 *            Pointer to the daylight saving specification.
 */
inline CVersitDaylight* CParserPropertyValueDaylight::Value() const
	{return iValue;}

//
//  CParserPropertyValueDateTime
//
/**
 * Gets a pointer to the date/time value.
 *
 * @returns   " TVersitDateTime* "
 *            Pointer to the date/time value.
 */
inline TVersitDateTime* CParserPropertyValueDateTime::Value() const
	{return iValue;}

//
//  CParserPropertyValueDate
//
/**
 * Gets a pointer to the date value.
 *
 * @returns   " TVersitDateTime* "
 *            Pointer to the date value.
 */
inline TVersitDateTime* CParserPropertyValueDate::Value() const
	{return iValue;}

//
//  CParserPropertyValueMultiDateTime
//
/**
 * Gets a pointer to the list of date/time values owned by the
 * <code>CParserPropertyValueMultiDateTime</code> object.
 *
 * @returns   " CArrayPtr<TVersitDateTime>* "
 *            Pointer to the array of date/time values.
 */
inline CArrayPtr<TVersitDateTime>* CParserPropertyValueMultiDateTime::Value() const
	{return iValue;}

//
//  CParserPropertyValueInt
//
/**
 *
 * Gets the signed integer property value.
 *
 * @returns   " TInt "
 *            The signed integer property value.
 */
inline TInt CParserPropertyValueInt::Value() const
	{return iValue;}

//
//	CParserProperty
//
/**
 * Sets a pointer to the property value.
 * Takes ownership of <code>aArrayOfParams</code>
 *
 * @param     " CParserPropertyValue* aPropertyValue "
 *              Pointer to generic parser property value.
 */
inline void CParserProperty::SetValue(CParserPropertyValue* aPropertyValue)
	{iPropertyValue=aPropertyValue;}

/**
 * Gets a pointer to the property value.
 *
 * @returns   " CParserPropertyValue* "
 *            Pointer to generic parser property value.
 */
inline CParserPropertyValue* CParserProperty::Value() const
	{return iPropertyValue;}

/**
 * Gets the UID of the property value.
 *
 * @returns   " TUid "
 *            UID of the property value.
 */
inline TUid CParserProperty::Uid() const
	{return iPropertyValue->Uid();}

/**
 * Gets the name of the property.
 *
 * @returns   " HBufC8*& "
 *            Pointer to the property name.
 */
inline HBufC8*& CParserProperty::NameBuf()
	{return iPropertyName;}

/**
 * Sets the property name UID.
 *
 * @param     " TUid aUid "
 *              A UID of the property name UID.
 */
inline void CParserProperty::SetNameUid(TUid aUid)
	{iPropertyNameUid=aUid;}

/**
 * Gets the property name UID.
 *
 * @returns   " TUid "
 *            UID of the property name UID
 */
inline TUid CParserProperty::NameUid() const
	{return iPropertyNameUid;}

/**
 * Sets the array of property parameters.
 * Takes ownership of <code>aArrayOfParams</code>

 * @param     " CArrayPtr<CParserParam>* aArrayOfParams "
 *              Array of property parameters.
 */
inline void CParserProperty::SetParamArray(CArrayPtr<CParserParam>* aArrayOfParams)
	{iArrayOfParams=aArrayOfParams;}
