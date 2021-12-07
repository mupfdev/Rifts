// VCAL.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
 
#if !defined(__VCAL_H__)
#define __VCAL_H__

#if !defined(__VERSIT_H__)
#include "versit.h"
#endif

#if !defined(__VRECUR_H__)
#include "vrecur.h"
#endif

_LIT(KVersitTokenVCalVersionNo, "1.0");

//
// CParserVCal
//
/**
 * A vCalendar parser.
 *
 * Adds a constructor and overrides
 * <code>CVersitParser::InternalizeL()</code> and
 * <code>ExternalizeL()</code>.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserVCal : public CVersitParser
	{
public:
	IMPORT_C static CParserVCal* NewL();
public: // from CVersitParser
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream);
protected: // from CVersitParser
	IMPORT_C CVersitParser* MakeEntityL(TInt aEntityUid,HBufC* aEntityName);
public: // from CVersitParser
	IMPORT_C TUid RecognizeToken(const TDesC8& aToken) const;
	IMPORT_C TInt RecognizeEntityName() const;
private:
	CParserVCal();
private: // from CVersitParser
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	};

//
// CVersitAlarm
//
/**
 *
 * An audio reminder for a vEvent or vTodo.
 *
 * Specifies the date/time for the alarm, the amount of time the alarm
 * will be snoozed (optional), the number of times that the alarm will
 * repeat, the binary data of the audio sound to be played when the alarm
 * runs (optional), and some text to associate with the alarm
 * (optional).An object of this class is owned by the
 * <code>CParserPropertyValueAlarm</code> class.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitAlarm : public CBase
	{
public:
	IMPORT_C static CVersitAlarm* NewL(TVersitDateTime* aRunTime, TTime* aSnoozeTime, TInt aRepeatCount, const TDesC& aAudioContent, const TDesC& aNote);
	IMPORT_C ~CVersitAlarm();
private:
	CVersitAlarm(TVersitDateTime* aRunTime, TTime* aSnoozeTime, TInt aRepeatCount);
	void ConstructL(const TDesC& aAudioContent, const TDesC& aNote);
public:	
	TVersitDateTime* iRunTime;
	TTime* iSnoozeTime;
	TInt iRepeatCount;
	HBufC* iAudioContent;
	HBufC* iNote;//Empty except for MAlarm
	};

//
// CParserVCalEntity
//
/**
 * Parser for vCalendar sub-entities.
 *
 * A vCalendar sub-entity is a vTodo or vEvent which is contained in a
 * vCalendar. vTodos and vEvents are derived from
 * <code>CRecurrenceParser</code> which provides recurrence information.
 * vEvents and vTodos may have alarm properties (see class
 * <code>CParserPropertyValueAlarm</code>).
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserVCalEntity : public CRecurrenceParser
	{
public:
	IMPORT_C static CParserVCalEntity* NewL();
	IMPORT_C ~CParserVCalEntity();
public: // from CVersitParser
	IMPORT_C void ExternalizeL(RWriteStream& aStream);
protected: // from CVersitParser
	IMPORT_C CParserPropertyValue* MakePropertyValueL(const TUid& aPropertyUid,HBufC16*& aValue);
	IMPORT_C CVersitAlarm* MakePropertyValueAlarmL(TPtr16 aAlarmValue);
	IMPORT_C TUid RecognizeToken(const TDesC8& aToken) const;
private:
	CParserVCalEntity();
private: // from CVersitParser
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	};


//
// CParserPropertyValueAlarm
//
/**
 * Defines an audio reminder property value for a vCalendar entity.
 *
 * An audio reminder is an alarm that is sounded for a vEvent, or for a
 * vTodo. The value for the audio reminder is stored as a
 * <code>CVersitAlarm</code>.To find out the property value type, use
 * <code>Uid()</code> defined in the base class
 * <code>CParserPropertyValue</code>. An alarm property UID has the value
 * <code>KVCalPropertyAlarmUid</code>.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CParserPropertyValueAlarm : public CParserTimePropertyValue
	{
public:
	IMPORT_C CParserPropertyValueAlarm(CVersitAlarm* aValue);
	IMPORT_C ~CParserPropertyValueAlarm();
	inline CVersitAlarm* Value() const;
public: // from CParserTimePropertyValue
	IMPORT_C void ConvertAllDateTimesToUTCL(const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight);
	IMPORT_C void ConvertAllUTCDateTimesToMachineLocalL(const TTimeIntervalSeconds& aIncrement);
public: // from CParserPropertyValue
	IMPORT_C void ExternalizeL(RWriteStream& aStream,const Versit::TEncodingAndCharset& aEncodingCharset,TInt aLengthOutput);
	IMPORT_C TBool IsAsciiCharacterSetSufficient();
private:
	CVersitAlarm* iValue;
	};

#include "vcal.inl"

#endif
